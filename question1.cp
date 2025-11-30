#include <stdio.h>    // standard input/output functions (printf, scanf)
#include <stdlib.h>   // memory allocation (malloc, free), exit codes

/* Iterative: build a result buffer by placing odds from left and evens from right.
   Does one pass over the input array. */
void iterative_rearrange(int arr[], int n) {
    if (n <= 1) return;                      // nothing to do for empty or single-element array
    int *res = (int*)malloc(n * sizeof(int)); // allocate temporary array of size n
    if (!res) return;                        // allocation failed -> just return (could handle error)
    int left = 0, right = n - 1;             // pointers for placing odds (left) and evens (right)
    for (int i = 0; i < n; ++i) {            // iterate over every element in the input
        if (arr[i] % 2 != 0) {               // arr[i] is odd
            res[left++] = arr[i];            // place at left index then increment left
        } else {                             // arr[i] is even
            res[right--] = arr[i];           // place at right index then decrement right
        }
    }
    /* copy back into arr */
    for (int i = 0; i < n; ++i) arr[i] = res[i]; // copy rearranged result into original array
    free(res);                              // free temporary memory
}

/* Recursive: in-place two-pointer partition
   Moves left forward until an even is found, moves right backward until an odd is found;
   swap and recurse on the inner subarray. */
void recursive_rearrange(int arr[], int left, int right) {
    if (left >= right) return;              // base case: zero or one element between pointers

    /* advance left to first even */
    while (left < right && (arr[left] % 2 != 0)) left++;
    /* move right to first odd from the end */
    while (left < right && (arr[right] % 2 == 0)) right--;

    if (left < right) {
        int tmp = arr[left];                 // swap arr[left] and arr[right]
        arr[left] = arr[right];
        arr[right] = tmp;
        /* recurse on inner subarray */
        recursive_rearrange(arr, left + 1, right - 1);
    }
}

/* Helper to print array */
void print_arr(const char *label, int arr[], int n) {
    printf("%s:", label);
    for (int i = 0; i < n; ++i) printf(" %d", arr[i]); // print all elements separated by spaces
    printf("\n");
}

/* Main: read input ONCE, then run both algorithms on copies and print results. */
int main(void) {
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n < 0) {    // read the size and validate it's a non-negative integer
        printf("Invalid n\n");
        return 1;
    }

    int *orig = (int*)malloc(n * sizeof(int)); // allocate array to store input values
    if (!orig && n > 0) return 1;            // allocation failed, exit with error

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &orig[i]) != 1) {    // read each integer; validate scanf succeeded
            printf("Invalid input\n");
            free(orig);
            return 1;
        }
    }
    /* Input scanned/read only once (done above). */

    /* Prepare copies for the two algorithms */
    int *a_iter = (int*)malloc(n * sizeof(int));
    int *a_rec  = (int*)malloc(n * sizeof(int));
    if ((!a_iter || !a_rec) && n > 0) { free(orig); free(a_iter); free(a_rec); return 1; }
    for (int i = 0; i < n; ++i) { a_iter[i] = orig[i]; a_rec[i] = orig[i]; }

    printf("\nOriginal array:");
    print_arr(" Original", orig, n);

    /* Iterative result */
    iterative_rearrange(a_iter, n);
    print_arr("Iterative result", a_iter, n);

    /* Recursive result */
    recursive_rearrange(a_rec, 0, n - 1);
    print_arr("Recursive result", a_rec, n);

    /* free memory */
    free(orig);
    free(a_iter);
    free(a_rec);
    return 0;
}
