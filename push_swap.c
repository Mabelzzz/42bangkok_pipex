// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>

// #define MAX_SIZE 500
// #define BASE 10

// int m = 0;

// typedef struct Stack {
//     int data[MAX_SIZE];
//     int top;
// } Stack;

// void push(Stack *stack, int value) {
//     stack->top++;
//     stack->data[stack->top] = value;
//     m++;
// }

// int pop(Stack *stack) {
//     int value = stack->data[stack->top];
//     stack->top--;
//     return value;
//     // m++;
// }

// bool is_empty(Stack *stack) {
//     return stack->top == -1;
// }

// void rotate(Stack *stack) {
//     if (stack->top >= 1) {
//         int first = stack->data[0];
//         for (int i = 0; i < stack->top; i++) {
//             stack->data[i] = stack->data[i + 1];
//         }
//         stack->data[stack->top] = first;
//         m++;
//     }
// }

// void radix_sort(Stack *a, Stack *b) {
//     bool sorted = false;
//     int digit_place = 1;

//     Stack buckets[BASE];
//     for (int i = 0; i < BASE; i++) {
//         buckets[i].top = -1;
//     }

//     while (!sorted) {
//         sorted = true;

//         while (!is_empty(a)) {
//             int value = pop(a);
//             int bucket_index = (value / digit_place) % BASE;

//             if (bucket_index > 0) {
//                 sorted = false;
//             }

//             push(&buckets[bucket_index], value);
//         }

//         for (int i = 0; i < BASE; i++) {
//             while (!is_empty(&buckets[i])) {
//                 push(a, pop(&buckets[i]));
//             }
//         }

//         digit_place *= BASE;
//     }
// }

// int main() {
//     Stack a = {.top = -1};
//     Stack b = {.top = -1};

//     // Fill stack a with random unique numbers
//     for (int i = 0; i < MAX_SIZE; i++) {
//         int value;
//         bool unique;
//         do {
//             value = rand() % 1000;
//             unique = true;
//             for (int j = 0; j <= a.top; j++) {
//                 if (a.data[j] == value) {
//                     unique = false;
//                     break;
//                 }
//             }
//         } while (!unique);
//         push(&a, value);
//     }

//     radix_sort(&a, &b);
//     // Print the sorted stack a
//     while (!is_empty(&a)) {
//         printf("%d ", pop(&a));
//     }
//     printf("m = %d\n", m);

//     return 0;
// }
// #include "push_swap.h"

void sort_stack(t_stack *a, t_stack *b)
{
    if (stack_size(a) <= 1)
        return;

    int pivot = stack_median(a);
    int pushed = 0;

    while (!stack_is_sorted(a))
    {
        if (stack_top(a) < pivot)
        {
            push(b, a);
            pushed++;
        }
        else
            rotate(a);
    }

    while (pushed--)
        push(a, b);

    sort_stack(a, b);
    while (stack_size(b))
        push(a, b);
}

// Sorts stack a using the quicksort algorithm
void quicksort(t_stack *a, t_stack *b, int size)
{
    if (size <= 3)
    {
        sort_small(a, b, size);
        return ;
    }
    int pivot = get_median(a, size);
    int ra_count = 0;
    int pb_count = 0;
    while (size--)
    {
        if (a->top->data <= pivot)
        {
            push(b, a, "pb\n");
            pb_count++;
        }
        else
        {
            rotate(a, "ra\n");
            ra_count++;
        }
    }
    while (ra_count--)
        reverse_rotate(a, "rra\n");
    quicksort(a, b, pb_count);
    while (pb_count--)
        push(a, b, "pa\n");
    quicksort(a, b, a->size);
}

// Sorts stack a using the push_swap algorithm
void push_swap(t_stack *a, t_stack *b)
{
    if (a->size <= 3)
    {
        sort_small(a, b, a->size);
        return ;
    }
    quicksort(a, b, a->size);
    while (b->size > 0)
    {
        int min_distance = get_min_distance(b, a);
        if (min_distance > b->size / 2)
            min_distance = b->size - min_distance;
        while (min_distance--)
        {
            if (get_direction(b, a) == 1)
                rotate(b, "rb\n");
            else
                reverse_rotate(b, "rrb\n");
        }
        push(a, b, "pa\n");
    }
}

// Main function
int main(int argc, char **argv)
{
    if (argc < 2)
        return (0);
    t_stack *a = create_stack(argc - 1);
    if (!a)
        error_exit();
    if (!fill_stack(a, argv))
    {
        free_stack(a);
        error_exit();
    }
    t_stack *b = create_stack(a->size);
    if (!b)
    {
        free_stack(a);
        error_exit();
    }
    push_swap(a, b);
    free_stack(a);
    free_stack(b);
    return (0);
}
