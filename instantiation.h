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

#include "stdlib.h"

#ifndef C_INSTANTIATION_H
#define C_INSTANTIATION_H

#define INSTANTIATION_LPAREN (

#define INSTANTIATION_EMPTY(...)
#define INSTANTIATION_EVAL(...) __VA_ARGS__
#define INSTANTIATION_EVAL_ID() INSTANTIATION_EVAL
#define INSTANTIATION_DEFER(...) __VA_ARGS__ INSTANTIATION_EMPTY()

#define INSTANTIATION_CONCAT(a, b) a##b
#define INSTANTIATION_CONCAT1(a, b) INSTANTIATION_CONCAT(a, b)

#define INSTANTIATION_INSTANTIATE_CONTAINER(class, type, arg)                  \
  INSTANTIATION_RETYPE(class, INSTANTIATION_DO_INSTANTIATE_CONTAINER, type, arg)
#define INSTANTIATION_DO_INSTANTIATE_CONTAINER(class, instantiated_type, type, \
                                               arg)                            \
  _do_instantiate_##class(instantiated_type, type, arg)

#define INSTANTIATION_GET_CONTAINER_TYPE(class, type)                          \
  INSTANTIATION_RETYPE(class, INSTANTIATION_DO_GET_CONTAINER_TYPE, type, )
#define INSTANTIATION_DO_GET_CONTAINER_TYPE(class, instantiated_type, type,    \
                                            arg)                               \
  instantiated_type

#define INSTANTIATION_RETYPE(class, callback, type, arg)                       \
  INSTANTIATION_HANDLE_TYPE(                                                   \
      class, callback, arg,                                                    \
      INSTANTIATION_EVAL(                                                      \
          INSTANTIATION_SANITIZE_PARSE_UNDERLYING INSTANTIATION_WRAP_PARENS(   \
              type)))
#define INSTANTIATION_SANITIZE_PARSE_UNDERLYING(underlying) underlying,

#define INSTANTIATION_HANDLE_TYPE(class, callback, arg, rest)                  \
  INSTANTIATION_HANDLE_TYPE1(class, callback, arg, rest, )
#define INSTANTIATION_HANDLE_TYPE1(class, callback, arg, underlying,           \
                                   modifiers, ...)                             \
  callback(class,                                                              \
           INSTANTIATION_CONCAT1(                                              \
               INSTANTIATION_EVAL(INSTANTIATION_CHECK_FIRST_EMPTY(             \
                   class, underlying,                                          \
                   INSTANTIATION_EVAL(INSTANTIATION_EVAL(                      \
                       INSTANTIATION_EVAL(INSTANTIATION_EVAL(                  \
                           INSTANTIATION_SPLIT_TYPE(underlying))))))),         \
               INSTANTIATION_SANITIZE_MODIFIERS(modifiers)),                   \
           underlying INSTANTIATION_REPARSE_MODIFIERS(modifiers), arg)

#define INSTANTIATION_CHECK_FIRST_EMPTY(...)                                   \
  INSTANTIATION_CHECK_FIRST_EMPTY1(__VA_ARGS__)
#define INSTANTIATION_CHECK_FIRST_EMPTY1(class, underlying, a, ...)            \
  INSTANTIATION_CHECK_FIRST_EMPTY2(INSTANTIATION_MAKE_COMMA a(), empty, class, \
                                   underlying, a, __VA_ARGS__)
#define INSTANTIATION_MAKE_COMMA() , full
#define INSTANTIATION_CHECK_FIRST_EMPTY2(...)                                  \
  INSTANTIATION_CHECK_FIRST_EMPTY3(__VA_ARGS__)
#define INSTANTIATION_CHECK_FIRST_EMPTY3(a, op, ...)                           \
  INSTANTIATION_CHECK_FIRST_EMPTY__##op(__VA_ARGS__)
#define INSTANTIATION_CHECK_FIRST_EMPTY__full(ignore, class, underlying, ...)  \
  INSTANTIATION_CONCAT_MANY1(class __VA_ARGS__)
#define INSTANTIATION_CHECK_FIRST_EMPTY__empty(class, type, ...)               \
  INSTANTIATION_CONCAT INSTANTIATION_LPAREN class##__, type

#define INSTANTIATION_CONCAT_MANY(arg) INSTANTIATION_CONCAT_MANY1(arg)
#define INSTANTIATION_CONCAT_MANY1(...)                                        \
  INSTANTIATION_CONCAT_MANY_IMPL(__VA_ARGS__, , , , , , )
