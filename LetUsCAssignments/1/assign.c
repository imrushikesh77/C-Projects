#include <stdio.h>

int main()
{
    int num;
    scanf("%d", &num);
    int add = 0;
    int ans = 0;
    while (num > 0)
    {
        int digit = num % 10;
        digit++;
        ans = ans * 10 + digit % 10 + add;
        add = digit / 10;
        num = num / 10;
    }
    int revAns = 0;
    while (ans > 0)
    {
        int digit = ans % 10;
        revAns = revAns * 10 + digit;
        ans = ans / 10;
    }
    printf("%d", revAns);
}