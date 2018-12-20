//
//  main.cpp
//  huffmantree
//
//  Created by tamchikit on 2018/10/16.
//  Copyright © 2018年 tamchikit. All rights reserved.
//还未实现从文件读入编码以及解码 2018.10.16

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;
typedef struct {
    unsigned int weight;
    char a;
    unsigned int parent,lchild,rchild;
}HTNode, *HuffmanTree;
typedef char * *HuffmanCode;

void HuffmanCoding(HuffmanTree HT, HuffmanCode &HC, int n);
void HuffmanDecoding(HuffmanTree &HT, int n);
void HuffmanBuilding(HuffmanTree &HT, unsigned int *w, char *a, int n);
void HuffmanToFile(HuffmanTree HT,int n);
void HuffmanFromFile(HuffmanTree &HT, int &n);
Status Select(HuffmanTree HT, int a, unsigned int *s1, unsigned int *s2);

void HuffmanBuilding(HuffmanTree &HT, unsigned int *w, char *a, int n){
    if (n<=1) {
        return;
    }
    int m=2*n-1;
    HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
    int i=0;
    HuffmanTree p;
    unsigned int s1,s2;
    for (p=HT+1, i=1; i<=n; ++i, ++p,++a, ++w) {
        *p = {*w,*a,0,0,0};
    }
    for (; i<=m; ++i, ++p) {
        *p={0,0,0,0,0};
    }
    for (i=n+1; i<=m; ++i) {
        Select(HT,i-1,&s1,&s2);
        HT[s1].parent=i;
        HT[s2].parent=i;
        HT[i].lchild=s1;
        HT[i].rchild=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
        HT[i].a='0';
    }
}

void HuffmanCoding(HuffmanTree HT, HuffmanCode &HC, int n){
    int i=0;
    HC=(HuffmanCode)malloc((n+1)*sizeof(char *));
    char *cd;
    int c;
    unsigned int f;
    cd=(char *)malloc(n*sizeof(char));
    cd[n-1]='\0';
    for (i=1; i<=n; ++i) {
        int start=n-1;
        for (c=i, f=HT[i].parent; f!=0; c=f,f=HT[f].parent) {
            if (HT[f].lchild==c) {
                cd[--start]='0';
            }
            else cd[--start]='1';
        }
        HC[i]=(char *)malloc((n-start)*sizeof(char));
        strcpy(HC[i], &cd[start]);
    }
    ofstream ofile;
    ofile.open("/Users/tanzhijie/Desktop/tmp/codefile.txt");
    for (int i=1; i<=n; i++) {
        ofile<<HC[i];
    }
    cout<<"Huffman Tree Code has been saved into /Users/tanzhijie/Desktop/tmp/codefile.txt."<<endl;
    free(cd);
    ofile.close();
}

void HuffmanToFile(HuffmanTree HT,int n){
    ofstream ofile;
    ofile.open("/Users/tanzhijie/Desktop/tmp/hfmTree.txt");
    int m=2*n-1;
    ofile<<n<<"\n";
    for (int i=0; i<=m; ++i) {
        ofile<<HT[i].weight<<" "<<HT[i].a<<" "<<HT[i].parent<<" "<<HT[i].lchild<<" "<<HT[i].rchild<<"\n";
    }
    cout<<"Huffman Tree has been saved into /Users/tanzhijie/Desktop/tmp/hfmTree.txt."<<endl;
    ofile.close();
}

void HuffmanFromFile(HuffmanTree &HT,int &n){
    ifstream ifile;
    ifile.open("/Users/tanzhijie/Desktop/tmp/hfmTree.txt");
    cout<<"reading huffman tree from file..."<<endl;
    ifile>>n;
    int m=2*n-1;
    HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
    for (int i=0; i<=m; i++) {
        ifile>>HT[i].weight>>HT[i].a>>HT[i].parent>>HT[i].lchild>>HT[i].rchild;
    }
    ifile.close();
}

void HuffmanDecoding(HuffmanTree &HT, int n){
    ifstream ifile;
    ofstream ofile;
    ifile.open("/Users/tanzhijie/Desktop/tmp/codefile.txt");
    ofile.open("/Users/tanzhijie/Desktop/tmp/textfile.txt");
    int m=2*n-1;
    int i,j=0;
    char ch[m-1];
    ifile>>ch;
    while(ch[j]!='\0'){
        i=m;
        while(0 != HT[i].lchild && 0 != HT[i].rchild){
            if('0' == ch[j]){
                i=HT[i].lchild;
            }
            else i=HT[i].rchild;
            ++j;
        }
        ofile<<HT[i].a<<" ";
    }
    ofile<<endl;
    cout<<"The code has been translated and saved into /Users/tanzhijie/Desktop/tmp/textfile.txt."<<endl;
    ifile.close();
    ofile.close();
}

Status Select(HuffmanTree HT, int a, unsigned int *s1, unsigned int *s2){
    long m1=99999999999;
    long m2=99999999999;
    int i=0;
    for (i=1; i<=a; i++) {
        if (HT[i].parent==0) {
            if(m1>HT[i].weight){
                m1=HT[i].weight;
                *s1=i;
            }
        }
    }
    for (i=1; i<=a; i++) {
        if (HT[i].parent==0) {
            if (m2>HT[i].weight&&i!=(*s1)) {
                m2=HT[i].weight;
                *s2=i;
            }
        }
    }
    return OK;
}

int main(int argc, const char * argv[]) {
    HuffmanTree HT;
    HuffmanTree HT1;
    HuffmanCode HC;
    HuffmanCode HC1;
    int n,n1;
    cout<<"please input n:"<<endl;
    cin>>n;
    char a[n];
    unsigned int w[n];
    for (int i=0; i<n; i++) {
        cout<<"please input the "<<i+1<<" char:"<<endl;
        cin>>a[i];
        cout<<"please input the "<<i+1<<" weight:"<<endl;
        cin>>w[i];
    }
    HuffmanBuilding(HT, w, a, n);
    HuffmanToFile(HT, n);
    cout<<"coding from save..."<<endl;
    HuffmanCoding(HT, HC, n);
    cout<<"coding from file..."<<endl;
    HuffmanFromFile(HT1,n1);
    HuffmanCoding(HT1, HC1, n1);
    HuffmanDecoding(HT1, n1);
    return 0;
}
