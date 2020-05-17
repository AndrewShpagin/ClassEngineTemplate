#include "comms-Math.h"

namespace comms {


// cPool::Alloc
byte * cPool::Alloc(const int Size) {
    if(Size <= 0) {
        return NULL;
    }
	cThread::LockMutex(cMutex::GetInstance()->cpool_m);
    byte *r = NULL;
    cPool_Store *P = GetPoolBySize(Size);
    if(P != NULL) {
        r = P->Allocate();
    }
    if(NULL == r) {
        r = new byte[Size];
    }
	cThread::UnlockMutex(cMutex::GetInstance()->cpool_m);
    return r;
}

// cPool::Free
void cPool::Free(byte *Ptr, const int Size) {
	cThread::LockMutex(cMutex::GetInstance()->cpool_m);
    cPool_Store *P = GetPoolBySize(Size);
    if(P != NULL) {
        P->Free(Ptr);
        Ptr = NULL;
    }
    if(Ptr != NULL) {
        delete[] Ptr;
    }
	cThread::UnlockMutex(cMutex::GetInstance()->cpool_m);
}

cPool_Store * COMMS_POOL[5] = { // 8, 16, 32, 64, 128
	NULL, NULL, NULL, NULL, NULL
};

int cPool_Debug::UsedCount = 0;

} // comms
