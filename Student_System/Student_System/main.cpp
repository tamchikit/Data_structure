//
//  main.cpp
//  Student_System
//
//  Created by tamchikit on 2018/9/18.
//  Copyright © 2018年 tamchikit. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include<fstream>
#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;
typedef struct Student{
    string name;
    ElemType mark;
    ElemType number;
    struct Student *next;
}Student, *StuList;

Status Input(StuList &L);//输入学生资料
Status Select(StuList L);//搜索学生
Status Del(StuList &L);//删除
Status Rewrite(StuList &L, string a, ElemType i, ElemType j);//修改学生信息
Status Show(StuList L);//显示学生信息
Status store(StuList L);//导出为txt
void login();
void logout();//登出
void rootmenu();//跟用户菜单选择系统函数
void guestmenu();//客人用户菜单选择系统函数
void Modify();//修改密码
void Rewrite1(StuList &L);
int pp=123456;
int c;
StuList S;


void rootmenu()                              //跟用户菜单选择系统函数
{
    system("cls");
    cout<<"\t\t     ╭♈♉♊♋♌♎══■□■□══════╮\n";
    cout<<"\t\t     │       学生信息管理系统     |\n";
    cout<<"\t\t     ╰══════■□■□══♏♐♑♓♒♍╯\n";
    cout<<"\t\t    ┌──────────────────────────┐\n";
    cout<<"\t\t    │ 1. 添加记录    2. 显示记录  │\n";
    cout<<"\t\t    │                          |\n";
    cout<<"\t\t    │ 3. 信息查询    4. 修改记录  │\n";
    cout<<"\t\t    │                          │\n";
    cout<<"\t\t    │ 5. 修改密码    6. 删除信息  │\n";
    cout<<"\t\t    │                          │\n";
    cout<<"\t\t    │ 7. 导出信息    8. 退出登陆  |\n";
    cout<<"\t\t    │                          │\n";
    cout<<"\t\t    └──────────────────────────┘\n";
    cout<<"\t\t请您选择(0-8):";
    cin>>c;
    while(c<0||c>8){
        cout<<"输入错误请重新输入"<<endl;
        cin>>c;
    }
    switch (c) {
        case 1:
            Input(S);
            break;
        case 2:
            Show(S);
            break;
        case 3:
            Select(S);
            break;
        case 4:
            Rewrite1(S);
            break;
        case 5:
            Modify();
            break;
        case 6:
            Del(S);
            break;
        case 7:
            store(S);
            break;
        default:
            logout();
            break;
    }
}

void Modify()//修改密码
{
    int verpsw, tempsw1, tempsw2 = 0;//pp为原始正确密码，verpsw为验证密码,tempsw为临时密码
    cout << "请输入原始密码"<<endl;
    cin >> verpsw;
    while (verpsw != pp)
    {
        cout << "密码错误，请重新输入" << endl;
        cin >> verpsw;
    }
    cout << "密码正确，验证成功" << endl;
    do {
        cout << "请输入需要新密码,输入1退出至主界面:" << endl;
        cin >> tempsw1;
        if (tempsw1 == 1)
        {
            rootmenu();
            break;
        }
        else cout << "请再次输入新密码:" << endl;
        cin >> tempsw2;
    }
    while (tempsw1 != tempsw2);
    cout << "验证成功.";
    pp = tempsw2;
    rootmenu();
}


void guestmenu()                              //客人用户菜单选择系统函数
{
    system("cls");
    cout<<"\t\t    ╭♈♉♊♋♌♎══■□■□══════╮\n";
    cout<<"\t\t    │       学生信息管理系统     |\n";
    cout<<"\t\t    ╰══════■□■□══♏♐♑♓♒♍╯\n";
    cout<<"\t\t    ┌──────────────────────────┐\n";
    cout<<"\t\t    │ 1. 信息查询    2. 显示记录  │\n";
    cout<<"\t\t    │                          |\n";
    cout<<"\t\t    │ 3. 退出登录    4.导出信息   │\n";
    cout<<"\t\t    │                          │\n";
    cout<<"\t\t    │ 5. 退出程序                |\n";
    cout<<"\t\t    └──────────────────────────┘\n";
    cout<<"\t\t请您选择(0-5):";
    cin>>c;
    while(c<0||c>5)
    {
        cout<<"输入错误请重新输入"<<endl;
        cin>>c;
    }
    switch (c) {
        case 1:
            Select(S);
            break;
        case 2:
            Show(S);
            break;
        case 3:
            logout();
            break;
        case 4:
            store(S);
            break;
        default:
            exit(0);
            break;
    }
}

void login()   //登录界面
{
    string username;
    int pwd;
    system("cls");
    cout<<"欢迎来到学生信息管理系统"<<endl<<endl;
    cout<<"请输入用户名："<<endl;
    cin>>username;
    cout<<"请6位数输入密码："<<endl;
    cin>>pwd;
    while ((username!="root"&&username!="guest")||(pwd!=pp&&pwd!=654321)) {
        cout<<"账户或密码错误,请重新输入!"<<endl<<endl;
        cout<<"请输入用户名：";
        cin>>username;
        cout<<"请6位数输入密码：";
        cin>>pwd;
    }
    cout<<"输出正确，欢迎登录"<<endl;
    while(username=="root"&&pwd==pp)
    {
        rootmenu();
    }
    while(username=="guest"&&pwd==654321)
    {
        guestmenu();
    }
}

