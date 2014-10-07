//
//  c_queue.c
//  concurr_queue
//
//  Created by Marisa Yeung on 10/7/14.
//  Copyright (c) 2014 Marisa Yeung. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "list.c"

typedef struct queue_t
{
    list_t list;
    pthread_mutex_t lock;
    pthread_cond_t isfull;
    pthread_cond_t isempty;
} queue_t;

void enqueue(queue_t q, void* data)
{
    
}