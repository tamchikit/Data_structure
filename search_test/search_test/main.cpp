//
//  main.cpp
//  search_test
//
//  Created by tamchikit on 2018/11/20.
//  Copyright © 2018 tamchikit. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
//数值型
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))

typedef int KeyType;
typedef struct {
    KeyType *elem;
    int length;
}SSTable;

KeyType Creat(SSTable &ST, int n);
KeyType Search(SSTable ST, KeyType key);
KeyType Search_Bin(SSTable ST,KeyType key);

KeyType Creat(SSTable &ST, int n){
    ST.length=n;
    ST.elem=(KeyType *)malloc(sizeof(KeyType)*(ST.length));
    for (int i=1; i<ST.length+1; i++) {
        cout<<"please input data from small to big:\n";
        cin>>ST.elem[i];
    }
    cout<<"顺序表构建完成\n";
    return OK;
}

KeyType Search(SSTable ST, KeyType key){
    ST.elem[0]=key;
    int i;
    for (i=ST.length; !EQ(ST.elem[i], key); --i);
    return i;
}

KeyType Search_Bin(SSTable ST,KeyType key){
    int low = 1;
    int high = ST.length;
    int mid;
    while (low<=high) {
        mid=(low+high)/2;
        if (EQ(key, ST.elem[mid])) {
            return mid;
        }
        else if(LT(key, ST.elem[mid])) high=mid-1;
        else low=mid+1;
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    SSTable ST;
    int n;
    int a;
    KeyType key;
    cout<<"please input the sstable's length:\n";
    cin>>n;
    Creat(ST, n);
    cout<<"顺序表查找：\n";
    cout<<"please input what you want to search:\n";
    cin>>key;
    a=Search(ST, key);
    cout<<a<<endl;
    cout<<"折半法查找：\n";
    cout<<"please input what you want to search:\n";
    cin>>key;
    a=Search_Bin(ST, key);
    cout<<a<<endl;
    return 0;
}