#define INSTANTIATION_CONCAT_MANY_IMPL(a, b, c, d, e, f, ...) a##b##c##d##e##f

#define INSTANTIATION_SPLIT_TYPE(arg) INSTANTIATION_SPLIT_WORD__##arg)
#define INSTANTIATION_SPLIT_TYPE_ID() INSTANTIATION_SPLIT_TYPE
#define INSTANTIATION_SPLIT_WORD__int                                          \
  , __int INSTANTIATION_DEFER(INSTANTIATION_SPLIT_TYPE_ID)()                   \
        INSTANTIATION_LPAREN
#define INSTANTIATION_SPLIT_WORD__long                                         \
  , __long INSTANTIATION_DEFER(INSTANTIATION_SPLIT_TYPE_ID)()                  \
        INSTANTIATION_LPAREN
#define INSTANTIATION_SPLIT_WORD__float                                        \
  , __float INSTANTIATION_DEFER(INSTANTIATION_SPLIT_TYPE_ID)()                 \
        INSTANTIATION_LPAREN
#define INSTANTIATION_SPLIT_WORD__double                                       \
  , __double INSTANTIATION_DEFER(INSTANTIATION_SPLIT_TYPE_ID)()                \
        INSTANTIATION_LPAREN
#define INSTANTIATION_SPLIT_WORD__signed                                       \
  , __signed INSTANTIATION_DEFER(INSTANTIATION_SPLIT_TYPE_ID)()                \
        INSTANTIATION_LPAREN
#define INSTANTIATION_SPLIT_WORD__unsigned                                     \
  , __unsigned INSTANTIATION_DEFER(INSTANTIATION_SPLIT_TYPE_ID)()              \
        INSTANTIATION_LPAREN
#define INSTANTIATION_SPLIT_WORD__struct                                       \
  , __struct__, INSTANTIATION_SPLIT_IDENTITY INSTANTIATION_LPAREN
#define INSTANTIATION_SPLIT_WORD__enum                                         \
  , __enum__, INSTANTIATION_SPLIT_IDENTITY INSTANTIATION_LPAREN
#define INSTANTIATION_SPLIT_WORD__void                                         \
  , __void INSTANTIATION_DEFER(INSTANTIATION_SPLIT_TYPE_ID)()                  \
        INSTANTIATION_LPAREN
#define INSTANTIATION_SPLIT_WORD__bool                                         \
  , __bool INSTANTIATION_DEFER(INSTANTIATION_SPLIT_TYPE_ID)()                  \
        INSTANTIATION_LPAREN
#define INSTANTIATION_SPLIT_WORD___Bool                                        \
  , ___Bool INSTANTIATION_DEFER(INSTANTIATION_SPLIT_TYPE_ID)()                 \
        INSTANTIATION_LPAREN
#define INSTANTIATION_SPLIT_WORD__SANITIZE_PARSE_UNDERLYING                    \
  INSTANTIATION_DEFER(INSTANTIATION_SPLIT_TYPE_ID)() INSTANTIATION_LPAREN
#define INSTANTIATION_SPLIT_WORD__ INSTANTIATION_EMPTY(
#define INSTANTIATION_SPLIT_IDENTITY(arg) arg

#define INSTANTIATION_SANITIZE_MODIFIERS(arg)                                  \
  INSTANTIATION_CONCAT_MANY(INSTANTIATION_APPEND_DROP(INSTANTIATION_EVAL(      \
      INSTANTIATION_EVAL(INSTANTIATION_EVAL(INSTANTIATION_EVAL(                \
          __, INSTANTIATION_SANITIZE_MODIFIERS_STEP arg))))))
#define INSTANTIATION_SANITIZE_MODIFIERS_STEP(arg)                             \
  p, INSTANTIATION_DEFER(INSTANTIATION_SANITIZE_MODIFIERS_STEP_ID)()
#define INSTANTIATION_SANITIZE_MODIFIERS_STEP_ID()                             \
  INSTANTIATION_SANITIZE_MODIFIERS_STEP
#define INSTANTIATION_SANITIZE_MODIFIERS_STEP_DROP x

