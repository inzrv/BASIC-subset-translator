#include <stdio.h>
int main(void) {
  float n;
  float f1;
  float f2;
  float tmp;
  printf("Input n\n");
  scanf("%f", &n);
  if (n < 0) {
    printf("n should be greater than or equal to 0\n");
  }
  f1 = 0;
  f2 = 1;
  while (n > 0) {
    tmp = f1 + f2;
    f1 = f2;
    f2 = tmp;
    n = n - 1;
  }
  printf("%.2f\n", (float)(f1));
  return 0;
}
