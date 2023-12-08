// 根据你所使用的语言C或C++，包含必要的头文件
// cpp is best in dataStruct,also python,although its slow.
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstring>
#include <functional>
using namespace std;

/*在此处定义存储课程信息的数据结构，课程信息包括：课程名称、学分、讲授学时、实践学时、课程类别、开课学期。*/
typedef struct course
{
    string coursename;
    float credit;
    int lectureHours;
    int practiceHours;
    string courseType;
    int term;
} DataType;

struct seqList         // 顺序线性表结构定义
{                      // 有3个数据成员
    int MAXNUM;        // 用于记录顺序线性表中能存放的最大元素个数的 整型 MAXNUM
    int curNum;        // 用于存放顺序线性表中数据元素的个数  整型  curNum
    DataType *element; // 用于存放顺序线性表数据元素的连续空间的起始地址
};

typedef struct seqList *PseqList;
struct BiTreeNode
{
    DataType data;
    BiTreeNode *left;
    BiTreeNode *right;
};
// 插入节点到二叉排序树
void insertBiTree(BiTreeNode *&root, DataType x)
{
    if (root == nullptr)
    {
        root = new BiTreeNode;
        root->data = x;
        root->left = root->right = nullptr;
    }
    else if (x.coursename < root->data.coursename)
    {
        insertBiTree(root->left, x);
    }
    else if (x.coursename > root->data.coursename)
    {
        insertBiTree(root->right, x);
    }
}
BiTreeNode *buildBiTree(PseqList &L)
{
    BiTreeNode *root = nullptr;
    for (int i = 0; i < L->curNum; i++)
    {
        insertBiTree(root, L->element[i]);
    }
    return root;
}
// 实验一：第1关
PseqList
createNullList_seq(int m)
{ // 此处填写代码，创建一个空的顺序线性表，能存放的最大元素个数为 m
    // 若m=0，则返回NULL
    if (m == 0)
    {
        return NULL;
    }

    PseqList L = new seqList;
    L->MAXNUM = m;
    L->curNum = 0;
    L->element = new DataType[m];

    return L;
}
void printList_seq(PseqList &L)
{ // 逐个输出线性表的元素，每门课程信息一行，课程信息的若干元素之间以一个空格为分隔符隔开
    for (int i = 0; i < L->curNum; i++)
    {
        DataType item = L->element[i];
        cout << item.coursename << " " << fixed << setprecision(6) << item.credit << " " << item.lectureHours << " " << item.practiceHours << " " << item.courseType << " " << item.term << endl;
    }
}

int readFromFile(PseqList &L)
{
    // ifstream file("/data/workspace/myshixun/src/course.txt");
    ifstream file("F:/c++/TouGe/ShiYan/course.txt");
    if (!file)
    {
        cout << "Failed to open file" << endl;
        return 0;
    }

    int count = 0;
    string line;
    while (getline(file, line))
    { // 从文件中读取一行字符,第一个参数是文件,第二个参数是存放在内存的变量
        if (line == "-")
        {
            break;
        }

        DataType item;
        istringstream iss(line); // Using istringstream instead of stringstream
        // inputStringStream输出字符串流,将line输出到内存的变量中
        iss >> item.coursename >> item.credit >> item.lectureHours >> item.practiceHours >> item.courseType >> item.term;

        L->element[L->curNum] = item;
        L->curNum++;
        count++;
    }

    file.close();
    return count;
}

