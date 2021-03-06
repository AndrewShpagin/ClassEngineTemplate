#pragma once

#include <iostream>
#include <thread>
#include <mutex>

typedef ptrdiff_t cPtrDiff;

#ifdef _WIN32
#define COMMS_WINDOWS
#ifdef _WIN64
#define COMMS_64
#endif // _WIN64
#ifdef _DEBUG
#define COMMS_ASSERT
#endif // _DEBUG
#ifdef _CONSOLE
#define COMMS_CONSOLE
#endif // _CONSOLE
#define COMMS_ALIASING
#endif // _WIN32

#ifdef __linux__
#define COMMS_LINUX
#ifdef __LP64__
#define COMMS_64
#endif // __LP64__
#define COMMS_ALIASING __attribute__((__may_alias__))
#endif // __linux__

#ifdef __APPLE__
#define COMMS_MACOS
#ifdef __LP64__
#define COMMS_64
#endif // __LP64__
#ifdef DEBUG
#define COMMS_ASSERT
#endif // DEBUG
#define COMMS_ALIASING
#endif // __APPLE__

#ifdef COMMS_WINDOWS
#ifndef WINVER
#define WINVER 0x0601 // Windows Vista and above
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601  // Windows Vista and above
#endif
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <Wspiapi.h>
#include <windows.h>
#define COMMS_ALIGN(x) __declspec(align(x))
#endif // COMMS_WINDOWS

#ifdef COMMS_MACOS
#include <float.h>
#include <unistd.h>
#include <math.h>
#include <sys/sysctl.h>
#include <signal.h>
#define COMMS_ALIGN(x) __attribute__ ((aligned(x)))
#endif // COMMS_MACOS

#ifdef COMMS_LINUX
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <limits>
#include <stdarg.h>
#include <signal.h>
#include <iconv.h>
#define COMMS_ALIGN(x) __attribute__ ((aligned(x)))
#endif // COMMS_LINUX

namespace comms {

class cVec4;
class cMat3;
class cMat4;
class cStr;
class cQuat;
class cRotation;
class cAngles;
class cBounds;
class cPlane;
class dVec4;
class dMat3;
class dMat4;


#include "cTypeDefs.h"

#ifdef COMMS_ASSERT
#ifdef COMMS_WINDOWS
#define cAssertBreak __debugbreak();
#endif // COMMS_WINDOWS
#if defined COMMS_MACOS || defined COMMS_LINUX
#define cAssertBreak raise(SIGINT);
#endif // COMMS_MACOS || COMMS_LINUX
#define cAssert(Exp) {\
	if(!(Exp)) {\
		cAssertBreak\
	}\
}
#define cAssertM(Exp, Msg) {\
	if(!(Exp)) {\
		cAssertBreak\
	}\
}
#else // !COMMS_ASSERT
#define cAssert(Exp)		((void)0)
#define cAssertM(Exp, Msg)	((void)0)
#endif // COMMS_ASSERT

//#define COMMS_TBB
	
#include "cMath.h"
#include "cList.h"
#include "cVec2.h"
#include "cVec3.h"
#include "cVec4.h"
#include "cRect.h"
#include "cMat3.h"
#include "cMat4.h"
#include "cQuat.h"
#include "cAngles.h"
#include "cRotation.h"
#include "cPool.h"
#include "cStr.h"
#include "cVec.h"
#include "cSphere.h"
#include "cPlane.h"
#include "cBounds.h"
#include "cSeg.h"
#include "cThread.h"
#include "dVec2.h"
#include "dVec3.h"
#include "dVec4.h"
#include "dMat3.h"
#include "dMat4.h"
#include "dSeg.h"

#ifndef COMMS_WINDOWS
inline void OutputDebugString(const char *Str) {
    std::cout << Str;
}
#endif // !Windows

} // comms

template <class X> using cList = comms::cList<X>; // Alias for "3DCoat". Note: under macOS there is enum value "cList" in the system header.
