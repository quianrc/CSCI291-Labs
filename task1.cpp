#include <stdio.h>
#include <stdbool.h>
#define SIZE 24
#define nRows 8
#define nCols 3
// FUNCTION PROTOTYPES
void print_array(int array[], int length);
void print_matrix(int mat[][nCols], int rows);
void set_array(int arr[], int length);
void rem_align(int arr[], int length, int pos);
void insert_align(int arr[], int length, int pos, int value);
void reshape(int arr[], int length, int arr2d[nRows][nCols]);
void print_trans_matrix(int arr2d[nRows][nCols]);
bool found_duplicate(int arr[], int length);
void flip_array(int arr[], int length, int flipped[]);

// MAIN FUNCTION
int main() {
    int arr[SIZE];
    int arr2d[nRows][nCols];
    int flipped[SIZE];
    // 1. Initialize array elements to their index
    set_array(arr, SIZE);
    printf("\n--- Original Array ---\n");
    print_array(arr, SIZE);
    // 2. Remove element at position 5
    rem_align(arr, SIZE, 5);
    printf("\n--- After Removing index 5 ---\n");
    print_array(arr, SIZE);
    // 3. Insert value 99 at position 3
    insert_align(arr, SIZE, 3, 99);
    printf("\n--- After Inserting 99 at index 3 ---\n");
    print_array(arr, SIZE);
    // 4. Reshape into 2D array (only valid if SIZE == nRows*nCols)
    reshape(arr, SIZE, arr2d);
    printf("\n--- Reshaped Matrix ---\n");
    print_matrix(arr2d, nRows);
    // 5. Print matrix column-by-column
    printf("\n--- Transposed (Column-wise) Matrix ---\n");
    print_trans_matrix(arr2d);
    // 6. Check for duplicates
    if (found_duplicate(arr, SIZE))
        printf("\nDuplicates found.\n");
    else
        printf("\nNo duplicates found.\n");
    // 7. Flip array
    flip_array(arr, SIZE, flipped);
    printf("\n--- Flipped Array ---\n");
    print_array(flipped, SIZE);
    return 0;
}
// FUNCTION DEFINITIONS
void print_array(int array[], int length) {
    for (int i = 0; i < length; i++)
        printf("array[%d] = %d\n", i, array[i]);
}
void print_matrix(int mat[][nCols], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < nCols; j++)
            printf("%4d ", mat[i][j]);
        printf("\n");
    }
}
void set_array(int arr[], int length) {
    for (int i = 0; i < length; i++)
        arr[i] = i;
}
void rem_align(int arr[], int length, int pos) {
    if (pos < 0 || pos >= length) {
        printf("Invalid position: %d\n", pos);
        return;
    }
    for (int i = pos; i < length - 1; i++)
        arr[i] = arr[i + 1];
    arr[length - 1] = arr[length - 2]; // optional, just to fill end
}
void insert_align(int arr[], int length, int pos, int value) {
    if (pos < 0 || pos >= length) {
        printf("Invalid position: %d\n", pos);
        return;
    }
    for (int i = length - 1; i > pos; i--)
        arr[i] = arr[i - 1];
    arr[pos] = value;
}
void reshape(int arr[], int length, int arr2d[nRows][nCols]) {
    if (length != nRows * nCols) {
        printf("Error: SIZE must equal nRows * nCols!\n");
        return;
    }
    int k = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            arr2d[i][j] = arr[k++];
}
void print_trans_matrix(int arr2d[nRows][nCols]) {
    for (int j = 0; j < nRows; j++ ) {
        for (int i=0;i<nRows; i++)
        printf("%4d", arr2d[i][j]);
        printf("\n");
    }
}
bool found_duplicate (int arr[],int length) {
    for (int i = 0; i < length; i++)
    for (int j = i + 1;j < length; j++)
    if (arr[i]==arr[j])
    return true;
    return false;
}

void flip_array(int arr[], int length, int flipped[]) {
    for (int i = 0 ; i < length; i++)
    flipped[i]=arr[length-1-i];
}
