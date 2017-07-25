/*
 * dlist.h
 *
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2016, Koynov Stas - skojnov@yandex.ru
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

#ifndef DLIST_HEADER
#define DLIST_HEADER


#include <stddef.h>





/*
 * Simple Circular doubly linked list implementation.
 *
 * Definitions and designations:
 *
 *
 *   next: ->
 *   prev: <-
 *
 *
 *   empty list:
 *       ______
 *      |      |
 *   -->| head |<--
 *   |  |______|  |
 *   |            |
 *   |____________|
 *
 *
 *
 *   list with nodes:
 *       ______     _______     _______
 *      |      |   |       |   |       |
 *   -->| head |<->| node0 |<->| node1 |<--
 *   |  |______|   |_______|   |_______|  |
 *   |                                    |
 *   |____________________________________|
 *
 *
 *
 * Node - a data structure (payloads) in which one of the fields is
 * a variable of type dlist_head.
 *
 * example:
 *
 * struct tmp_data
 * {
 *    struct dlist_head list;
 *    int               data;
 * };
 *
 *
 * node* - a pointer to a Node, which is a pointer == pointer to
 * member (dlist_head) within the struct of data.
 *
 * If a member(dlist_head) in data structure (payloads) is
 * the first member (offset == 0) then the Node* == node*
 *
 * To get pointer to data structure(payloads), if you have a pointer to a node,
 * use the function: dlist_data
 *
 *
 *  Algorithmic complexity:
 *
 *  dlist_size            -     O(n)
 *  dlist_empty           -     O(1)  use it for check
 *  dlist_is_first        -     O(1)
 *  dlist_is_last         -     O(1)
 *  dlist_is_singular     -     O(1)
 *
 *  dlist_push_front      -     O(1)
 *  dlist_pop_front       -     O(1)
 *  dlist_push_back       -     O(1)
 *  dlist_pop_back        -     O(1)
 *  dlist_del             -     O(1)
 *  dlist_replace         -     O(1)
 *  dlist_replace_init    -     O(1)
 *  dlist_move_to_front   -     O(1)
 *  dlist_move_to_back    -     O(1)
 *  dlist_rotate_left     -     O(1)
 *  dlist_rotate_right    -     O(1)
 *  dlist_splice_front    -     O(1)
 *  dlist_splice_back     -     O(1)
 *  dlist_reverse         -     O(n)
 *
 *  //Get Data from node
 *  dlist_data            -     O(1)
 *  dlist_first_data      -     O(1)
 *  dlist_last_data       -     O(1)
 *
 *  //Iterator
 *  dlist_citer           -     O(n)
 *  dlist_criter          -     O(n)
 *  dlist_iter            -     O(n)
 *  dlist_riter           -     O(n)
 *  dlist_data_citer      -     O(n)
 *  dlist_data_criter     -     O(n)
 *  dlist_data_iter       -     O(n)
 *  dlist_data_riter      -     O(n)
 *
 *  //Algorithm
 *  dlist_for_each        -     O(n)
 *  dlist_min             -     O(n)
 *  dlist_max             -     O(n)
 *  dlist_minmax          -     O(n)
 *  dlist_find            -     O(n)
 *  dlist_find2           -     O(n)
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



static inline void sys_dlist_splice(struct dlist_head *list,
                                    struct dlist_head *prev,
                                    struct dlist_head *next)
{
    struct dlist_head *first = list->next;
    struct dlist_head *last  = list->prev;

    first->prev = prev;
    prev->next  = first;

    last->next = next;
    next->prev = last;
}



/*
 * dlist_splice_front - transfers all the elements of list into the container(head)
 *                     this is designed for stacks
 *
 * list: the new list to add.
 * head: the place to add elements of list.
 */
static inline void dlist_splice_front(struct dlist_head *list,
                                      struct dlist_head *head)
{
    if(!dlist_empty(list))
    {
        sys_dlist_splice(list, head, head->next);
        dlist_init_head(list);
    }
}



/*
 * dlist_splice_back - transfers all the elements of list into the container(head)
 *                     this is designed for queue
 *
 * list: the new list to add.
 * head: the place to add elements of list.
 */
static inline void dlist_splice_back(struct dlist_head *list,
                                     struct dlist_head *head)
{
    if (!dlist_empty(list))
    {
        sys_dlist_splice(list, head->prev, head);
        dlist_init_head(list);
    }
}



