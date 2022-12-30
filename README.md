# ❓ What is this repository about

# 🧰 How to implement custom generic data structure

# 🚩 Usage examples
## Example for [stack](https://github.com/m0t9/c-generics/blob/master/stack.h)

## Example for [vector](https://github.com/m0t9/c-generics/blob/master/vector.h)
### Code
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
### Output
```
3 products in list
1. Potatoes
2. Carrots
3. Milk
```

