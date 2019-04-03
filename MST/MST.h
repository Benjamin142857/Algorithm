//
// Created by apls on 4/3/2019.
//

#ifndef MST_MST_H
#define MST_MST_H

#include "GrapeMartix.h"

/** Def ----------------------------------------------------**/
// 结构体定义-边
typedef struct {
    int start_node, stop_node;          // 边起点与终点
    int weight;                         // 边权值
} Edge;

/** Fun ----------------------------------------------------**/
// Prim-普里姆算法 TODO 待补判断图的有向无向
void prim(PGraphMartix pgm, Edge res[]) {
    // res[]    边数组，最小生成树结果，元素数=node_num-1
    int min_idx=0;                // 临时存放档次遍历最小路径的边数组索引   idx{res[idx]}
    int min_weight;             // 临时存放当次遍历最小边权值            min{res[idx].weight}
    Edge temp_edge;             // 临时中转边，用于res[]数组中元素位置的交换

    // 1. 初始化res[]  (默认从V_0开始生成树)
    for (int i=0; i < pgm->node_num-1; i++) {
        res[i].start_node = 0;
        res[i].stop_node = i+1;
        res[i].weight = pgm->edge_value[0][i+1];
    }

    // 2. 从V_0开始，循环遍历所有点    (从V_0开始，默认V_0已遍历，只需再遍历node-1个点)
    for (int finish_node=0; finish_node < pgm->node_num-1; finish_node++) {
        min_weight = MAXVALUE;      // 先将当次最小边权值临时设为∞，即MAX

        // 2.1 从剩下的边数组res[]中找最小边
        for (int res_idx=finish_node; res_idx < pgm->node_num-1; res_idx++) {
            if (res[res_idx].weight < min_weight) {
                min_weight = res[res_idx].weight;
                min_idx = res_idx;
            }
        }

        // 2.2 将当次遍历所找的最小边res[min_idx]与res[finish_node]位置交换（可理解为移到前面），作为已遍历过该点的标记
        temp_edge = res[min_idx];
        res[min_idx] = res[finish_node];
        res[finish_node] = temp_edge;


        // 2.3 遍历了新点，相当于获取新视野，考虑该点可到达的路径，若比原来res[]中未遍历的路径短，则更新res[]
        for (int stop_node_idx=finish_node+1; stop_node_idx < pgm->node_num-1; stop_node_idx++) {
            int v_start = res[finish_node].stop_node;
            int v_stop = res[stop_node_idx].stop_node;
            if (pgm->edge_value[v_start][v_stop] < res[stop_node_idx].weight) {
                res[stop_node_idx].start_node = v_start;
                res[stop_node_idx].weight = pgm->edge_value[v_start][v_stop];
            };
        }
    }

    // 3 打印结果
    for (int res_idx=0; res_idx < pgm->node_num-1; res_idx++) {
        printf("\n最小生成树为:\n");
        printf("(%d, %d, %d)", res[res_idx].start_node, res[res_idx].stop_node, res[res_idx].weight);
    }
}


#endif //MST_MST_H