// 实验一：第2关
int isFullList_seq(PseqList &L)
{
    // 判断顺序线性表是否已满，若已满，返回值为1，否则返回值为0
    if (L->curNum == L->MAXNUM)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int insertP_seq(PseqList &L, int p, DataType x)
{ // 在线性表L中下标为p的位置插入数据元素x，若下标p非法或线性表已满无法插入数据，返回0；插入成功返回值为1
  // 如果线性表满了， 还需输"list is full"的提示
  // 如果插入位置非法，需输出提示"position is illegel"
    if (isFullList_seq(L))
    {
        cout << "list is full" << endl;
        return 0;
    }

    if (p < 0 || p > L->curNum)
    {
        cout << "position is illegel" << endl;
        return 0;
    }

    for (int i = L->curNum; i > p; i--) // curNum是顺序表中当前元素的个数
    {
        L->element[i] = L->element[i - 1];
    }

    L->element[p] = x; // 腾出下标为p的位置后，插入元素x
    L->curNum++;
    return 1;
}

void insertPre_seq(PseqList &L, int p, DataType x)
{
    // 在线性表L中下标为p的位置的前面插入数据元素x，若下标p非法或线性表已满无法插入数据，返回0；插入成功返回值为1
    // 提示：直接调用insertP函数实现即可
    insertP_seq(L, p - 1, x);
}

void insertPost_seq(PseqList &L, int p, DataType x)
{
    // 在线性表L中下标为p的位置的后面插入数据元素x，若下标p非法或线性表已满无法插入数据，返回0；插入成功返回值为1
    // 提示：直接调用insertP函数实现即可
    insertP_seq(L, p + 1, x);
}
int findPos(PseqList &L, DataType x)
{
    // 根据要插入的课程名称查找在顺序表中插入的位置，返回值是插入课程信息的下标位置

    for (int i = 0; i < L->curNum; i++)
    {
        if ((x.term < L->element[i].term) || (x.term == L->element[i].term && x.coursename < L->element[i].coursename)) // 按学期和课程名称的顺序进行比较
        {
            return i;
        }
    }
    return L->curNum; // 若找不到合适的位置，则将课程信息插入到最后
}

int insertFromFile(string filename, PseqList &L)
{
    // 从filename为文件名的文件中读取课程信息，按学期、课程名称顺序插入线性表L，使课程信息按学期、课程名称有序
    ifstream file(filename);
    if (!file)
    {
        cout << "Failed to open file" << endl;
        return 0;
    }

    int count = 0;
    string line;
    while (getline(file, line))
    {
        if (line == "-")
        {
            break;
        }

        DataType item;
        istringstream iss(line);
        iss >> item.coursename >> item.credit >> item.lectureHours >> item.practiceHours >> item.courseType >> item.term;

        int pos = findPos(L, item); // 找到插入位置
        insertP_seq(L, pos, item);
        count++;
    }

    file.close();
    return count;
    // 返回值是插入课程信息的条数
}

void writeToFile(PseqList &L)
{                                                              // 将线性表L中的课程信息写入 /data/workspace/myshixun/src/course1.txt
    ofstream file("/data/workspace/myshixun/src/course1.txt"); // 打开文件，如果文件不存在则创建新文件
    if (!file)                                                 // 检查文件是否成功打开
    {
        cout << "Failed to open file" << endl; // 若文件打开失败，则输出错误信息并返回
        return;
    }

    for (int i = 0; i < L->curNum; i++) // 遍历线性表中的课程信息
    {
        DataType item = L->element[i]; // 获取当前课程信息
        // 将课程信息按指定格式写入文件
        file << item.coursename << " " << fixed << setprecision(6) << item.credit << " " << item.lectureHours << " " << item.practiceHours << " " << item.courseType << " " << item.term << endl;
    }

    file.close(); // 关闭文件
}

// 实验一：第3关
int destroyList_seq(PseqList &L)
{
    // 返回值为销毁的线性表中现有数据元素的个数，若待销毁的线性表不存在，则返回0
    if (L == NULL)
    {
        return 0;
    }
    int count = L->curNum;
    delete[] L->element;
    delete L;
    return count;
}

// 实验一：第4关
int locate_seq(PseqList &L, char *x)
{ // 在顺序表L中查与x相同的课程名称的课程信息的下标位置，若不存在给定值，则返回-1
    for (int i = 0; i < L->curNum; i++)
    {
        if (L->element[i].coursename == x)
        {
            return i;
        }
    }
    return -1;
}

DataType locatePos_seq(PseqList &L, int pos)
{ // 在顺序表L中查找指定位置pos处的数据元素，若位置非法，则返回第0个数据元素
    cout << defaultfloat;
    if (pos < 0 || pos >= L->curNum)
    {
        return L->element[0];
    }
    return L->element[pos];
}

// 实验一：第5关
int deletePos_seq(PseqList &L, int pos)
{ // 在顺序表L中删除与下标pos处的数据元素，若pos非法，则返回-1；否则返回1
    if (pos < 0 || pos >= L->curNum)
    {
        return -1;
    }

    for (int i = pos; i < L->curNum - 1; i++)
    {
        L->element[i] = L->element[i + 1];
    }
    L->curNum--;
    return 1;
}

int delete_seq(PseqList &L, char *x)
{ // 在顺序表L中删除与参数x值相同的课程信息，返回删除数据元素的个数
  // 可以使用之前已完成的操作
    int count = 0;
    for (int i = 0; i < L->curNum; i++)
    {
        if (L->element[i].coursename == x)
        {
            deletePos_seq(L, i);
            count++;
        }
    }
    return count;
}

// 实验1,第六关
void analyse(PseqList &L)
{
    // 创建两个数组，用于存储每个学期和课程类型的统计信息
    double termCredit[8] = {0}; // 每个学期的学分
    double termTime[8] = {0};   // 每个学期的学时
    double typeCredit[3] = {0}; // 每个课程类型的学分
    double typeTime[3] = {0};   // 每个课程类型的学时

    // 统计每个学期和课程类型的学分和学时
    for (int i = 0; i < L->curNum; i++)
    {
        int term = L->element[i].term;
        int type;
        if (L->element[i].courseType == "BJ")
            type = 0;
        else if (L->element[i].courseType == "BS")
            type = 1;
        else if (L->element[i].courseType == "BT")
            type = 2;

        termCredit[term - 1] += L->element[i].credit;
        termTime[term - 1] += L->element[i].lectureHours + L->element[i].practiceHours;
        typeCredit[type] += L->element[i].credit;
        typeTime[type] += L->element[i].lectureHours + L->element[i].practiceHours;
    }

    // 输出统计结果
    cout << "统计信息1：" << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << i + 1 << " " << fixed << setprecision(6) << termCredit[i] << " " << fixed << setprecision(0) << termTime[i] << endl;
    }

    cout << "统计信息2：" << endl;
    cout << "BJ " << fixed << setprecision(6) << typeCredit[0] << " " << fixed << setprecision(0) << typeTime[0] << endl;
    cout << "BS " << fixed << setprecision(6) << typeCredit[1] << " " << fixed << setprecision(0) << typeTime[1] << endl;
    cout << "BT " << fixed << setprecision(6) << typeCredit[2] << " " << fixed << setprecision(0) << typeTime[2] << endl;
}

