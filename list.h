/*
 *  list.h
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

#ifndef LIST_HEADER
#define LIST_HEADER


#include <stddef.h>





/*
 * Simple Circular linked lists implementation.
 *
 */





struct list_head
{
    struct list_head *next;
};





#define INIT_LIST_HEAD(name) { &(name) }

#define DECLARE_LIST_HEAD(name) \
    struct list_head name = INIT_LIST_HEAD(name)



static inline void list_init_head(struct list_head *list)
{
    list->next = list;
}



/*
 * list_empty - tests whether a list is empty
 *
 * head: the list to test.
 *
 * ret: true  //if the container size is 0
 * ret: false //otherwise.
 */
static inline int list_empty(const struct list_head *head)
{
    return head->next == head;
}



/*
 * list_is_first - tests whether node is the first node in list head
 *
 * node: the node to test
 * head: the head of the list
 *
 *  ret: true   // if [...] -> [head] -> [node] -> [...]
 *  ret: false  // else
 */
static inline int list_is_first(const struct list_head *node,
                                const struct list_head *head)
{
    return head->next == node;
}



/*
 * list_is_last - tests whether node is the last node in list head
 *
 * node: the node to test
 * head: the head of the list
 *
 *  ret: true   // if [...] -> [node] -> [head] -> [...]
 *  ret: false  // else
 */
static inline int list_is_last(const struct list_head *node,
                               const struct list_head *head)
{
    return node->next == head;
}



/*
 * list_is_singular - tests whether a list has just one node.
 *
 * head: the list to test.
 *
 * ret: true  //if the container size == 1
 * ret: false //if the container size != 1
 */
static inline int list_is_singular(const struct list_head *head)
{
    return !list_empty(head) && (head->next->next == head);
}



/*
 * list_size - Returns the number of elements in the list container.
 *
 * head: the list to test.
 * ret:  the number of elements in the list
 */
static inline size_t list_size(const struct list_head *head)
{
    size_t size = 0;
    const struct list_head *it;
    for(it = (head)->next; it != (head); it = it->next)
        size++;

    return size;
}



/*
 * list_first - Returns the first node of the list.
 *
 * head: the list
 * ret:  the first node of the list //if list dont empty
 * ret:  head                       //if list empty
 */
static inline struct list_head *list_first(const struct list_head *head)
{
    return head->next;
}



/*
 * list_last - Returns the last node of the list.
 *
 * head: the list
 * ret:  the last node of the list //if list dont empty
 * ret:  head                      //if list empty
 */
static inline struct list_head *list_last(const struct list_head *head)
{
    struct list_head *it;
    for(it = (head)->next; it->next != (head); it = it->next);

    return it;
}



/*
 * list_prev - Returns the previous node of the current node.
 *
 * head: the node
 * ret:  the previous node of the node //if node is in list (dont empty)
 * ret:  node                          //if node is not in list (empty)
 */
static inline struct list_head *list_prev(const struct list_head *node)
{
    return list_last(node);
}



/*
 * Insert a new node between two known consecutive nodes.
 *
 * This is only for internal list manipulation where we know
 * the prev/next nodes already!
 *
 * before:  [prev] -> [next]
 * after:   [prev] -> [node] -> [next]
 *
 */
static inline void sys_list_add(struct list_head *node,
                                struct list_head *prev)
{
    node->next = prev->next;
    prev->next = node;
}



/*
 * list_push_front - add a new node
 *
 * node: new node to be added
 * head: list head to add it after
 *
 * Inserts a new node at the beginning of the list,
 * before its current first element.
 *
 * before:  [prev] -> [head] -> [next]
 * after:   [prev] -> [head] -> [node] -> [next]
 *
 */
static inline void list_push_front(struct list_head *node, struct list_head *head)
{
    sys_list_add(node, head);
}



/*
 * list_push_back - add a new node
 *
 * node: new node to be added
 * head: list head to add it before
 *
 * Insert a new node at the end of the list,
 * after its current last element.
 *
 * before:  [prev] -> [head] -> [next]
 * after:   [prev] -> [node] -> [head] -> [next]
 */
static inline void list_push_back(struct list_head *node, struct list_head *head)
{
    sys_list_add(node, list_last(head));
}



/*
 * Delete a list node by making the prev/next nodes
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next nodes already!
 */
static inline void sys_list_del(struct list_head *prev, struct list_head *next)
{
    prev->next = next;
}



/*
 * sys_list_del_node - deletes node from list.
 *
 * node: the element to delete from the list.
 *
 * Note: list_empty() on node does not return true after this,
 *       the node is in an undefined state.
 *
 * before:  [prev] -> [node] -> [next]
 * after:   [prev] -> [next];              [node] -> old_val
 */
static inline void sys_list_del_node(struct list_head *node)
{
    sys_list_del(list_prev(node), node->next);
}



/*
 * list_del - deletes node from list.
 *
 * node: the element to delete from the list.
 *
 * Note: list_empty() on node return true after this
 *
 * before:  [prev] -> [node] -> [next]
 * after:   [prev] -> [next];              [node] -> self
 */
static inline void list_del(struct list_head *node)
{
    sys_list_del_node(node);
    list_init_head(node);
}





#endif  //LIST_HEADER
