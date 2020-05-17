#pragma once

//-----------------------------------------------------------------------------
// cThread
//-----------------------------------------------------------------------------
namespace cThread {
	
typedef void (*ThreadProc)(void *);

#if defined COMMS_WINDOWS
typedef HANDLE ThreadHandle;
typedef HANDLE ThreadMutex;
#endif // COMMS_WINDOWS

#if defined COMMS_MACOS || defined COMMS_LINUX || defined COMMS_IOS || defined COMMS_TIZEN
#include <pthread.h>
typedef pthread_t ThreadHandle;
typedef pthread_mutex_t ThreadMutex;
#endif // COMMS_MACOS || COMMS_LINUX || COMMS_IOS || COMMS_TIZEN

int CpuCount();
void Sleep(const dword Milliseconds);
void AddDeadThread(ThreadHandle h);
ThreadHandle CreateThread(ThreadProc Proc, void *Param, const bool Critical = false, const int Index = 0);
void DeleteThread(ThreadHandle *Thread);
void WaitAndDeleteThread(ThreadHandle *Thread);
void CancelAndDeleteThread(ThreadHandle *Thread);

void CreateMutex(ThreadMutex &Mutex);
void DeleteMutex(ThreadMutex &Mutex);
void LockMutex(ThreadMutex &Mutex);
void UnlockMutex(ThreadMutex &Mutex);

}; // cThread

/// Contains mutexes which "comms" uses internally
class cMutex {
public:
	cThread::ThreadMutex logMutex;
	cThread::ThreadMutex logMutex2;
	cThread::ThreadMutex cpool_m;
	cThread::ThreadMutex dead_m;
	cThread::ThreadMutex InputEvents;
	// cMutex.ctor
	cMutex() {
		cThread::CreateMutex(logMutex);
		cThread::CreateMutex(logMutex2);
		cThread::CreateMutex(cpool_m);
		cThread::CreateMutex(dead_m);
		cThread::CreateMutex(InputEvents);
	}
	// cMutex.GetInstance
	static cMutex * GetInstance() {
		static cMutex *Ptr = new cMutex;
		return Ptr;
	}
};