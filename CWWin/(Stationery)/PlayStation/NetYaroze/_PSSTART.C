/*
 *	_psstart.c	- Startup Routine for the Sony PlayStation
 *
 *	Copyright © 1996 metrowerks inc. All Rights Reserved.
 *
 */

/************************************************************/
/*															*/
/* This file must be the first file in the project.			*/
/*															*/
/************************************************************/
 
extern void main();
extern void InitHeap();

#ifdef __cplusplus
extern "C" void __start(void);
#else
asm void __start(void);
#endif

asm void __start(void) 
{
	.set	reorder
	
	/* Initialize all the registers to 0*/
	move	t0,zero
	move	v0,t0
	move	v1,t0
	
	move	a0,t0
	move	a1,t0
	move	a2,t0
	move	a3,t0

	move	t1,t0
	move	t2,t0
	move	t3,t0
	move	t4,t0
	move	t5,t0
	move	t6,t0
	move	t7,t0
	move	t8,t0
	move	t9,t0
	
	move	s1,t0
	move	s1,t0
	move	s2,t0
	move	s3,t0
	move	s4,t0
	move	s5,t0
	move	s6,t0
	move	s7,t0
	move	fp,t0	// s8

	move	k0,t0
	move	k1,t0

	/* Initialize sp										*/
	li		sp,_stack_addr
	
	/* Set the global pointer.  _gp is know by the 			*/
	/* linker and the assembler								*/
	li		gp,_gp	
	
    /* Initialize the .sbss and the .bss sections to 0              */
    li      t0,_sbss_addr   /* .sbss address                        */
    li      t1,_sbss_size   /* .sbss size                           */
L2:
    beq     t1,0,L1         /* size is a word size                  */
    sw      zero,0(t0)
    addiu   t0,t0,4
    addiu   t1,t1,-4
    b       L2
L1:

    li       t0,_bss_addr    /* .bss address                        */
    li       t1,_bss_size    /* .bss size                           */
L3:
    beq      t1,0,L4         /* size is a word size                 */
    sw       zero,0(t0)
    addiu    t0,t0,4
    addiu    t1,t1,-4
    b        L3
L4:

	/* initialize the heap to the area between the end of .bss & bottom of stack */
	li		a0,_bss_addr
	li		at,_bss_size
	addu	a0,a0,at		/* calculate end of .bss section */

	addi	a0,a0,15		/* round up to even multiple of 16 */
	addiu	at,zero,-16
	and		a0,a0,at

	li		a1,_stack_addr
	li		at,_stack_size
	sll		at,at,10
	subu	a1,a1,at		/* calculate bottom of stack */
	subu	a1,a1,a0		/* find distance from top of .bss to bottom of stack */

	jal		InitHeap		/* call InitHeap to set it up */
	nop

#ifdef __cplusplus
	/* For C++, calls all the static initializers			*/
	la		t0,__static_init
	jalr	ra,t0
#endif

	/* last but not least, set up for co-pro 2 */
	mfc0	t0,12
	lui		t1,0x4000
	or		t0,t0,t1
	mtc0	t0,12

	/* Call the main program								*/
	la		t0,main
	jalr	ra,t0
	nop

	/* terminate the program with a special break instruction */
	breakc	0x8201
	nop
}
