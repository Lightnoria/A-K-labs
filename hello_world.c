#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/ktime.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("YAROSLAV");
MODULE_DESCRIPTION("Hello world module");
MODULE_VERSION("0.01");
uint param = 1;
module_param(param, uint, 0754);
MODULE_PARM_DESC(param, "UINT: amount of repeats of HELLO WORLD!\n");

struct occur_list{
	struct list_head list;
	ktime_t time;
};
static LIST_HEAD(occ_list);

static int __init hello_init(void)
{
	struct occur_list *list_node;
	if (param >= 5 & param <= 10) {
	printk(KERN_WARNING "PARAMETER BETWEEN 5 AND 10\n");
	};
	if (param == 0) {
	printk(KERN_WARNING "PARAMETER EQUALS 0\n");
	}
	if (param > 10) {
		printk(KERN_ERR "PARAMETER MORE THAN 10\n");
		return -EINVAL;
	}
	int i;
	for (i = 0; i < param; i++) {
		list_node = kmalloc(sizeof(*list_node), GFP_KERNEL);
		if (!list_node) {
			printk(KERN_ERR "MEMORY ALLOCATION ERROR!\n");
			return -ENOMEM;
		}
		list_node->time = ktime_get();
		INIT_LIST_HEAD(&list_node->list);
		list_add_tail(&list_node->list, &occ_list);
		printk(KERN_INFO "Hello World!\n");
	}
	return 0;
}
static void __exit hello_exit(void)
{
	printk(KERN_INFO "Goodbye world!\n");
	struct occur_list *tmp, *node;
	list_for_each_entry_safe(node, tmp, &occ_list, list) {
	printk(KERN_INFO "%d\n", node->time);
	list_del(&node->list);
	kfree(node);
	}
}
module_init(hello_init);
module_exit(hello_exit);
