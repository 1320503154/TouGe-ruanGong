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

void headAdjust(int arr[], int noLeaf, int length)
{
    int temp = arr[noLeaf - 1]; // 此时 temp 存储的是根节点
    for (int leaf = 2 * noLeaf; leaf <= length; leaf *= 2)
    {
        if (leaf < length && arr[leaf - 1] < arr[leaf])
        {           // 注意数组下标需要减 1
            leaf++; // 如果右子节点的值更大，指向右子节点
        }
        if (temp >= arr[leaf - 1])
        {
            break; // 父节点的值大于等于子节点的最大值
        }
        else
        {
            arr[noLeaf - 1] = arr[leaf - 1];
            noLeaf = leaf; // 子节点和父节点交换 index 和 value
        }
    }
    arr[noLeaf - 1] = temp;
}

void buildMaxHeap(int arr[], int len)
{
    // 从最后一个非叶子节点开始，依次进行向下调整
    for (int noLeaf = len / 2; noLeaf > 0; noLeaf--)
    {
        headAdjust(arr, noLeaf, len);
    }
}

void heapSort(int a[], int n)
{
    buildMaxHeap(a, n);
    print(a, n);

    // 依次取出堆顶元素，将剩余部分重新构建成最大堆
    for (int i = n - 1; i > 0; i--)
    {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        headAdjust(a, 1, i);
        print(a, n); // 在每次循环后打印数组，可观察排序过程
    }
}

int main(void)
{
    int num = 10;
    int data[10] = {49, 38, 65, 97, 49, 13, 27, 76, 90, 12};
    heapSort(data, num);
    printf("Sorted array: ");
    print(data, num);
    return 0;
}