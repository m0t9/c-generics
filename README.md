# c-generics

## ❓ What is this repository about
C language does not support generics and templates. This repository introduces one of the possible (and convenient) ways to implement generic containers using C preprocessing macros.

## 🧰 How to implement custom generic data structure
1. Header file with any generic container implementation **must** include `instantiation.h` file, which allows programmer to use simpler and standardized typed container initialization.
2. Container ***instantiation*** should be implemented in implicit and explicit ways. Implicit instantiation is a `#define` directive that accepts arguments such as structure name, type (data type that structure will contain), arguments (optional instantiation parametres). This instantiation will explicitly create a ***template*** of data structure of the given type. This define name **must** have the form `_do_instantiate_<struct_name>`.
3. Explicit instantiation is a convenient way for programmer to create a template of data structure. This `#define` may have the form `instantiate_<struct_name>(type)` and substitute `INSTANTIATION_INSTANTIATE_CONTAINER(<struct_name>, <type>, )`.
4. To create an ***instance*** of previously described container header file **must** implement directive `#define <struct_name>(<type>)` that declares a type named `INSTANTIATION_GET_CONTAINER_NAME(<struct_name>, <type>)`.
5. Container methods can be implemented in different ways (either `#define` or regular functions). It may depend on container type or your ideology :)

You can check implementation details in our examples of [stack implementation](https://github.com/m0t9/c-generics/blob/master/stack.h) and [vector implementation](https://github.com/m0t9/c-generics/blob/master/vector.h).

## 🚩 Usage
### Example for [stack](https://github.com/m0t9/c-generics/blob/master/stack.h)
#### Code
```c
#include <stdio.h>
#include "stack.h"

typedef struct box {
    int weight;
    char *content;
} box;

instantiate_stack(box);

int main() {
    stack(box) storage = init_stack();

    box toolbox = {.weight = 5, .content = "tools"};
    box clothes = {.weight = 3, .content = "t-shirts, pants"};
    box paper = {.weight = 1, .content = "sheets of paper"};

    stack_push(&storage, toolbox);
    stack_push(&storage, clothes);
    stack_push(&storage, paper);

    printf("%lld boxes in storage\n", stack_size(&storage));
    while (!stack_empty(&storage)) {
        printf("Box with %s and weight %d kg.\n", stack_top(&storage).content, stack_top(&storage).weight);
        stack_pop(&storage);
    }
}
```
#### Output
```
3 boxes in storage
Box with sheets of paper and weight 1 kg.
Box with t-shirts, pants and weight 3 kg.
Box with tools and weight 5 kg.
```
### Example for [vector](https://github.com/m0t9/c-generics/blob/master/vector.h)
#### Code
```c
#include <stdio.h>
#include "vector.h"

instantiate_vector((char)(*));

int main() {
    vector((char)(*)) shopping_list = init_vector();

    vector_push(&shopping_list, "Potatoes");
    vector_push(&shopping_list, "Carrots");
    vector_push(&shopping_list, "Meat");
    vector_pop(&shopping_list);
    vector_push(&shopping_list, "Milk");

    printf("%d products in list\n", vector_size(&shopping_list));
    for (int i = 0; i < vector_size(&shopping_list); i++) {
        printf("%d. %s\n", i + 1, shopping_list[i]);
    }

    vector_destroy(&shopping_list);
    return 0;
}
```
#### Output
```
3 products in list
1. Potatoes
2. Carrots
3. Milk
```
## 🌟 I express my gratitude to [Ivanq](https://github.com/imachug) for his great contribution!
