//
//  main.cpp
//  tree_test1
//
//  Created by tamchikit on 2018/10/9.
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
typedef char TElemType;
typedef struct BiTNode{
    TElemType   data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;
typedef struct Stack{
    BiTree data;
    struct Stack *next;
}Stack, *Lstack;

Status CreateBiTree(BiTree &T);
Status PrePrintBiTree(BiTree T,  Status (* Visit)(TElemType e));
Status InPrintBiTree(BiTree T, Status (* Visit)(TElemType e));
Status PrintElement(TElemType e);
Status ChangeBiTree(BiTree &T);

Status CreateBiTree(BiTree &T){
    char c;
    cout<<"请一个一个按照先序输入树的结点,结束请输入\\：\n";
    cin>>c;
    if (c=='\\') {
        T = NULL;
    }
    else{
        if (!(T=(BiTree)malloc(sizeof(BiTNode)))) {
            exit(OVERFLOW);
        }
        T->data=c;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
    return OK;
}

Status PrintElement(TElemType e){
    cout<<e<<" ";
    return OK;
}

Status PrePrintBiTree(BiTree T,  Status ( * Visit)(TElemType e)){
    if (T) {
        if (Visit(T->data)) {
            if (PrePrintBiTree(T->lchild, Visit)) {
                if (PrePrintBiTree(T->rchild, Visit)) {
                    return OK;
                }
            }
            return ERROR;
        }
    }
    return OK;
}

Status InPrintBiTree(BiTree T,  Status (* Visit)(TElemType e)){
    if (T) {
        if (InPrintBiTree(T->lchild, Visit)) {
            if (Visit(T->data)) {
                if (InPrintBiTree(T->rchild, Visit)) {
                    return OK;
                }
            }
        }
    }
    return OK;
}

Status ChangeBiTree(BiTree &T){
    BiTree tmp;
    if (T) {
        if (T->lchild||T->rchild) {
            tmp=T->lchild;
            T->lchild=T->rchild;
            T->rchild=tmp;
            return OK;
        }
    }
    ChangeBiTree(T->lchild);
    ChangeBiTree(T->rchild);
    return OK;
}

int main(int argc, const char * argv[]) {
    BiTree T;
    CreateBiTree(T);
    cout<<"先序遍历得到的树为：\n";
    PrePrintBiTree(T, PrintElement);
    cout<<"\n中序遍历的到的树为：\n";
    InPrintBiTree(T, PrintElement);
    cout<<endl;
    ChangeBiTree(T);
    cout<<"交换后先序遍历得到的树为：\n";
    PrePrintBiTree(T, PrintElement);
    cout<<"\n交换后中序遍历的到的树为：\n";
    InPrintBiTree(T, PrintElement);
    cout<<endl;
    return 0;
}
