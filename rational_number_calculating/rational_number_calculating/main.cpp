//
//  main.cpp
//  rational_number_calculating
//
//  Created by tamchikit on 2018/9/11.
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
typedef ElemType *Rational_Num;

Status InitRational_Num(Rational_Num &T, ElemType a1, ElemType a2);
Status ADD(Rational_Num T1, Rational_Num T2, Rational_Num &T3);
Status SUB(Rational_Num T1, Rational_Num T2, Rational_Num &T3);
Status MUL(Rational_Num T1, Rational_Num T2, Rational_Num &T3);
Status DIV(Rational_Num T1, Rational_Num T2, Rational_Num &T3);
Status DEL(Rational_Num T1);
int gcd(int a, int b);

int gcd(int a, int b){
    int c,tmp;
    if(a<b){
        tmp=a;
        a=b;
        b=tmp;
    }
    while(b!=0){
        c=a%b;
        a=b;
        b=c;
    }
    return a;
}

int main(int argc, const char * argv[]) {
    Rational_Num T1,T2,T3;
    ElemType a1,a2,b1,b2;
    cout<<"请输入第一个有理数，第一个数字为分子，第二个数字为分母：\n";
    cin>>a1>>a2;
    cout<<"请输入第二个有理数，第一个数字为分子，第二个数字为分母：\n";
    cin>>b1>>b2;
    if (a2<=0|b2<=0) {
        cout<<"WARN:有理数分母不能为零或等于负数，请重新输入！\n";
        cout<<"请输入第一个有理数，第一个数字为分子，第二个数字为分母：\n";
        cin>>a1>>a2;
        cout<<"请输入第二个有理数，第一个数字为分子，第二个数字为分母：\n";
        cin>>b1>>b2;
    }
    else{
        InitRational_Num(T1,a1,a2);
        InitRational_Num(T2,b1,b2);
        cout<<"您构造的两个有理数分别为："<<a1<<"/"<<a2<<" "<<b1<<"/"<<b2<<"\n";
        ADD(T1,T2,T3);
        cout<<T1[0]<<"/"<<T1[1]<<" "<<"+"<<" "<<T2[0]<<"/"<<T2[1]<<"="<<T3[0]<<"/"<<T3[1]<<"\n";
        SUB(T1,T2,T3);
        cout<<T1[0]<<"/"<<T1[1]<<" "<<"-"<<" "<<T2[0]<<"/"<<T2[1]<<"="<<T3[0]<<"/"<<T3[1]<<"\n";
        MUL(T1,T2,T3);
        cout<<T1[0]<<"/"<<T1[1]<<" "<<"*"<<" "<<T2[0]<<"/"<<T2[1]<<"="<<T3[0]<<"/"<<T3[1]<<"\n";
        DIV(T1,T2,T3);
        cout<<T1[0]<<"/"<<T1[1]<<" "<<"/"<<" "<<T2[0]<<"/"<<T2[1]<<"="<<T3[0]<<"/"<<T3[1]<<"\n";
    }
    DEL(T1);
    DEL(T2);
    DEL(T3);
    getchar();
    return 0;
}

Status InitRational_Num(Rational_Num &T, ElemType a1, ElemType a2){
    T=(ElemType *)malloc(sizeof(ElemType)*2);
    if (!T) {
        exit(OVERFLOW);
    }
    T[0]=a1;
    T[1]=a2;
    return OK;
}

Status ADD(Rational_Num T1, Rational_Num T2, Rational_Num &T3){
    int a,b,c;
    c = gcd(T1[1], T2[1]);
    a = T1[1]/c;
    b = T2[1]/c;
    InitRational_Num(T3, T1[0]*b+T2[0]*a, a*b*c);
    return OK;
}

Status SUB(Rational_Num T1, Rational_Num T2, Rational_Num &T3){
    int a,b,c;
    c = gcd(T1[1], T2[1]);
    a = T1[1]/c;
    b = T2[1]/c;
    InitRational_Num(T3, T1[0]*b-T2[0]*a, a*b*c);
    return OK;
}

Status MUL(Rational_Num T1, Rational_Num T2, Rational_Num &T3){
    int tmp1,tmp2;
    tmp1 = T1[0]*T2[0];
    tmp2 = T1[1]*T2[1];
    InitRational_Num(T3, tmp1/gcd(tmp1, tmp2), tmp2/gcd(tmp1, tmp2));
    return OK;
}

Status DIV(Rational_Num T1, Rational_Num T2, Rational_Num &T3){
    int tmp1,tmp2;
    tmp1 = T1[0]*T2[1];
    tmp2 = T1[1]*T2[0];
    InitRational_Num(T3, tmp1/gcd(tmp1, tmp2), tmp2/gcd(tmp1, tmp2));
    return OK;
}

Status DEL(Rational_Num T1){
    if (!T1) {
        exit(OVERFLOW);
    }
    T1[0]=NULL;
    T1[1]=NULL;
    return OK;
}
