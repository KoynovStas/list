/*
 * list.h
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

#ifndef LIST_HEADER
#define LIST_HEADER


#include <stddef.h>





/*
 * Simple Circular linked list implementation.
 *
 * Definitions and designations:
 *
 *
 *   next: -->
 *
 *
 *   empty list:
 *       ______
 *      |      |
 *   -->| head |---
 *   |  |______|  |
 *   |            |
 *   |____________|
 *
 *
 *
 *   list with nodes:
 *       ______     _______     _______
 *      |      |   |       |   |       |
 *   -->| head |-->| node0 |-->| node1 |---
 *   |  |______|   |_______|   |_______|  |
 *   |                                    |
 *   |____________________________________|
 *
 *
 *
 * Node - a data structure (payloads) in which one of the fields is
 * a variable of type list_head.
 *
 * example:
 *
 * struct tmp_data
 * {
 *    struct list_head list;
 *    int              data;
 * };
 *
 *
 * node* - a pointer to a Node, which is a pointer == pointer to
 * member (list_head) within the struct of data.
 *
 * If a member(list_head) in data structure (payloads) is
 * the first member (offset == 0) then the Node* == node*
 *
 * To get pointer to data structure(payloads), if you have a pointer to a node,
 * use the function: list_data
 *
 *
 *  Algorithmic complexity:
 *
 *  list_size            -     O(n)
 *  list_empty           -     O(1)  use it for check
 *  list_is_first        -     O(1)
 *  list_is_last         -     O(1)
 *  list_is_singular     -     O(1)
 *
 *  list_push_front      -     O(1)
 *  list_pop_front       -     O(1)
 *  list_push_back       -     O(n)
 *  list_pop_back        -     O(n)
 *  list_del             -     O(n)
 *  list_replace         -     O(n)
 *  list_replace_init    -     O(n)
 *  list_move_to_front   -     O(n)
 *  list_move_to_back    -     O(2n)
 *  list_rotate_left     -     O(2n)
 *  list_rotate_right    -     O(2n)
 *  list_splice_front    -     O(n)
 *  list_splice_back     -     O(2n)
 *  list_reverse         -     O(n)
 *  list_swap            -     O(3n)
 *
 *  //Get Data from node
 *  list_data            -     O(1)
 *  list_first_data      -     O(1)
 *  list_last_data       -     O(n)
 *
 *  //Iterator
 *  list_citer           -     O(n)
 *  list_iter            -     O(n)
 *  list_data_citer      -     O(n)
 *  list_data_iter       -     O(n)
 *
 *  //Algorithm
 *  list_for_each        -     O(n)
 *  list_min             -     O(n)
 *  list_max             -     O(n)
 *  list_minmax          -     O(n)
 *  list_find            -     O(n)
 *  list_find2           -     O(n)
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



/*
 * list_pop_front - Delete first element
 *
 * Removes the first element in the list container,
 * effectively reducing its size by one.
 *
 * head: list head
 *
 * Note: list_empty() on first node return true after this
 */
static inline void list_pop_front(struct list_head *head)
{
    struct list_head *first_node = head->next;
    head->next = first_node->next;
    list_init_head(first_node);
}



/*
 * list_pop_back - Delete last element
 *
 * Removes the last element in the list container,
 * effectively reducing its size by one.
 *
 * head: list head
 *
 * Note: list_empty() on last node return true after this
 */
static inline void list_pop_back(struct list_head *head)
{
    struct list_head *last_node = list_last(head);
    sys_list_del_node(last_node);
    list_init_head(last_node);
}



/*
 * list_replace - replace old node by new node
 *
 * old_node: the element to be replaced
 * new_node: the new element to insert
 *
 * If old_node was empty, it will be overwritten for _init variant
 *
 * Note: new_node should be free. out of the list.
 */
static inline void list_replace(struct list_head *old_node,
                                struct list_head *new_node)
{
    struct list_head *prev_old_node = list_prev(old_node);

    new_node->next       = old_node->next;
    prev_old_node->next  = new_node;
}

