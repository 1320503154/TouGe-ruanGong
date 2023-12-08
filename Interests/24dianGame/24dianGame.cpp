#include <iostream>
#include <vector>
using namespace std;
// 函数声明
bool calculate24(vector<int> &nums, string &result);
bool isEquals24(double num);
bool isSolvable(vector<int> &nums);

int main()
{
    vector<int> nums;
    cout << "请输入四个整数（空格分隔）: ";
    for (int i = 0; i < 4; i++)
    {
        int num;
        cin >> num;
        nums.push_back(num);
    }

    string result;
    bool solvable = calculate24(nums, result);

    if (solvable)
    {
        cout << "计算结果为24的表达式: " << result << endl;
    }
    else
    {
        cout << "无法通过运算得到24" << endl;
    }

    return 0;
}

// 计算24点游戏的结果
// 参数nums: 存储运算数的向量
// 参数result: 存储结果表达式的字符串
// 返回值: 是否存在解
bool calculate24(vector<int> &nums, string &result)
{
    // 先判断是否存在解
    if (!isSolvable(nums))
    {
        return false;
    }

    // 当只剩下一个数时，判断是否等于24
    if (nums.size() == 1)
    {
        if (isEquals24(nums[0]))
        {
            result = to_string(nums[0]);
            return true;
        }
        return false;
    }

    // 遍历所有可能的组合
    for (int i = 0; i < nums.size(); i++)
    {
        for (int j = i + 1; j < nums.size(); j++)
        {
            int a = nums[i];
            int b = nums[j];
            nums.erase(nums.begin() + j);
            nums.erase(nums.begin() + i);

            // 四种基本运算符
            vector<char> operators = {'+', '-', '*', '/'};
            for (char op : operators)
            {
                // 得到新的计算结果
                double num = 0;
                string expression;
                switch (op)
                {
                case '+':
                    num = a + b;
                    expression = "(" + to_string(a) + " + " + to_string(b) + ")";
                    break;
                case '-':
                    num = a - b;
                    expression = "(" + to_string(a) + " - " + to_string(b) + ")";
                    break;
                case '*':
                    num = a * b;
                    expression = "(" + to_string(a) + " * " + to_string(b) + ")";
                    break;
                case '/':
                    if (b != 0)
                    {
                        num = static_cast<double>(a) / b;
                        expression = "(" + to_string(a) + " / " + to_string(b) + ")";
                    }
                    break;
                }

                if (num != 0)
                {
                    // 将新的计算结果添加到nums中
                    nums.push_back(static_cast<int>(num));

                    // 递归计算剩余的数
                    string subResult;
                    if (calculate24(nums, subResult))
                    {
                        result = expression + " " + subResult;
                        return true;
                    }

                    // 回溯，移除添加的数
                    nums.pop_back();
                }
            }

            // 回溯，恢复原来的状态
            nums.insert(nums.begin() + i, a);
            nums.insert(nums.begin() + j, b);
        }
    }

    // 无解
    return false;
}

// 判断数值是否等于24（使用浮点数比较，考虑精度误差）
bool isEquals24(double num)
{
    return abs(num - 24) < 0.000001;
}

// 判断是否存在解
bool isSolvable(vector<int> &nums)
{
    if (nums.size() != 4)
    {
        return false;
    }

    for (int i = 0; i < 4; i++)
    {
        if (nums[i] <= 0)
        {
            return false;
        }
    }

    return true;
}