#define INSTANTIATION_REPARSE_MODIFIERS(arg)                                   \
  INSTANTIATION_APPEND_DROP(                                                   \
      INSTANTIATION_EVAL(INSTANTIATION_EVAL(INSTANTIATION_EVAL(                \
          INSTANTIATION_EVAL(INSTANTIATION_REPARSE_MODIFIERS_STEP arg)))))
#define INSTANTIATION_REPARSE_MODIFIERS_STEP(arg)                              \
  *INSTANTIATION_DEFER(INSTANTIATION_REPARSE_MODIFIERS_STEP_ID)()
#define INSTANTIATION_REPARSE_MODIFIERS_STEP_ID()                              \
  INSTANTIATION_REPARSE_MODIFIERS_STEP
#define INSTANTIATION_REPARSE_MODIFIERS_STEP_DROP

#define INSTANTIATION_APPEND_DROP(...) INSTANTIATION_APPEND_DROP1(__VA_ARGS__)
#define INSTANTIATION_APPEND_DROP1(...) __VA_ARGS__##_DROP

#define INSTANTIATION_WRAP_PARENS(arg)                                         \
  INSTANTIATION_CHOOSE(                                                        \
      (arg), INSTANTIATION_CONCAT1(                                            \
                 INSTANTIATION_DROP_,                                          \
                 INSTANTIATION_EVAL(                                           \
                     INSTANTIATION_PAREN_FALLBACK INSTANTIATION_CONCAT1(       \
                         INSTANTIATION_DEPARENTHESIZE_,                        \
                         INSTANTIATION_WRAP_PARENS_IMPL(arg)))))
#define INSTANTIATION_WRAP_PARENS_IMPL(arg) INSTANTIATION_WRAP_PARENS_CHECK_PAREN2(INSTANTIATION_WRAP_PARENS_CHECK_PAREN arg))
#define INSTANTIATION_WRAP_PARENS_CHECK_PAREN(arg) INSTANTIATION_HAS_PAREN(arg)
#define INSTANTIATION_WRAP_PARENS_CHECK_PAREN2(arg2)                           \
  INSTANTIATION_CONCAT(INSTANTIATION_REMOVE_, arg2)
#define INSTANTIATION_REMOVE_INSTANTIATION_WRAP_PARENS_CHECK_PAREN INSTANTIATION_WRAP_PARENS_ADD(
#define INSTANTIATION_REMOVE_INSTANTIATION_HAS_PAREN(arg) 1((arg)
#define INSTANTIATION_WRAP_PARENS_ADD(arg) INSTANTIATION_WRAP_PARENS_ADD_WORD__##arg)
#define INSTANTIATION_WRAP_PARENS_ADD_WORD__int 1((int)
#define INSTANTIATION_WRAP_PARENS_ADD_WORD__long 1((long)
#define INSTANTIATION_WRAP_PARENS_ADD_WORD__float 1((float)
#define INSTANTIATION_WRAP_PARENS_ADD_WORD__double 1((double)
#define INSTANTIATION_WRAP_PARENS_ADD_WORD__signed 1((signed)
#define INSTANTIATION_WRAP_PARENS_ADD_WORD__unsigned 1((unsigned)
#define INSTANTIATION_WRAP_PARENS_ADD_WORD__struct 0(struct
#define INSTANTIATION_WRAP_PARENS_ADD_WORD__enum 0(enum
#define INSTANTIATION_WRAP_PARENS_ADD_WORD__void 1((void)
#define INSTANTIATION_WRAP_PARENS_ADD_WORD__bool 1((bool)
#define INSTANTIATION_WRAP_PARENS_ADD_WORD___Bool 1((_Bool)
#define INSTANTIATION_DEPARENTHESIZE_0(arg) (arg)
#define INSTANTIATION_DEPARENTHESIZE_1(arg) arg

#define INSTANTIATION_PAREN_FALLBACK(arg) OK(arg)
#define INSTANTIATION_DROP_OK(arg) OK, (arg)
#define INSTANTIATION_DROP_INSTANTIATION_PAREN_FALLBACK FAIL, (

#define INSTANTIATION_CHOOSE(...) INSTANTIATION_CHOOSE1(__VA_ARGS__)
#define INSTANTIATION_CHOOSE1(a, choice, b) INSTANTIATION_CHOOSE_##choice(a, b)
#define INSTANTIATION_CHOOSE_OK(a, b) b
#define INSTANTIATION_CHOOSE_FAIL(a, b) a

#endif // C_INSTANTIATION_H
