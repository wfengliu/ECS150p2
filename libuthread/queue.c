#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

typedef struct qnode
{
	void *val;
	struct qnode *next;
} QNode;

typedef struct queue
{
	int count;
	QNode *head;
	QNode *tail;
} Queue;

queue_t queue_create(void)
{
	Queue *new_list;
	new_list = malloc(sizeof(Queue));

	if (new_list == NULL)
		return NULL;

	new_list->count = 0;
	new_list->head = NULL;
	new_list->tail = NULL;

	return new_list;
}

int queue_isempty(queue_t queue)
{
	if(queue->head == NULL && queue->tail == NULL)
		return 1;
	else
		return 0;
}

int queue_destroy(queue_t queue)
{
	if (queue == NULL || queue_isempty(queue))
		return -1;

	QNode *destroyNode;
	void *vptr = NULL;
	while (!queue_isempty(queue))
	{
		destroyNode = queue->head;
		queue_dequeue(queue, vptr);
		free(destroyNode);
	}

	free(queue);

	return 0;
}

int queue_enqueue(queue_t queue, void *data)
{
	QNode *new_node = malloc(sizeof(QNode));
	if (queue == NULL || data == NULL || new_node == NULL)
		return -1;

	new_node->val = data;
	new_node->next = NULL;

	if (queue_isempty(queue))
		queue->head = queue->tail = new_node;
	else
	{
		queue->tail->next = new_node;
		queue->tail = new_node;
	}
	queue->count++;

	return 0;
}

int queue_dequeue(queue_t queue, void **data)
{
	if (queue == NULL || data == NULL || queue_isempty(queue))
		return -1;
	
	if (queue->count == 1) {
		queue->tail = NULL;
	}

	*data = queue->head->val; 
	queue->head = queue->head->next;
	queue->count--;
	return 0;
}

int queue_delete(queue_t queue, void *data)
{
	if(queue == NULL || data == NULL)
		return -1;
	
	QNode *pre = NULL;
	QNode *walk = queue->head;
	while (walk != NULL) {
		if (walk->val == data) { 

			if (pre == NULL) { 
				queue->head = walk->next;
				queue->tail = NULL;
			}
			else if (walk->next == NULL) { 
				queue->tail = pre;
			}
			else {
				pre->next = walk->next;
			}
			queue->count--;
			return 0;
		} 
		pre = walk;
		walk = walk->next;
	}

	return -1;
}

int queue_iterate(queue_t queue, queue_func_t func)
{
	/* TODO Phase 1 */

	if (queue == NULL || func == NULL || queue_isempty(queue))
		return -1;

	QNode *walk = queue->head;
	while (walk != NULL) {
		QNode* checkNext = walk->next;
		func(queue, walk->val);
		walk = checkNext;
	}

	return 0;
}