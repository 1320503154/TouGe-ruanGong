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

int insertPre_seq(PseqList &L, int p, DataType x)
{
    // 在线性表L中下标为p的位置的前面插入数据元素x，若下标p非法或线性表已满无法插入数据，返回0；插入成功返回值为1
    // 提示：直接调用insertP函数实现即可
    insertP_seq(L, p - 1, x);
}

int insertPost_seq(PseqList &L, int p, DataType x)
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
int hashFunction(int term)
{
    // 使用C++标准库的哈希函数，以学期作为key
    hash<int> hashFunc;
    return hashFunc(term) % TABLE_SIZE;
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
    int index = hashFunction(x.term);

    while (hashTable.table[index].isOccupied)
    {
        // 线性探测法
        index = (index + 1) % TABLE_SIZE;
    }

    hashTable.table[index].data = x;
    hashTable.table[index].isOccupied = true;
}
// 实验二：第3关
int hash_search_open(PseqList &L, DataType x)
{
    HashTable hashTable;            // 直接在栈上创建即可,函数取的都是引用
    initializeHashTable(hashTable); // 初始化,全部标记占据属性设置为false
    for (int i = 0; i < L->curNum; i++)
    {
        insertIntoHashTable(hashTable, L->element[i]);
    }
    int index = hashFunction(x.term);
    int comparisons = 0;

    while (hashTable.table[index].isOccupied) // 当table里面有元素的时候进行循环
    {
        comparisons++;
        if (hashTable.table[index].data.coursename == x.coursename)
        {
            // 找到了匹配项，输出比较信息
            cout << "最终结果是:" << hashTable.table[index].data.coursename << endl;
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
    int index = hashFunction(x.term);

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
int hash_search_link(PseqList &L, DataType x)
{ // 利用线性表L中的数据，设计散列函数，说明散列函数设计理由
    // 选用链地址法进行冲突处理，建立散列表
    // 实现在散列表的查找函数，在函数中输出每次比较的数据元素对应的课程名称
    int index = hashFunction(x.term);
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
            if (current->data.coursename == x.coursename)
            {
                cout << current->data.coursename << endl;
                return comparisons;
            }
            // cout << current->data.coursename << endl; // 输出每次比较的数据元素对应的课程名称
            current = current->next;
        }
    }
    // 没找到匹配项
    return 0;
}

// 实验三：第1关
// 直接插入排序，在函数中输出每趟排序后的结果
void insert_sort(PseqList &L)
{
}

// 实验三：第2关
// 二分插入排序，在函数中输出每趟排序后的结果
void biinsert_sort(PseqList &L)
{
}

// 实验三：第3关
// 希尔排序，在函数中输出每趟排序后的结果
void shell_sort(PseqList &L)
{
}

// 实验三：第4关
// 简单选择排序，在函数中输出每趟排序后的结果
void select_sort(PseqList &L)
{
}

// 实验三：第5关
// 堆排序，在函数中输出每趟排序后的结果
void heap_sort(PseqList &L)
{
}
void printCourse(PseqList &L)
{
    for (int i = 0; i < L->curNum; i++)
    {
        cout << L->element[i].coursename << ',';
    }
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
void top_sort(PseqList &L)
{
}
// 主函数,我是sb,把seqlist.h编译成可执行文件,不应该把库文件编译成可执行文件exe吧.感谢GPT4.直接找到问题了,换成cpp文件,编译完成就可以执行了.
int main()
{
    PseqList L = createNullList_seq(100); // 创建顺序线性表
    readFromFile(L);                      // 从文件中读取课程信息

    // 测试实验二第3关：开放地址法哈希查找
    cout << "开放地址法哈希查找：" << endl;
    DataType course3 = {
        "数据结构与算法",
        5,
        56,
        24,
        "BT",
        3,
    };
    int comparisons3 = hash_search_open(L, course3);
    cout << "比较次数：" << comparisons3 << endl;

    // 测试实验二第4关：链地址法哈希查找
    cout << "链地址法哈希查找：" << endl;
    // DataType course4 = {"数据库系统原理", 3, 48, 0, "BT", 4};
    // 操作系统 2.5 40 0 BT 4
    DataType course5 = {"操作系统", 2.5, 40, 0, "BT", 4};
    int comparisons4 = hash_search_link(L, course5);
    cout << "比较次数：" << comparisons4 << endl;

    destroyList_seq(L); // 销毁顺序线性表

    return 0;
}