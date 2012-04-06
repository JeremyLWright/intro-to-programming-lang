#include <stdio.h>


#define swapByName(x, y) \
    x = x + y;\
    y = x - y;\
    x = x - y;

void swap(int& x, int& y)
{
    x = x + y;
    y = x - y;
    x = x - y;
}

void swapByValueResult(int& x, int& y)
{
    int tx = x;
    int ty = y;
    tx = tx + ty;
    ty = tx - ty;
    tx = tx - ty;
    x = tx;
    y = ty;

}

main()
{
    int i = 1;
    int a[3];
    a[0] = 2;
    a[1] = 1;
    a[2] = 0;

    swapByValueResult(i, a[i]);
    printf("%d %d %d %d\n", i, a[0], a[1], a[2]);
    swapByValueResult(a[i], a[i]);
    printf("%d %d %d\n", a[0], a[1], a[2]);
    return 0;
}

