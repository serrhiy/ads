#include <stdio.h>

double wrapMyCos(double x, unsigned n, double* previos) {
  if (n <= 1) {
    printf("F%u comeback: %lf\n", n, *previos);
    return *previos;
  }
  const double totalSum = wrapMyCos(x, n - 1, previos);
  const unsigned i = n - 1;
  const double next = -*previos * (x * x) / (4 * i * i - 2 * i);
  printf("F%u comeback: %lf\n", n, next);
  const double sum = totalSum + next;
  *previos = next;
  return sum;
}

double myCos(double x, unsigned n) {
  double previos = 1.0;
  return wrapMyCos(x, n, &previos);
}

int main(int argc, char const *argv[]) {
  const unsigned n = 5;
  double x;
  printf("Enter x: ");
  scanf("%lf", &x);
  const double res = myCos(x, n);
  printf("cos(%lf) = %lf\n", x, res);
  return 0;
}