// 实验二：第1关
// 提示：本关主程序使用实验一的代码，从文件course.txt 读取课程信息，生成线性表L
// 使用实验三的第6关，将线性表L按课程名称排序后调用本函数进行折半查找
// 在函数中，输出每趟比较的课程信息的课程名称
int binary_search(PseqList &L, char *x)
{ // 在有序顺序表L中查找与x相同的课程名称的课程信息，若不存在给定值，则返回0
    // 在函数中输出每次查找比较的顺序表中对应的数据元素（课程名称），观察和体验折半查找的过程
    int left = 0;
    int right = L->curNum - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (L->element[mid].coursename < x)
        {
            // x in right side
            cout << L->element[mid].coursename << endl;
            left = mid + 1;
        }
        else if (L->element[mid].coursename > x)
        {
            // x in left side
            cout << L->element[mid].coursename << endl;
            right = mid - 1;
        }
        else
        {
            cout << L->element[mid].coursename << endl;
            return 1;
        }
    }
    return 0;
}

// 实验二：第2关

int biTree_search(PseqList &L, char *x)
{ // 利用线性表L中的数据，建立二叉排序树，并在二叉排序树中检索与x相同的课程名称

    // 输出每次比较的数据元素对应的课程名称，实验报告中画出二叉排序树，手工推演检索过程，观察实验结果，比较检索过程是否与手工推演一致
    // 可根据需要自己创建必要的函数
    BiTreeNode *root = buildBiTree(L);
    int comparisons = 0;
    while (root != nullptr)
    {
        comparisons++;
        if (x < root->data.coursename)
        {
            cout << root->data.coursename << endl;
            root = root->left;
        }
        else if (x > root->data.coursename)
        {
            cout << root->data.coursename << endl;
            root = root->right;
        }
        else
        {
            // 找到了匹配项，输出比较信息
            cout << root->data.coursename << endl;
            return comparisons;
        }
    }
    // 未找到匹配项
    return 0;
}
// 链表定义
struct ListNode
{
    DataType data;
    ListNode *next;
};
struct LinkedList
{
    ListNode *head;
    LinkedList() : head(nullptr) {}
};
// 哈希表定义
const int TABLE_SIZE = 100;
struct HashNode
{
    DataType data;
    int isOccupied; // 用于标记该位置是否被占据
};
struct LinkedHashNode
{
    LinkedList list; // 每一个list对应一个头节点.和被占据的标记
    int isOccupied;  // 用于标记该位置是否被占据
};
struct LinkedHashTable
{
    LinkedHashNode table[TABLE_SIZE];
};
struct HashTable
{
    HashNode table[TABLE_SIZE];
};
int hashFunction(string key)
{
    // 使用C++标准库的哈希函数,以课程名作为key
    hash<string> hashFunc;
    return hashFunc(key) % TABLE_SIZE;
}
// 初始化链式散列表
void initializeLinkedHashTable(LinkedHashTable &hashTable)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hashTable.table[i].isOccupied = false;
    }
}
// 初始化散列表
void initializeHashTable(HashTable &hashTable)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hashTable.table[i].isOccupied = false;
    }
}
// 插入数据到散列表
void insertIntoHashTable(HashTable &hashTable, DataType x)
{
    int index = hashFunction(x.coursename);

    while (hashTable.table[index].isOccupied)
    {
        // 线性探测法
        index = (index + 1) % TABLE_SIZE;
    }

    hashTable.table[index].data = x;
    hashTable.table[index].isOccupied = true;
}
// 实验二：第3关
int hash_search_open(PseqList &L, string x)
{
    HashTable hashTable;            // 直接在栈上创建即可,函数取的都是引用
    initializeHashTable(hashTable); // 初始化,全部标记占据属性设置为false
    for (int i = 0; i < L->curNum; i++)
    {
        insertIntoHashTable(hashTable, L->element[i]);
    }
    int index = hashFunction(x);
    int comparisons = 0;

    while (hashTable.table[index].isOccupied) // 当table里面有元素的时候进行循环
    {
        comparisons++;
        if (hashTable.table[index].data.coursename == x)
        {
            // 找到了匹配项，输出比较信息
            cout << hashTable.table[index].data.coursename << endl;
            return comparisons; // 返回比较次数
        }

        index = (index + 1) % TABLE_SIZE; // 线性探测
    }

    // 未找到匹配项
    return 0;
}
// 链式线性表相关操作:
void insertLinkedHashTable(LinkedHashTable &hashTable, DataType x)
{
    int index = hashFunction(x.coursename);

    ListNode *node = new ListNode{x, nullptr};
    ListNode *current = hashTable.table[index].list.head;

    if (!current)
    {
        hashTable.table[index].list.head = node;
    }
    else
    {
        while (current->next)
        {
            current = current->next;
        }
        current->next = node;
    }

    // 标记位置已被占据
    hashTable.table[index].isOccupied = true;
}

