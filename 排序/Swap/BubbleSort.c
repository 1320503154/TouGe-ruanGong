#include <stdio.h>
#include <stdbool.h>
void print(int a[], int n)
{ // 输出数组元素，数字之间以一个空格为界，输出结束后换一行
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void bubbleSort(int a[], int n) // 对数组a中的n个元素进行排序，调用print函数输出每趟排序后的结果
{
    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false; // 标记本轮是否有交换发生
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            { // 如果前面的元素大于后面的元素
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp; // 让大的元素冒泡到后面
                swapped = true;  // 发生了交换
            }
        }
        if (!swapped)
        { // 如果没有发生交换，提前结束排序
            break;
        }
        print(a, n); // 输出每趟排序后的结果
    }
}

int main(void)
{
    int num;
    scanf("%d", &num);
    int data[num];
    for (int i = 0; i < num; i++)
    {
        scanf("%d", &data[i]);
    }
    bubbleSort(data, num);
}