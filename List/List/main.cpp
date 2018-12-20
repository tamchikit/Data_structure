//
//  main.cpp
//  List
//
//  Created by tamchikit on 2018/9/18.
//  Copyright © 2018年 tamchikit. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

void CreateList(LinkList &L, int n);
Status ListInsert(LinkList &L, int i, ElemType e);
Status DelList(LinkList &L, int i);
Status PrintList(LinkList L);

int main(int argc, const char * argv[]) {
    LinkList L;
    int n=4;
    CreateList(L, n);
    PrintList(L);
    ListInsert(L, 4, 9);
    PrintList(L);
    DelList(L, 3);
    PrintList(L);
    return 0;
}

void CreateList(LinkList &L, int n){
    L = (LinkList) malloc(sizeof(LNode));
    L->next = NULL;
    for (int i=n; i>0; --i) {
        LinkList p = (LinkList) malloc(sizeof(LNode));
        cout<<"please input a number:\n";
        cin>>p->data;
        p->next=L->next;
        L->next=p;
    }
}

Status ListInsert(LinkList &L, int i, ElemType e){
    LinkList p=L;
    int j=0;
    while (p&&j<i-1) {
        p=p->next;
        ++j;
    }
    if (!p||j>i-1) {
        return ERROR;
    }
    LinkList s=(LinkList) malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

Status DelList(LinkList &L, int i){
    LinkList p=L;
    int j=0;
    while (p->next&&j<i-1) {
        p = p->next;
        ++j;
    }
    if (!p->next||j>i-1) {
        return ERROR;
    }
    LinkList q=p->next;
    p->next=q->next;
    free(q);
    return OK;
}

Status PrintList(LinkList L){
    if (!L) {
        return ERROR;
    }
    while (L) {
        cout<<L->data<<" ";
        L=L->next;
    }
    cout<<"\n";
    return OK;
}
