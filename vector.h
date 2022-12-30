/**
  * Copyright 2022 Ivan Machugovskiy
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy
  * of this software and associated documentation files (the "Software"), to
  * deal in the Software without restriction, including without limitation the
  * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
  * sell copies of the Software, and to permit persons to whom the Software is
  * furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in
  * all copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  * IN THE SOFTWARE.
  */

#ifndef C_VECTOR_H
#define C_VECTOR_H

#include "instantiation.h"

struct vector__header {
    int _size;
    int _capacity;
};

/** Typed vector hidden instantiation */
#define _do_instantiate_vector(struct_name, type, arg) typedef type *struct_name

/** Typed vector instantiation */
#define instantiate_vector(type) INSTANTIATION_INSTANTIATE_CONTAINER(vector, type, )

/** Typed vector initialization */
#define vector(type) INSTANTIATION_GET_CONTAINER_TYPE(vector, type)
void *init_vector() {
    struct vector__header *header = malloc(sizeof(struct vector__header));
    header->_size = 0;
    header->_capacity = 0;
    return header + 1;
}

/** Method that returns number of items in vector */
#define vector_size(vector) ((struct vector__header *)*(vector)-1)->_size

/** Method that pushes given value to the end of the vector */
#define vector_push(vector, value)                                             \
  do {                                                                         \
    __typeof__((vector)) _vector = (vector);                                   \
    struct vector__header *header = (struct vector__header *)*_vector - 1;     \
    if (header->_size == header->_capacity) {                                  \
      size_t _new_capacity = header->_capacity * 2 + 1;                        \
      header = realloc(header, sizeof(struct vector__header) +                 \
                                   _new_capacity * sizeof(**_vector));         \
      header->_capacity = _new_capacity;                                       \
      *_vector = (void *)(header + 1);                                         \
    }                                                                          \
    (*_vector)[header->_size++] = (value);                                     \
  } while (0)

/** Method that removes item from the back of the vector */
#define vector_pop(vector)                                                     \
  do {                                                                         \
    struct vector__header *header = (struct vector__header *)*(vector)-1;      \
    header->_size--;                                                           \
  } while (0)

/** Method that clears all the memory occupied by vector */
#define vector_destroy(vector) free((struct vector__header *)*(vector)-1)

#endif //C_VECTOR_H
