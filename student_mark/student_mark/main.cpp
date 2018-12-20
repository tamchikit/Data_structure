//
//  main.cpp
//  student_mark
//
//  Created by tamchikit on 2018/12/4.
//  Copyright © 2018 tamchikit. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef struct Student{
    int mark;
    int rank;
    char name[20];
}Student,*Stu;

Status Initstudent(Stu &S, int i);
Status Sort(Student &S, int n);

Status Initstudent(Stu &S,int i){
    cout<<"请输入第"<<i+1<<"个学生的姓名:\n";
    cin>>S[i].name;
    cout<<"请输入第"<<i+1<<"个学生的成绩:\n";
    cin>>S[i].mark;
    return OK;
}

Status Sort(Stu &S, int n){
    int i = 0, j = 0, k = 0;
    Student tmp;
    for (i=0; i < n-1; i++)
    {
        k = i;
        for (j=i+1; j < n; j++)
        {
            if (S[k].mark < S[j].mark)
            {
                k = j;
            }
        }
        
        if (k != i)
        {
            tmp=S[k];
            S[k]=S[i];
            S[i]=tmp;
        }
    }
    int rank=1;
    for (int i=0; i<n; i++) {
        if (i>0) {
            if (S[i].mark==S[i-1].mark) {
                S[i].rank=S[i-1].rank;
                rank++;
            }
            else {
                rank++;
                S[i].rank=rank;
            }
        }
        else S[i].rank=rank;
    }
    return OK;
}

int main(int argc, const char * argv[]) {
    int n;
    cout << "欢迎来到学生成绩统计系统!\n请输入学生个数：\n";
    cin>>n;
    Stu S = (Stu) malloc(n*(sizeof(Student)));
    for (int i=0; i<n; i++) {
        Initstudent(S, i);
    }
    cout<<"初始化成功！\n";
    Sort(S, n);
    for (int i=0; i<n; i++) {
        cout<<"第 "<<S[i].rank<<" 名是 "<<S[i].name<<" 成绩为： "<<S[i].mark<<"\n";
    }
    return 0;
}
