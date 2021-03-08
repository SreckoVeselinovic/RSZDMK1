#include <stdio.h>


if(a > b)
return a - b;
else
return b - a;


void PrintResult(int res)
{
printf("Result: %d\n", res);
}


int main()
{
int a = 3;
int b = 8;
int c;
if(a > b)
return a - b;
else
return b - a;

PrintResult(c);
return 0;
}