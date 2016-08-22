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



/*
 * dlist_push_front - add a new node
 *
 * node: new node to be added
 * head: list head to add it after
 *
 * Inserts a new node at the beginning of the list,
 * before its current first element.
 *
 * before:  [prev] <-> [head] <-> [next]
 * after:   [prev] <-> [head] <-> [node] <-> [next]
 *
 */
static inline void dlist_push_front(struct dlist_head *node, struct dlist_head *head)
{
    sys_dlist_add(node, head, head->next);
}



/*
 * dlist_push_back - add a new node
 *
 * node: new node to be added
 * head: list head to add it before
 *
 * Insert a new node at the end of the list,
 * after its current last element.
 *
 * before:  [prev] <-> [head] <-> [next]
 * after:   [prev] <-> [node] <-> [head] <-> [next]
 */
static inline void dlist_push_back(struct dlist_head *node, struct dlist_head *head)
{
    sys_dlist_add(node, head->prev, head);
}



/*
 * Delete a list node by making the prev/next nodes
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next nodes already!
 */
static inline void sys_dlist_del(struct dlist_head *prev, struct dlist_head *next)
{
    next->prev = prev;
    prev->next = next;
}



/*
 * sys_dlist_del_node - deletes node from list.
 *
 * node: the element to delete from the list.
 *
 * Note: dlist_empty() on node does not return true after this,
 *       the node is in an undefined state.
 *
 * before:  [prev] <-> [node] <-> [next]
 * after:   [prev] <-> [next];              old_val <- [node] -> old_val
 */
static inline void sys_dlist_del_node(struct dlist_head *node)
{
    sys_dlist_del(node->prev, node->next);
}



/*
 * dlist_del - deletes node from list.
 *
 * node: the element to delete from the list.
 *
 * Note: dlist_empty() on node return true after this
 *
 * before:  [prev] <-> [node] <-> [next]
 * after:   [prev] <-> [next];              self <- [node] -> self
 */
static inline void dlist_del(struct dlist_head *node)
{
    sys_dlist_del(node->prev, node->next);
    dlist_init_head(node);
}



/*
 * dlist_pop_front - Delete first element
 *
 * Removes the first element in the list container,
 * effectively reducing its size by one.
 *
 * head: list head
 *
 * Note: list_empty() on first node return true after this
 */
static inline void dlist_pop_front(struct dlist_head *head)
{
    dlist_del(head->next);
}



/*
 * dlist_pop_back - Delete last element
 *
 * Removes the last element in the list container,
 * effectively reducing its size by one.
 *
 * head: list head
 *
 * Note: list_empty() on last node return true after this
 */
static inline void dlist_pop_back(struct dlist_head *head)
{
    dlist_del(head->prev);
}



/*
 * dlist_replace - replace old node by new node
 *
 * old_node: the element to be replaced
 * new_node: the new element to insert
 *
 * If old_node was empty, it will be overwritten for _init variant
 *
 * Note: new_node should be free. out of the list.
 */
static inline void dlist_replace(struct dlist_head *old_node,
                                 struct dlist_head *new_node)
{
    new_node->next       = old_node->next;
    new_node->next->prev = new_node;
    new_node->prev       = old_node->prev;
    new_node->prev->next = new_node;
}

static inline void dlist_replace_init(struct dlist_head *old_node,
                                      struct dlist_head *new_node)
{
    dlist_replace(old_node, new_node);
    dlist_init_head(old_node);
}



/*
 * dlist_move_to_front - delete from one list and add as another's head
 *
 * node: the node to move
 * head: the head that will precede our node
 */
static inline void dlist_move_to_front(struct dlist_head *node,
                                       struct dlist_head *head)
{
    sys_dlist_del_node(node);
    dlist_push_front(node, head);
}



/*
 * dlist_move_to_back - delete from one list and add as another's tail
 *
 * node: the node to move
 * head: the head that will follow our node
 */
static inline void dlist_move_to_back(struct dlist_head *node,
                                      struct dlist_head *head)
{
    sys_dlist_del_node(node);
    dlist_push_back(node, head);
}



/*
 * dlist_rotate_left - rotate the list to the left
 *
 * head: the head of the list
 *
 * before:  [...] <-> [nodeN] <-> [head]  <-> [node1] <-> [node2]  <-> [...]
 * after:   [...] <-> [nodeN] <-> [node1] <-> [head]  <-> [node2]  <-> [...]
 */
static inline void dlist_rotate_left(struct dlist_head *head)
{
    struct dlist_head *first;

    if( !dlist_empty(head) )
    {
        first = head->next;
        dlist_move_to_back(first, head);
    }
}



/*
 * dlist_rotate_right - rotate the list to the right
 *
 * head: the head of the list
 *
 * before:  [...] <-> [nodeN] <-> [head]  <-> [node1] <-> [node2] <-> [...]
 * after:   [...] <-> [head]  <-> [nodeN] <-> [node1] <-> [node2] <-> [...]
 */
static inline void dlist_rotate_right(struct dlist_head *head)
{
    struct dlist_head *last;

    if( !dlist_empty(head) )
    {
        last = head->prev;
        dlist_move_to_front(last, head);
    }
}







#endif  //DLIST_HEADER
