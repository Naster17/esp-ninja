#include <stdio.h>

#define TH 20

int main(void)
{

    int a = 21;
    printf("a: %d TH: %d\n", a, -TH);
    if (a <= TH && a >= -TH)
    {
        printf("wee!\n");
    }
    return 0;
}
