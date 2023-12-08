#include <stdio.h>
void print(int a[], int n)
{
    // 输出数组元素，数字之间以一个空格为界，输出结束后换一行
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void selectSort(int a[], int n) // 对数组a中的n个元素进行排序，调用print函数输出每趟排序后的结果
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;                    // 使用min保存最小元素的index
        for (int j = i + 1; j < n; j++) // 从i到n-1中选择最小的元素
        {
            if (a[j] < a[min]) // 找到最小的元素的index
                min = j;
        }
        if (min != i)
            swap(&a[i], &a[min]); // 传入整数指针而不是具体的整数值
        print(a, n);
    }
}

int main(void)
{
    int num;
    scanf("%d", &num);
    int data[num];
    for (int i = 0; i < num; i++)
        scanf("%d", &data[i]);

    selectSort(data, num);
}