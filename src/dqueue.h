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



/*
 * dqueue_is_singular - tests whether a dqueue has just one node.
 *
 * dqueue: the dqueue to test.
 *
 * ret: true  //if the container size == 1
 * ret: false //if the container size != 1
 */
static inline int dqueue_is_singular(const struct dqueue_t *dqueue)
{
    return (dqueue->size == 1);
}



/*
 * dqueue_size - Returns the number of elements in the dqueue container.
 *
 * dqueue: the dqueue to test.
 * ret:  the number of elements in the dqueue
 */
static inline size_t dqueue_size(const struct dqueue_t *dqueue)
{
    return dqueue->size;
}



/*
 * dqueue_push_front - add a new node
 *
 * node: new node to be added
 * dqueue: dqueue to add it after
 *
 * Inserts a new node at the beginning of the dqueue,
 * before its current first element.
 *
 * before:  [prev] <-> [head] <-> [next]
 * after:   [prev] <-> [head] <-> [node] <-> [next]
 */
static inline void dqueue_push_front(dqueue_node *node, struct dqueue_t *dqueue)
{
    dlist_push_front(node, &dqueue->head);
    dqueue->size++;
}



/*
 * dqueue_push_back - add a new node
 *
 * node: new node to be added
 * dqueue: dqueue to add it before
 *
 * Insert a new node at the end of the list,
 * after its current last element.
 *
 * before:  [prev] <-> [head] <-> [next]
 * after:   [prev] <-> [node] <-> [head] <-> [next]
 */
static inline void dqueue_push_back(dqueue_node *node, struct dqueue_t *dqueue)
{
    dlist_push_back(node, &dqueue->head);
    dqueue->size++;
}



/*
 * dqueue_del - deletes node from dqueue.
 *
 * node: the element to delete from the dqueue.
 *
 * Note: dlist_empty() on node return true after this
 *
 * before:  [prev] <-> [node] <-> [next]
 * after:   [prev] <-> [next];              self <- [node] -> self
 */
static inline void dqueue_del(dqueue_node *node, struct dqueue_t *dqueue)
{
    dlist_del(node);
    dqueue->size--;
}



/*
 * dqueue_pop_front - Delete first element
 *
 * Removes the first element in the dqueue container,
 * effectively reducing its size by one.
 *
 * dqueue: dqueue
 *
 * Note: dlist_empty() on first node return true after this
 */
static inline void dqueue_pop_front(struct dqueue_t *dqueue)
{
    if(dqueue->size)
        dqueue_del(dqueue->head.next, dqueue);
}



/*
 * dqueue_pop_back - Delete last element
 *
 * Removes the last element in the dqueue container,
 * effectively reducing its size by one.
 *
 * dqueue: dqueue
 *
 * Note: dlist_empty() on last node return true after this
 */
static inline void dqueue_pop_back(struct dqueue_t *dqueue)
{
    if(dqueue->size)
        dqueue_del(dqueue->head.prev, dqueue);
}



/*
 * dqueue_replace - replace old node by new node
 *
 * old_node: the element to be replaced
 * new_node: the new element to insert
 *
 * If old_node was empty, it will be overwritten for _init variant
 *
 * Note: new_node should be free. out of the dqueue.
 */
static inline void dqueue_replace(dqueue_node *old_node,
                                  dqueue_node *new_node)
{
    dlist_replace(old_node, new_node);
}

static inline void dqueue_replace_init(dqueue_node *old_node,
                                       dqueue_node *new_node)
{
    dlist_replace_init(old_node, new_node);
}



/*
 * dqueue_move_to_front - move node to front
 *
 * node: the node to move
 * dqueue: the dqueue that Contains our node
 */
static inline void dqueue_move_to_front(dqueue_node *node,struct dqueue_t *dqueue)
{
    dlist_move_to_front(node, &dqueue->head);
}



/*
 * dqueue_move_to_back - move node to back
 *
 * node: the node to move
 * dqueue: the dqueue that Contains our node
 */
static inline void dqueue_move_to_back(dqueue_node *node, struct dqueue_t *dqueue)
{
    dlist_move_to_back(node, &dqueue->head);
}



