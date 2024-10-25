/* The i370 arch is a 32-bit arch. */
#define __WORDSIZE 32

/* The currently available compilers for i370 are gcc-3.2.3 and
 * gcc-3.4.6 and the open watcom compiler. The gcc's, at least,
 * do not have a built-in `true` keyword. It's not in C90, at least.
 */
#if (defined __GNUC__  && __GNUC__ < 4)
#define true 1
#endif