static inline void list_replace_init(struct list_head *old_node,
                                     struct list_head *new_node)
{
    list_replace(old_node, new_node);
    list_init_head(old_node);
}



/*
 * list_move_to_front - delete from one list and add as another's head
 *
 * node: the node to move
 * head: the head that will precede our node
 */
static inline void list_move_to_front(struct list_head *node,
                                      struct list_head *head)
{
    sys_list_del_node(node);
    list_push_front(node, head);
}



/*
 * list_move_to_back - delete from one list and add as another's tail
 *
 * node: the node to move
 * head: the head that will follow our node
 */
static inline void list_move_to_back(struct list_head *node,
                                     struct list_head *head)
{
    sys_list_del_node(node);
    list_push_back(node, head);
}



/*
 * list_rotate_left - rotate the list to the left
 *
 * head: the head of the list
 *
 * before:  [...] -> [nodeN] -> [head]  -> [node1] -> [node2]  -> [...]
 * after:   [...] -> [nodeN] -> [node1] -> [head]  -> [node2]  -> [...]
 */
static inline void list_rotate_left(struct list_head *head)
{
    struct list_head *first;

    if( !list_empty(head) )
    {
        first = head->next;
        list_move_to_back(first, head);
    }
}



/*
 * list_rotate_right - rotate the list to the right
 *
 * head: the head of the list
 *
 * before:  [...] -> [nodeN] -> [head]  -> [node1] -> [node2] -> [...]
 * after:   [...] -> [head]  -> [nodeN] -> [node1] -> [node2] -> [...]
 */
static inline void list_rotate_right(struct list_head *head)
{
    struct list_head *last;

    if( !list_empty(head) )
    {
        last = list_last(head);
        list_move_to_front(last, head);
    }
}



static inline void sys_list_splice(struct list_head *list,
                                   struct list_head *prev,
                                   struct list_head *next)
{
    struct list_head *first = list->next;
    struct list_head *last  = list_last(list);

    prev->next = first;
    last->next = next;
}



/*
 * list_splice_front - transfers all the elements of src into the container(dest)
 *                     this is designed for stacks
 *
 * dest: list to copy to  (copy to front)
 * src:  list to copy from
 */
static inline void list_splice_front(struct list_head *src,
                                     struct list_head *dest)
{
    if(!list_empty(src))
    {
        sys_list_splice(src, dest, dest->next);
        list_init_head(src);
    }
}



/*
 * list_splice_back - transfers all the elements of src into the container(dest)
 *                    this is designed for queue
 *
 * dest: list to copy to  (copy to back)
 * src:  list to copy from
 */
static inline void list_splice_back(struct list_head *src,
                                    struct list_head *dest)
{
    if (!list_empty(src))
    {
        sys_list_splice(src, list_prev(dest), dest);
        list_init_head(src);
    }
}



/*
 * list_reverse - reverse the list
 *
 * head: the head of the list
 *
 * before:  [...] -> [N] -> [head] -> [1] -> [2] -> [3] -> [...]
 * after:   [...] -> [3] -> [2] -> [1] -> [head] -> [N] -> [...]
 */
static inline void list_reverse(struct list_head *head)
{
    if( list_empty(head) || list_is_singular(head) )
        return;


    DECLARE_LIST_HEAD(tmp);
    struct list_head *last, *first_node;

    last = head->next; //first node will be last

    while(head->next != head)
    {
        //extract first node from list
        first_node = head->next;
        head->next = first_node->next;

        list_push_front(first_node, &tmp);
    }

    last->next = head;         //the last node should point to the head
    head->next = first_node;   //now head point to the reverse list
}



/*
 * list_swap - Exchanges the contents of the containers.
 * Does not invoke any move, copy, or swap operations on individual elements.
 *
 */
static inline void list_swap(struct list_head *head1, struct list_head *head2)
{
    if(head1 == head2)
        return;

    DECLARE_LIST_HEAD(tmp);

    list_splice_front(head1, &tmp);
    list_splice_front(head2, head1);
    list_splice_front(&tmp, head2);
}





