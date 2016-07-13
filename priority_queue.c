#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * min heap
 */

#define DEFAULT_CAPACITY 50
/* 
 * return 1, if first > second
 * return 0, if first = second
 * return -1, if first < second
 */
typedef int (*COMPAR)(void *, void *);
typedef struct priority_queue priority_queue;

struct priority_queue {
	size_t capacity;
	size_t size;
	char **data;
	int (*compar)(void *, void *);
};

priority_queue *create_priority_queue(COMPAR compar) {
    priority_queue *pq = (priority_queue *) malloc(sizeof(priority_queue));
    pq->capacity = DEFAULT_CAPACITY;
    pq->size = 0;
    pq->data = (char **)malloc(sizeof(char *) * (pq->capacity + 1));
    pq->compar = compar;
    return pq;
}

void flow_down(priority_queue *pq, size_t index) {
    if(index > pq->size || index * 2 > pq->size) return;
    size_t t = index * 2;
    if(t + 1 < pq->size) {
        if(pq->compar(pq->data[t], pq->data[t+1]) > 0)
            t += 1;
    }
    if(pq->compar(pq->data[index], pq->data[t]) > 0) {
        char *tmp = pq->data[index];
        pq->data[index] = pq->data[t];
        pq->data[t] = tmp;
        flow_down(pq, t);
    }
}

void flow_up(priority_queue *pq, size_t index) {
    if(index > 1 && pq->compar(pq->data[index], pq->data[index/2]) < 0) {
        char *tmp = pq->data[index];
        pq->data[index] = pq->data[index/2];
        pq->data[index/2] = tmp;
        flow_up(pq, index/2);
    }
}

void priority_queue_insert(priority_queue *pq, void *e) {
    if(pq->size >= pq->capacity) {
        pq->capacity = pq->capacity * 2 + 1;
        char **new_data = (char **) malloc(sizeof(char *) * pq->capacity);
        memcpy(new_data+1, pq->data+1, sizeof(char *) * pq->size);
        free(pq->data);
        pq->data = new_data;
    }

    pq->size += 1;
    pq->data[pq->size] = (char *) e;
    flow_up(pq, pq->size);
}

void* priority_queue_delete_min(priority_queue *pq) {
    if(pq->size <= 0) return NULL;
    void *result = pq->data[0];
    if(--pq->size > 0) {
        pq->data[0] = pq->data[pq->size];
        flow_down(pq, 0);
    }
    return result;
}
