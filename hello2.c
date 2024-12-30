#include "hello1.h"
#include <linux/ktime.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YAROSLAV");
MODULE_DESCRIPTION("Hello world module 2");
MODULE_VERSION("0.02");
MODULE_PARM_DESC(param, "amount of repeats of HELLO WORLD!\n");

uint param = 1;
module_param(param, uint, 0754);

static int __init hello_init(void)
{
	if (param >= 5 & param <= 10) {
	pr_warn("PARAMETER BETWEEN 5 AND 10\n");
	};
	if (param == 0) {
	pr_warn("PARAMETER EQUALS 0\n");
	}
	BUG_ON(param>10);
    ktime_t b_temp, a_temp;
    int i;
    for (i = 0; i < param; i++) {
        b_temp=ktime_get();
        hello_print(param);
        a_temp=ktime_get();
        add_elem(b_temp,a_temp);
	}
	return 0;
}

static void __exit hello_exit(void){
}

module_init(hello_init);
module_exit(hello_exit);