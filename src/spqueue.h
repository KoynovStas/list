/*
 * spqueue.h
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

#ifndef SPQUEUE_H
#define SPQUEUE_H

#include <stddef.h>





/*
 *  A priority queue is a container that provides constant time lookup
 *  of the largest or smallest (see compare function) element,
 *  at the expense of logarithmic insertion and extraction.
 *
 *  spqueue_t - static priority queue based on static array (standart binary heap)
 *
 *  Algorithmic complexity:
 *
 *  spqueue_size    -   O(1)
 *  spqueue_top     -   O(1)
 *  spqueue_pop     -   O(ln(n))
 *  spqueue_push    -   O(ln(n))
 *  spqueue_swap    -   O(1)
 */



typedef int (*pqueue_cmp_func)(void*, void*);



struct spqueue_t
{
    void          **items;
    size_t          size;
    size_t          capacity;
    pqueue_cmp_func cmp_func; // <= for min heap, >= for max heap
};



// Helpful Macros
#define PQUEUE_LEFT(i)   ((i<<1)+1)
#define PQUEUE_RIGHT(i)  ((i<<1)+2)
#define PQUEUE_PARENT(i) ((i-1)>>1)



#define DECLARE_SPQUEUE(name, capacity, cmp_func)    \
    void* pqueue_ ## name ## _items[capacity];       \
    struct spqueue_t name = { pqueue_ ## name ## _items, 0, capacity, cmp_func }





static inline void spqueue_init(struct spqueue_t *pqueue, void **items,
                                size_t capacity, pqueue_cmp_func cmp_func)
{
    pqueue->items    = items;
    pqueue->size     = 0;
    pqueue->capacity = capacity;
    pqueue->cmp_func = cmp_func;
}



static inline void spqueue_item_swap(struct spqueue_t *pqueue, size_t i, size_t j)
{
    void* tmp        = pqueue->items[i];
    pqueue->items[i] = pqueue->items[j];
    pqueue->items[j] = tmp;
}



static inline void spqueue_sift_down(struct spqueue_t *pqueue, size_t i)
{

    while(PQUEUE_LEFT(i) < pqueue->size)
    {
        size_t left  = PQUEUE_LEFT(i);
        size_t right = PQUEUE_RIGHT(i);
        size_t j     = left;

        if( (right < pqueue->size) && pqueue->cmp_func(pqueue->items[right], pqueue->items[left]) )
            j = right;

        if( pqueue->cmp_func(pqueue->items[i], pqueue->items[j]) )
            break;

        spqueue_item_swap(pqueue, i, j);

        i = j;
    }
}



static inline void spqueue_sift_up(struct spqueue_t *pqueue, size_t i)
{

    while( (i>0) && pqueue->cmp_func(pqueue->items[i], pqueue->items[PQUEUE_PARENT(i)]) )   // i == 0 is root
    {
        spqueue_item_swap(pqueue, i, PQUEUE_PARENT(i));
        i = PQUEUE_PARENT(i);
    }
}





#endif // SPQUEUE_H
