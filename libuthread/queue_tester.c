#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.c"

#define TEST_ASSERT(assert)				\
do {									\
	printf("ASSERT: " #assert " ... ");	\
	if (assert) {						\
		printf("PASS\n");				\
	} else	{							\
		printf("FAIL\n");				\
		exit(1);						\
	}									\
} while(0)

/* Create */
void test_create(void)
{
	fprintf(stderr, "*** TEST create ***\n");

	TEST_ASSERT(queue_create() != NULL);
}

void test_enqueue_dequeue(void)
{
	int data = 3, data2 = 4, data3 = 5, *ptr, result;
	queue_t q;
	
	fprintf(stderr, "\n*** TEST queue_dequeue ***\n");
	
	q = queue_create();
	
	fprintf(stderr, "\n*** TEST DEQUEUE ON EMPTY ***\n");
	result = queue_dequeue(q, (void**)&ptr);
	TEST_ASSERT(result == -1);
    TEST_ASSERT(q->count == 0);

    fprintf(stderr, "\n*** TEST ENQUEUE ON EMPTY ***\n");
	result = queue_enqueue(q, &data);
	TEST_ASSERT(q->count == 1);
	TEST_ASSERT(q->head->val == &data);
	TEST_ASSERT(q->tail->val == &data);

    fprintf(stderr, "\n*** TEST ENQUEUE ON ONE NODE ***\n");
    result = queue_enqueue(q, &data2);
	TEST_ASSERT(result == 0);
    TEST_ASSERT(q->count == 2);
    TEST_ASSERT(q->head->val == &data);
    TEST_ASSERT(q->tail->val == &data2);

    fprintf(stderr, "\n*** TEST ENQUEUE ON MULTIPLE ***\n");
    result = queue_enqueue(q, &data3);
	TEST_ASSERT(result == 0);
    TEST_ASSERT(q->count == 3);
    TEST_ASSERT(q->head->val == &data);
    TEST_ASSERT(q->tail->val == &data3);

    fprintf(stderr, "\n*** TEST DEQUEUE ON MULTIPLE ***\n");
    result = queue_dequeue(q, (void**)&ptr);
	TEST_ASSERT(result == 0);
    TEST_ASSERT(q->head->val == &data2);
    TEST_ASSERT(q->tail->val == &data3);
	TEST_ASSERT(q->count == 2);
    

    queue_dequeue(q, (void**)&ptr);
	
    fprintf(stderr, "\n*** TEST DEQUEUE ON ONE NODE ***\n");
    result = queue_dequeue(q, (void**)&ptr);
	TEST_ASSERT(result == 0);
	TEST_ASSERT(q->head == NULL);
	TEST_ASSERT(q->tail == NULL);
    TEST_ASSERT(q->count == 0);
    
}

void print_int(queue_t q, void *node_val)
{
	printf("%d ", *(int*)node_val);
}

void test_delete(void) {
	int data = 3, data2 = 4, data3 = 5, data4 = 6;
	int doesntExist = 7;
	queue_t q;

	q = queue_create();
	int result;

	fprintf(stderr, "\n*** TEST queue_delete EMPTY LIST***\n");
	result = queue_delete(q, &data);
	TEST_ASSERT(result == -1);
	TEST_ASSERT(q->count == 0);
	TEST_ASSERT(q->head == NULL);
	TEST_ASSERT(q->tail == NULL);

	fprintf(stderr, "\n*** TEST queue_enqueue NULL***\n");
	result = queue_delete(q, NULL);
	TEST_ASSERT(result == -1);
	TEST_ASSERT(q->count == 0);
	TEST_ASSERT(q->head == NULL);
	TEST_ASSERT(q->tail == NULL);
	
	queue_enqueue(q, &data);
	fprintf(stderr, "\n*** TEST queue_delete ONE-NODE LIST***\n");
	printf("queue before: ");
	queue_iterate(q, print_int); // print before
	result = queue_delete(q, &data);
	printf("\nqueue after: \n");
	queue_iterate(q, print_int); // print after
	TEST_ASSERT(result == 0);
	TEST_ASSERT(q->count == 0);
	TEST_ASSERT(q->head == NULL);
	TEST_ASSERT(q->tail == NULL);

	queue_enqueue(q, &data);
	queue_enqueue(q, &data2);
	queue_enqueue(q, &data3);
	queue_enqueue(q, &data4);

	fprintf(stderr, "\n*** TEST queue_delete MIDDLE NODE FROM MULTIPLE-NODE LIST***\n");
	printf("queue before: ");
	queue_iterate(q, print_int);
	printf("\n");
	TEST_ASSERT(q->count == 4);
	result = queue_delete(q, &data2);
	printf("queue after: ");
	queue_iterate(q, print_int);
	printf("\n"); 
	TEST_ASSERT(q->count == 3);

	fprintf(stderr, "\n*** TEST queue_delete HEAD NODE FROM MULTIPLE-NODE LIST***\n");
	printf("queue before: ");
	queue_iterate(q, print_int);
	printf("\n"); 
	TEST_ASSERT(q->count == 3);
	result = queue_delete(q, &data);
	printf("queue after: ");
	queue_iterate(q, print_int);
	printf("\n");
	TEST_ASSERT(q->count == 2);

	fprintf(stderr, "\n*** TEST queue_delete TAIL NODE FROM MULTIPLE-NODE LIST***\n");
	printf("queue before: ");
	queue_iterate(q, print_int);
	printf("\n"); 
	TEST_ASSERT(q->count == 2);
	result = queue_delete(q, &data4);
	printf("queue after: ");
	queue_iterate(q, print_int);
	printf("\n");
	TEST_ASSERT(q->count == 1);

	fprintf(stderr, "\n*** TEST queue_delete NONEXSISTING DATA***\n");
	result = queue_delete(q, &doesntExist);
	TEST_ASSERT(result == -1);
}

void increment(queue_t q, void *node_val) {
	printf("Before: %d\n", *(int*)node_val);
	*(int*)node_val += 1;
	printf("After: %d\n", *(int*)node_val);
}

void test_iterate(void) {
    int data = 3, data2 = 4, data3 = 5;
	queue_t q;
	q = queue_create();

	printf("\n*** TEST_ITERATE ON EMPTY LIST ***\n");
	int iter = queue_iterate(q, increment);
	TEST_ASSERT(iter == -1);

    queue_enqueue(q, &data);
    queue_enqueue(q, &data2);
	queue_enqueue(q, &data3);
	printf("\n*** TEST_ITERATE ON FUNCTION INCREMENT ***\n");
    iter = queue_iterate(q, increment);
	TEST_ASSERT(iter == 0);
}

void test_destroy() {
    int data = 3;
    int data2 = 4;
    queue_t q;

	q = queue_create();
	printf("\n***TEST_DESTROY ON EMPTY LIST***\n");
	int des = queue_destroy(q);
	TEST_ASSERT(des == -1);

	printf("\n***TEST_DESTROY ON MULTIPLE NODES***\n");
    queue_enqueue(q, &data);
    queue_enqueue(q, &data2);
    des = queue_destroy(q);

    TEST_ASSERT(des == 0);
}

int main(void)
{
	//test_create();
	//test_enqueue_dequeue();
	//test_delete();
	//test_iterate();
	test_destroy();
    
	
	return 0;
}
