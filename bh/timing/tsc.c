#ifndef __KERNEL__
	#define __KERNEL__
#endif

#ifndef MODULE
	#define MODULE
#endif

#define EXPORT_SYMTAB
#define SUCCESS 0

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <asm/msr.h>
uint64_t rdtsc(void);
int myinit(void);
void myexit(void);

uint64_t rdtsc(void) {
uint32_t lo, hi;
/* We cannot use "=A", since this would use %rax on x86_64 */
__asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
printk("\n high=%ld low=%ld",(unsigned long)hi,(unsigned long)lo);
return (uint64_t)hi << 32 | lo;
}

/* entry point */
int myinit(void)
{
	printk("\n Module Inserted\n");
        printk("\n rdtsc() == %llu\n", (unsigned long long)rdtsc());
	return SUCCESS;
}

/* exit point */
void myexit(void)
{
	printk("\n rdtsc() == %llu\n", (unsigned long long)rdtsc());
	printk("\n Module Removed\n");
}


MODULE_AUTHOR("Soctel");
MODULE_DESCRIPTION("Example");
MODULE_LICENSE("GPL");
module_init(myinit);
module_exit(myexit);
