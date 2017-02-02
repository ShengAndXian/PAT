
// PAT甲级1013 Battle Over City，原题地址：https://www.patest.cn/contests/pat-a-practise/1013
// 解题分析：
//  无向连通图和并查集的应用。初始状态是连通图，当一个城市被占领后，与之相连的道路都不通，然后求需要修多少条路才能
//  使得剩下的城市保持连通。我们先储存所有的边，纪录每条边所连接的两个城市。当一个城市被占领后，任何一条连接该城市与
//  其他城市的边都被标记为已被占领。然后遍历剩下的边，将每一条边所连接的城市加入并查集，之后遍历并查集，计算出并查集
//  中集合的数量，所需要修复道路的数量就等于集合的数量减一。
#include<stdio.h>
#include<stdlib.h>

struct edge{
    int start;
    int end;
};//一条边

// 在并查集中查找祖先，并且压缩路径
int find(int *union_find , int n){
    if(union_find[n] != -1)
        return union_find[n] = find(union_find , union_find[n]);
    return n;
}

// 合并两个集合
void merge(int *union_find , int a , int b){
    union_find[a] = b;
}
// 计算需要修复路的数量
int repaired_ways(int N , struct edge *E , int M , int occupied_vertex){
    int *union_find;
    int i;
    int *occupied;
    int ancestor_1 , ancestor_2;
    int count = 0;

    // 建立并查集合
    union_find = (int *)malloc(sizeof(int) * N);
    occupied = (int *)malloc(sizeof(int) * M);
    // 初始化
    for(i = 0;i < N;i++)
        union_find[i] = -1;
    for(i = 0;i < M;i++)
        occupied[i] = 0;
    
    // 与被占领城市相连的边标记为已占领
    for(i = 0;i < M;i++){
        if(E[i].start == occupied_vertex || E[i].end == occupied_vertex)
            occupied[i] = 1;
    }

    // 遍历剩下的边
    for(i = 0;i < M;i++){
        if(occupied[i] == 1)
            continue;
        
        // 在并查集中查找边所连接的两个城市的祖先
        ancestor_1 = find(union_find , E[i].start);
        ancestor_2 = find(union_find , E[i].end);
        // 如果不在同一集合，则合并两个集合
        if(ancestor_1 != ancestor_2)
            merge(union_find , ancestor_1 , ancestor_2);
    }

    // 遍历并查集，计算集合的数量
    for(i = 1;i < N;i++){
        if(union_find[i] == -1)
            count++;
    }

    // 所需要修复的路的数量等于集合数量减一
    return count - 1;
}


int main(){
    int N , M , K;
    int i;
    struct edge*E;
    int start , end;
    int query;
    int num;

    scanf("%d %d %d" , &N , &M , &K);
    // 构建边集
    E = (struct edge*)malloc(sizeof(struct edge) * M);
    // 输入
    for(i = 0;i < M;i++){
        scanf("%d %d" , &start , &end);
        E[i].start = start;
        E[i].end = end;
    }
    // 查询
    for(i = 0;i < K;i++){
        scanf("%d" , &query);
        num = repaired_ways(N , E , M , query);
        printf("%d\n" , num);
    }
}