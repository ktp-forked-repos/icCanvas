#ifndef __ICCANVASMANAGER_CAPI__ICM_RENDERSCHEDULER__H__
#define __ICCANVASMANAGER_CAPI__ICM_RENDERSCHEDULER__H__

#include <icCanvasManagerC.h>

#include <cairo.h>

#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

    typedef void *icm_renderscheduler;

    icm_renderscheduler icm_renderscheduler_construct(icm_application app);
    icm_renderscheduler icm_renderscheduler_reference(icm_renderscheduler wrap);
    int icm_renderscheduler_dereference(icm_renderscheduler wrap);

    icm_renderer icm_renderscheduler_renderer(icm_renderscheduler wrap);
    void icm_renderscheduler_set_renderer(icm_renderscheduler wrap, icm_renderer r);

    void icm_renderscheduler_request_tile(icm_renderscheduler wrap, icm_drawing d, int x, int y, int size, int time);
    void icm_renderscheduler_request_tiles(icm_renderscheduler wrap, icm_drawing d, cairo_rectangle_t *rect, int size, int time);
    void icm_renderscheduler_revoke_request_rect(icm_renderscheduler wrap, icm_drawing d, int x_min, int y_min, int x_max, int y_max, bool is_inverse);
    void icm_renderscheduler_revoke_request_zoom(icm_renderscheduler wrap, icm_drawing d, int zoom_min, int zoom_max, bool is_inverse);
    void icm_renderscheduler_background_tick(icm_renderscheduler wrap);
    int icm_renderscheduler_collect_request(icm_renderscheduler wrap, icm_drawing d, cairo_rectangle_t *out_tile_rect);

#ifdef __cplusplus
}
#endif

#endif
