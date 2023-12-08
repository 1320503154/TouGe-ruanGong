#include <stdio.h>
void print(int a[], int n)
{ // 输出数组元素，数字之间以一个空格为界，输出结束后换一行
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}
int Partition(int a[], int left, int right)
{
    int pivot = a[left];
    while (left < right)
    {
        while (left < right && a[right] >= pivot)
        {
            right--;
        } // 当上述循环执行完毕,找到了小于pivot的元素,放到left指针指向的位置
        a[left] = a[right];
        while (left < right && a[left] < pivot)
        {
            left++;
        } // 当循环结束,找到了在左侧的大于pivot的元素.
        a[right] = a[left];
    }
    // 进行完划分,得到left==right,
    a[left] = pivot;
    return left;
}

void qSort(int a[], int left, int right)
{
    if (left < right)
    {
        int pivot = Partition(a, left, right);
        qSort(a, left, pivot - 1);
        qSort(a, pivot + 1, right);
    }
}
int main(void)
{
    int num;
    scanf("%d", &num);
    int data[num];
    for (int i = 0; i < num; i++)
        scanf("%d", &data[i]);

    qSort(data, 0, num - 1);
    print(data, num);
}