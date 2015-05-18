#ifndef __ICCANVASMANAGER__DISPLAYSUITE_HPP__
#define __ICCANVASMANAGER__DISPLAYSUITE_HPP__

#include "../icCanvasManager.hpp"

namespace icCanvasManager {
    class Renderer;

    /* A collection of rendering and presentation implementations leveraging
     * a particular underlying technology. Tiles generated by the Renderer
     * created by a DisplaySuite are guaranteed to be both compatible as well
     * as reasonably efficient to use in the Presenter created by the same
     * DisplaySuite object.
     *
     * DisplaySuite cannot be created by core code as it is designed to
     * leverage platform-specific technology. You must solicit a Suite in your
     * constructor in order to use it.
     */
    class DisplaySuite : public virtual RefCnt {
    protected:
        DisplaySuite();
    public:
        virtual ~DisplaySuite();

        /* Certain DisplaySuite components may support running outside of the
         * thread that main() was called on, with certain limitations. This
         * enum allows DisplaySuite components to signal how much concurrency
         * is allowed.
         */
        typedef enum {
            /* Implementation supports no concurrency of any kind and can only
             * be called from the main thread.
             */
            CONCURRENCY_MAIN_THREAD_ONLY,

            /* Implementation supports no concurrency of any kind but can be
             * accessed from any thread, so long as thread access is externally
             * synchronized such that only one thread ever accesses the
             * implementation.
             */
            CONCURRENCY_SINGLE_THREAD,

            /* Implementation supports no concurrency of any kind but can be
             * accessed from any thread, so long as thread access is externally
             * synchronized such that only one thread can access the
             * implementation. Access to the implementation may be transferred
             * across threads.
             */
            CONCURRENCY_SINGLE_THREAD_TRANSFERRABLE,

            /* Implementation supports parallel processing through the use of
             * multiple implementation objects, so long as each implementation
             * object's thread access is externally synchronized such that only
             * one thread can access a particular instance. Access to each
             * instance may be transferred across threads.
             *
             * Concurrent use of multiple instances is expected to provide
             * linear or near-linear performance gains up to the number of
             * available hardware threads.
             */
            CONCURRENCY_MULTIPLE_INSTANCES,

            /* Implementation supports parallel processing through one or more
             * implementation objects, and additionally supports concurrent
             * access from multiple threads to a single instance object.
             * Implementation internally synchronizes concurrent access across
             * multiple threads.
             *
             * Concurrent use of a single instance is internally synchronized
             * (e.g. through locks or atomics) to ensure consistent state.
             *
             */
            CONCURRENCY_REENTRANT_INSTANCES,
        } ConcurrencyLevel;

        virtual void report_concurrency_level(ConcurrencyLevel *out_renderer_lvl, ConcurrencyLevel *out_presenter_lvl) = 0;

        /* Creates a new Renderer instance with the implementations of the
         * particular DisplaySuite.
         */
        virtual Renderer* create_renderer() = 0;

        /* Free a TILE generated by a DisplaySuite implementation.
         */
        virtual void free_tile(DisplaySuiteTILE tile) = 0;

        /* Determine if direct transfers of tile contents between this and
         * another DisplaySuite implementation are possible.
         */
        virtual bool can_direct_transfer(DisplaySuite *other) = 0;

        /* Directly transfer a TILE between this DisplaySuite's preferred tile
         * representation to another DisplaySuite's preferred tile
         * representation.
         *
         * The copy bit determines if the direct transfer operation should make
         * a copy of the original tile. If it is not set, the client should
         * assume that the original TILE was freed and can no longer be used.
         * If it is set, then both TILEs can be used and freed independently.
         *
         * If this function returns 0, direct transfers between it and the
         * other DisplaySuite are not supported. The DisplaySuite MUST NOT
         * return 0 for direct transfer operations that it previously indicated
         * were supported in can_direct_transfer.
         */
        virtual DisplaySuiteTILE direct_transfer(DisplaySuite* other, DisplaySuiteTILE tile, bool copy_bit) = 0;

        /* Transfer a TILE between this DisplaySuite's preferred tile
         * representation to the generic tile data representation defined by
         * TileCache.
         *
         * Generic tile data is owned by the caller of the function and is
         * allocated using the new[] operator (hence should be deleted with the
         * delete[] operator).
         */
        virtual TileCache::TileData* export_tile(DisplaySuiteTILE tile) = 0;

        /* Transfer a TILE between the generic tile data representation defined
         * by TileCache to this DisplaySuite's preferred tile representation.
         *
         * Generic tile data is owned by the caller of the function and is
         * allocated using the new[] operator (hence should be deleted with the
         * delete[] operator).
         */
        virtual DisplaySuiteTILE import_tile(TileCache::TileData *tile_dat) = 0;
    };
}

#endif