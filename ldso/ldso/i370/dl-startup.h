/*
 * Architecture specific code used by dl-startup.c
 */

/* Why is this here, instead of some *.S file ? */

/* Below is an attempt, but it doesn't make it out the gates
   because ... I'm lazy.

   The core issue is that PIC code with the current i370 ABI uses
   not one, but two base registers: one for the text segment, so that
   branch targets can be computed as offsets, and another, for the
   data segment, where the literal pool and the page table reside.
   This makes the text segment position independent, while all the
   relocation targets reside in the pool (thus making the text segment
   shareable, whereas each instance gets its own copy of the pool.)

   Its easy to find out where one is loaded: just have _start issue
   BASR rN,0 and rN now holds the current address. If _start is in the
   .text segment, then we know where everything else is in the text
   segment, e.g. by computing the relative address _dlstart - . and
   adding it to the BASR result. We can jump to it. Great!  But then,
   where is the pool?

   Alternately, put _start in the .data segment, issue BASR and now
   we know where the .data segment got loaded (and so we know where
   the pools are, e.g. by computing the relative address
   _dl_start$pool - . Great! But where's the text sgement?

   There's two ways to solve this. One is to walk the .dynsym section
   in assembly code, right here, and search for _dl_start$pool. Yuck.
   (At least one of the other arches does this.) The search cannot be
   done in C code because the C code will inevitably use the pool,
   whose address we don't know. Not much is needed: only the addr of
   _dl_start$pool as a minimum, and may as well get _dl_start$pgt
   and _dl_start$text since we're at it. Plug em into the plt stub
   and we're good to go.

   The other way to solve this requires a weird linker trick. This
   would place a copy of the pool in the text segment as well as in
   .data.pool. This will make all literals in the pool accessible to
   the C code; function addresses in the pool will be garbage, so
   function calls through it are not allowed. Then, hunt down the
   .data.pool section in C code, relocate it correctly, and then
   switch to using that, instead of the temporary .text pool. Maybe
   the -Bsymbolic flag in the linker could be used to set this up.

   The third solution is to revise the assembler to keep two literal
   pools: one for constants, since these never need relocation, and
   can safely live in the text sgement. The other pool would hold
   anything relocatable. This is perhaps the cleanest solution. Of
   course, on entry, the .daata.pool still needs to be relocated,
   just as it needs to be done in all three scenarios. But at least
   this avoids having to walk .dlsym in assembly.

   I didn't expect the Spanish Inquisition.
 */
__asm__(
    " .section .text\n"
    ".globl   _dl_start\n"
    ".globl   _start\n"
    " .type _start,@function\n"
    " .balign 4\n"
    "_start:\n"
    " BASR    r6,0\n"              /* Figure out where we are. */
    " .using .,r6\n"               /* Establish addressing. */
    " ST      r1,0(r11)\n"         /* r1 holds SP, r11 holds FP. */
    " L       r15,=A(_start_glue)\n"
    " BASR    r14,r15\n"           /* Perform relocation. */

/* TODO: I guess 0(r11) should be _GLOBAL_OFFSET_TABLE_ ?? */
    " L       r2,0(r2)\n"          /* Get value of argc. */
    " ST      r2,92(,r11)\n"       /* Pass argc on stack. */
    " ST      r3,96(,r11)\n"       /* Pass argv on stack. */
    " ST      r4,100(,r11)\n"      /* Pass envp on stack. */
    " ST      r5,104(,r11)\n"      /* Something something aux vector. */
    " BASR    r14,r15\n"           /* r15 now holds relocated main()\n. */

/* TODO: call _dl_fini */

    /* Create a fake stub, just enough to get to the C code. */
    ".globl   _dl_start$fent\n"
    ".globl   _dl_start$pool\n"
    ".globl   _dl_start$pgt\n"
    ".globl   _start_glue\n"
    " .type _start_glue,@function\n"
    " .balign 4\n"
    "_start_glue:\n"
    " L       r12,12(r15)\n"
    " BR      r12\n"
    " NOPR    0\n"
    " .long 0\n"
    " .long _dl_start$fent\n"
    " .long _dl_start$pool\n"
    " .long 512\n"                 /* Stack size. Unknown but large. */
    " .long _dl_start$pgt\n"

    " .ltorg\n"
    " .size _start,.-_start\n"
    " .size _start_glue,.-_start_glue\n"
    " .previous\n"
);


/* Get a pointer to the argv array.  On many platforms this can be just
 * the address of the first argument, on other platforms we need to
 * do something a little more subtle here.  */
#define GET_ARGV(ARGVP, ARGS) ARGVP = (((unsigned long *) ARGS)+1)


/* We can't call functions earlier in the dl startup process */
#define NO_FUNCS_BEFORE_BOOTSTRAP


/* Handle relocation of the symbols in the dynamic loader. */
static __always_inline
void PERFORM_BOOTSTRAP_RELOC(ELF_RELOC *rpnt, unsigned long *reloc_addr,
	unsigned long symbol_addr, unsigned long load_addr, Elf32_Sym *symtab)
{
	switch (ELF_R_TYPE(rpnt->r_info)) {
		case R_I370_ADDR31:
			*reloc_addr = symbol_addr;
			break;
		case R_I370_NONE:
			break;
		case R_I370_RELATIVE:
			*reloc_addr = load_addr + rpnt->r_addend;
			break;
		default:
			_dl_exit(1);
			break;
	}
}
