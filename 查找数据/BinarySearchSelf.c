#include <stdio.h>

int main(void)
{
    int data[] = {-1, 15, 66, 99, 122, 189};
    int key;
    scanf("%d", &key);
    int size = sizeof(data) / sizeof(data[0]);
    // 此处填写代码，调用find_pos，在a数组中查找给定数据x的位置，并输出函数返回值
    /*------------begin-----------------*/
    int left = 0, right = size - 1; // left和right分别表示数组的第一个元素和最后一个元素
    int count = 0;                  // count表示比较的次数
    while (left < right)            // 当left小于right时，说明还没有找到
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
    printf("left,right is %d %d\n", left, right);
    printf("data[left],data[right] is %d %d\n", data[left], data[right]);
    if (data[left] != key) // 如果left和right相等，说明没有找到
        printf("0");
    printf("%d", count + 1);
    /*------------end-----------------*/
    return 1;
}
