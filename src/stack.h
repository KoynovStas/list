/*
 * stack.h
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

#ifndef STACK_H
#define STACK_H

#include "list.h"





/*
 * The stack is a container adapter that gives the programmer
 * the functionality of a stack - specifically, a FILO (first-in, last-out).
 *
 * This adapter uses list like inner container.
 *
 *
 *  Algorithmic complexity:
 *
 *  stack_size    -   O(1)
 *  stack_top     -   O(1)
 *  stack_push    -   O(1)
 *  stack_pop     -   O(1)
 */





struct stack_t
{
    struct list_head head;
    size_t           size;
};





#define DECLARE_STACK(name) \
    struct stack_t name = { { &name.head }, 0 }



static inline void stack_init(struct stack_t *stack)
{
    stack->head.next = &stack->head;
    stack->size      = 0;
}



/*
 * stack_top - Returns pointer to the top element in the stack.
 * This is the most recently pushed element.
 * This element will be removed on a call to pop().
 * If stack is empty returns NULL.
 *
 * stack: the stack to work.
 *
 * ret: ptr   //pointer to the top element in the stack
 * ret: NULL  //if stack is empty.
 */
static inline struct list_head* stack_top(struct stack_t *stack)
{
    if( stack->size )
        return stack->head.next;
    else
        return NULL;
}



/*
 * stack_push - Pushes the given element (data) to the top of the stack.
 *
 * stack: the stack to work.
 * data:  the data for pushes.
 *
 * ret: none
 */
static inline void stack_push(struct list_head* data, struct stack_t *stack)
{
    list_push_front(data, &stack->head);
    stack->size++;
}



/*
 * stack_pop - Removes the top element from the stack.
 *
 * stack: the stack to work.
 *
 * ret: none
 */
static inline void stack_pop(struct stack_t *stack)
{
    if( !list_empty(&stack->head) )
    {
        list_pop_front(&stack->head);
        stack->size--;
    }
}





#endif // STACK_H
