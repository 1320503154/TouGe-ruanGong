#include <stdio.h>
#include <stdlib.h>

/*数据结构定义*/
typedef int DataType;
typedef struct
{
    DataType *data; // 用于存放待排序关键字的起始地址
    int NUM;        // 待排序关键字的个数
} SortObject;

typedef struct node // 用于表插入排序的数据结构
{
    DataType info;
    struct node *next;
} linkObject;
typedef linkObject *LinkNode;
// 输出顺序表
void print(SortObject *p)
{
    for (int i = 0; i < p->NUM; i++)
        printf("%d ", p->data[i]);
    printf("\n");
}

// 输出链表
void printLink(linkObject *Head)
{
    linkObject *p = Head->next;
    while (p)
    {
        printf("%d ", p->info);
        p = p->next;
    }
    printf("\n");
}

/*第一关
此处请填写代码实现递增序进行直接插入排序,
 要求每趟排序后 调用print函数，输出关键字的排列情况*/
void insertSort(SortObject *Rec)
{

    /*----begin------*/
    int i, j, temp = 0;
    // 算法的空间复杂度是常数级的O(1),因为和问题规模NUM无关
    for (i = 1; i <= Rec->NUM; i++)
    {
        if (Rec->data[i] < Rec->data[i - 1]) // 如果当前元素小于前一个元素
        {
            temp = Rec->data[i]; // 将当前元素存入temp
            for (j = i - 1; j >= 0 && Rec->data[j] > temp; j--)
            // 检查所有前面已经排好序的元素.
            {
                Rec->data[j + 1] = Rec->data[j]; // 所有大于temp的元素都向后挪位
            }
            Rec->data[j + 1] = temp; // 这里的j++是因为在循环结束后会--j,此时j的右边才是要插入的位置.
        }
        print(Rec);
    }
    /*-----end------*/
}

/*第二关
此处请填写代码实现递增序进行二分插入排序,

  实质是在已经有序的表中采用二分法查找插入位置
  要求每趟排序后 调用print函数，输出关键字的排列情况*/
void binInsertSort(SortObject *Rec)
{
    printf("the result of binInsertSort:\n");
    /*----begin------*/
    // 为什么可以呢,是因为插入排序中,要插入的元素之前的元素其实都已经排序好了,查找的时候
    // 就是在已经排序的数组里面找下标,使用折半查找是最快的.

    // 当low>high时折半查找停止,将[low,i-1]内的全部元素右移,将temp赋值到low所指的位置.
    // 当mid指针指向的元素和当前查找元素的值相等,往右边区间继续查找插入位置.
    // 右边区间:low=mid+1,左边区间:high=mid-1
    int i, j, low, high, mid, temp = 0;
    for (i = 1; i <= Rec->NUM; i++)
    {
        if (Rec->data[i] < Rec->data[i - 1]) // 如果当前元素小于前一个元素
        {
            temp = Rec->data[i]; // 保存当前元素
            low = 0;
            high = i - 1;
            while (low <= high)
            {
                mid = (low + high) / 2;
                if (Rec->data[mid] > temp) // temp在左侧区间
                    high = mid - 1;
                else // 在右侧区间,包含中间元素等于temp的情况
                    low = mid + 1;
            } // loop is done and low > high,low is the insert location
            for (j = i - 1; j >= 0 && j >= low; --j)
            {
                Rec->data[j + 1] = Rec->data[j];
            }
            Rec->data[low] = temp;
        }
        if (i != Rec->NUM)
        {
            print(Rec);
        }
    }
    /*-----end------*/
}

/* 第四关
此处请填写代码实现递增序进行希尔排序,

  要求每趟排序后 调用print函数，输出关键字的排列情况
  */

void shellSort(SortObject *Rec, int d)
{
    // 没有哨兵版本的.
    int num = d * 2;
    int i, j = 0;
    for (; d > 0; d /= 2)
    {
        for (i = d; i < num; i++)
        {
            int temp = Rec->data[i];
            for (j = i - d; j >= 0 && Rec->data[j] > temp; j -= d)
            {
                Rec->data[j + d] = Rec->data[j]; // 当第一个元素大于第二个元素时,
                // 二者交换,空出的j + d后面给temp
            }
            Rec->data[j + d] = temp;
        }
        print(Rec);
    }
}
/*第三关
此处请填写代码实现递增序进行表插入排序,
  Head是表头结点，不存放数据，info是待插入数据
  要求每趟排序后 调用printLink函数，输出关键字的排列情况
  */
void listSort(linkObject *head)
{

    /*----begin------*/
    LinkNode prev = head->next;
    LinkNode curr = prev->next;
    while (curr != NULL)
    {
        if (curr->info >= prev->info) // 后面节点大于前面节点,有序,继续移动指针
        {
            prev = curr; // 保存要操作链表的前一个节点
            curr = curr->next;
        }
        else
        { // 后面节点<=前面节点
            // 找到小于cur.data的最大节点
            LinkNode p = head;
            while (p->next != NULL && p->next->info < curr->info)
            {
                p = p->next;
            }
            // 此时的p就是小于cur值的最大值节点
            prev->next = curr->next; // 删除curr节点在原先链表的顺序
            // 插入curr到p和p->next之间
            curr->next = p->next;
            p->next = curr;
            // 然后更新cur节点,保持节点之间原本的关系,继续循环
            curr = prev->next;
        }
        printLink(head);
    }
    /*-----end------*/
}
