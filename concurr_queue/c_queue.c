//
//  c_queue.c
//  concurrancy queue
//
//  Created by Marisa Yeung on 10/7/14.
//  Copyright (c) 2014 Marisa Yeung. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "list.h"

typedef struct queue_t
{
    list_t *list;
    //int max;
    pthread_mutex_t lock;
    pthread_cond_t notfull;
    pthread_cond_t notempty;
    
} queue_t;

void enqueue(queue_t *q, void* data)
{
    lnode_t *n = lnode_create(data);
    
    pthread_mutex_lock(&q->lock);
    
    if (list_isfull(q->list)) {
        pthread_cond_wait(&q->notfull, &q->lock);
    }
    
    if (list_isempty(q->list)) {
        list_append(q->list, n);
        pthread_cond_broadcast(&q->notempty);
    }
    
    pthread_mutex_unlock(&q->lock);
}

void* dequeue(queue_t *q)
{
    lnode_t *n;
    pthread_mutex_lock(&q->lock);
    
    if (list_isempty(q->list)) {
        pthread_cond_wait(&q->notempty, &q->lock);
    }
    
    if (list_isfull(q->list)) {
        n = list_del_first(q->list);
        pthread_cond_broadcast(&q->notfull);
    }
    else {
        n = list_del_first(q->list);
    }
    
    pthread_mutex_unlock(&q->lock);
    
    return lnode_get(n);
}

queue_t* init_queue(int max)
{
    queue_t *q;
    list_t *list = list_create(max);
    q->list = list;
    
    //q->max = max;
    
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->notfull, NULL);
    pthread_cond_init(&q->notempty, NULL);
    
    return q;
}

/*
 *
 */
void destroy_queue(queue_t *q)
{
    //note, list_destroy never calls free(node->data)
    list_destroy_nodes(q->list);
    list_destroy(q->list);
    q->list = NULL;
    pthread_cond_destroy(&q->notfull);
    pthread_cond_destroy(&q->notempty);
    pthread_mutex_destroy(&q->lock);
}
