#pragma once

//-----------------------------------------------------------------------------
// cThread
//-----------------------------------------------------------------------------
namespace cThread {
	
typedef void (*ThreadProc)(void *);

#if defined COMMS_WINDOWS
typedef HANDLE ThreadHandle;
#endif // COMMS_WINDOWS

#if defined COMMS_MACOS || defined COMMS_LINUX || defined COMMS_IOS || defined COMMS_TIZEN
#include <pthread.h>
typedef pthread_t ThreadHandle;
#endif // COMMS_MACOS || COMMS_LINUX || COMMS_IOS || COMMS_TIZEN

int CpuCount();
/// cThread::SleepSec
inline void SleepSec(const int Sec) {
	std::this_thread::sleep_for(std::chrono::seconds(Sec));
}
/// cThread::SleepMs
inline void SleepMs(const int Ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(Ms));
}
void AddDeadThread(ThreadHandle h);
void RemoveDeadThreads();
void RemoveDeadThread(ThreadHandle h);
ThreadHandle CreateThread(ThreadProc Proc, void *Param, const bool Critical = false, const int Index = 0);
void DeleteThread(ThreadHandle *Thread);
void WaitAndDeleteThread(ThreadHandle *Thread);
void CancelAndDeleteThread(ThreadHandle *Thread);

}; // cThread

/// Contains mutexes which "comms" uses internally
class cMutex {
public:
	static cMutex* GetInstance() {
		static cMutex* Ptr = new cMutex;
		return Ptr;
	}
	std::mutex logMutex;
	std::mutex logMutex2;
	std::mutex cpool_m;
	std::mutex dead_m;
	std::mutex InputEvents;
};