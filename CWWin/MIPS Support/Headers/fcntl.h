/*
 *	File:		fcntl.h
 *				©1993-1995 metrowerks Inc. All rights reserved
 *	Author:		Berardino E. Baratta
 *
 *	Content:	Interface file to standard UNIX-style entry points ...
 *
 *	NB:			This file implements some UNIX low level support.  These functions
 *				are not guaranteed to be 100% conformant.
 */

#ifndef	_FCNTL
#define	_FCNTL

#pragma options align=mac68k

#if __CFM68K__ && __USING_IMPORTED_ANSI__
#pragma import on
#endif

/* local typedefs (used by creat) */
typedef unsigned long	mode_t;

/*
 *	Mode values accessible to open()
 */
#define O_RDWR			0x0			/* open the file in read/write mode */
#define O_RDONLY		0x1			/* open the file in read only mode */
#define O_WRONLY		0x2			/* open the file in write only mode */
#define O_APPEND		0x0100		/* open the file in append mode */
#define O_CREAT			0x0200		/* create the file if it doesn't exist */
#define O_EXCL			0x0400		/* if the file already exists don't create it again */
#define O_TRUNC			0x0800		/* truncate the file after opening it */
#define O_NRESOLVE		0x1000		/* Don't resolve any aliases */
#define O_ALIAS			0x2000		/* Open alias file (if the file is an alias) */
#define O_RSRC 			0x4000		/* Open the resource fork */
#define O_BINARY		0x8000		/* open the file in binary mode (default is text mode) */

/*
 *	Commands available to fcntl()
 */
#define F_DUPFD			0x0			/* return a duplicate file descriptor */

#ifdef __cplusplus
extern "C" {
#endif

/*
 *	Opens a file and returns it's id.
 */
int open(const char *path, int oflag);

/*
 *	Creates and opens a file, returning the filenumber.  Note can only be used to set
 *	binary mode (default is text mode) using O_BINARY
 */
int creat(const char *path, mode_t mode);

/*
 *	File control routine.
 */
int fcntl(int fildes, int cmd, ...);

#ifdef __cplusplus
}
#endif

#if __CFM68K__ && __USING_IMPORTED_ANSI__
#pragma import reset
#endif

#pragma options align=reset

#endif