// 实验二：第4关
int hash_search_link(PseqList &L, string x)
{ // 利用线性表L中的数据，设计散列函数，说明散列函数设计理由
    // 选用链地址法进行冲突处理，建立散列表
    // 实现在散列表的查找函数，在函数中输出每次比较的数据元素对应的课程名称
    int index = hashFunction(x);
    LinkedHashTable HashTable;
    initializeLinkedHashTable(HashTable);
    for (int i = 0; i < L->curNum; i++)
    {
        insertLinkedHashTable(HashTable, L->element[i]);
    }
    int comparisons = 0;
    if (HashTable.table[index].isOccupied)
    {
        ListNode *current = HashTable.table[index].list.head;
        while (current)
        {
            comparisons++;
            if (current->data.coursename == x)
            {
                cout << current->data.coursename << endl;
                return comparisons;
            }
            cout << current->data.coursename << endl; // 输出每次比较的数据元素对应的课程名称
            current = current->next;
        }
    }
    // 没找到匹配项
    return 0;
}

// 实验三：第1关
// 直接插入排序，在函数中输出每趟排序后的结果
void printCourse(PseqList &L)
{
    for (int i = 0; i < L->curNum; i++)
    {
        cout << L->element[i].coursename << ",";
    }
    cout << endl;
}
void insert_sort(PseqList &L)
{
    for (int i = 1; i < L->curNum; i++)
    {
        DataType temp = L->element[i]; // 取出未排序序列中的第一个元素
        int j = i - 1;

        // 将该元素与已排序序列从后往前比较，如果该元素小于已排序序列中的某个元素，则将已排序序列中的元素向后移动，给该元素腾出插入位置
        while (j >= 0 && L->element[j].coursename > temp.coursename)
        {
            L->element[j + 1] = L->element[j];
            j--;
        }

        L->element[j + 1] = temp; // 将该元素插入到已排序序列中的正确位置

        // 输出每趟排序后的课程名称
        printCourse(L);
    }
}

