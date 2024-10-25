/* The i370 uses the older linux kernel 2.2.1 version */

#ifndef _BITS_DIRENT_H
#define _BITS_DIRENT_H	1

struct dirent
  {
    long d_ino;
    __off_t d_off;
    unsigned short int d_reclen;
    char d_name[256];
  };

#ifdef __USE_LARGEFILE64
/* The i370 doesn't actually have one of these, but the uClibc 
   defines expect this, because wordsize=32 sets
   __ILP32_OFFBIG_CFLAGS to -D_FILE_OFFSET_BITS=64 which is
   semi-correct cause we have 64-bit offsets in the kernel,
   but just not the general dirent. Anyway, __USE_LARGEFILE64
   gets set as a result and I can't turn it off.

   Here's the next gotcha: The libc/misc/dirent/Makefile.in builds
   libc/misc/dirent/readdir64.c unconditionally. And that file
   says #if __WORDSIZE != 64 # define __DIRENT_TYPE struct dirent64
   which seems wtf to me, but whatever, I will not argue with the
   maintainers. Thus, this dirent must be same as above, for things
   to actually work.
 */
struct dirent64
  {
    long d_ino;
    __off_t d_off;
    unsigned short int d_reclen;
    char d_name[256];
  };
#endif


#define d_fileno  d_ino

#undef  _DIRENT_HAVE_D_NAMLEN
#define _DIRENT_HAVE_D_RECLEN
#define _DIRENT_HAVE_D_OFF
#undef _DIRENT_HAVE_D_TYPE

#endif /* bits/dirent.h */
