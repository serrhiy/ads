#include<stdio.h>
#include<math.h>

double f(unsigned n, unsigned* cntOperations) {

  double result = 1;
  unsigned cnt = 5;    // =1 | =0.0 | =1 | *cntOperations | = 

  double sinsSum = 0.0;

  for (int i = 1; i <= n; i++) {

    sinsSum = sinsSum + sin(i);
    
    result = result * ( ( cos(i) + 1 ) / sinsSum );

    cnt += 11;            // <= | ++ | = | + | sin | = | * | cos | + | / | jmp
  }
  
  *cntOperations = cnt;
  return result;
}

int main(int argc, char* argv[]) {
  unsigned n, countOfOperations;

  printf("Enter natural number: ");
  scanf("%u", &n);

  double res = f(n, &countOfOperations);

  printf("f(%d) = %.7lf\nCount of operations = %u\n", n, res, countOfOperations);

  return 0;
}