#ifndef C_GENERICS_QUEUE_H
#define C_GENERICS_QUEUE_H

#include "instantiation.h"

/** Typed queue hidden instantiation */
#define _do_instantiate_queue(struct_name, type, arg)                                                   \
struct struct_name##__item {                                                                            \
    type _value;                                                                                        \
    struct struct_name##__item *_next, *_prev;                                                          \
};                                                                                                      \
typedef struct struct_name {                                                                            \
    struct struct_name##__item *_front, *_back;                                                         \
    size_t _size;                                                                                       \
} struct_name

/** Typed queue instantiation */
#define instantiate_queue(type) INSTANTIATION_INSTANTIATE_CONTAINER(queue, type, )

/** Typed queue initialization */
#define queue(type) INSTANTIATION_GET_CONTAINER_TYPE(queue, type)
#define init_queue() {._size = 0, ._front = NULL, ._back = NULL}

/** Method that returns number of items in queue */
#define queue_size(queue) ((queue)->_size)

/** Method that returns true(1) if queue is empty */
#define queue_empty(queue) ((queue)->_size == 0)

/** Method that returns item from the front of the queue */
#define queue_front(queue) ((queue)->_front->_value)

/** Method that returns item from the back of the queue */
#define queue_back(queue) ((queue)->_back->_value)

/** Method that pushes given value to back of the queue */
#define queue_push(queue, value) do {                                                                   \
    typeof(queue) _queue = (queue);                                                                     \
    typeof(_queue->_front) _new_item = (typeof(_queue->_front))malloc(sizeof(typeof(*_queue->_front))); \
    _new_item->_value = value;                                                                          \
    _new_item->_next = _new_item->_prev = NULL;                                                         \
    _queue->_size++;                                                                                    \
    if (_queue->_size == 1) _queue->_front = _queue->_back = _new_item;                                 \
    else {                                                                                              \
        _new_item->_next = _queue->_back;                                                               \
        _queue->_back->_prev = _new_item;                                                               \
        _queue->_back = _new_item;                                                                      \
    }                                                                                                   \
} while (0)

/** Method that removes item from the front of the queue */
#define queue_pop(queue) do {                                                                           \
    typeof(queue) _queue = (queue);                                                                     \
    typeof(_queue->_front) _new_front = _queue->_front->_prev;                                          \
    free(_queue->_front);                                                                               \
    _queue->_size--;                                                                                    \
    _queue->_front = _new_front;                                                                        \
    if (_new_front != NULL) _new_front->_next = NULL;                                                   \
} while(0)

/** Method that removes all items from the queue */
#define queue_clear(queue) do {                                                                         \
   typeof(queue) __queue = (queue);                                                                     \
    while (!queue_empty(__queue)) queue_pop(__queue);                                                   \
} while (0)

/** Method that swaps content of two queues */
#define queue_swap(queue_1, queue_2) do {                                                               \
    typeof((queue_1)) _queue_1 = (queue_1);                                                             \
    typeof((queue_2)) _queue_2 = (queue_2);                                                             \
    typeof(*_queue_1) temp_queue = *_queue_1;                                                           \
    *_queue_1 = *_queue_2;                                                                              \
    *_queue_2 = temp_queue;                                                                             \
} while(0)

#endif //C_GENERICS_QUEUE_H
