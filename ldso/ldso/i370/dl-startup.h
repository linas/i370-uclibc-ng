/*
 * Architecture specific code used by dl-startup.c
 */

/* Why is this here, instead of some *.S file ? */
__asm__(
    " .section .text\n"
    ".globl   _start\n"
    " .type _start,@function\n"
    " .balign 4\n"
    "_start:\n"
    " BASR    r6,0\n"              /* Figure out where we are. */
    " .using .,r6\n"               /* Establish addressing. */
    " ST      r1,0(r11)\n"         /* r1 holds SP, r11 holds FP. */
    " L       r15,=V(_dl_start)\n"
    " BASR    r14,r15\n"           /* Perform relocation. */

/* TODO: I guess 0(r11) should be _GLOBAL_OFFSET_TABLE_ ?? */
    " L       r2,0(r2)\n"          /* Get value of argc. */
    " ST      r2,92(,r11)\n"       /* Pass argc on stack. */
    " ST      r3,96(,r11)\n"       /* Pass argv on stack. */
    " ST      r4,100(,r11)\n"      /* Pass envp on stack. */
    " ST      r5,104(,r11)\n"      /* Something something aux vector. */
    " BASR    r14,r15\n"           /* r15 now holds relocated main()\n. */

/* TODO: call _dl_fini */

    " .ltorg\n"
    " .size _start,.-_start\n"
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
