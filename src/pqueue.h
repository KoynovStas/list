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





#endif // PQUEUE_H
