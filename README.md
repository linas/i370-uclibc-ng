uClibc for i370
---------------
This is a port of the uClibc-ng C library to the i370 toolchain for the
IBM System/370 instruction set. It is a part of the 25th anniversary
edition of the [i370 Bigfoot Project](https://github.com/linas/i370-bigfoot).
Additional background info is at
[Linas' i370 website](https://linas.org/linux/i370/i370.html).

### Building Quickstart
General instructions are in the [INSTALL](INSTALL) file.

Quickstart:
* `make menuconfig` select i370 CPU
* In "Target Architecture Features and Options", scroll to bottom and
  set location of kernel headers.
* In "Development/debugging options", fill in
  "Cross-compiling toolchain prefix" with
  `/usr/local/i370-ibm-linux/bin` (as appropriate).

Original README
---------------
  uClibc-ng - a small C Library for Linux

uClibc-ng (aka µClibc-ng/pronounced yew-see-lib-see-next-generation) is a C
library for developing embedded Linux systems. It is much smaller than the GNU
C Library, but nearly all applications supported by glibc also work perfectly
with uClibc-ng.

uClibc-ng is a spin-off of uClibc from http://www.uclibc.org from Erik Andersen
and others.

Porting applications from glibc to uClibc-ng typically involves just
recompiling the source code.  uClibc-ng even supports shared libraries and
threading. It currently runs on standard Linux and MMU-less (also known as
µClinux) systems with support for Alpha, ARC, ARM, Blackfin, CRIS, FR-V, HPPA,
IA64, KVX, LM32, M68K/Coldfire, Metag, Microblaze, MIPS, MIPS64, NDS32, NIOS2,
OpenRisc, PowerPC, SuperH, Sparc, Tile, x86, x86_64 and Xtensa processors.

If you are building an embedded Linux system and you find that glibc is eating
up too much space, you should consider using uClibc-ng.  If you are building a
huge fileserver with 12 Terabytes of storage, then using glibc may make more
sense.  Unless, for example, that 12 Terabytes will be Network Attached Storage
and you plan to burn Linux into the system's firmware...

uClibc-ng is maintained by Waldemar Brodkorb and is licensed under the GNU
LESSER GENERAL PUBLIC LICENSE. This license allows you to make closed source
commercial applications using an unmodified version of uClibc-ng. You do not
need to give away all your source code just because you use uClibc-ng and/or
run on Linux. You should, however, carefuly review the license and make certain
you understand and abide by it strictly.

For installation instructions, see the file INSTALL.

uClibc-ng strives to be standards compliant, which means that most
documentation written for SuSv3, or for glibc also applies to uClibc-ng
functions.  However, many GNU extensions are not supported because they have
not been ported, or more importantly, would increase the size of uClibc-ng
disproportional to the added functionality.

Additional information can be found at https://uclibc-ng.org/.

uClibc-ng may be freely modified and distributed under the terms of the GNU
Lesser General Public License, which can be found in the file COPYING.LIB.

And most of all, be sure to have some fun! :-)
 -Waldemar
