class icCanvasGtk.DrawingWindow : Gtk.ApplicationWindow {
    private Gtk.ScrolledWindow scrollwdgt;
    private icCanvasGtk.CanvasWidget canvaswdgt;
    private icCanvasGtk.WindowDock dock;
    
    public DrawingWindow(icCanvasGtk.Application app) {
        Object(application: app);
        
        this.title = "icCanvas";
        this.window_position = Gtk.WindowPosition.CENTER;
        this.set_default_size(400, 400);
        
        this.dock = new icCanvasGtk.WindowDock();
        this.add(dock);
        
        app.docking_ctrl.add_dock(this.dock);
        
        this.scrollwdgt = new Gtk.ScrolledWindow(null, null);
        this.dock.center = scrollwdgt;
        
        this.canvaswdgt = new icCanvasGtk.CanvasWidget();
        this.scrollwdgt.add(canvaswdgt);
        
        icCanvasGtk.DockablePanel dt = new icCanvasGtk.DockablePanel();
        dt.label = "I am wearing pants";
        
        Gtk.Button btn = new Gtk.Button.with_label("Do something funny");
        dt.add(btn);
        
        icCanvasGtk.DockablePanel dt2 = new icCanvasGtk.DockablePanel();
        dt2.label = "Box packing test";
        
        Gtk.Box bx = new Gtk.Box(Gtk.Orientation.VERTICAL, 5);
        bx.pack_start(new Gtk.Button.with_label("Button 1"));
        bx.pack_start(new Gtk.Button.with_label("Button 2"));
        bx.pack_start(new Gtk.Button.with_label("Button 3"));
        dt2.add(bx);
        
        this.dock.add_dockable(dt, icCanvasGtk.Dock.Edge.LEFT);
        this.dock.add_dockable(dt2, icCanvasGtk.Dock.Edge.RIGHT);
        
        icCanvasGtk.DockableToolbar db = new icCanvasGtk.DockableToolbar();
        
        Gtk.Toolbar tb = new Gtk.Toolbar();
        
        Gtk.Image tbn1img = new Gtk.Image.from_icon_name("document-open", Gtk.IconSize.SMALL_TOOLBAR);
        Gtk.ToolButton tbn1 = new Gtk.ToolButton(tbn1img, null);
        tb.add(tbn1);
        
        Gtk.Image tbn2img = new Gtk.Image.from_icon_name("window-close", Gtk.IconSize.SMALL_TOOLBAR);
        Gtk.ToolButton tbn2 = new Gtk.ToolButton(tbn2img, null);
        tb.add(tbn2);
        
        db.add(tb);
        
        this.dock.add_dockable(db, icCanvasGtk.Dock.Edge.TOP);
    }
    
    public icCanvasGtk.Drawing drawing {
        set {
            this.canvaswdgt.drawing = value.core_drawing;
        }
    }
    
    public void tile_rendered() {
        this.canvaswdgt.queue_draw();
    }
}