#include <stdio.h>

int Calculation(int a, int b)
{
if(a > b)
return a - b;
else
return b - a;
}

void PrintResult(int res)
{
printf("Result: %d\n", res);
}


int main()
{
int a = 3;
int b = 8;
int c;
Calculation (a,b);
PrintResult(c);
return 0;
}