//---------------- Get Data from node ----------------





/*
 * list_data - get the struct (data) for this node
 *
 * node:   the node.
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node(list_head) within the struct of data.
 */
#define list_data(node, type, member) \
    (type *)( (const char *)node - offsetof(type, member) )



/*
 * list_data_or_null - get the struct (data) for this node
 *
 * node:   the node.
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node(list_head) within the struct of data.
 *
 * Note it returns NULL if the list(node) is empty.
 */
#define list_data_or_null(node, type, member) \
    (list_empty(node) ? NULL : list_data(node, type, member))



/*
 * list_first_data - get the first struct (data) from a list
 *
 * head:   the list head to take the element from.
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node(list_head) within the struct of data.
 *
 * Note - list don't have to  be empty.
 */
#define list_first_data(head, type, member) \
    list_data((head)->next, type, member)



/*
 * list_last_data - get the last struct (data) from a list
 *
 * head:   the list head to take the element from.
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node(list_head) within the struct of data.
 *
 * Note - list don't have to  be empty.
 */
#define list_last_data(head, type, member) \
    list_data(list_last(head), type, member)



/*
 * list_first_data_or_null - get the first struct (data) from a list
 *
 * head:   the list head to take the element from.
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node(list_head) within the struct of data.
 *
 * Note it returns NULL if the list(node) is empty.
 */
#define list_first_data_or_null(head, type, member) \
    (list_empty(head) ? NULL : list_first_data(head, type, member))



/*
 * list_last_data_or_null - get the last struct (data) from a list
 *
 * head:   the list head to take the element from.
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node(list_head) within the struct of data.
 *
 * Note it returns NULL if the list(node) is empty.
 */
#define list_last_data_or_null(head, type, member) \
    (list_empty(head) ? NULL : list_last_data(head, type, member))





//---------------- Iterator ----------------





/*
 * list_citer - constant iterate over a list
 *
 * it:   the &struct list_head to use as a loop cursor(iterator).
 * head: the head for your list.
 *
 * Note: You do not have to change list in this cycle.
 *
 */
#define list_citer(it, head) \
    for( it = (head)->next; it != (head); it = it->next )



/*
 * list_iter - iterate over a list safe against removal of list node
 *
 * it:     the &struct list_head to use as a loop cursor(iterator).
 * tmp_it: another &struct list_head to use as temporary cursor(iterator)
 * head:   the head for your list.
 */
#define list_iter(it, tmp_it, head)                          \
    for( it = (head)->next, tmp_it = it->next; it != (head); \
         it = tmp_it, tmp_it = it->next)



/*
 * list_data_citer - constant iterate over list of given type (data)
 *
 * it:     the &struct data to use as a loop cursor(iterator).
 * head:   the &list_head to take the element from.
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node(list_head) within the struct of data.
 *
 * Note You do not have to change list in this cycle.
 */
#define list_data_citer(it, head, type, member)         \
    for (it = list_data((head)->next, type, member);    \
         &it->member != (head);                         \
         it = list_data(it->member.next, type, member))



/*
 * list_data_iter - iterate over list of given type
 *
 * it:     the &struct data to use as a loop cursor(iterator).
 * head:   the &list_head to take the element from.
 * tmp_it: another &struct list_head to use as temporary cursor(iterator)
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node(list_head) within the struct of data.
 */
#define list_data_iter(it, head, tmp_it, type, member)                         \
    for (it = list_data((head)->next, type, member), tmp_it = it->member.next; \
         &it->member != (head);                                                \
         it = list_data(tmp_it, type, member), tmp_it = it->member.next)





//---------------- Algorithm ----------------





/*
 * list_for_each - Applies function fn to each of the elements in the range [first,last)
 *
 * first, last is Input iterators to the initial and final positions in a sequence.
 * The range used is [first,last), which contains all the elements
 * between first and last, including the element pointed by first
 * but not the element pointed by last.
 *
 * first:  the &list_head to use as a first element
 * last:   the &list_head to use as a last element.
 * fn:     Unary function that accepts an element in the range as argument.
 */
