#include "comms-Math.h"
#ifdef COMMS_TBB
#include <tbb/spin_mutex.h>
#endif // COMMS_TBB

namespace comms {

#ifdef COMMS_TBB
	tbb::spin_mutex TBB_CPOOL_MUTEX;
#endif

// cPool::Alloc
byte * cPool::Alloc(const int Size) {
    if(Size <= 0) {
        return NULL;
    }
#ifdef COMMS_TBB
	tbb::spin_mutex::scoped_lock lk(TBB_CPOOL_MUTEX);
#else
	static cMutex* Mutex = cMutex::GetInstance();
	Mutex->cpool_m.lock();
#endif
    byte *r = NULL;
    cPool_Store *P = GetPoolBySize(Size);
    if(P != NULL) {
        r = P->Allocate();
    }
    if(NULL == r) {
        r = new byte[Size];
    }
#ifndef COMMS_TBB
	Mutex->cpool_m.unlock();
#endif
    return r;
}

// cPool::Free
void cPool::Free(byte *Ptr, const int Size) {
#ifdef COMMS_TBB
	tbb::spin_mutex::scoped_lock lk(TBB_CPOOL_MUTEX);
#else
	static cMutex* Mutex = cMutex::GetInstance();
	Mutex->cpool_m.lock();
#endif
    cPool_Store *P = GetPoolBySize(Size);
    if(P != NULL) {
        P->Free(Ptr);
        Ptr = NULL;
    }
    if(Ptr != NULL) {
        delete[] Ptr;
    }
#ifndef COMMS_TBB
	Mutex->cpool_m.unlock();
#endif
}

cPool_Store * COMMS_POOL[5] = { // 8, 16, 32, 64, 128
	NULL, NULL, NULL, NULL, NULL
};

int cPool_Debug::UsedCount = 0;

} // comms
