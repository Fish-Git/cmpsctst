// Copyright (C) 2012-2019, Software Development Laboratories, "Fish" (David B. Trout)
///////////////////////////////////////////////////////////////////////////////
// cmpsctst_stdinc.h  --  Precompiled headers
///////////////////////////////////////////////////////////////////////////////
//
// Include file for standard system include files or
// project specific include files that are used relatively
// frequently but are otherwise changed fairly infrequently.
// This header MUST be the first #include in EVERY source file.
//
///////////////////////////////////////////////////////////////////////////////

/*-------------------------------------------------------------------*/
/* This file contains #include statements for all of the header      */
/* files which are not dependent on the mainframe architectural      */
/* features selected and thus are eligible for precompilation        */
/*-------------------------------------------------------------------*/

#ifndef _HSTDINC_H
#define _HSTDINC_H

#define SDL_HYPERION            /* Distinguish ourselves from others */
#define NOT_HERC                /* This is the utility, not Hercules */

#ifdef HAVE_CONFIG_H
  #ifndef    _CONFIG_H
  #define    _CONFIG_H
    #include <config.h>         /* Hercules build configuration      */
  #endif /*  _CONFIG_H*/
#endif
  #include "hqainc.h"           /* User build settings overrides     */
#ifdef WIN32
  #include "vsvers.h"           /* Visual Studio compiler constants  */
  #include "targetver.h"        /* Minimum Windows platform          */
#endif

/*-------------------------------------------------------------------*/
/* Required system headers...           (these we must ALWAYS have)  */
/*-------------------------------------------------------------------*/

#include "ccnowarn.h"           /* suppress compiler warning support */

#ifdef _MSVC_
///////////////////////////////////////////////////////////////////////////////
// Windows system headers...

#define _CRT_SECURE_NO_WARNINGS     // (I know what I'm doing thankyouverymuch)

#include <Windows.h>        // (Master include file for Windows applications)
#include <stddef.h>         // (common constants, types, variables)
#include <stdlib.h>         // (commonly used library functions)
#include <stdio.h>          // (standard I/O routines)
#include <sys/stat.h>       // (stat() and fstat() support)
#include <time.h>           // (time routines and types)
#include <setjmp.h>         // (setjmp/longjmp)
#include <errno.h>          // (ENOENT)

#else // !_MSVC_
///////////////////////////////////////////////////////////////////////////////
// Linux, etc, system headers...

#include <stddef.h>         // (common constants, types, variables)
#include <stdlib.h>         // (commonly used library functions)
#include <string.h>         // (strrchr)
#include <stdio.h>          // (standard I/O routines)
#include <time.h>           // (time routines and types)
#include <setjmp.h>         // (setjmp/longjmp)
#include <errno.h>          // (ENOENT)
#include <sys/mman.h>       // (mprotect)
#include <signal.h>         // (sigaction)
#include <sys/resource.h>   // (getrusage)
#include <sys/time.h>       // (gettimeofday)
#include <sys/types.h>      // (needed by sys/stat?!)
#include <sys/stat.h>       // (stat() and fstat() support)
#include <stdint.h>         // (standard integer definitions)
#include <limits.h>         // (INT_MAX)
#include <stdarg.h>         // (va_start)
#include <ctype.h>          // (isalnum)

#endif // _MSVC_

///////////////////////////////////////////////////////////////////////////////
// Miscellaneous #defines and typedefs

#ifndef __cplusplus
typedef unsigned char bool;
#define true 1
#define false 0
#endif

///////////////////////////////////////////////////////////////////////////////
// Headers common to ALL platforms...

#include "cmpsctst.h"       // (Master product header)

#endif // _HSTDINC_H
///////////////////////////////////////////////////////////////////////////////