static inline void list_for_each(struct list_head *first, struct list_head *last,
                                 void (*fn) (struct list_head *node))
{
    struct list_head *it = first;
    for(; it != last; fn(it), it = it->next);
}



/*
 * list_min - Return smallest element in range
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
 * first:  the &list_head to use as a first element.
 * last:   the &list_head to use as a last element.
 * comp:   Binary function that accepts two elements in the range as arguments,
 *         and returns a value convertible to bool. The value returned indicates
 *         whether the element passed as first argument is considered less than the second.
 *         The function shall not modify any of its arguments
 */
static inline struct list_head* list_min(struct list_head *first, struct list_head *last,
                                         int (*comp) (const struct list_head *n1, const struct list_head *n2) )
{
    if(first==last)
        return last;

    struct list_head *smallest = first;
    struct list_head *it       = first;

    while( (it = it->next) != last )
        if(comp(it, smallest))
            smallest=it;

    return smallest;
}



/*
 * list_max - Return largest element in range
 *
 * Returns an iterator pointing to the element with the largest value
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
 * first:  the &list_head to use as a first element.
 * last:   the &list_head to use as a last element.
 * comp:   Binary function that accepts two elements in the range as arguments,
 *         and returns a value convertible to bool. The value returned indicates
 *         whether the element passed as first argument is considered less than the second.
 *         The function shall not modify any of its arguments
 */
static inline struct list_head* list_max(struct list_head *first, struct list_head *last,
                                         int (*comp) (const struct list_head *n1, const struct list_head *n2) )
{
    if(first==last)
        return last;

    struct list_head *largest = first;
    struct list_head *it      = first;

    while( (it = it->next) != last )
        if(comp(largest, it))
            largest=it;

    return largest;
}



/*
 * list_minmax - Return the smallest and largest element in the range [first, last).
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
 * first:  the &list_head to use as a first element.
 * last:   the &list_head to use as a last element.
 * comp:   Binary function that accepts two elements in the range as arguments,
 *         and returns a value convertible to bool. The value returned indicates
 *         whether the element passed as first argument is considered less than the second.
 *         The function shall not modify any of its arguments
 * res:    res[0] - min
 *         res[1] - max
 */
static inline void list_minmax(struct list_head *first, struct list_head *last,
                               int (*comp) (const struct list_head *n1, const struct list_head *n2),
                               struct list_head *res[2])
{
    res[0] = first;  //min
    res[1] = first;  //max

    if(first==last)
        return;


    struct list_head *it = first;

    while( (it = it->next) != last )
    {
        if(comp(it, res[0]))
            res[0]=it;

        if(comp(res[1], it))
            res[1]=it;
    }
}



/*
 * list_find - Find element in range
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
 * first: the &list_head to use as a loop cursor(iterator)
 * last:  the &list_head to use as a last element.
 * pred:  Unary function that accepts an element in the range as argument
 *        and returns a value convertible to bool.
 *        The value returned indicates whether the element is considered a match
 *        in the context of this function.
 *        The function shall not modify its argument.
 *        This can either be a function pointer or a function object.
 */
static inline struct list_head* list_find(struct list_head *first, struct list_head *last,
                                          int (*pred) (const struct list_head *node) )
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
 * list_find2 - Find element in range
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
 * first: the &list_head to use as a loop cursor(iterator)
 * last:  the &list_head to use as a last element.
 * pred:  Binary function that accepts an element in the range as argument
 *        and returns a value convertible to bool.
 *        The value returned indicates whether the element is considered a match
 *        in the context of this function.
 *        The function shall not modify its argument.
 *        This can either be a function pointer or a function object.
 * data:  Pointer to user data for pred function.
 */
static inline struct list_head* list_find2(struct list_head *first, struct list_head *last,
                                           int (*pred) (const struct list_head *node, void *data), void *data)
{
    while( first != last )
    {
        if( pred(first, data) )
            return first;

        first = first->next;
    }

    return last;
}





#endif  //LIST_HEADER
