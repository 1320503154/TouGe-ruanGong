// 包含必要的头文件
#include <iostream>
#include <cmath>

using namespace std;

void compute(int data[], int n, int target)
{ // 在此处填写代码，在data数组中查找是否存在两个元素之和为target，并按要求输出
    /*-----------begin---------------*/
    int i, j;
    int flag = 0; // 没找到,falg=0
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (data[i] + data[j] == target)
            {
                flag = 1; // 找到了,falg=1
                cout << i << "," << j << endl;
            }
        }
    }
    if (flag == 0)
    {
        cout << -1 << "," << -1 << endl;
    }
    /*-----------end---------------*/
}

int main(void)
{
    int a[] = {-3, 2, 5, 9, 15, 32};
    int x;
    cin >> x;
    compute(a, 6, x);
}