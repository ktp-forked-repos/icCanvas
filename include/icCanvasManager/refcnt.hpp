#ifndef __ICCANVASMANAGER_REFCNT__H_
#define __ICCANVASMANAGER_REFCNT__H_

#include "../icCanvasManager.hpp"

namespace icCanvasManager {
    class RefCnt {
        int references;
    public:
        RefCnt();
        virtual ~RefCnt();

        void ref();
        void deref();
    }
}

#endif
