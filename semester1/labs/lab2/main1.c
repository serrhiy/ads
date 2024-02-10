#include<stdio.h>
#include<math.h>

double f(unsigned n, unsigned* cntOperations) {

  double result = 1;
  unsigned cnt = 4;     // =1 | =1 | *cntOperations | = 

  for (int i = 1; i <= n; i++) {

    double denominator = 0.0;
    for (int j = 1; j <= i; j++) {
      denominator = denominator + sin(j);
      cnt += 6;                           // <= | ++ | = | + | sin | jmp
    }
    
    result = result * ( ( cos(i) + 1 ) / denominator );
    cnt += 10;            // <= | ++ | =0.0 | =1 | = | * | cos | + | / | jmp 
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