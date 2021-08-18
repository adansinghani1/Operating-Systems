#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

struct birthday
{
   char *name;
   int nameLength;
   char *gender;
   int month;
   int day;
   int year;
    struct list_head list;

};

/**
 * The following defines and initializes a list_head object named birthday_list
 */
static LIST_HEAD(birthday_list);

_Bool compare_birthday(const struct birthday *b1, const struct birthday *b2){
    return (b1->nameLength > b2->nameLength) && (b1->year < b2->year) && (b1->month < b2->month)
    && (b1->day < b2->day);
}

int simple_init(void)
{
	int simple_init(void)
{
	struct birthday *person;
	struct birthday *head;
	printk(KERN_INFO "Loading Module\n");

	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->name = "Marques";
	person->nameLength = 7;
	person->gender = "Male";
	person->month = 1;
	person->day = 2;
	person->year= 2000;
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);
	head = person;

	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->name = "Nate";
	person->nameLength = 4;
	person->gender = "Male";
	person->month = 2;
	person->day = 24;
	person->year= 1999;
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);

	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->name = "Charlie";
	person->nameLength = 7;
	person->gender = "Female";
	person->month = 1;
	person->day = 17;
	person->year= 1999;
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);

	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->name = "Serena";
	person->nameLength = 6;
	person->gender = "Female";
	person->month = 6;
	person->day = 1;
	person->year= 2001;
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);

	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->name = "Elice";
	person->nameLength = 5;
	person->gender = "Female";
	person->month = 8;
	person->day = 9;
	person->year= 1999;
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);


	struct birthday *ptr;
	list_for_each_entry(ptr, &birthday_list, list){
	printk(KERN_INFO "Name: %s nameLength: %d Gender: %s Birthday: Month: %d Day: %d Year: %d \n", ptr->name, ptr->nameLength, ptr->gender, ptr->month, ptr->day, ptr->year);
	}

	//finding a female with the longest name

  struct birthday *oldestfemale = head;
    _Bool check;
    list_for_each_entry(ptr, &birthday_list, list){
        check = compare_birthday(ptr, oldestfemale;
        if (check && ptr->gender == "Female")
            oldestfemale = ptr;
    }

    list_del(&oldestfemale->list);
    kfree(oldestfemale);

        // Printing updated list
    printk(KERN_INFO "Deleted the female with the longest name. Updated list is here:");    list_for_each_entry(ptr, &birthday_list, list){
        printk(KERN_INFO "Name: %s nameLength: %d Birthday: %d/%d/%d\n", ptr->name, ptr->nameLength, ptr->month, ptr->day, ptr->year);
    }

       return 0;

}



void simple_exit(void) {

	printk(KERN_INFO "Removing Module\n");
	struct birthday *ptr, *next;
	list_for_each_entry_safe(ptr,next,&birthday_list,list){
	printk(KERN_INFO "Removing %s %d %s %d/%d/%d \n",  ptr->name, ptr->nameLength, ptr->gender, ptr->month, ptr->day, ptr->year);




}
}



module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernel Data Structures");
MODULE_AUTHOR("SGG");
