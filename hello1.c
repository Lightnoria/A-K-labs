#include "hello1.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YAROSLAV");
MODULE_DESCRIPTION("Hello world module 1");
MODULE_VERSION("0.02");

struct occur_list{
	struct list_head list;
	ktime_t time_before;
    ktime_t time_after;
};
static LIST_HEAD(occ_list);
struct occur_list *list_node;
int num = 0;

void hello_print(int param){
	pr_info("Hello World!\n");
}

int add_elem(ktime_t before, ktime_t after){
    list_node = kmalloc(sizeof(*list_node), GFP_KERNEL);
	if (!list_node) {
		pr_info("MEMORY ALLOCATION ERROR!\n");
		return -ENOMEM;
	}
	list_node->time_before = before;
    list_node->time_after = after;
	INIT_LIST_HEAD(&list_node->list);
	list_add_tail(&list_node->list, &occ_list);
	num++;
	if(num==5){
		pr_err("начебто kmalloc() повернув 0");
		BUG();
	}
    return 0;
}

EXPORT_SYMBOL(hello_print);
EXPORT_SYMBOL(add_elem);

static void __exit hello_exit(void)
{
	printk(KERN_INFO "Goodbye world!\n");
	struct occur_list *tmp, *node;
	list_for_each_entry_safe(node, tmp, &occ_list, list) {
	pr_info("Time: %d\n", node->time_after - node->time_before);
	list_del(&node->list);
	kfree(node);
	}
}

module_exit(hello_exit);
