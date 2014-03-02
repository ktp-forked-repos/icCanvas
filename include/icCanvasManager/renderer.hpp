#ifndef __ICCANVASMANAGER_RENDERER_HPP__
#define __ICCANVASMANAGER_RENDERER_HPP__

#include "../icCanvasManager.hpp"

#include <cairo.h>
#include <cstdint>

namespace icCanvasManager {
    /* Class which implements icCanvas drawing methods.
     */
    class Renderer {
        int32_t x, y, zoom;             //Canvas parameters
        int32_t tw, th;                 //Surface parameters
        float xscale, yscale;           //Derived caluations
        int32_t xmin, xmax, ymin, ymax;
        cairo_surface_t* xrsurf;        //Cairo surface to draw on
        
        /* Convert stroke coordinates to tile space. */
        void coordToTilespace(const int32_t x, const int32_t y, int32_t* out_tx, int32_t* out_ty);
    public:
        /* Specify the current drawing surface, location, and zoom level.
         * 
         * The cairo surface pointer given to the renderer does not transfer
         * memory ownership, but must point to valid memory for the entire time
         * that you draw with this renderer.
         * 
         * The cairo surface must be an Image Surface.
         */
        void enterImageSurface(const int32_t x, const int32_t y, const int32_t zoom, cairo_surface_t* xrsurf);
        
        /* Given a brushstroke, draw it onto the surface at the specified
         * position and zoom level.
         */
        void drawStroke(BrushStroke& br);
    };
}

#endif
