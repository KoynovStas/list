/*
 *  dlist.h
 *
 *
 *  Copyright (c) 2016, Koynov Stas - skojnov@yandex.ru
 *
 *  All rights reserved.
 *
 *
 *  BSD 3-Clause License:
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  * Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DLIST_HEADER
#define DLIST_HEADER


#include <stddef.h>





/*
 * Simple Circular doubly linked lists implementation.
 *
 */





struct dlist_head
{
    struct dlist_head *next;
    struct dlist_head *prev;
};





#define INIT_DLIST_HEAD(name) { &(name), &(name) }

#define DECLARE_DLIST_HEAD(name) \
    struct dlist_head name = INIT_DLIST_HEAD(name)



static inline void dlist_init_head(struct dlist_head *list)
{
    list->next = list;
    list->prev = list;
}



/*
 * dlist_empty - tests whether a list is empty
 *
 * head: the list to test.
 *
 * ret: true  //if the container size is 0
 * ret: false //otherwise.
 */
static inline int dlist_empty(const struct dlist_head *head)
{
    return head->next == head;
}



/*
 * dlist_is_first - tests whether node is the first node in list head
 *
 * node: the node to test
 * head: the head of the list
 *
 *  ret: true   // if [...] <-> [head] <-> [node] <-> [...]
 *  ret: false  // else
 */
static inline int dlist_is_first(const struct dlist_head *node,
                                 const struct dlist_head *head)
{
    return node->prev == head;
}



/*
 * dlist_is_last - tests whether node is the last node in list head
 *
 * node: the node to test
 * head: the head of the list
 *
 *  ret: true   // if [...] <-> [node] <-> [head] <-> [...]
 *  ret: false  // else
 */
static inline int dlist_is_last(const struct dlist_head *node,
                                const struct dlist_head *head)
{
    return node->next == head;
}



/*
 * dlist_is_singular - tests whether a list has just one node.
 *
 * head: the list to test.
 *
 * ret: true  //if the container size == 1
 * ret: false //if the container size != 1
 */
static inline int dlist_is_singular(const struct dlist_head *head)
{
    return !dlist_empty(head) && (head->next == head->prev);
}



/*
 * dlist_size - Returns the number of elements in the list container.
 *
 * head: the list to test.
 * ret:  the number of elements in the list
 */
static inline size_t dlist_size(const struct dlist_head *head)
{
    size_t size = 0;
    const struct dlist_head *it;
    for(it = (head)->next; it != (head); it = it->next)
        size++;

    return size;
}



/*
 * Insert a new node between two known consecutive nodes.
 *
 * This is only for internal list manipulation where we know
 * the prev/next nodes already!
 *
 * before:  [prev] <-> [next]
 * after:   [prev] <-> [node] <-> [next]
 *
 */
static inline void sys_dlist_add(struct dlist_head *node,
                                 struct dlist_head *prev,
                                 struct dlist_head *next)
{
    next->prev = node;
    node->next = next;
    node->prev = prev;
    prev->next = node;
}








#endif  //DLIST_HEADER
