#include <stdio.h>

int find_pos(int data[], int n, int key)
{ // 在数组data中查找给定数据key，n是数组中数据元素的个数，返回值是数据元素比较的次数.

    /*------------begin-----------------*/
    int left = 0, right = n - 1; // left和right分别表示数组的第一个元素和最后一个元素
    int count = 0;               // count表示比较的次数
    while (left < right)         // 当left小于right时，说明还没有找到
    {
        int mid = (left + right) >> 1; // mid表示数组中间元素的下标
        if (data[mid] == key)          // 如果中间元素等于key，说明找到了
            return count + 1;          // 返回比较的次数
        else if (data[mid] < key)      // 如果中间元素小于key，说明key在右边
            left = mid + 1;            // 将left移到中间元素的右边
        else if (data[mid] > key)      // 如果中间元素大于key，说明key在左边
            right = mid - 1;           // 将right移到中间元素的左边
        count++;                       // 比较次数加1
    }
    if (data[left] != key) // 如果left和right相等，说明没有找到
        return 0;
    return count + 1;
    /*------------end-----------------*/
}

int main(void)
{
    int a[] = {-1, 15, 66, 99, 122, 189};
    int x;
    scanf("%d", &x);
    int size = sizeof(a) / sizeof(a[0]);
    // 此处填写代码，调用find_pos，在a数组中查找给定数据x的位置，并输出函数返回值
    /*------------begin-----------------*/
    find_pos(a, size, x);
    printf("%d", find_pos(a, size, x));
    /*------------end-----------------*/

    return 1;
}
