#include <iostream>
#include <vector>

// 合并两个已排序的子数组
void merge(std::vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1; // 左子数组的长度
    int n2 = right - mid;    // 右子数组的长度

    // 创建临时数组存放两个子数组
    std::vector<int> L(n1);
    std::vector<int> R(n2);

    // 将数据拷贝到临时数组 L 和 R 中
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i]; // 左子数组从 left 开始

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j]; // 右子数组从 mid+1 开始

    // 归并两个子数组到原数组 arr
    int i = 0, j = 0, k = left; // k 从 left 开始
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // 将剩余的元素拷贝到 arr 中
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// 归并排序
void mergeSort(std::vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        // 递归地对左右两个子数组进行排序
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // 合并两个有序的子数组
        merge(arr, left, mid, right);
    }
}

int main()
{
    // 待排序数组
    std::vector<int> arr = {25, 84, 71, 47, 15, 27, 68, 35, 20};
    int n = arr.size();

    // 输出原始数组
    std::cout << "Original Array: ";
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // 进行归并排序
    mergeSort(arr, 0, n - 1);

    // 输出排序后的数组
    std::cout << "Sorted Array: ";
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";

    return 0;
}