Status Input(StuList &L){
    ElemType num,mark;
    StuList p = L;
    ElemType student_num;
    string name;
    cout << "请输入学生个数:\n";
    cin >> student_num;
    for (int i=0 ; i<student_num; i++) {
        cout << "请输入学号:\n";
        cin >> num;
        while (p) {
            if(num!=p->number){
                p=p->next;
            }
            else{
                cout<<"学号已存在，请重新输入！\n";
                Input(L);
            }
        }
        p=L;
        while (p->next) {
            p=p->next;
        }
        cout<<"请输入姓名:\n";
        cin>>name;
        cout<<"请输入成绩：\n";
        cin>>mark;
        StuList s = (StuList) malloc(sizeof(Student));
        s->next = NULL;
        s->name = name;
        s->number = num;
        s->mark = mark;
        p->next = s;
    }
    return OK;
}

Status Show(StuList L){
    StuList p = L->next;
    StuList tmp;
    int key;
    cout<<"请选择："<<endl;
    cout<<"1、按学号由小到大查看；"<<endl;
    cout<<"2、按成绩由高到低查看；"<<endl;
    cin>>key;
    switch (key) {
        case 2:
            for (StuList i=L->next; i!=NULL; i=i->next) {
                StuList max=i;
                StuList j=i;
                while (j!=NULL) {
                    if (j->mark>max->mark) {
                        max=j;
                    }
                    j=j->next;
                }
                if (max!=i) {
                    Rewrite(tmp, max->name, max->number, max->mark);
                    Rewrite(max, i->name, i->number, i->mark);
                    Rewrite(i, tmp->name, tmp->number, tmp->mark);
                }
            }
            while (p!=NULL) {
                cout<<"学生"<< p->name <<"的学号为： "<< p->number <<"成绩为: "<< p->mark <<endl;
                p=p->next;
            }
            break;
            
        default:
            for (StuList i=L->next; i!=NULL; i=i->next) {
                StuList min=i;
                StuList j=i;
                while (j!=NULL) {
                    if (j->number<min->number) {
                        min=j;
                    }
                    j=j->next;
                }
                if (min!=i) {
                    Rewrite(tmp, min->name, min->number, min->mark);
                    Rewrite(min, i->name, i->number, i->mark);
                    Rewrite(i, tmp->name, tmp->number, tmp->mark);
                }
            }
            while (p!=NULL) {
                cout<<"学生"<<p->name<<"的学号为： "<<p->number<<"成绩为: "<<p->mark<<endl;
                p=p->next;
            }
            break;
    }
    return OK;
}

Status Select(StuList L){
    int num;
    cout<<"请输入学生学号以查询：\n";
    cin>>num;
    StuList t=L;
    while (t->number!=num) {
        t=t->next;
        if (t==NULL) {
            cout<<"输入的学号不存在,请重新输入\n";
            Select(L);
        }
    }
    cout<<"学生"<<t->name<<"的学号为："<<t->number<<"成绩为： "<<t->mark<<endl;
    return OK;
}

void Rewrite1(StuList &L){
    string newname;
    ElemType number,newmark;
    cout<<"请输入要修改的学生的学号：\n";
    cin>>number;
    cout<<"请输入学生成绩：\n";
    cin>>newmark;
    cout<<"请输入学生姓名：\n";
    cin>>newname;
    Rewrite(L, newname, number, newmark);
}

Status Rewrite(StuList &L, string a, ElemType i, ElemType j){
    StuList t=L->next;
    while (t->number!=i) {
        t=t->next;
        if (t==NULL) {
            return ERROR;
        }
    }
    t->name=a;
    t->number=i;
    t->mark=j;
    return OK;
}

Status store(StuList L){
    ofstream fout("/Users/tanzhijie/Desktop/Studentsysterm.txt");
    fout<<"学号   学生姓名   成绩"<<endl;
    StuList p =L->next;
    while (p) {
        fout<<p->number<<"     ";
        fout<<p->name<<"        ";
        fout<<p->mark<<endl;
        p=p->next;
    }
    cout<<"成功导出学生信息为/Users/tanzhijie/Desktop/Studentsysterm.txt\n";
    return OK;
}

Status Del(StuList &L){
    int num;
    cout<<"请输入要删除的学生学号：\n";
    cin>>num;
    StuList t=L;
    StuList tmp;
    if (t->next==NULL) {
        cout<<"输入的学号不存在,请重新输入\n";
        Del(L);
    }
    else{
        while (t->next->number!=num) {
            t=t->next;
        }
    }
    tmp = t;
    t->next=t->next->next;
    free(tmp->next);
    return OK;
}

void logout()//登出
{
    string username;
    int pwd;
    system("cls");
    cout<<"欢迎来到学生信息管理系统"<<endl<<endl;
    cout<<"请输入用户名："<<endl;
    cin>>username;
    cout<<"请6位数输入密码："<<endl;
    cin>>pwd;
    while ((username!="root"&&username!="guest")||(pwd!=pp&&pwd!=654321)) {
        cout<<"账户或密码错误,请重新输入!"<<endl<<endl;
        cout<<"请输入用户名：";
        cin>>username;
        cout<<"请6位数输入密码：";
        cin>>pwd;
    }
    cout<<"输出正确，欢迎登录"<<endl;
    while(username=="root"&&pwd==pp)
    {
        rootmenu();
    }
    while(username=="guest"&&pwd==654321)
    {
        guestmenu();
    }
}

int main(int argc, const char * argv[]) {
    S = (StuList)malloc(sizeof(Student));
    S->next=NULL;
    login();
    return 0;
}
