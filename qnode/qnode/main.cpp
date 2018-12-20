//
//  main.cpp
//  qnode
//
//  Created by tamchikit on 2018/10/3.
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
typedef struct QNode{
    ElemType data;
    struct QNode *next;
}QNode, *Queueptr;
typedef struct {
    Queueptr front;
    Queueptr rear;
}LinkQueue;
typedef struct Lnode{
    ElemType data;
    struct Lnode *next;
}stacknode,*linkstack;

Status initstack(linkstack top);
Status isempty(linkstack top);
Status push(linkstack top, ElemType e);
Status pop(linkstack top, ElemType &e);
Status printstack(linkstack top);
Status initqueue(LinkQueue *q);
Status enqueue(LinkQueue *q,ElemType e);
Status dequeue(LinkQueue *q, ElemType &e);

Status initstack(linkstack top){
    top->next=NULL;
    return OK;
}
Status isempty(linkstack top){
    if (top->next==NULL) {
        return OK;
    }
    return ERROR;
}
Status push(linkstack top, ElemType e){
    linkstack p;
    p=(linkstack)malloc(sizeof(stacknode));
    if (!p) {
        return ERROR;
    }
    p->data=e;
    p->next=top->next;
    top->next=p;
    return OK;
}
Status pop(linkstack top,ElemType &e){
    if (isempty(top)) {
        return ERROR;
    }
    linkstack p=top->next;
    e=p->data;
    top->next=p->next;
    free(p);
    return OK;
}
Status printstack(linkstack top){
    linkstack p;
    p=top;
    while (p->next!=NULL) {
        cout<<p->next->data;
        p=p->next;
    }
    cout<<endl;
    return OK;
}
Status initqueue(LinkQueue *q){
    q->front=q->rear=(Queueptr)malloc(sizeof(QNode));
    if (!q->front) {
        exit(OVERFLOW);
    }
    q->front->next=NULL;
    return OK;
}
Status enqueue(LinkQueue *q,ElemType e){
    Queueptr p=(Queueptr)malloc(sizeof(QNode));
    if (!p) {
        exit(OVERFLOW);
    }
    p->data=e;
    p->next=NULL;
    q->rear->next=p;
    q->rear=p;
    return  OK;
}
Status dequeue(LinkQueue *q, ElemType &e){
    if (q->front==q->rear) {
        return ERROR;
    }
    Queueptr p;
    p=q->front->next;
    e=p->data;
    q->front->next=p->next;
    if (q->rear==p) {
        q->rear=q->front;
    }
    free(p);
    return OK;
}
int main(int argc, const char * argv[]) {
    int key;
    cout<<"请选择需要的操作：\n";
    cout<<"1、链栈\n2、链队列\n";
    cin>>key;
    switch (key) {
        case 1:
            linkstack s;
            s=(linkstack)malloc(sizeof(stacknode));
            initstack(s);
            cout<<"4个进站元素依次为：\n";
            for (int i=0; i<4; i++) {
                ElemType a;
                cin>>a;
                push(s, a);
            }
            cout<<"栈顶到栈底的元素依次为：\n";
            printstack(s);
            ElemType b,c,d;
            pop(s, b);
            pop(s, c);
            pop(s, d);
            push(s, b);
            cout<<"出栈的元素为：\n"<<c<<"  "<<d<<endl;
            cout<<"现在的栈中元素为：\n";
            printstack(s);
            break;
            
        default:
            LinkQueue q;
            initqueue(&q);
            ElemType a,e,f,g,h;
            cout<<"请输入进队的5个元素：\n";
            for (int i=0; i<5; i++) {
                cin>>a;
                enqueue(&q, a);
            }
            cout<<"出队元素为：\n";
            dequeue(&q, a);
            dequeue(&q, e);
            dequeue(&q, f);
            dequeue(&q, g);
            dequeue(&q, h);
            cout<<e<<" "<<f<<endl;
            enqueue(&q, a);
            enqueue(&q, g);
            enqueue(&q, h);
            cout<<"现在的队列为：\n";
            for (int i=0; i<3; i++) {
                ElemType e;
                dequeue(&q, e);
                cout<<e<<" ";
            }
            cout<<endl;
            break;
    }
    
    return 0;
}
