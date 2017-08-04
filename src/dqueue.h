/*
 * dqueue.h
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

#ifndef DQUEUE_H
#define DQUEUE_H

#include "dlist.h"





typedef struct dlist_head dqueue_node;



struct dqueue_t
{
    struct dlist_head head;
    size_t            size;
};





#define INIT_DQUEUE(name) { { &(name.head), &(name.head) }, 0 }

#define DECLARE_DQUEUE(name) \
    struct dqueue_t name = INIT_DQUEUE(name)



#define INIT_DQUEUE_NODE(name) { &(name), &(name) }

#define DECLARE_DQUEUE_NODE(name) \
    dqueue_node name = INIT_DQUEUE_NODE(name)





static inline void dqueue_init(struct dqueue_t *dqueue)
{
    dlist_init_head(&dqueue->head);
    dqueue->size = 0;
}



static inline void dqueue_init_node(dqueue_node *node)
{
    dlist_init_head(node);
}



/*
 * dqueue_empty - tests whether a dqueue is empty
 *
 * dqueue: the dqueue to test.
 *
 * ret: true  //if the container size is 0
 * ret: false //otherwise.
 */
static inline int dqueue_empty(struct dqueue_t *dqueue)
{
    return dlist_empty(&dqueue->head);
}



/*
 * dqueue_is_first - tests whether node is the first node in dqueue
 *
 * node: the node to test
 * dqueue: the dqueue
 *
 *  ret: true   // if [...] <-> [head] <-> [node] <-> [...]
 *  ret: false  // else
 */
static inline int dqueue_is_first(const dqueue_node *node,
                                  const struct dqueue_t *dqueue)
{
    return node == dqueue->head.next;
}



/*
 * dqueue_is_last - tests whether node is the last node in dqueue
 *
 * node: the node to test
 * dqueue: the dqueue
 *
 *  ret: true   // if [...] <-> [node] <-> [head] <-> [...]
 *  ret: false  // else
 */
static inline int dqueue_is_last(const dqueue_node *node,
                                 const struct dqueue_t *dqueue)
{
    return node == dqueue->head.prev;
}





#endif // DQUEUE_H
