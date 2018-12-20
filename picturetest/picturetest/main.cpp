//
//  main.cpp
//  picturetest
//
//  Created by tamchikit on 2018/10/30.
//  Copyright © 2018 tamchikit. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define FALSE 0
#define TRUE 1
#define INFINITY 65535
#define MAX_VERTEX_NUM 6

typedef int Status;
typedef int ElemType;
typedef char InfoType;
typedef int VRType;
typedef Status PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef VRType ShortPathTable[MAX_VERTEX_NUM];
typedef char VertexType;
typedef struct ArcCell{
    VRType adj;
    InfoType *info;
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct {
    VertexType vexs[MAX_VERTEX_NUM];
    AdjMatrix arcs;
    int vexnum,arcnum;
}MGraph;

Status CreatGraph(MGraph &G);
int LocateVex(MGraph G, VertexType v);
Status Input(InfoType info);
void ShortestPath_DIJ(MGraph G, VertexType v, PathMatrix &P, ShortPathTable &D);

Status CreatGraph(MGraph &G){
    int IncInfo;
    VertexType v1,v2;
    VRType w;
    cout<<"请输入图的节点数:\n";
    cin>>G.vexnum;
    cout<<"请输入图的弧数:\n";
    cin>>G.arcnum;
    cout<<"请输入各弧是否含有其他信息，1为有，0为无:\n";
    cin>>IncInfo;
    for (int i=0; i<G.vexnum; i++) {
        cout<<"请输入顶点名:\n";
        cin>>G.vexs[i];
    }
    for (int i=0; i<G.vexnum; i++) {
        for (int j=0; j<G.vexnum; j++) {
            G.arcs[i][j] = {INFINITY,NULL};
        }
    }
    for (int k=0; k<G.arcnum; k++) {
        cout<<"请输入弧尾节点:\n";
        cin>>v1;
        cout<<"请输入弧头节点:\n";
        cin>>v2;
        cout<<"请输入弧的权值:\n";
        cin>>w;
        int i = LocateVex(G,v1);
        int j = LocateVex(G,v2);
        G.arcs[i][j].adj = w;
        if (IncInfo) {
            Input(*G.arcs[i][j].info);
        }
    }
    return OK;
}

int LocateVex(MGraph G, VertexType v){
    for (int i=0; i<G.vexnum; i++) {
        if (G.vexs[i]==v) {
            return i;
        }
    }
    return ERROR;
}

Status Input(InfoType info){
    cout<<"请输入弧的其他信息:\n";
    cin>>info;
    return OK;
}

void ShortestPath_DIJ(MGraph G, VertexType v1, PathMatrix &P, ShortPathTable &D){
    int v0=LocateVex(G, v1);
    int v;
    Status final[MAX_VERTEX_NUM];
    for (v=0; v<G.vexnum; v++) {
        final[v]=FALSE;
        D[v] = G.arcs[v0][v].adj;
        for (int w=0; w<G.vexnum; w++) {
            P[v][w]=FALSE;
        }
        if (D[v]<INFINITY) {
            P[v][v0]=TRUE;
            P[v][v]=TRUE;
        }
    }
    D[v0]=0;
    final[v0]=TRUE;
    for (int i=1; i<G.vexnum; i++) {
        int min = INFINITY;
        for (int w=0; w<G.vexnum; w++) {
            if (!final[w]) {
                if (D[w]<min) {
                    v=w;
                    min=D[w];
                }
            }
        }
        final[v]=TRUE;
        for (int w=0; w<G.vexnum; w++) {
            if (!final[w]&&(min+G.arcs[v][w].adj<D[w])) {
                D[w]=min+G.arcs[v][w].adj;
                for (int i=0; i<MAX_VERTEX_NUM; i++) {
                    P[w][i]=P[v][i];
                }
                P[w][w] = TRUE;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    MGraph G;
    CreatGraph(G);
    PathMatrix P;
    ShortPathTable D;
    ShortestPath_DIJ(G, G.vexs[0], P, D);
    for (int i=0; i<G.vexnum; i++) {
        for (int j=0; j<G.vexnum; j++) {
            cout<<P[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
    for (int i=0; i<G.vexnum; i++) {
        cout<<D[i]<<" ";
    }
    return 0;
}
