// PAT甲级1030 Travel Plan，原题地址：https://www.patest.cn/contests/pat-a-practise/1030
// 解题分析：
//  这一题和1018 Public Bike Management类似，是dijkstra算法和DFS的应用，但比其稍微简单一点。程序使用了
//  邻接链表储存整张图，我觉得这样一来不容易爆栈，使用邻接矩阵虽然简单但如果作为局部变量的话，节点数量一大就容易
//  爆栈。解题的大致思路是，先用dijkstra算法计算出从给定的出发点到其他点的最短路径，这个过程不需要考虑cost，接下
//  来深度搜索整张图，利用目的地点的最短路径做剪枝操作，即如果当前的路长大于目的地点的最短路径则不往下搜索，这样一来
//  可以节省一些时间。走过的路长用全局变量length记录，费用用cost记录，最小费用用min_cost记录，当搜索到目的地节点
//  时比较cost和min_cost，如果cost比min_cost小，则更新min_cost，清空stack，并将目的地节点放入stack，返回1，否则
//  直接返回0。对于其他不是目的地节点的节点，如果有与之相连的点返回1，则该节点入栈，表明其在有最短路径和最小费用的路径上，
//  如果与之相连的点全部返回0，则直接返回0.DFS的时候注意在继续往下搜索时，要将当前节点设置为已访问，防止重复搜索造成死循环，
//  当从当前点返回上一个节点时，要将当前节点设置为未访问，这样其他点才能继续访问之。最后按格式输出即可。
#include<stdio.h>
#include<stdlib.h>

#define INFINITY 100000
struct node{
    int index;
    int distance;
    int cost;
    struct node *next;
};//储存相邻点和边的信息
struct city{
    int shortest_distance;
    int visited;
    struct node *ptr;
};//储存各个节点信息

void initialize(struct city G[]);
void connect(struct city G[] , int c1 , int c2 , int distance , int cost);
void dijkstra(struct city G[]);
int DFS(struct city G[] , int start);
void output(struct city G[]);

// 全局变量定义
int n , m , s , d;
int stack[500];
int top = -1;
int min_cost = INFINITY;
int cost = 0;
int length = 0;

int main(){
    struct city G[500];
    int c1 , c2;
    int distance , cost;
    int i;

    // 输入
    scanf("%d%d%d%d" , &n , &m , &s , &d);
    // 初始化
    initialize(G);
    // 连接
    for(i = 0;i < m;i++){
        scanf("%d%d%d%d" , &c1 , &c2 , &distance , &cost);
        connect(G , c1 , c2 , distance , cost);
        connect(G , c2 , c1 , distance , cost);
    }
    // 计算最短路径
    G[s].shortest_distance = 0;
    dijkstra(G);
    // 将所有点设置为未访问，否则会对DFS产生影响
    for(i = 0;i < n;i++)
        G[i].visited = 0;
    // 深度搜索整张图
    DFS(G , s);
    // 输出
    output(G);
}

// 初始化
void initialize(struct city G[]){
    int i;

    for(i = 0;i < n;i++){
        G[i].shortest_distance = INFINITY;
        G[i].visited = 0;
        G[i].ptr = NULL;
    }
}

// 连接两点
void connect(struct city G[] , int c1 , int c2 , int distance , int cost){
    struct node *ptr;

    ptr = (struct node *)malloc(sizeof(struct node));
    ptr->index = c2;
    ptr->distance = distance;
    ptr->cost = cost;
    ptr->next = G[c1].ptr;
    G[c1].ptr = ptr;
}

// 最短路径算法
void dijkstra(struct city G[]){
    int i;
    int min , index;
    int temp;
    struct node *ptr;

    while(1){
        min = INFINITY;
        for(i = 0;i < n;i++){
            if(G[i].visited == 0 && G[i].shortest_distance < min){
                min = G[i].shortest_distance;
                index = i;
            }
        }
        if(min == INFINITY)
            break;
        G[index].visited = 1;
        ptr = G[index].ptr;
        while(ptr != NULL){
            temp = G[index].shortest_distance + ptr->distance;
            if(temp < G[ptr->index].shortest_distance)
                G[ptr->index].shortest_distance = temp;
            ptr = ptr->next;
        }
    }   
}

// 深度搜索
int DFS(struct city G[] , int start){
    int flag = 0;
    struct node *ptr;

    // 如果当前点为目的地节点
    if(start == d){
        // 如果cost小于min_cost
        if(cost < min_cost){
            // 更新min_cost
            min_cost = cost;
            // 清空stack
            top = -1;
            // 将目的地节点放入stack
            stack[++top] = start;
            // 返回1
            return 1;
        }
        // 否则返回0
        else 
            return 0;
    }
    // 如果不是目的地节点，则先将其设置为已访问
    G[start].visited = 1;
    ptr = G[start].ptr;
    // 遍历相连的所有点
    while(ptr != NULL){
        // 更新length和cost
        length += ptr->distance;
        cost += ptr->cost;
        // 如果相连点没有访问过并且路长小于等于目的地节点的最短路径
        if(G[ptr->index].visited == 0 && length <= G[d].shortest_distance){
            // 继续往下搜索，如果返回结果是1
            if(DFS(G , ptr->index))
                // flag设置为1
                flag = 1;
        }
        // 还原length和cost
        length -= ptr->distance;
        cost -= ptr->cost;
        // 继续处理其他相连的点
        ptr = ptr->next;
    }
    // 向上一点返回时设置为未访问
    G[start].visited = 0;
    // 如果flag为1
    if(flag){
        // 将当前点放入stack
        stack[++top] = start;
        // 返回1
        return 1;
    }
    // 否则直接返回0
    else
        return 0;
}

void output(struct city G[]){
    int i;

    for(i = top;i >= 0;i--)
        printf("%d " , stack[i]);
    printf("%d %d" , G[d].shortest_distance , min_cost);
}