/*
 * dlist_reverse - reverse the list
 *
 * head: the head of the list
 *
 * before:  [...] <-> [N] <-> [head] <-> [1] <-> [2] <-> [3] <-> [...]
 * after:   [...] <-> [3] <-> [2] <-> [1] <-> [head] <-> [N] <-> [...]
 */
static inline void dlist_reverse(struct dlist_head *head)
{
    if( dlist_empty(head) || dlist_is_singular(head) )
        return;

    DECLARE_DLIST_HEAD(tmp);


    while(head->next != head)
    {
        dlist_move_to_front(head->next, &tmp);
    }

    sys_dlist_splice(&tmp, head, head->next);
}





//---------------- Get Data from node ----------------





/*
 * dlist_data - get the struct (data) for this node
 *
 * node:   the node.
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node(dlist_head) within the struct of data.
 */
#define dlist_data(node, type, member) \
     (type *)( (const char *)node - offsetof(type, member) )



/*
 * dlist_data_or_null - get the struct (data) for this node
 *
 * node:   the node.
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node(dlist_head) within the struct of data.
 *
 * Note it returns NULL if the list(node) is empty.
 */
#define dlist_data_or_null(node, type, member) \
    (dlist_empty(node) ? NULL : dlist_data(node, type, member))



/*
 * dlist_first_data - get the first struct (data) from a list
 *
 * head:   the dlist head to take the element from.
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node(dlist_head) within the struct of data.
 *
 * Note - list don't have to  be empty.
 */
#define dlist_first_data(head, type, member) \
    dlist_data((head)->next, type, member)



/*
 * dlist_last_data - get the last struct (data) from a list
 *
 * head:   the list head to take the element from.
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node(dlist_head) within the struct of data.
 *
 * Note - list don't have to  be empty.
 */
#define dlist_last_data(head, type, member) \
    dlist_data((head)->prev, type, member)



/*
 * dlist_first_data_or_null - get the first struct (data) from a list
 *
 * head:   the list head to take the element from.
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node(dlist_head) within the struct of data.
 *
 * Note it returns NULL if the list(node) is empty.
 */
#define dlist_first_data_or_null(head, type, member) \
    (dlist_empty(head) ? NULL : dlist_first_data(head, type, member))



/*
 * dlist_last_data_or_null - get the last struct (data) from a list
 *
 * head:   the list head to take the element from.
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node(dlist_head) within the struct of data.
 *
 * Note it returns NULL if the list(node) is empty.
 */
#define dlist_last_data_or_null(head, type, member) \
    (dlist_empty(head) ? NULL : dlist_last_data(head, type, member))





//---------------- Iterator ----------------





/*
 * dlist_citer - constant iterate over a list
 *
 * it:    the &struct dlist_head to use as a loop cursor(iterator).
 * head:  the head for your list.
 *
 * Note You do not have to change list in this cycle.
 *
 */
#define dlist_citer(it, head) \
    for( it = (head)->next; it != (head); it = it->next )



/*
 * dlist_criter - constant revers iterate over a list
 *
 * it:    the &struct dlist_head to use as a loop cursor(iterator).
 * head:  the head for your list.
 *
 * Note You do not have to change list in this cycle.
 */
#define dlist_criter(it, head) \
    for( it = (head)->prev; it != (head); it = it->prev )



/*
 * dlist_iter - iterate over a list safe against removal of list node
 *
 * it:     the &struct dlist_head to use as a loop cursor(iterator).
 * tmp_it: another &struct dlist_head to use as temporary cursor(iterator)
 * head:   the head for your list.
 */
#define dlist_iter(it, tmp_it, head)                         \
    for( it = (head)->next, tmp_it = it->next; it != (head); \
         it = tmp_it, tmp_it = it->next)



/*
 * dlist_riter - reverse iterate over a list safe against removal of list node
 *
 * it:     the &struct dlist_head to use as a loop cursor(iterator).
 * tmp_it: another &struct dlist_head to use as temporary cursor(iterator)
 * head:   the head for your list.
 */
#define dlist_riter(it, tmp_it, head)          \
    for(it  = (head)->prev, tmp_it = it->prev; \
        it != (head);                          \
        it  = tmp_it, tmp_it = it->prev)



/*
 * dlist_data_citer - constant iterate over list of given type (data)
 *
 * it:     the &struct data to use as a loop cursor(iterator).
 * head:   the &dlist_head to take the element from.
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node(dlist_head) within the struct of data.
 *
 * Note You do not have to change list in this cycle.
 */
