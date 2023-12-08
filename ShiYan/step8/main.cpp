#include "../seqlist.h"
int main(void)
{
    PseqList L = createNullList_seq(50);
    readFromFile(L);

    char name[40];
    cin >> name;
    int t = biTree_search(L, name);
    if (t == 0)
        cout << "没有找到!";
    else
        cout << "找到了!";
    // printList_seq(L);
}