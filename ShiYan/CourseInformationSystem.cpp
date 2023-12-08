#include "./seqlist.h"

int main(void)
{
    PseqList L = createNullList_seq(50);
    readFromFile(L);
    printList_seq(L);
    char name[40];
    cin >> name;
    cout << locate_seq(L, name) << endl;
    int pos;
    cin >> pos;
    DataType x = locatePos_seq(L, pos);
    cout << x.coursename << " " << x.term << " " << x.credit << endl;
}