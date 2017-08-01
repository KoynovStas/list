/*
 * pqueue.h
 *
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2017, Koynov Stas - skojnov@yandex.ru
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PQUEUE_H
#define PQUEUE_H

#include <stdlib.h>
#include "spqueue.h"





/*
 *  A priority queue is a container that provides constant time lookup
 *  of the largest or smallest (see compare function) element,
 *  at the expense of logarithmic insertion and extraction.
 *
 *  pqueue_t - priority queue based on dynamic array (standart binary heap)
 *
 *
 *  Algorithmic complexity:
 *
 *  pqueue_size    -   O(1)
 *  pqueue_top     -   O(1)
 *  pqueue_pop     -   O(ln(n))
 *  pqueue_push    -   O(ln(n))
 *  pqueue_swap    -   O(1)
 */





struct pqueue_t
{
    void          **items;
    size_t          size;
    size_t          capacity;
    pqueue_cmp_func cmp_func; // <= for min heap, >= for max heap
    size_t          inc_step; // increment step for malloc (see insert func)
};



/*
 * pqueue_init - init the priority queue.
 *
 * pqueue:   the priority queue for work.
 * inc_step: increment step for realloc in push func (if == 0 realloc dont call)
 * capacity: current capacity of queue
 * cmp_func: compare function for work heap
 *
 * ret: -1    //if cant get memory
 * ret: 0     //good job. the priority queue was init.
 */
static inline int pqueue_init(struct pqueue_t *pqueue, size_t inc_step,
                              size_t capacity, pqueue_cmp_func cmp_func)
{

    pqueue->items = malloc(capacity*sizeof(void *));
    if( !pqueue->items )
        return -1; // fuck cant get memory


    pqueue->size     = 0;
    pqueue->capacity = capacity;
    pqueue->cmp_func = cmp_func;
    pqueue->inc_step = inc_step;

    return 0; //good job
}



/*
 * pqueue_push - Pushes the given element item to the priority queue.
 * If the priority queue is full and pqueue->inc_step != 0 will be call realloc
 * function for get memory.
 *
 *
 * pqueue: the priority queue for work.
 * item:   the item for push
 *
 * ret: -1    //if pqueue is full and cant push
 * ret: 0     //good job. item was pushed to the priority queue.
 */
static inline int pqueue_push(struct pqueue_t *pqueue, void *item)
{
    if( (pqueue->size >= pqueue->capacity) && pqueue->inc_step )
    {
        size_t new_capacity = pqueue->capacity + pqueue->inc_step;
        void* tmp = realloc(pqueue->items, new_capacity*sizeof(void *));

        if(!tmp)
            return -1; //cant get memory


        pqueue->items    = tmp;
        pqueue->capacity = new_capacity;
    }


    return spqueue_push((struct spqueue_t *)pqueue, item);
}


/*
 * pqueue_top - Returns reference to the top element in the priority queue.
 * This element will be removed on a call to pop().
 *
 * pqueue: the priority queue for work.
 *
 * ret: NULL   //if pqueue is empty
 * ret: *Item  //good job ret top item.
 */
static inline void* pqueue_top(struct pqueue_t *pqueue)
{
    return spqueue_top((struct spqueue_t *)pqueue);
}



/*
 * pqueue_pop - Removes the top element from the priority queue.
 *
 * pqueue: the priority queue for work.
 */
static inline void pqueue_pop(struct pqueue_t *pqueue)
{
    spqueue_pop((struct spqueue_t *)pqueue);
}



/*
 * pqueue_swap - Exchanges the contents of the containers pqueue1 and pqueue2
 *
 * pqueue1/2: the priority queues for work.
 */
static inline void pqueue_swap(struct pqueue_t *pqueue1, struct pqueue_t *pqueue2)
{
    struct pqueue_t tmp = *pqueue1;
    *pqueue1            = *pqueue2;
    *pqueue2            = tmp;
}





#endif // PQUEUE_H
