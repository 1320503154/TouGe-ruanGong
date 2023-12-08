// 根据你所使用的语言C或C++，包含必要的头文件
// cpp is best in dataStruct,also python,although its slow.
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
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
// 实验一：第1关
PseqList createNullList_seq(int m)
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
    ifstream file("/data/workspace/myshixun/src/course.txt");
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
