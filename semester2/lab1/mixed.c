#include <stdio.h>

double wrapMyCos(double x, unsigned i, unsigned n, double previos) {
  if (i >= n) return 1.0;
  const double next = -previos * (x * x) / (4 * i * i - 2 * i);
  const double totalSum = wrapMyCos(x, i + 1, n, next);
  const double sum = next + totalSum;
  return sum;
}

double myCos(double x, unsigned n) {
  return wrapMyCos(x, 1, n, 1.0);
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
