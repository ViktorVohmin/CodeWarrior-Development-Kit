/*
 *	string.h
 *	
 *		Copyright © 1995 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __string__
#define __string__

#pragma options align=mac68k

#include <size_t.h>
#include <null.h>

#define __max_errstr	32

__extern_c

void * memset(void * dst, int val, size_t n);
void * memchr(const void * src, int val, size_t n);
int		 memcmp(const void * src1, const void * src2, size_t n);

__end_extern_c

#if !__MC68K__ || _NO_FAST_STRING_INLINES_ || __dest_os != __mac_os

	__extern_c
	
	void * memcpy (void * dst, const void * src, size_t n);
	void * memmove(void * dst, const void * src, size_t n);
	
	__end_extern_c

#else /* !(!__MC68K__ || _NO_FAST_STRING_INLINES_ || __dest_os != __mac_os) */

	__extern_c
	
	void * __memcpy(void * : __A1, const void * : __A0, size_t : __D0) : __A1
		= {
				0xA22E			/* _BlockMoveData */
			};
	
	void * __memmove(void * : __A1, const void * : __A0, size_t : __D0) : __A1
		= {
				0xA22E			/* _BlockMoveData */
			};
	
	__end_extern_c
	
	#ifdef __cplusplus
	
		inline void * memcpy (void * dst, const void * src, size_t n)
			{ return __memcpy(dst, src, len); }
		
		inline void * memmove(void * dst, const void * src, size_t n)
			{ return __memmove(dst, src, len); }
	
	#else
	
		void * memcpy (void * dst, const void * src, size_t n);
		void * memmove(void * dst, const void * src, size_t n);
		
		#define memcpy(dst, src, len)		__memcpy(dst, src, len)
		#define memmove(dst, src, len)	__memmove(dst, src, len)
	
	#endif

#endif /* !__MC68K__ || _NO_FAST_STRING_INLINES_ */

#if !__MC68K__ || _NO_FAST_STRING_INLINES_

	__extern_c
	
	size_t strlen (const char * str);
	char * strcpy (char * dst, const char * src);
	
	__end_extern_c

#else /* !(!__MC68K__ || _NO_FAST_STRING_INLINES_) */

	__extern_c
	
	size_t __strlen(const char * : __A0) : __D0
		= {
				0x70FF,			/*		moveq		-1, d0	*/
				0x5280,			/* @1	addq.l	#1, d0	*/
				0x4A18,			/*		tst.b		(a0)+		*/
				0x66FA			/*		bne.s		@1			*/
			};
		
	char * __strcpy(char * : __A0, const char * : __A1) : __D0 
		= {
				0x2008,			/*		move.l	a0, d0				*/
				0x10D9,			/* @1	move.b	(a1)+, (a0)+	*/
				0x66FC			/*		bne.s		@1						*/
			};
	
	__end_extern_c
	
	#ifdef __cplusplus
	
		inline size_t strlen(const char * str)
			{ return __strlen(str); }
		
		inline char * strcpy(char * dst, const char * src)
			{ return __strcpy(dst, src); }
	
	#else
	
		size_t strlen (const char * str);
		char * strcpy (char * dst, const char * src);
		
		#define strlen(str)				__strlen(str)
		#define strcpy(dst, src)	__strcpy(dst, src)
	
	#endif

#endif /* !__MC68K__ || _NO_FAST_STRING_INLINES_ */

__extern_c

char * strncpy(char * dst, const char * src, size_t n);

char * strcat (char * dst, const char * src);
char * strncat(char * dst, const char * src, size_t n);

int    strcmp (const char * str1, const char * str2);
int    strncmp(const char * str1, const char * str2, size_t n);

int    strcoll(const char * str1, const char * str2);
size_t strxfrm(      char * str1, const char * str2, size_t n);

char * strchr (const char * str, int chr);
char * strrchr(const char * str, int chr);
char * strpbrk(const char * str, const char * set);
size_t strspn (const char * str, const char * set);
size_t strcspn(const char * str, const char * set);
char * strtok (      char * str, const char * set);

char * strstr(const char * str, const char * pat);

char * strerror(int errnum);

char * __strerror(int errnum, char * str);

__end_extern_c

#pragma options align=reset

#endif
