//
//  main.cpp
//  tourguide_exam
//
//  Created by tamchikit on 2018/12/18.
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
#define MAX_VERTEX_NUM 20

typedef int Status;
typedef int ElemType;
typedef char InfoType;
typedef int VRType;
typedef Status PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef VRType ShortPathTable[MAX_VERTEX_NUM];
typedef struct VertexType{
    string name;
    string information;
}VertexType;
typedef struct ArcCell{
    VRType adj;
    VRType cost;
    InfoType *info;
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct {
    VertexType vexs[MAX_VERTEX_NUM];
    AdjMatrix arcs;
    int vexnum,arcnum;
}MGraph;

Status CreatGraph(MGraph &G);
int LocateVex(MGraph G, string v);
Status Input(InfoType info);
void ShortestPath_DIJ(MGraph G, int v0, PathMatrix &P, ShortPathTable &D);
void CostleastPath_DIJ(MGraph G, int c0, PathMatrix &CP, ShortPathTable &CD);

Status CreatGraph(MGraph &G){
    int IncInfo;
    VertexType v1,v2;
    VRType w;
    VRType cc;
    cout<<"请输入城市数:\n";
    cin>>G.vexnum;
    cout<<"请输入道路数:\n";
    cin>>G.arcnum;
    cout<<"请输入各道路是否含有其他信息，1为有，0为无:\n";
    cin>>IncInfo;
    for (int i=0; i<G.vexnum; i++) {
        cout<<"请输入城市名:\n";
        cin>>G.vexs[i].name;
        cout<<"请输入城市信息：\n";
        cin>>G.vexs[i].information;
    }
    for (int i=0; i<G.vexnum; i++) {
        for (int j=0; j<G.vexnum; j++) {
            G.arcs[i][j] = {INFINITY,NULL};
        }
    }
    for (int k=0; k<G.arcnum; k++) {
        cout<<"请输入道路起点:\n";
        cin>>v1.name;
        cout<<"请输入道路终点:\n";
        cin>>v2.name;
        cout<<"请输入道路长度:\n";
        cin>>w;
        cout<<"请输入道路花费:\n";
        cin>>cc;
        int i = LocateVex(G,v1.name);
        int j = LocateVex(G,v2.name);
        G.arcs[i][j].adj = w;
        G.arcs[i][j].cost = cc;
        if (IncInfo) {
            Input(*G.arcs[i][j].info);
        }
    }
    cout<<"地图创建成功"<<endl;
    cout<<"城市 ：";
    for (int i=0; i<G.vexnum; i++) {
        cout<<i<<"、"<<G.vexs[i].name<<" ";
    }
    cout<<endl;
    return OK;
}

int LocateVex(MGraph G, string v){
    for (int i=0; i<G.vexnum; i++) {
        if (G.vexs[i].name==v) {
            return i;
        }
    }
    return ERROR;
}

Status Input(InfoType info){
    cout<<"请输入道路的其他信息:\n";
    cin>>info;
    return OK;
}

void ShortestPath_DIJ(MGraph G, int v0, PathMatrix &P, ShortPathTable &D){
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

void CostleastPath_DIJ(MGraph G, int c0, PathMatrix &CP, ShortPathTable &CD){
    int c;
    Status final[MAX_VERTEX_NUM];
    for (c=0; c<G.vexnum; c++) {
        final[c]=FALSE;
        CD[c] = G.arcs[c0][c].cost;
        for (int w=0; w<G.vexnum; w++) {
            CP[c][w]=FALSE;
        }
        if (CD[c]<INFINITY) {
            CP[c][c0]=TRUE;
            CP[c][c]=TRUE;
        }
    }
    CD[c0]=0;
    final[c0]=TRUE;
    for (int i=1; i<G.vexnum; i++) {
        int min = INFINITY;
        for (int w=0; w<G.vexnum; w++) {
            if (!final[w]) {
                if (CD[w]<min) {
                    c=w;
                    min=CD[w];
                }
            }
        }
        final[c]=TRUE;
        for (int w=0; w<G.vexnum; w++) {
            if (!final[w]&&(min+G.arcs[c][w].cost<CD[w])) {
                CD[w]=min+G.arcs[c][w].cost;
                for (int i=0; i<MAX_VERTEX_NUM; i++) {
                    CP[w][i]=CP[c][i];
                }
                CP[w][w] = TRUE;
            }
        }
    }
}



int main(int argc, const char * argv[]) {
    cout<<"*****欢迎来到谭智杰导游系统*****"<<endl<<"先让我了解一下你的城市吧！"<<endl;
    MGraph G;
    CreatGraph(G);
    PathMatrix P;
    PathMatrix CP;
    ShortPathTable D;
    ShortPathTable CD;
    int key=0;
    int choice1=0;
    int choice2=0;
    int choice3=0;
    int choice4=0;
    int choice5=0;
    while (key!=-1) {
        cout<<"*****操作：1、查看景点信息     2、查看最短路径   3、查看最少花费路径*****"<<endl;
        cout<<"*****请选择操作(-1则结束):\n";
        cin>>key;
        if (key==1) {
            while (choice1!=-1) {
                cout<<"*****请输入想查询的城市（-1则结束）：\n";
                cin>>choice1;
                cout<<"*****城市名称："<<G.vexs[choice1].name<<"\n*****城市介绍："<<G.vexs[choice1].information<<endl;
            }
        }
        if (key==2) {
            while (choice2!=-1) {
                cout<<"*****请输入起点(-1则结束)：\n";
                cin>>choice2;
                cout<<"*****请输入终点(-1则结束)：\n";
                cin>>choice3;
                if (choice3!=choice2&&choice2<G.vexnum&&choice3<G.vexnum&&choice2>=0&&choice3>=0) {
                    cout<<"******"<<G.vexs[choice2].name<<"到"<<G.vexs[choice3].name<<"的最短路线为：";
                    ShortestPath_DIJ(G, choice2, P, D);
                    for (int i=0; i<G.vexnum; i++) {
                        if (P[choice3][i]) {
                            cout<<G.vexs[i].name;
                            cout<<"->";
                        }
                    }
                    cout<<" 最短路程为："<<D[choice3]<<endl;
                }
                else if(choice2!=-1){
                    cout<<"请输入正确城市!"<<endl;
                    choice2=0;
                    choice3=0;
                }
            }
        }
        if (key==3) {
            while (choice4!=-1) {
                cout<<"*****请输入起点(-1则结束)：\n";
                cin>>choice4;
                cout<<"*****请输入终点(-1则结束)：\n";
                cin>>choice5;
                if (choice5!=choice4&&choice4<G.vexnum&&choice5<G.vexnum&&choice4>=0&&choice5>=0) {
                    cout<<"******"<<G.vexs[choice4].name<<"到"<<G.vexs[choice5].name<<"的最少花费路线为：";
                    CostleastPath_DIJ(G, choice4, CP, CD);
                    for (int i=0; i<G.vexnum; i++) {
                        if (CP[choice5][i]) {
                            cout<<G.vexs[i].name;
                            cout<<"->";
                        }
                    }
                    cout<<" 最短少花费为："<<CD[choice5]<<endl;
                }
                else if(choice4!=-1){
                    cout<<"请输入正确城市!"<<endl;
                    choice4=0;
                    choice5=0;
                }
            }
        }
        if(key!=-1&&key!=1&&key!=2&&key!=3){
            cout<<"请输入正确的操作！"<<endl;
            key=0;
            break;
        }
    }
    cout<<"谭智杰  2017051752"<<endl;
    return 0;
}

