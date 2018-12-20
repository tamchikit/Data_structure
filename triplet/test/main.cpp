//
//  main.cpp
//  test
//
//  Created by tamchikit on 2018/9/4.
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
typedef ElemType *Triplet;

Status InitTriplet(Triplet &T, ElemType v1, ElemType v2, ElemType v3);
Status max(ElemType v1, ElemType v2, ElemType v3);
Status putin(Triplet T);
Status getfrom(Triplet T);

int main()
{
    Triplet T;
    ElemType v1=0,v2=0,v3=0;
    InitTriplet(T,v1,v2,v3);
    putin(T);
    getfrom(T);
    cout<<"The Triplet is: "<<T[0]<<T[1]<<T[2]<<"\n";
    ElemType biggest=max(T[0],T[1],T[2]);
    cout<<"The biggest one is: "<<biggest<<"\n";
    getchar();
    return 0;
}
Status InitTriplet(Triplet &T, ElemType v1, ElemType v2, ElemType v3)
{
    T=(ElemType *) malloc(3*sizeof(ElemType));
    if(!T)
        exit(OVERFLOW);
    T[0]=v1;
    T[1]=v2;
    T[2]=v3;
    return OK;
}
Status max(ElemType v1, ElemType v2, ElemType v3)
{
    ElemType a=v1>v2?v1:v2;
    return a>v3?a:v3;
}
Status putin(Triplet T){
    int place;
    while (T[0]==NULL||T[1]==NULL||T[2]==NULL){
        cout<<"Please input the number where you want to put the data:\n";
        cin>>place;
        if (place>2) {
            cout<<"place can't be bigger than 2!\n";
            return 0;
        }
    cout<<"please input your data for "<<place<<":\n";
    cin>>T[place];
    }
    return OK;
}
Status getfrom(Triplet T){
    int place;
    cout<<"please input a number to get the data:\n";
    cin>>place;
    if (place>2) {
        cout<<"place can't be bigger than 2!\n";
        return 0;
    }
    cout<<"the "<<place<<" data is:"<<T[place]<<"\n";
    return OK;
}
