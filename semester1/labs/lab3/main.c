#include <stdio.h>
#define SIZE 7

void printMatrix(double* matrix, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%.2lf\t", *(matrix + i * cols + j));
    }
    printf("\n");
  }
}

int main(int argc, char* argv[]) {
  double matrix[][SIZE] = {
    {  5.35,  3.79, -4.93,  3.31,  0.04, -8.31, -5.83 },
    { -7.33,  5.35,  6.19, -0.54, -2.31, -4.05,  2.64 },
    { -7.47, -1.39, -2.57, -2.88,  8.03,  6.88,  0.61 },
    { -8.85, -9.88,  7.63,  0.00,  2.70,  2.80, -9.33 },
    {  2.09, -4.18,  4.82, -5.82, -2.57, -6.83,  5.09 },
    {  6.14,  9.96,  7.74,  1.23, -7.13,  5.35, -1.25 },
    { -7.53,  7.17, -1.72,  2.13,  1.62,  4.55, -2.57 },
  };

  printf("Initial matrix:\n");
  printMatrix((double*)matrix, SIZE, SIZE);

  int minPos = 0;
  int maxPos = 0;
  for (int i = 1; i < SIZE; i++) {
    const double elem = matrix[i][i];

    if (elem < matrix[minPos][minPos]) {
      minPos = i;
    }
    else if (elem >= matrix[maxPos][maxPos]) {
      maxPos = i;
    }
  }

  printf("\nMin value = %.2lf, position = %d\n", matrix[minPos][minPos], minPos);
  printf("Max value = %.2lf, position = %d\n\n", matrix[maxPos][maxPos], maxPos);

  // swap
  double temp = matrix[minPos][minPos];
  matrix[minPos][minPos] = matrix[maxPos][maxPos];
  matrix[maxPos][maxPos] = temp;

  printf("Result matrix:\n");
  printMatrix((double*)matrix, SIZE, SIZE);
  
  return 0;
}