//
// Created by Benjamin142857 on 4/2/2019.
//

#ifndef GRAPE_GRAPEMARTIX_H
#define GRAPE_GRAPEMARTIX_H

#include "malloc.h"

/** Def ----------------------------------------------------**/
// 宏
#define MAXNUM 20				/*** 图的最大顶点数  ***/
#define MAXVALUE 65535		/*** 最大值  ***/

// 结构体定义
struct GraphMartix{
    char data[MAXNUM];                             // 保存顶点信息（序号或字母）
    int graph_type;		                           // 图的类型（0：无向图；1：有向图）
    int node_num;		                           // 顶点的数量
    int edge_num;		                           // 边的数量
    int edge_value[MAXNUM][MAXNUM];                // 用二维数组保存点到点的边的权值
    int flag_traverse[MAXNUM];                     // 遍历标记

};
// 类型定义 - GraphMartix指针
typedef struct GraphMartix *PGraphMartix;

/** Fun ----------------------------------------------------**/

// 创建图(邻接矩阵表示)
PGraphMartix GraphMartix_create(int graph_type, int node_num) {
    // 1. 定义指针，分配内存
    PGraphMartix gp = (PGraphMartix)malloc(sizeof(struct GraphMartix));

    // 2.判断是否分配成功
    if(gp != NULL) {
        gp->graph_type = graph_type;
        gp->node_num = node_num;
        gp->edge_num = 0;
        int weight;     //临时权-中转

        // 2.1 输入定点信息，保存到图data
        printf("[1] 输入图中各顶点信息：\n");
        for(int i=0; i<gp->node_num; i++ ) {
            printf("第%d个顶点：", i+1);
            printf("\n");
            getchar();
            scanf("%c", &(gp->data[i]));
        }

        // 2.2 输入边权信息，保存到图edge_value
        printf("[2] 输入构成各边的顶点及权值：\n");
        for(int i=0 ; i < gp->node_num; i++) {
            for(int j=0; j < gp->node_num; j++) {
                printf("(%d, %d): ", i, j);
                printf("\n");
                scanf("%d", &weight);
                if(weight == -1) {
                    gp->edge_value[i][j] = MAXVALUE;
                }
                else if(weight == 0) {
                    gp->edge_value[i][j] = weight;
                }
                else {
                    gp->edge_value[i][j] = weight;
                    gp->edge_num += 1;
                }
            }
        }

        // 2.3 计算边数
        gp->edge_num = gp->edge_num / 2;

        return gp;
    }
    else {
        free(gp);
        printf("GrapeMartix create fail !!!\n");
        return NULL;
    }
}

// 清空矩阵
void GraphMartix_clear(PGraphMartix gp) {
    for(int i=0 ; i<gp->node_num ; i++) {
        for(int j=0 ; j<gp->node_num ; j++) {
            gp->edge_value[i][j] = MAXVALUE; 	/*** 设置矩阵中各元素的值为MAXVALUE  ***/
        }
    }
}


//  以二维坐标的形式打印矩阵
void GrapeMartix_print(PGraphMartix gp) {
    for(int j=0 ; j<gp->node_num ; j++) {
        printf("%c",gp->data[j]); 	/*** 在第一行输出顶点信息  ***/
    }

    printf("\n");

    for(int i=0 ; i<gp->node_num ; i++) {
        printf("%c",gp->data[i]);

        for(int j=0 ; j<gp->node_num ;j++) {
            if(gp->edge_value[i][j] == MAXVALUE) {
                printf("Z ");
            }
            else {
                printf("%d ",gp->edge_value[i][j]);
            }
        }
        printf("\n");
    }
}


#endif //GRAPE_GRAPEMARTIX_H