#define dlist_data_citer(it, head, type, member)         \
    for (it = dlist_data((head)->next, type, member);    \
         &it->member != (head);                          \
         it = dlist_data(it->member.next, type, member))



/*
 * dlist_data_criter - constant reverse iterate over list of given type (data)
 *
 * it:     the &struct data to use as a loop cursor(iterator).
 * head:   the &dlist_head to take the element from.
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node(dlist_head) within the struct of data.
 *
 * Note You do not have to change list in this cycle.
 */
#define dlist_data_criter(it, head, type, member)        \
    for (it = dlist_data((head)->prev, type, member);    \
         &it->member != (head);                          \
         it = dlist_data(it->member.prev, type, member))



/*
 * dlist_data_iter - iterate over list of given type
 *
 * it:     the &struct data to use as a loop cursor(iterator).
 * head:   the &dlist_head to take the element from.
 * tmp_it: another &struct dlist_head to use as temporary cursor(iterator)
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node(dlist_head) within the struct of data.
 */
#define dlist_data_iter(it, head, tmp_it, type, member)                         \
    for (it = dlist_data((head)->next, type, member), tmp_it = it->member.next; \
         &it->member != (head);                                                 \
         it = dlist_data(tmp_it, type, member), tmp_it = it->member.next)



/*
 * dlist_data_riter - reverse iterate over list of given type
 *
 * it:     the &struct data to use as a loop cursor(iterator).
 * head:   the &dlist_head to take the element from.
 * tmp_it: another &struct dlist_head to use as temporary cursor(iterator)
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node(dlist_head) within the struct of data.
 */
#define dlist_data_riter(it, head, tmp_it, type, member)                        \
    for (it = dlist_data((head)->prev, type, member), tmp_it = it->member.prev; \
         &it->member != (head);                                                 \
         it = dlist_data(tmp_it, type, member), tmp_it = it->member.prev)





//---------------- Algorithm ----------------





/*
 * dlist_for_each - Applies function fn to each of the elements in the range [first,last)
 *
 * first, last is Input iterators to the initial and final positions in a sequence.
 * The range used is [first,last), which contains all the elements
 * between first and last, including the element pointed by first
 * but not the element pointed by last.
 *
 * first:  the &dlist_head to use as a first element
 * last:   the &dlist_head to use as a last element.
 * fn:     Unary function that accepts an element in the range as argument.
 */
static inline void dlist_for_each(struct dlist_head *first, struct dlist_head *last,
                                  void (*fn) (struct dlist_head *node))
{
    struct dlist_head *it = first;
    for(; it != last; fn(it), it = it->next);
}



/*
 * dlist_min - Return smallest element in range
 *
 * Returns an iterator pointing to the element with the smallest value
 * in the range [first,last).
 *
 * An element is the smallest if no other element compares less than it.
 * If more than one element fulfills this condition,
 * the iterator returned points to the first of such elements.
 *
 * first, last is Input iterators to the initial and final positions
 * of the sequence to compare
 * The range used is [first,last), which contains all the elements
 * between first and last, including the element pointed by first
 * but not the element pointed by last.
 *
 * first:  the &dlist_head to use as a loop cursor(iterator)
 * last:   the &dlist_head to use as a last element.
 * comp:   Binary function that accepts two elements in the range as arguments,
 *         and returns a value convertible to bool. The value returned indicates
 *         whether the element passed as first argument is considered less than the second.
 *         The function shall not modify any of its arguments
 */
static inline struct dlist_head* dlist_min(struct dlist_head *first, struct dlist_head *last,
                                           int (*comp) (const struct dlist_head *n1, const struct dlist_head *n2) )
{
    if(first==last)
        return last;

    struct dlist_head *smallest = first;
    struct dlist_head *it       = first;

    while( (it = it->next) != last )
        if(comp(it, smallest))
            smallest=it;

    return smallest;
}



/*
 * dlist_max - Return largest element in range
 *
 * Returns an iterator pointing to the element with the with the largest value
 * in the range [first,last).
 *
 * An element is the largest if no other element does not compare less than it.
 * If more than one element fulfills this condition,
 * the iterator returned points to the first of such elements.
 *
 * first, last is Input iterators to the initial and final positions
 * of the sequence to compare
 * The range used is [first,last), which contains all the elements
 * between first and last, including the element pointed by first
 * but not the element pointed by last.
 *
 * first:  the &dlist_head to use as a first element.
 * last:   the &dlist_head to use as a last element.
 * comp:   Binary function that accepts two elements in the range as arguments,
 *         and returns a value convertible to bool. The value returned indicates
 *         whether the element passed as first argument is considered less than the second.
 *         The function shall not modify any of its arguments
 */
