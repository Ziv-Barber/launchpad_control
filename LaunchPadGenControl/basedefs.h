
/*
 * Code license:
 *
 * The Basic C RT Extentions Library.
 * Copyright (C) Ziv Barber.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

/**
 * @file
 * @brief Basic defines.
 *
 * This header files declares some basic defines that hiding the private implementation 
 * of the basic C types on different compilers and operation systems.
 *
 * @b Interesting @b Bookmarks:
 *
 * Please search for the following key word on the code to locate some interesting places on the code:
 *
 * -# @b BMK_TODO - We need to finish code this part.
 */

#ifndef H_BASE_DEFS_HEAD
#define H_BASE_DEFS_HEAD

/*
 * Header files needed to be include with this header:
 */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Some public definess:
 */

/* !@!:defs */

#ifdef _MSC_VER
#ifndef _WINDOWS_ALL_
#define _WINDOWS_ALL_
#endif
#endif
#ifdef _WIN32_WCE
#ifndef _WINDOWS_ALL_
#define _WINDOWS_ALL_
#endif
#ifndef D_BS_CBAPI
#ifdef _i386_
#define D_BS_CBAPI
#endif
#endif
#endif

#ifndef D_BS_CBAPI
#ifdef _WINDOWS_ALL_
#define D_BS_CBAPI __stdcall
#else
#define D_BS_CBAPI
#endif
#endif

#ifdef __cplusplus
#define D_BS_NULL 0L           /* A typical definition of NULL in C++. */
#else
#define D_BS_NULL ((void*) 0L) /* C defines NULL this way. */
#endif /* C++ */

/* Windows CE always using unicode: */
#ifdef _WIN32_WCE
#ifndef _UNICODE
#define BS_UNICODE
#endif
#endif

#ifdef _UNICODE
#ifndef BS_UNICODE
#define BS_UNICODE
#endif /* BS_UNICODE */
#endif /* _UNICODE */

#ifdef _WINDOWS_ALL_
typedef signed __int8 bs_int8; /* signed 8 bit. */
typedef unsigned __int8 bs_uint8; /* unsigned 8 bit. */
typedef signed __int16 bs_int16; /* signed 16 bit. */
typedef unsigned __int16 bs_uint16; /* unsigned 16 bit. */
typedef signed __int32 bs_int32; /* signed 32 bit. */
typedef unsigned __int32 bs_uint32; /* unsigned 32 bit. */
#ifndef _WIN32_WCE
typedef signed __int64 bs_int64; /* signed 64 bit. */
typedef unsigned __int64 bs_uint64; /* unsigned 64 bit. */
#endif
#else
/* BMK_TODO: we should fix it someday to support other 64-bits compilers, etc: */
#if (defined(HPUX) && defined(__cplusplus) && !defined(__GNUC__) && __cplusplus < 199707L) || (defined(SCO) && defined(__cplusplus) && !defined(__GNUC__) && __cplusplus == 1L)
typedef char bs_int8; /* signed 8 bit. */
#else
typedef signed char bs_int8; /* signed 8 bit. */
#endif
typedef unsigned char bs_uint8; /* unsigned 8 bit. */
typedef signed short bs_int16; /* signed 16 bit. */
typedef unsigned short bs_uint16; /* unsigned 16 bit. */
typedef signed long bs_int32; /* signed 32 bit. */
typedef unsigned long bs_uint32; /* unsigned 32 bit. */
typedef signed long long bs_int64; /* signed 64 bit. */
typedef unsigned long long bs_uint64; /* unsigned 64 bit. */
#endif /* _WINDOWS_ALL_ */

/* Characters: */
#ifdef BS_UNICODE
#define STRCHR bs_uint16
#define t_bs_strchar bs_uint16
#define BS_T(textStr) (bs_uint16 *) L ## textStr
#define M_BS_T(textStr) (bs_uint16 *) L ## textStr
#else
#define STRCHR bs_int8
#define t_bs_strchar bs_uint8
#define BS_T(textStr) (bs_int8 *) textStr
#define M_BS_T(textStr) (bs_int8 *) textStr
#endif /* BS_UNICODE */

/* Use as integer when you don't care about the size of the integer and 
   you need the maximum size possible, at last 32bits: */
#ifdef bs_uint64
typedef bs_uint64 bs_uintmax;
typedef bs_int64 bs_intmax;
#else
typedef bs_uint32 bs_uintmax;
typedef bs_int32 bs_intmax;
#endif

/*
 * New names:
 */

#define t_bs_int8 bs_int8
#define t_bs_uint8 bs_uint8
#define t_bs_int16 bs_int16
#define t_bs_uint16 bs_uint16
#define t_bs_int32 bs_int32
#define t_bs_uint32 bs_uint32
#ifdef bs_uint64
#define t_bs_int64 bs_int64
#define t_bs_uint64 bs_uint64
#endif
#define t_bs_intmax bs_intmax
#define t_bs_uintmax bs_uintmax

/* @!@:defs */

/*
 * Public prototypes:
 */

#ifdef __cplusplus
}
#endif

#endif /* H_BASE_DEFS_HEAD */

/*
 * End of the header file basedefs.h
 */

