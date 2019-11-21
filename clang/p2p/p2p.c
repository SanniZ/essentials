#include <stdio.h>
#include <stdlib.h>

struct stu_test {
    int id;
    int val;
};

int malloc_test(struct stu_test **ptr) {
    struct stu_test *p = malloc(sizeof(struct stu_test));
    p->id = 1;
    p->val = 880;
 
    *ptr = p;
}

int main() {
    struct stu_test *stu = NULL;

    malloc_test(&stu);
    if (stu) {
        printf("stu.id=%d\n", stu->id);
        printf("stu.val=%d\n", stu->val);
        free(stu);
    } else {
        printf("stu is NULL\n");
    }
}
