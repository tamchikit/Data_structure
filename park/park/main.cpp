//
//  main.cpp
//  park
//
//  Created by tamchikit on 2018/10/4.
//  Copyright © 2018年 tamchikit. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100

typedef int Status;
typedef int ElemType;

typedef struct car{
    char al;
    ElemType num;
    ElemType time;
}car;
typedef struct Stack{
    struct car data[MAXSIZE];
    ElemType top;
    ElemType num;
}Sqstack,*Snode ;
typedef struct Qnode{
    struct car data;
    Qnode *next;
}Qnode;
typedef struct linkqueue{
    Qnode *front;
    Qnode *rear;
    ElemType num;
}linkqueue,*Lnode;

Status initstack(Snode  &s);
Status initlinkqueue(Lnode &q);
Status isemptystack(Snode  s);
Status isfullstack(Snode s, ElemType n);
Status isemptylinkqueue(Lnode q);
Status inlinkqueue(Lnode &q, car s);
Status pushstack(Snode &s, car c);
Status popstack(Snode &s, car c);
Status outlqueue(Lnode q,car &c);


Status initstack(Snode &s){
    s=(Snode )malloc(sizeof(Sqstack));
    s->top=-1;
    s->num=0;
    return OK;
}
Status initlinkqueue(Lnode &q){
    Qnode *p;
    q=(Lnode )malloc(sizeof(linkqueue));
    p=(Qnode *)malloc(sizeof(Qnode));
    p->next=NULL;
    q->front=q->rear=p;
    q->num=0;
    return OK;
}
Status isemptystack(Snode s){
    if (s->top==-1) {
        return  1;
    }
    else{
        return 0;
    }
}
Status isfullstack(Snode s, ElemType n){
    if (s->num==n) {
        return 1;
    }
    else{
        return 0;
    }
}
Status isemptylinkqueue(Lnode q){
    if (q->front==q->rear) {
        return 1;
    }
    else{
        return 0;
    }
}
Status inlinkqueue(Lnode &q, car s){
    Qnode *p;
    p=(Qnode *)malloc(sizeof(Qnode));
    p->data=s;
    q->num++;
    p->next=NULL;
    q->rear->next=p;
    q->rear=p;
    return OK;
}
Status pushstack(Snode &s, car c){
    s->top++;
    s->data[s->top]=c;
    s->num++;
    return OK;
}
Status popstack(Snode &s, car c){
    Snode p;
    ElemType t;
    initstack(p);
    while (s->data[s->top].num!=c.num) {
        pushstack(p, s->data[s->top]);
        s->top--;
        s->num--;
    }
    t=c.time-s->data[s->top].time;
    s->top--;
    s->num--;
    while (isemptystack(p)==0) {
        pushstack(s, p->data[p->top]);
        p->top--;
        p->num--;
    }
    return t;
}
Status outlqueue(Lnode q,car &c){
    Qnode *p;
    p=q->front->next;
    q->front->next=p->next;
    q->num--;
    if (q->front->next==NULL) {
        q->rear=q->front;
    }
    c=p->data;
    free(p);
    return OK;
}

int main(int argc, const char * argv[]) {
    Snode parkstack;
    Lnode parkqueue;
    car c;
    int n,t;
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo=localtime(&rawtime);
    initstack(parkstack);
    initlinkqueue(parkqueue);
    cout<<"======================"<<endl;
    cout<<"请输入停车场最大容量：\n";
    cin>>n;
    cout<<"请输入车辆信息，（A/P/W/D/E），车牌号码，到达时间\n";
    cin>>c.al>>c.num>>c.time;
    while (c.al!='E') {
        if (c.al=='A') {
            if (isfullstack(parkstack,n)==1) {
                inlinkqueue(parkqueue, c);
                cout<<"这辆车在门外便道上第"<<parkqueue->num<<"个位置\n";
                cout<<"请输入车辆信息，（A/P/W/D/E），车牌号码，到达时间\n";
            }
            else{
                pushstack(parkstack, c);
                cout<<"这辆车在停车场内第"<<parkstack->num<<"个位置上\n";
                cout<<"请输入车辆信息，（A/P/W/D/E），车牌号码，到达时间\n";
            }
        }
        if (c.al=='D') {
            t=popstack(parkstack, c);
            cout<<"这辆车的停留时间为："<<t<<endl;
            cout<<"请输入车辆信息，（A/P/W/D/E），车牌号码，到达时间\n";
            if (isemptylinkqueue(parkqueue)==0) {
                outlqueue(parkqueue, c);
                pushstack(parkstack, c);
            }
        }
        if (c.al=='P'&&c.num==0&&c.time==0) {   //显示停车场车辆数目
            cout<<"停车场内车辆数目为："<<parkstack->num<<endl;
            cout<<"请输入车辆信息，（A/P/W/D/E），车牌号码，到达时间\n";
        }
        if (c.al=='W'&&c.num==0&&c.time==0) {
            cout<<"候车场车辆数目为："<<parkqueue->num<<endl;
            cout<<"请输入车辆信息，（A/P/W/D/E），车牌号码，到达时间\n";
        }
        cin>>c.al>>c.num>>c.time;
    }
    cout<<"输入结束n";
    cout<<"current local time and date:"<<asctime(timeinfo)<<endl;
    return 1;
}
