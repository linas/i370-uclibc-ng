/*
 * Various assembly language/system dependent hacks that are required
 * so that we can minimize the amount of platform specific code.
 */

/* Define this if the system uses RELOCA.  */
#define ELF_USES_RELOCA
#include <elf.h>

/* Here we define the magic numbers that this dynamic loader should accept */
#define MAGIC1 EM_SH
#undef  MAGIC2

/* Used for error messages */
#define ELF_TARGET "i370"

struct elf_resolve;
extern unsigned long _dl_linux_resolver(struct elf_resolve * tpnt, int reloc_entry);

#if 0
static __always_inline unsigned int
_dl_urem(unsigned int n, unsigned int base)
{
	return 0;
}
#endif

#define do_rem(result, n, base)     ((result) = _dl_urem((n), (base)))

/* ELF_RTYPE_CLASS_PLT iff TYPE describes relocation of a PLT entry or
   TLS variable, so undefined references should not be allowed to
   define the value.
   ELF_RTYPE_CLASS_NOCOPY iff TYPE should not be allowed to resolve to one
   of the main executable's symbols, as for a COPY reloc.  */
# define elf_machine_type_class(type) \
  ((((type) == R_SH_JMP_SLOT || (type) == R_SH_TLS_DTPMOD32		      \
     || (type) == R_SH_TLS_DTPOFF32 || (type) == R_SH_TLS_TPOFF32)	      \
    * ELF_RTYPE_CLASS_PLT)						      \
   | (((type) == R_SH_COPY) * ELF_RTYPE_CLASS_COPY))

/* Return the link-time address of _DYNAMIC.  Conveniently, this is the
   first element of the GOT.  This must be inlined in a function which
   uses global data.  */
static __always_inline Elf32_Addr __attribute__ ((unused))
elf_machine_dynamic (void)
{
	register Elf32_Addr *got;
	// __asm__ ("mov r12,%0" :"=r" (got));
	return *got;
}

/* Return the run-time load address of the shared object.  */
static __always_inline Elf32_Addr __attribute__ ((unused))
elf_machine_load_address (void)
{
	Elf32_Addr addr;
#if LATER
	__asm__ (""
	     : "=r" (addr) : : "r0", "r1", "r2");
#endif
	return addr;
}

static __always_inline void
elf_machine_relative (Elf32_Addr load_off, const Elf32_Addr rel_addr,
		      Elf32_Word relative_count)
{
	Elf32_Addr value;
	Elf32_Rela * rpnt = (void *)rel_addr;

	do {
		Elf32_Addr *const reloc_addr = (void *) (load_off + rpnt->r_offset);

		if (rpnt->r_addend)
			value = load_off + rpnt->r_addend;
		else {
			// COPY_UNALIGNED_WORD (reloc_addr, &value, (int) reloc_addr & 3);
			value += load_off;
		}
		// COPY_UNALIGNED_WORD (&value, reloc_addr, (int) reloc_addr & 3);
		rpnt++;
	} while (--relative_count);
// #undef COPY_UNALIGNED_WORD
}
