//
//  main.c
//  concurr_queue
//
//  Created by Marisa Yeung on 10/7/14.
//  Copyright (c) 2014 Marisa Yeung. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "c_queue.c"

#define MAX 10

queue_t *q;

void *producer(void *ptr)
{
    for (long i = 1; i < 20; i++)
    {
        enqueue(q, (void *) i);
    }
    
    return NULL;
}

void *consumer(void *ptr)
{
    long d = 0;
    
    for (int i = 1; i < 20; i++)
    {
        d = (long) dequeue(q);
    }
    
    return NULL;
}


int main(int argc, const char * argv[])
{
    // Check input args
	if (argc != 1)
    {
		printf("Usage: %s <num threads>\n",
               argv[0]);
		exit(EXIT_FAILURE);
	}
    
    int n_thread = atoi(argv[1]);
    
    q = init_queue(10);
    
    pthread_t threads[n_thread];
    
    for (int i = 0; i < n_thread; ++i) {
        if ((i % 2) == 0) {
            if (pthread_create(&threads[i], NULL, &producer, NULL)) {
                printf("Could not create threads\n");
                exit(EXIT_FAILURE);
            }
        }
        else {
            if (pthread_create(&threads[i], NULL, &consumer, NULL)) {
                printf("Could not create threads\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    
    for (int i = 0; i < n_thread; ++i) {
        if (pthread_join(threads[i], NULL)) {
            printf("Could not join threads\n");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

