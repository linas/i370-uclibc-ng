#ifndef _BITS_STAT_STRUCT_H
#define _BITS_STAT_STRUCT_H

/* This file provides the i370 version of struct stat. */

struct kernel_stat {
	unsigned int st_dev;
	unsigned int st_ino;
	unsigned int st_mode;
	unsigned short st_nlink;
	unsigned int st_uid;
	unsigned int st_gid;
	unsigned int st_rdev;
	unsigned long  st_size;
	unsigned long  st_blksize;
	unsigned long  st_blocks;
	struct timespec st_atim;
	struct timespec st_mtim;
	struct timespec st_ctim;
	unsigned long     __unused4;
	unsigned long     __unused5;
};

#endif	/*  _BITS_STAT_STRUCT_H */
