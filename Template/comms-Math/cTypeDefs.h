#pragma once

typedef unsigned char		byte;
typedef unsigned short		word;
typedef unsigned int		dword;

#if defined COMMS_WINDOWS
typedef unsigned __int64	qword;
typedef signed	 __int64	int64;
#endif // COMMS_WINDOWS

#if defined COMMS_MACOS || defined COMMS_LINUX || defined COMMS_IOS || defined COMMS_TIZEN
#ifdef COMMS_64
typedef unsigned long qword;
typedef signed long int64;
#else // 32
typedef unsigned long long qword;
typedef signed long long int64;
#endif // COMMS_64
#endif // COMMS_MACOS || COMMS_LINUX || COMMS_IOS || COMMS_TIZEN
