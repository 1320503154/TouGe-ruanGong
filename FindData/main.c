#include <stdio.h>

int find_pos(int data[], int n, int key)
{ // 在数组data中查找给定数据key,n表示数组中数据元素的个数
    /*------------begin-----------------*/
    for (int i = 0; i < n; i++)
    {
        if (data[i] == key)
            return i;
    }
    return -1;
    /*------------end-----------------*/
}

int main(void)
{
    int a[] = {99, 23, 5, 189, -1, 66};
    int x;
    scanf("%d", &x);
    int size = sizeof(a) / sizeof(a[0]);
    // 此处填写代码，调用find_pos，在a数组中查找给定数据x的位置，并输出函数返回的数据元素的位置
    /*------------begin-----------------*/
    printf("%d\n", find_pos(a, size, x));
    /*------------end-----------------*/

    return 1;
}
