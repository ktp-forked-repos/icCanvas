#include <icCanvasAppKit.h>

typedef struct {
    __unsafe_unretained ICAKDockableView* dockable;
    __unsafe_unretained ICAKDock* dock;
    __unsafe_unretained NSPanel* panel;
    __unsafe_unretained ICAKDockingRow* row;
    
    BOOL has_selected_target;
    
    //Target type 1: Selecting a dock
    __unsafe_unretained ICAKDock* selected_dock;
    ICAKDockEdge selected_edge;
    NSInteger selected_offset;
    
    //Target type 2: Selecting an NSPanel
    __unsafe_unretained NSPanel* selected_panel;
    
    //Common to all panels
    NSInteger selected_pos;
} ICAKDockingControllerDockData;

@implementation ICAKDockingController {
    NSMutableArray* _panels;
    NSMutableArray* _docks;
    
    NSMutableDictionary* _docknfo;
}

- (id)init {
    self = [super init];
    
    if (self != nil) {
        self->_panels = [NSMutableArray arrayWithCapacity:10];
        self->_docks = [NSMutableArray arrayWithCapacity:10];
        self->_docknfo = [[NSMutableDictionary alloc] init];
    }
    
    return self;
};

- (void)dockableViewWillDetach:(ICAKDockableView*)view {
    ICAKDockingControllerDockData dat;
    
    NSValue* maybeDat = [self->_docknfo objectForKey:[NSValue valueWithNonretainedObject:view]];
    if (maybeDat == nil) {
        return; //WTF
    }
    
    [maybeDat getValue:&dat];
    
    if (dat.dock == nil && view.superview.subviews.count <= 1) {
        return;
    }
    
    NSRect frameRelativeToWindow = [view convertRect:view.bounds toView:nil];
    
    frameRelativeToWindow.origin.x -= ICAKDockableViewPanelMargins;
    frameRelativeToWindow.origin.y -= ICAKDockableViewPanelMargins;
    frameRelativeToWindow.size.width += ICAKDockableViewPanelMargins * 2;
    frameRelativeToWindow.size.height += ICAKDockableViewPanelMargins * 2;
    
    NSRect frameRelativeToScreen = [view.window convertRectToScreen:frameRelativeToWindow];
    NSPanel* package = [[NSPanel alloc] initWithContentRect:frameRelativeToScreen styleMask:(NSTitledWindowMask|NSClosableWindowMask|NSResizableWindowMask|NSUtilityWindowMask) backing:NSBackingStoreBuffered defer:TRUE];
    [package standardWindowButton:NSWindowZoomButton].enabled = NO;
    
    frameRelativeToWindow.origin.x = 0;
    frameRelativeToWindow.origin.y = 0;
    
    ICAKDockingRow* row = [[ICAKDockingRow alloc] initWithFrame:frameRelativeToWindow];
    row.vertical = YES;
    
    package.contentView = row;
    [row addSubview:view positioned:NSWindowAbove relativeTo:nil];
    
    [package makeKeyAndOrderFront:nil];
    
    [self addPanel:package];
    [self didAddDockable:view toPanel:package onRow:row];
};

