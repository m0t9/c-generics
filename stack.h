#ifndef C_STACK_H
#define C_STACK_H

#include "instantiation.h"

/** Typed stack hidden instantiation */
#define _do_instantiate_stack(struct_name, type, arg)                                                  \
struct struct_name##__item {                                                                           \
    type _value;                                                                                       \
    struct struct_name##__item *_next;                                                                 \
};                                                                                                     \
typedef struct struct_name {                                                                           \
    struct struct_name##__item *_top;                                                                  \
    size_t _size;                                                                                      \
} struct_name

/** Typed stack instantiation */
#define instantiate_stack(type) INSTANTIATION_INSTANTIATE_CONTAINER(stack, type, )

/** Typed stack initialization */
#define stack(type) INSTANTIATION_GET_CONTAINER_TYPE(stack, type)
#define init_stack() {._size = 0, ._top = NULL}

/** Method that returns number of items in stack */
#define stack_size(stack) (stack)->_size

/** Method that returns true(1) if stack is empty */
#define stack_empty(stack) ((stack)->_size == 0)

/** Method that returns item from the top of the stack */
#define stack_top(stack) (stack)->_top->_value

/** Method that pushes given value to top of the stack */
#define stack_push(stack, value) do {                                                                  \
    typeof((stack)) _stack = (stack);                                                                  \
    typeof(_stack->_top) new_top = (typeof(_stack->_top))malloc(sizeof(typeof(*_stack->_top)));        \
    new_top->_value = value;                                                                           \
    new_top->_next = _stack->_top;                                                                     \
    _stack->_top = new_top;                                                                            \
    _stack->_size++;                                                                                   \
} while(0)

/** Method that removes item from the top of the stack */
#define stack_pop(stack) do {                                                                          \
    typeof((stack)) _stack = (stack);                                                                  \
    typeof(_stack->_top) old_top = _stack->_top;                                                       \
    _stack->_top = _stack->_top->_next;                                                                \
    free(old_top);                                                                                     \
    _stack->_size--;                                                                                   \
} while(0)

/** Method that swaps content of two stacks */
#define stack_swap(stack_1, stack_2) do {                                                              \
    typeof((stack_1)) _stack_1 = (stack_1);                                                            \
    typeof((stack_2)) _stack_2 = (stack_2);                                                            \
    typeof(*_stack_1) temp_stack = *_stack_1;                                                          \
    *_stack_1 = *_stack_2;                                                                             \
    *_stack_2 = temp_stack;                                                                            \
} while(0)

/** Method that removes all items from the stack */
#define stack_clear(stack) do {                                                                        \
typeof((stack)) _stack_t = (stack);                                                                    \
while(!stack_empty(_stack_t))stack_pop(_stack_t);} while(0)

#endif //C_STACK_H
