#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/ktime.h>

extern void hello_print(int param);
extern int add_elem(ktime_t before, ktime_t after);
