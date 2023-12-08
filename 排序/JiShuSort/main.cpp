#include <iostream>
#include <vector>

// 函数：找到数组中的最大值
int findMax(const std::vector<int> &arr)
{
    int max = arr[0];
    for (int i = 1; i < arr.size(); i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

// 函数：基数排序的计数排序步骤，根据当前位上的数字进行排序
void countingSort(std::vector<int> &arr, int exp)
{
    // exp 表示当前位数，例如 exp=1 表示按照个位上的数字进行排序,exp=10 表示按照十位上的数字进行排序,以此类推
    const int n = arr.size();
    std::vector<int> output(n, 0);
    std::vector<int> count(10, 0);

    // 计算每个数字出现的次数
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // 修改 count[i]，使得 count[i] 包含该位数字在 output[] 中的实际位置
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // 构建排序后的数组
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // 将排序后的数组复制回 arr[] 中，arr[] 现在包含了根据当前位排序的数字
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// 主函数：实现基数排序
void radixSort(std::vector<int> &arr)
{
    // 找到数组中的最大值，以确定数字的位数
    int max = findMax(arr);

    // 对每一位进行计数排序
    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSort(arr, exp);
}

int main()
{
    // 待排序数组
    std::vector<int> arr = {25, 84, 71, 47, 15, 27, 68, 35, 20};

    // 输出原始数组
    std::cout << "原始数组: ";
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // 执行基数排序
    radixSort(arr);

    // 输出排序后的数组
    std::cout << "排序后的数组: ";
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";

    return 0;
}