/*
 * dqueue_rotate_left - rotate the dqueue to the left
 *
 * dqueue: dqueue
 *
 * before:  [...] <-> [nodeN] <-> [head]  <-> [node1] <-> [node2]  <-> [...]
 * after:   [...] <-> [nodeN] <-> [node1] <-> [head]  <-> [node2]  <-> [...]
 */
static inline void dqueue_rotate_left(struct dqueue_t *dqueue)
{
    dlist_rotate_left(&dqueue->head);
}



/*
 * dqueue_rotate_right - rotate the dqueue to the right
 *
 * dqueue: dqueue
 *
 * before:  [...] <-> [nodeN] <-> [head]  <-> [node1] <-> [node2] <-> [...]
 * after:   [...] <-> [head]  <-> [nodeN] <-> [node1] <-> [node2] <-> [...]
 */
static inline void dqueue_rotate_right(struct dqueue_t *dqueue)
{
    dlist_rotate_right(&dqueue->head);
}



/*
 * dqueue_splice_front - transfers all the elements of src into the container(dest)
 *
 * dest: dqueue to copy to (copy to front)
 * src:  dqueue to copy from
 */
static inline void dqueue_splice_front(struct dqueue_t *src, struct dqueue_t *dest)
{
    if(src->size)
    {
        sys_dlist_splice(&src->head, &dest->head, dest->head.next);
        dest->size += src->size;
        dqueue_init(src);
    }
}



/*
 * dqueue_splice_back - transfers all the elements of src into the container(dest)
 *
 * dest: dqueue to copy to  (copy to back)
 * src:  dqueue to copy from
 */
static inline void dqueue_splice_back(struct dqueue_t *src, struct dqueue_t *dest)
{
    if(src->size)
    {
        sys_dlist_splice(&src->head, dest->head.prev, &dest->head);
        dest->size += src->size;
        dqueue_init(src);
    }
}



/*
 * dqueue_reverse - reverse the dqueue
 *
 * dqueue: the dqueue
 *
 * before:  [...] <-> [N] <-> [head] <-> [1] <-> [2] <-> [3] <-> [...]
 * after:   [...] <-> [3] <-> [2] <-> [1] <-> [head] <-> [N] <-> [...]
 */
static inline void dqueue_reverse(struct dqueue_t *dqueue)
{
    dlist_reverse(&dqueue->head);
}



/*
 * dqueue_swap - Exchanges the contents of the containers.
 * Does not invoke any move, copy, or swap operations on individual elements.
 */
static inline void dqueue_swap(struct dqueue_t *dqueue1, struct dqueue_t *dqueue2)
{
    if(dqueue1 == dqueue2)
        return;

    DECLARE_DQUEUE(tmp);

    dqueue_splice_front(dqueue1, &tmp);
    dqueue_splice_front(dqueue2, dqueue1);
    dqueue_splice_front(&tmp, dqueue2);
}





//---------------- Get Data from node ----------------





/*
 * dqueue_data - get the struct (data) for this node
 *
 * node:   the node.
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node(dqueue_node) within the struct of data.
 */
#define dqueue_data(node, type, member) \
     (type *)( (const char *)node - offsetof(type, member) )



/*
 * dqueue_data_or_null - get the struct (data) for this node
 *
 * node:   the node.
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node(dqueue_node) within the struct of data.
 *
 * Note it returns NULL if the node is empty (not in dqueue).
 */
#define dqueue_data_or_null(node, type, member) \
    (dlist_empty(node) ? NULL : dqueue_data(node, type, member))



/*
 * dqueue_first_data - get the first struct (data) from a dqueue
 *
 * dqueue: the dqueue to take the element from.
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node within the struct of data.
 *
 * Note - dqueue don't have to  be empty.
 */
#define dqueue_first_data(dqueue, type, member) \
    dqueue_data((dqueue)->head.next, type, member)



/*
 * dqueue_last_data - get the last struct (data) from a dqueue
 *
 * dqueue: the dqueue to take the element from.
 * type:   the type of the struct of data this is embedded in.
 * member: the name of the node(dlist_head) within the struct of data.
 *
 * Note - dqueue don't have to  be empty.
 */
#define dqueue_last_data(dqueue, type, member) \
    dqueue_data((dqueue)->head.prev, type, member)





#endif // DQUEUE_H
