#include "comms-Math.h"

namespace comms {

namespace cThread {

cList<ThreadHandle> DeadThreads;

void AddDeadThread(ThreadHandle h){
	cThread::LockMutex(cMutex::GetInstance()->dead_m);
	DeadThreads.Add(h);
	cThread::UnlockMutex(cMutex::GetInstance()->dead_m);
}

#ifdef COMMS_WINDOWS

// CpuCount
int CpuCount() {
	static int Cpus = -1;
	if(-1 == Cpus) {
		SYSTEM_INFO si;
		GetSystemInfo(&si);
		Cpus = cMath::Max(1, (int)si.dwNumberOfProcessors);
	}
	return Cpus;
}

// Sleep
void Sleep(const dword Milliseconds) {
	::Sleep(Milliseconds);
}

// CreateThread
ThreadHandle CreateThread(ThreadProc Proc, void *Param, const bool Critical, const int Index) {
	{
		cThread::LockMutex(cMutex::GetInstance()->dead_m);
		for (int i = 0; i < DeadThreads.Count(); i++){
			DeleteThread(&DeadThreads[i]);
		}
		DeadThreads.Clear();
		cThread::UnlockMutex(cMutex::GetInstance()->dead_m);
	}
	ThreadHandle hThread = ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Proc, Param, CREATE_SUSPENDED, NULL);
	if(Critical) {
		SetThreadPriority(hThread, THREAD_PRIORITY_TIME_CRITICAL);
	}
	ResumeThread(hThread);
	return hThread;
}

// CancelAndDeleteThread
void CancelAndDeleteThread(ThreadHandle *Thread) {
#ifdef COMMS_WINDOWS
	if(*Thread != NULL) {
		TerminateThread(*Thread, 0);
		CloseHandle(*Thread);
		*Thread = NULL;
	}
#endif // COMMS_WINDOWS
}

// DeleteThread
void DeleteThread(ThreadHandle *Thread) {
	if(*Thread != NULL) {
		CloseHandle(*Thread);
		*Thread = NULL;
	}
}

// WaitAndDeleteThread
void WaitAndDeleteThread(ThreadHandle *Thread) {
	if(*Thread != NULL) {
		WaitForSingleObject(*Thread, INFINITE);
		CloseHandle(*Thread);
		*Thread = NULL;
	}
}

// CreateMutex
void CreateMutex(ThreadMutex &Mutex) {
	Mutex = ::CreateMutex(NULL, FALSE, NULL);
}

// DeleteMutex
void DeleteMutex(ThreadMutex &Mutex) {
	CloseHandle(Mutex);
}

// LockMutex
void LockMutex(ThreadMutex &Mutex) {
	WaitForSingleObject(Mutex, INFINITE);	
}

// UnlockMutex
void UnlockMutex(ThreadMutex &Mutex) {	
	ReleaseMutex(Mutex);
}

#endif // COMMS_WINDOWS

#if defined COMMS_MACOS || defined COMMS_LINUX || defined COMMS_IOS || defined COMMS_TIZEN

// CpuCount
int CpuCount() {
	static int Cpus = -1;
	if(-1 == Cpus) {
#ifdef COMMS_MACOS
		size_t s = sizeof(Cpus);
		sysctlbyname("hw.logicalcpu", &Cpus, &s, NULL, 0);
#endif // COMMS_MACOS
#ifdef COMMS_LINUX
		Cpus = sysconf(_SC_NPROCESSORS_ONLN);
#endif // COMMS_LINUX
#if defined COMMS_IOS || defined COMMS_TIZEN
		Cpus = -1;
#endif // COMMS_IOS || COMMS_TIZEN
		Cpus = cMath::Max(1, Cpus);
	}
	return Cpus;
}

// Sleep
void Sleep(const dword Milliseconds) {
#if !defined COMMS_IOS && !defined COMMS_TIZEN
	usleep(1000 * Milliseconds);
#endif // !COMMS_IOS && !COMMS_TIZEN
}

// CreateThread
ThreadHandle CreateThread(ThreadProc Proc, void *Param, const bool Critical, const int Index) {
	pthread_t th;
	pthread_create(&th, NULL, (void *(*)(void *))Proc, Param);
	return th;
}

// For every thread we should call "pthread_join" OR "pthread_detach" because resources are not freed automatically after finishing thread procedure.
// We should NOT call both "pthread_join" and "pthread_detach" because this results in "double free" crash.

// CancelAndDeleteThread
void CancelAndDeleteThread(ThreadHandle *Thread) {
	if(*Thread != 0) {
		pthread_cancel(*Thread);
		pthread_detach(*Thread);
		*Thread = 0;
	}
}

// DeleteThread
void DeleteThread(ThreadHandle *Thread) {
	if(*Thread != 0) {
		pthread_detach(*Thread); // Doesn't stop the thread. It just specifies the system to free resources of already finished thread OR
		// to free resources in the future after the thread will be finished. It is valid to call "pthread_t th; pthread_create(&th, NULL, Proc, NULL); pthread_detach(th);".
		*Thread = 0;
	}
}

// WaitAndDeleteThread
void WaitAndDeleteThread(ThreadHandle *Thread) {
	if(*Thread != 0) {
		pthread_join(*Thread, NULL);
		*Thread = 0;
	}
}

// CreateMutex
void CreateMutex(ThreadMutex &Mutex) {
	pthread_mutex_init(&Mutex, NULL);
}

// ThreadMutex
void DeleteMutex(ThreadMutex &Mutex) {
	pthread_mutex_destroy(&Mutex);
}

// LockMutex
void LockMutex(ThreadMutex &Mutex) {
	pthread_mutex_lock(&Mutex);
}

// UnlockMutex
void UnlockMutex(ThreadMutex &Mutex) {
	pthread_mutex_unlock(&Mutex);
}

#endif // COMMS_MACOS || COMMS_LINUX || COMMS_IOS || COMMS_TIZEN

} // cThread

} // comms
