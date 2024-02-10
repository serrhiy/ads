#include <stdio.h>

double wrapMyCos(double x, unsigned i, unsigned n, double previos, double totalSum) {
  if (i >= n) return totalSum;
  const double next = -previos * (x * x) / (4 * i * i - 2 * i);
  printf("F%u descent: %lf\n", i + 1, next);
  const double sum = totalSum + next;
  return wrapMyCos(x, i + 1, n, next, sum);
}

double myCos(double x, unsigned n) {
  printf("F%u descent: %lf\n", 1, 1.0);
  return wrapMyCos(x, 1, n, 1.0, 1.0);
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
