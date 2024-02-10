#include <stdio.h>

#define ROWS 7
#define COLS 10

void swap(int* x, int* y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

void sort(int matrix[][COLS], int length) {
  int left = 0, right = length - 1;
  int changes = 1;
  
  while (left < right && changes == 1) {
    changes = 0;

    for (int i = left; i < right; i++) {
      if (matrix[i][i] < matrix[i + 1][i + 1]) {
        swap(&matrix[i][i], &matrix[i + 1][i + 1]);
        changes = 1;
      }
    }
    right--;

    for (int i = right; i > left; i--) {
      if (matrix[i][i] > matrix[i - 1][i - 1]) {
        swap(&matrix[i][i], &matrix[i - 1][i - 1]);
        changes = 1;
      }
    }
    left++;
  }
}

void printMatrix(int matrix[][COLS], int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%6d", matrix[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char const *argv[]) {
  int matrix[][COLS] = {
    { -23, -85,  37, -37,  68,  62, -80,  80,   0, -34 },
    {  27,  58, -40,  36,  45, -33,  77,   5,  26, -35 },
    {  46, -98,   6, -55,  -8, -85,  26,  14,  35,  87 },
    { -25, -36,  -5,  88, -84, -54, -84,  55, -95,   6 },
    { -98,  41,  65,  14,  27,  13,  46,  88, -69, -24 },
    { -97,   7,  95,  15, -84, -61,  72, -71,  90, -78 },
    {  75,  74,  94,  57,  44,  77,  80, -45, -20,  86 },
    {  70,  71, -57, -38, -64,  28,  63, -46,  43, -78 },
    {  53, -60,  20, -51, -40,   5, -93,  47,  68,  -9 },
    { -91,   6,  15, -93,  66,  71,  22,  68, -91, -94 },
  };

  printf("Initial matrix:\n");
  printMatrix(matrix, ROWS, COLS);
  printf("\n");

  sort(matrix, ROWS);
  
  printf("Result matrix:\n");
  printMatrix(matrix, ROWS, COLS);
  
  return 0;
}
