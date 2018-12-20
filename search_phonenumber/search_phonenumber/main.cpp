//
//  main.cpp
//  search_phonenumber
//
//  Created by tamchikit on 2018/11/27.
//  Copyright © 2018 tamchikit. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include<cstring>
#include <iostream>
using namespace std;

typedef int Status;
typedef char* KeyType;
typedef struct User{
    char name[50];
    char num[20];
}User;
typedef struct Node{
    User user;
    Node *next;
}Node;
int user_num;
const int MaxSize = 10000;
const int MOD = 9973;
Node *hashtable[MaxSize];

int Hash(char *key);
void add_record(char *name, char *tel_num);
bool Hsearch(char *name, char *tel_num);

int Hash(char *key){
    unsigned long h = 0;
    while(*key){
        h = (h<<4) + *key++;
        unsigned long g = h&0Xf0000000L;
        if(g) h ^= g>>24;
        h &= ~g;
    }
    return h % MOD;
}

void add_record(char *name, char *tel_num){
    int key = Hash(name);
    Node *node = new Node;
    strcpy(node->user.name, name);
    strcpy(node->user.num, tel_num);
    node->next = hashtable[key];
    hashtable[key] = node;
}

bool Hsearch(char *name, char *tel_num){
    int key = Hash(name);
    Node *p = hashtable[key];
    while(p != NULL){
        if(strcmp(name, p->user.name) == 0){
            strcpy(tel_num, p->user.num);
            return true;
        }
        p = p->next;
    }
    return false;
}

int main(int argc, const char * argv[]) {
    int i, k;
    char name[20], tel_num[20];
    memset(hashtable, 0, sizeof(hashtable));
    cout << "系统初始化：先录入用户的人数：";
    cin >> user_num;
    for(i = 0; i < user_num; i ++){
        cout << "请录入用户的名字：" << endl;
        cin >> name;
        cout<<"请录入用户的电话号码:\n";
        cin>>tel_num;
        add_record(name, tel_num);
    }
    cout << "系统初始化完毕。" << endl;
    while(1){
        cout << "\n请输入要执行的操作(1.查询,0.退出系统): ";
        cin >> k;
        if(k != 1) break;
        cout << "请出入要查询的用户名: ";
        cin >> name;
        if(!Hsearch(name, tel_num)) cout << "对不起，没有你要查询的用户。" << endl;
        else cout << "你所查询用户的电话号码为：" << tel_num << endl;
    }
    return 0;
}
