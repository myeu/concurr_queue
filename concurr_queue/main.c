//
//  main.c
//  concurr_queue
//
//  Created by Marisa Yeung on 10/7/14.
//  Copyright (c) 2014 Marisa Yeung. All rights reserved.
//

#include <stdio.h>
#include "c_queue.c"

void *producer(void *ptr)
{
    
    return NULL;
}

void *consumer(void *ptr)
{
    int d = 0;
    
    
    
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
    
    pthread_t threads[n_thread];
    
    for (int i = 0; i < n_thread; ++i) {
        if (pthread_create(&threads[i], NULL, &producer, NULL)) {
            printf("Could not create threads\n");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