- (void)dockableView:(ICAKDockableView*)view wasDraggedByEvent:(NSEvent*)evt {
    NSPoint window_loc = evt.locationInWindow;
    NSRect testrect;
    testrect.origin = window_loc;
    testrect.size.width = 0.0;
    testrect.size.height = 0.0;
    
    NSRect convertedRect = [view.window convertRectToScreen:testrect];
    NSPoint screen_loc = convertedRect.origin;
    
    __block ICAKDockingControllerDockData dat; //why do I gotta DO this
    
    NSValue* maybeDat = [self->_docknfo objectForKey:[NSValue valueWithNonretainedObject:view]];
    if (maybeDat == nil) {
        return; //WTF
    }
    [maybeDat getValue:&dat];
    
    dat.has_selected_target = NO;
    dat.selected_dock = nil;
    dat.selected_panel = nil;
    
    for (ICAKDock* dock in self->_docks) {
        [dock traverseDockablesWithBlock:^(ICAKDockEdge edge, NSInteger row_cnt, ICAKDockingRow* row) {
            NSRect winRelFrame = [row convertRect:row.frame toView:nil];
            NSRect absFrame = [row.window convertRectToScreen:winRelFrame];
            
            if (NSPointInRect(screen_loc, absFrame) && [row canAcceptDockableView:view]) {
                NSInteger current_pos = 0;
                for (NSView* maybe_dockable in row.subviews) {
                    if ([maybe_dockable isKindOfClass:ICAKDockableView.class]) {
                        ICAKDockableView* dv = (ICAKDockableView*)maybe_dockable;
                        NSRect marginless_frame = [row marginlessFrameOfSubview:view];
                        
                        if (NSPointInRect(screen_loc, marginless_frame)) {
                            break;
                        }
                    }
                    current_pos++;
                }
                
                dat.has_selected_target = YES;
                dat.selected_dock = dock;
                dat.selected_edge = edge;
                dat.selected_offset = row_cnt;
                dat.selected_pos = current_pos;
                
                return YES;
            }
            
            return NO;
        }];
        
        if (dat.has_selected_target) {
            break;
        }
        
        //Consider the edges of the frame
        NSRect dockWinFrame = [dock convertRect:dock.frame toView: nil];
        NSRect dockAbsFrame = [dock.window convertRectToScreen:dockWinFrame];
        NSRect insetDockFrame = NSInsetRect(dockAbsFrame, fmin(25.0f, dockAbsFrame.size.width / 2.0f), fmin(25.0f, dockAbsFrame.size.height / 2.0f));
        
        if (screen_loc.x >= dockAbsFrame.origin.x && screen_loc.x <= insetDockFrame.origin.x) {
            dat.has_selected_target = YES;
            dat.selected_dock = dock;
            dat.selected_edge = ICAKDockEdgeLeft;
            dat.selected_offset = -1;
            dat.selected_pos = 0;
        }
        
        if (screen_loc.x >= dockAbsFrame.origin.y && screen_loc.y <= insetDockFrame.origin.y) {
            dat.has_selected_target = YES;
            dat.selected_dock = dock;
            dat.selected_edge = ICAKDockEdgeBottom;
            dat.selected_offset = -1;
            dat.selected_pos = 0;
        }
        
        if (screen_loc.x >= insetDockFrame.origin.x + dockAbsFrame.size.width && screen_loc.x <= dockAbsFrame.origin.x + dockAbsFrame.size.width) {
            dat.has_selected_target = YES;
            dat.selected_dock = dock;
            dat.selected_edge = ICAKDockEdgeRight;
            dat.selected_offset = -1;
            dat.selected_pos = 0;
        }
        
        if (screen_loc.y >= insetDockFrame.origin.y + dockAbsFrame.size.height && screen_loc.y <= dockAbsFrame.origin.y + dockAbsFrame.size.height) {
            dat.has_selected_target = YES;
            dat.selected_dock = dock;
            dat.selected_edge = ICAKDockEdgeTop;
            dat.selected_offset = -1;
            dat.selected_pos = 0;
        }
        
        if (dat.has_selected_target) break;
    }
    
    if (dat.has_selected_target) {
        view.window.alphaValue = 0.6;
    } else {
        view.window.alphaValue = 1.0;
    }
    
    [self->_docknfo setObject:[NSValue valueWithBytes:&dat objCType:@encode(ICAKDockingControllerDockData)] forKey:[NSValue valueWithNonretainedObject:view]];
};

- (void)dockableViewWasReleased:(ICAKDockableView*)view {
    ICAKDockingControllerDockData dat;
    
    NSValue* maybeDat = [self->_docknfo objectForKey:[NSValue valueWithNonretainedObject:view]];
    if (maybeDat != nil) {
        [maybeDat getValue:&dat];
    }
    
    if (dat.has_selected_target) {
        if (dat.selected_dock) {
            [dat.selected_dock attachDockableView:view toEdge:dat.selected_edge onRow:dat.selected_offset atOffset:dat.selected_pos];
        }
        
        //TODO: Release to Panel
    }
};

- (void)addPanel:(NSPanel*)panel {
    [self->_panels addObject:panel];
};

- (void)addDock:(ICAKDock*)dock {
    [self->_docks addObject:dock];
    dock.dockingController = self;
};

- (void)addDrawingController:(ICAKDrawingController*)dc {
    [self addDock:dc.dock];
};

- (void)didAddDockable:(ICAKDockableView*)view toDock:(ICAKDock*)dock onRow:(ICAKDockingRow*)row {
    ICAKDockingControllerDockData dat;
    
    NSValue* maybeDat = [self->_docknfo objectForKey:[NSValue valueWithNonretainedObject:view]];
    if (maybeDat != nil) {
        [maybeDat getValue:&dat];
    }
    
    dat.dockable = view;
    dat.dock = dock;
    dat.panel = nil;
    dat.row = row;
    
    [self->_docknfo setObject:[NSValue valueWithBytes:&dat objCType:@encode(ICAKDockingControllerDockData)] forKey:[NSValue valueWithNonretainedObject:view]];
};

- (void)didAddDockable:(ICAKDockableView*)view toPanel:(NSPanel*)panel onRow:(ICAKDockingRow*)row {
    ICAKDockingControllerDockData dat;
    
    NSValue* maybeDat = [self->_docknfo objectForKey:[NSValue valueWithNonretainedObject:view]];
    if (maybeDat != nil) {
        [maybeDat getValue:&dat];
    }
    
    dat.dockable = view;
    dat.dock = nil;
    dat.panel = panel;
    dat.row = row;
    
    [self->_docknfo setObject:[NSValue valueWithBytes:&dat objCType:@encode(ICAKDockingControllerDockData)] forKey:[NSValue valueWithNonretainedObject:view]];
};

@end