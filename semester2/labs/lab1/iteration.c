#include <stdio.h>

double myCos(double x, unsigned n) {
  double res = 1.0;
  double previos = res;
  for (int i = 1; i < n; i++) {
    previos = -previos * (x * x) / (4 * i * i - 2 * i);
    res += previos;
  }
  return res;
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