// 实验三：第2关
// 二分插入排序，在函数中输出每趟排序后的结果
void biinsert_sort(PseqList &L)
{
    int low, high, mid = 0;
    int n = L->curNum;

    for (int i = 1; i < n; i++)
    {
        DataType temp = L->element[i];

        low = 0;
        high = i - 1; // 在排序的过程中,arr[0]和arr[i-1]这部分是已经排好序的元素

        while (low <= high)
        {
            mid = (high + low) / 2;
            if (L->element[mid].coursename > temp.coursename)
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        // 最后low和high相等，都是指向插入位置的前一个位置
        //  将元素往后移动
        for (int j = i - 1; j >= low; j--)
        {
            L->element[j + 1] = L->element[j];
        }
        L->element[low] = temp;
        printCourse(L);
    }
}

// 实验三：第3关
// 希尔排序，在函数中输出每趟排序后的结果
// 希尔排序，在函数中输出每趟排序后的结果
void shell_sort(PseqList &L)
{
    int n = L->curNum; // n = 4

    // 定义希尔增量序列
    int gap = n / 2; // gap = 2
    printCourse(L);
    while (gap > 0)
    {
        for (int i = gap; i < n; i++)
        { // i=gap=2,n=4
            DataType temp = L->element[i];
            int j = i; // j=2
            // 当2》=2并且【0】位元素的课程大于temp的。
            while (j >= gap && L->element[j - gap].coursename > temp.coursename)
            {
                L->element[j] = L->element[j - gap]; // 【2】=【0】,在gap序列上进行元素的右移。
                j -= gap;                            // j=j-gap=0
            }

            L->element[j] = temp; // 在当前位置插入temp
        }

        // 输出每趟排序后的课程名称
        printCourse(L);

        gap /= 2; // 缩小增量
    }
}

// 实验三：第4关
// 简单选择排序，在函数中输出每趟排序后的结果
void select_sort(PseqList &L)
{
    int n = L->curNum;
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i; // 假设当前的i下标元素最小
        for (int j = i + 1; j < n; j++)
        {
            if (L->element[j].coursename < L->element[minIndex].coursename)
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        { // 找到最小元素，和当前i指定的元素交换。
            DataType temp = L->element[i];
            L->element[i] = L->element[minIndex];
            L->element[minIndex] = temp;
        }
        printCourse(L);
    }
}

// 实验三：第5关
// 堆排序，在函数中输出每趟排序后的结果
void heap_sort(PseqList &L)
{
}

// 实验三：第6关
// 冒泡排序，在函数中输出每趟排序后的结果
void bubble_sort(PseqList &L)
{

    for (int i = 0; i < L->curNum - 1; i++)
    {
        int swapped = 0;
        for (int j = 0; j < L->curNum - i - 1; j++)
        {
            if (L->element[j].coursename > L->element[j + 1].coursename)
            { // 如果前面的课程名字在uni_code上面比较,而比后面的大,交换前后.
                DataType temp = L->element[j + 1];
                L->element[j + 1] = L->element[j];
                L->element[j] = temp;
                swapped = 1;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}

// 实验三：第7关
// 快排序，在函数中输出每趟排序后的结果
void quick_sort(PseqList &L, int left, int right)
{
}

// 实验四：第1关
// 图的拓扑排序，在函数中输出每趟排序后的结果
// 自行增加必要的函数，能通过线性表的先后修关系创建图，并自选结构存储图，实现拓扑排序
// course.txt内容如下,按照学期建立有向无环图,并进行拓扑排序.学期信息就是最后一列.1,2,3,4
// 计算机科学导论 3.5 40 16 BJ 1
// 程序设计与问题求解 3.5 56 0 BJ 1
// 工程概论 1 16 0 BJ 2
// 离散数学 4.5 72 0 BT 2
// 数据结构与算法 5 56 24 BT 3
// Web前端技术及可视化开发 3 32 16 BT 3
// 计算机组成原理 3 40 8 BT 3
// 数据库系统原理 3 48 0 BT 4
// 操作系统 2.5 40 0 BT 4
// 面向对象程序设计 2 24 8 BT 3

// 先完成图的创建,use 邻接表
// 邻接表的结构
struct EdgeNode // 边表中的结点
{
    int endvex;                // 相邻顶点在顶点表中下标
    struct EdgeNode *nextedge; // 链字段
};
typedef struct EdgeNode *EdgeList;

typedef struct
{
    string vertex;     // 记录顶点信息
    int degree;        // 用于记录顶点的入度，在拓扑排序时需使用
    EdgeList edgelist; // 指向边表的指针
} VexNode;
typedef struct
{
    VexNode vexs[10]; // 10个顶点
    int vcount;       // 顶点数
} GraphList;
void top_sort(PseqList &L)
{
    GraphList graph;
    graph.vcount = L->curNum;
    for (int i = 0; i < L->curNum; i++)
    {
        graph.vexs[i].vertex = L->element[i].coursename;
        graph.vexs[i].degree = 0;
        graph.vexs[i].edgelist = nullptr;
    }

    // 建立边表
    for (int i = 0; i < L->curNum; i++)
    {
        for (int j = 0; j < L->curNum; j++)
        {
            if (L->element[i].term == L->element[j].term - 1) // 说明顶点i的学期是顶点j的学期的前一学期
            {
                // i -> j
                EdgeList edge = new EdgeNode;
                edge->endvex = j; // i链接j
                // 将该边插入到顶点i的边表中,头插法,例子:i->m
                edge->nextedge = graph.vexs[i].edgelist;
                graph.vexs[i].edgelist = edge;
                // 经过上面的处理:i->j->m
                graph.vexs[j].degree++; // 将顶点j的入度加1
            }
        }
    }

    // 拓扑排序
    int count = 0;               // 代表已经排序的顶点数
    while (count < graph.vcount) // 循环直到所有顶点都被排序完
    {
        for (int i = 0; i < graph.vcount; i++)
        {
            if (graph.vexs[i].degree == 0)
            {
                // 说明该顶点的入度为0，可以进行拓扑排序
                cout << graph.vexs[i].vertex << endl; // 打印该顶点
                graph.vexs[i].degree = -1;            // 将该顶点的入度设置为-1，表示已经排序过
                count++;                              // 已经排序过的顶点数加1
                EdgeList edge = graph.vexs[i].edgelist;
                while (edge)
                {
                    // 将该顶点的所有邻接顶点的入度减1
                    graph.vexs[edge->endvex].degree--;
                    edge = edge->nextedge;
                }
            }
        }
    }
}
int main()
{
    // 测试拓扑排序
    PseqList L = createNullList_seq(50);
    readFromFile(L);
    top_sort(L);
    return 0;
}