static inline struct dlist_head* dlist_max(struct dlist_head *first, struct dlist_head *last,
                                           int (*comp) (const struct dlist_head *n1, const struct dlist_head *n2) )
{
    if(first==last)
        return last;

    struct dlist_head *largest = first;
    struct dlist_head *it      = first;

    while( (it = it->next) != last )
        if(comp(largest, it))
            largest=it;

    return largest;
}



/*
 * dlist_minmax - Return the smallest and largest element in the range [first, last).
 *
 * Returns array of an iterators pointing to the element:
 * with the smallest value res[0] in the range [first,last).
 * with the largest value  res[1] in the range [first,last).
 *
 * An element is the smallest if no other element compares less than it.
 * If more than one element fulfills this condition,
 * the iterator returned points to the first of such elements.
 *
 * An element is the largest if no other element does not compare less than it.
 * If more than one element fulfills this condition,
 * the iterator returned points to the first of such elements.
 *
 * first, last is Input iterators to the initial and final positions
 * of the sequence to compare
 * The range used is [first,last), which contains all the elements
 * between first and last, including the element pointed by first
 * but not the element pointed by last.
 *
 * first:  the &dlist_head to use as a first element.
 * last:   the &dlist_head to use as a last element.
 * comp:   Binary function that accepts two elements in the range as arguments,
 *         and returns a value convertible to bool. The value returned indicates
 *         whether the element passed as first argument is considered less than the second.
 *         The function shall not modify any of its arguments
 * res:    res[0] - min
 *         res[1] - max
 */
static inline void dlist_minmax(struct dlist_head *first, struct dlist_head *last,
                               int (*comp) (const struct dlist_head *n1, const struct dlist_head *n2),
                               struct dlist_head *res[2])
{
    res[0] = first;  //min
    res[1] = first;  //max

    if(first==last)
        return;


    struct dlist_head *it = first;

    while( (it = it->next) != last )
    {
        if(comp(it, res[0]))
            res[0]=it;

        if(comp(res[1], it))
            res[1]=it;
    }
}



/*
 * dlist_find - Find element in range
 *
 * Returns an iterator to the first element in the range [first,last)
 * for which pred returns true.
 * If no such element is found, the function returns last.
 *
 * first, last is Input iterators to the initial and final positions
 * of the sequence to find
 * The range used is [first,last), which contains all the elements
 * between first and last, including the element pointed by first
 * but not the element pointed by last.
 *
 * first: the &dlist_head to use as a loop cursor(iterator)
 * last:  the &dlist_head to use as a last element.
 * pred:  Unary function that accepts an element in the range as argument
 *        and returns a value convertible to bool.
 *        The value returned indicates whether the element is considered a match
 *        in the context of this function.
 *        The function shall not modify its argument.
 *        This can either be a function pointer or a function object.
 */
static inline struct dlist_head* dlist_find(struct dlist_head *first, struct dlist_head *last,
                                            int (*pred) (const struct dlist_head *node) )
{
    while( first != last )
    {
        if( pred(first) )
            return first;

        first = first->next;
    }

    return last;
}



/*
 * dlist_find2 - Find element in range
 *
 * Returns an iterator to the first element in the range [first,last)
 * for which pred returns true.
 * If no such element is found, the function returns last.
 *
 * first, last is Input iterators to the initial and final positions
 * of the sequence to find
 * The range used is [first,last), which contains all the elements
 * between first and last, including the element pointed by first
 * but not the element pointed by last.
 *
 * first: the &dlist_head to use as a loop cursor(iterator)
 * last:  the &dlist_head to use as a last element.
 * pred:  Binary function that accepts an element in the range as argument
 *        and returns a value convertible to bool.
 *        The value returned indicates whether the element is considered a match
 *        in the context of this function.
 *        The function shall not modify its argument.
 *        This can either be a function pointer or a function object.
 * data:  Pointer to user data for pred function.
 */
static inline struct dlist_head* dlist_find2(struct dlist_head *first, struct dlist_head *last,
                                             int (*pred) (const struct dlist_head *node, void *data), void *data)
{
    while( first != last )
    {
        if( pred(first, data) )
            return first;

        first = first->next;
    }

    return last;
}





#endif  //DLIST_HEADER
