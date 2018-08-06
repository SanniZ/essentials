#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct list {
	int id;
	char name[8];

	struct list *last;        
	struct list *next;
} list_t;


typedef struct list_header {
	int total_num;
	int next_serial_index;

	list_t *list;
} list_header_t;

list_header_t * list_init_header(void) {
	list_header_t *head = malloc(sizeof(list_header_t));
	if (!head) {
		printf("list_init_header(): error, invalid input\n");
		return NULL;
	}

	memset(head, 0, sizeof(list_header_t));
	head->total_num = 0;
	head->next_serial_index = 1;
	head->list = NULL;

	return head;
}


list_t* list_calloc(void){
	list_t *ptr = malloc(sizeof(list_t));
	if (ptr == NULL) {
		printf("list_calloc(): error, malloc failed.\n");
		return NULL;
	}

	memset(ptr, 0, sizeof(list_t));
	ptr->id = -1;
	memset(ptr->name, 0, sizeof(ptr->name));
	ptr->last = NULL;
	ptr->next = NULL;

	return ptr;
}

int list_add(list_header_t *head, char *name) {
	list_t *ptr;

	if (!head) {
		printf("list_add(): error, invalid input\n");
		return -1;
	}

	if (!head->list) {
		head->list = list_calloc();
		ptr = head->list;
	} else {
		// get tail of list.
		ptr = head->list;
		while(ptr) {
			if (ptr->next) {
				ptr = ptr->next;;
			} else {
				break;
			}
		}		
        	ptr->next = list_calloc();
		ptr->next->last = ptr;
		ptr = ptr->next;
	}

	ptr->id = head->next_serial_index;
	memcpy(ptr->name, name, sizeof(ptr->name));

	head->next_serial_index++;
	head->total_num++;

	return 0;
}

int list_del(list_header_t *head, int id) {
	list_t *ptr;

	if (!head || !head->list) {
		printf("list_del(): error, invalid input.\n");
		return -1;
	}

	// get tail of list.
	ptr = head->list;
	while(ptr) {
		if (ptr->id == id) {
			if (id == 1) { // it is head of list.
				head->list = ptr->next;
				head->list->last = NULL;
			} else {
				ptr->last->next = ptr->next;
			}

			head->total_num--;
			free(ptr);
			break;
		}

		ptr = ptr->next;
	}

	return 0;
}

int list_update(list_header_t *head, int id, char *name) {
	list_t *ptr, *last;

	if (!head || !head->list) {
		printf("list_del(): error, invalid input.\n");
		return -1;
	}

	// get tail of list.
	ptr = head->list;
	while(ptr) {
		if (ptr->id == id) {
			memcpy(ptr->name, name, sizeof(ptr->name));
			break;
		}

		ptr = ptr->next;
	}

	return 0;
}

void list_print(list_header_t *head) {
	list_t *list = head->list;

	while(list) {
		printf("[%d]: %s\n", list->id, list->name);
		list = list->next;
	}
	printf("total_num=%d\n", head->total_num);
}

void list_free(list_header_t *head) {
	list_t *list = head->list, *next;

	while(list) {
		next = list->next;
		free(list);
		list = next;
	}

	free(head);
}

int main(int argc, char *args[]) {
	list_header_t *head =  list_init_header();
	if (!head) {
		printf("error, failed to init list header!\n");
		return -1;
	}

	printf("------Add to list-------.\n");
	list_add(head, "Wang");
	list_add(head, "Huang");
	list_add(head, "Hu");
	list_add(head, "Li");
	list_print(head);

	printf("-----del index of 3------.\n");
	list_del(head, 3);
	list_print(head);

	printf("-----Add new index-------.\n");
	list_add(head, "Deng");
	list_print(head);

	printf("-----update index of 4-----.\n");
	list_update(head, 4, "Zhang");
	list_print(head);

	printf("-----del index of 1------.\n");
	list_del(head, 1);
	list_print(head);

	list_free(head);
}


