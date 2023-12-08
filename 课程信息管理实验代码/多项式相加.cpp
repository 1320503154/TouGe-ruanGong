#ifndef _LAB1_H_
#define _LAB1_H_
#include <stdlib.h>
#include <stdio.h>

struct node
{
    int exp;
    int coef;
    struct node *next;
};

typedef struct node *PNODE;

PNODE createPoly(void)
{
    PNODE head = (PNODE)malloc(sizeof(struct node));
    head->exp = -1;
    head->coef = 0;
    head->next = NULL;
    scanf("%d%d", &coef, &exp);
    PNODE p = (PNODE)malloc(sizeof(struct node));
    if (exp | coef)
    {
        p->coef = coef;
        p->exp = exp;
        p->next = NULL;
        head->next = p;
    }
    else
        return head;
    scanf("%d%d", &coef, &exp);
    while (exp | coef)
    {
        PNODE q = (PNODE)malloc(sizeof(struct node));
        q->coef = coef;
        q->exp = exp;
        q->next = NULL;
        p->next = q;
        p = q;
        scanf("%d%d", &coef, &exp);
    }
    return head;
}

PNODE addPoly(PNODE polyAddLeft, PNODE polyAddRight)
{
    PNODE pLeft = polyAddLeft->next;
    PNODE pRight = polyAddRight->next;
    PNODE pre = pLeft;
    PNODE temp = NULL;
    int add = 0;
    while (pLeft != NULL && pRight != NULL)
    {
        if (pLeft->exp < pRight->exp)
        {
            pre = pLeft;
            pLeft = pLeft->next;
        }
        else if (pLeft->exp > pRight->exp)
        {
            if (pLeft == polyAddLeft->next)
            {
                temp = pRight;
                pRight = pRight->next;
                temp->next = pre;
                polyAddLeft->next = temp;
                temp = NULL;
            }
            else
            {
                temp = pRight->next;
                pRight->next = pLeft;
                pre->next = pRight;
                pRight = temp;
                temp = NULL;
                pre = pre->next;
            }
        }
        else
        {
            add = pLeft->coef + pRight->coef;
            pLeft->coef = add;
            temp = pRight;
            pRight = pRight->next;
            free(temp);
            temp = NULL;

            if (add == 0)
            {
                temp = pLeft;
                pLeft = pLeft->next;
                free(temp);
                temp = NULL;
                pre->next = pLeft;
            }
        }
    }
    if (pRight != NULL)
    {
        pre->next = pRight;
    }
    polyAddRight->next = NULL;
    return polyAddLeft;
}

void printPoly(PNODE poly)
{
    PNODE temp = poly->next;
    while (temp->next != NULL)
    {
        printf("%dx^%d+", temp->coef, temp->exp);
        temp = temp->next;
    }
    printf("%dx^%d", temp->coef, temp->exp);
}

void destroyPoly(PNODE poly)
{
    if (poly->next == NULL)
        return;
    PNODE p = poly;
    PNODE temp = NULL;
    while (poly != NULL)
    {
        temp = poly;
        poly = poly->next;
        free(temp);
    }
    p->next = NULL;
}
#endif