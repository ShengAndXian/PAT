// PAT甲级1003 Emergency，原题地址：https://www.patest.cn/contests/pat-a-practise/1003
// 解题分析：
//  题目本质上是Dijkstra算法的应用，多了计算最短路径的数量和最大的人数。首先按题目要求需要构建一张图，这里我用了
//  邻接表，虽然比较麻烦，但也是习惯了。构建好图之后使用dijkstra算法从所给的出发点出发计算每一个节点的最短路径，
//  对于一个不在已知最短路径的点的集合中的节点，如果被集合内的点访问时，其distance大于集合内的点的distance加上
//  两点之间的路长，则更新distance，同时更新最短路径的数量。这里有一个坑，本来我写的时候直接将其更新为1，后来发现
//  应该更新为集合内的点的最短路径数量。相应的更新最大的人数为集合内的点的人数加上当前点的人数。如果当前点的distance
//  等于集合内的点distance加上两点之间的路长，则当前点的最短路径数量需要加上集合内的点的最短路径数量，同时如果集合内
//  的点的最大人数加上当前点的人数大于当前点的最大人数，则更新当前点的最大人数。最终输出要求的目的地节点的最短路径数量
//  和最大人数即可。
#include<stdio.h>
#include<stdlib.h>

#define Max 500
#define INFINITY 100000
struct node{
    int index;
    int length;
    struct node *next;
};//相邻的节点
struct vertex{
    int visited;
    int distance;
    int numOfPeople;
    int numOfShortestPath;
    int maxNumOfPeople;
    struct node *ptrToNode;
};//用结构体储存每一个节点的相关信息
struct graph{
    int N;
    int start;
    int end;
    struct vertex arr[Max];
};//整张图

struct graph *initialize();
void constructNode(struct graph *G , int start , int end , int length);
void findShortestPath(struct graph *G);
void output(struct graph *G);

int main(){
    struct graph *G;

    G = initialize();//初始化
    findShortestPath(G);//计算每一个节点的最短路径
    output(G);//输出
}

struct graph *initialize(){
    struct graph *G;
    int N , M , C1 , C2;
    int people;
    int start , end , length;
    int i;
    struct node *ptrToNode;

    //给图分配内存
    G = (struct graph *)malloc(sizeof(struct graph));


    scanf("%d %d %d %d" , &N , &M , &C1 , &C2);
    G->N = N;
    G->start = C1;
    G->end = C2;
    //初始化
    for(i = 0;i < N;i++){
        G->arr[i].visited = 0;
        G->arr[i].distance = INFINITY;
        G->arr[i].maxNumOfPeople = -INFINITY;
        G->arr[i].ptrToNode = NULL;
    }

    //输入人数
    for(i = 0;i < N;i++){
        scanf("%d" , &people);
        G->arr[i].numOfPeople = people;
    }

    //出发点初始化
    G->arr[C1].distance = 0;
    G->arr[C1].maxNumOfPeople = G->arr[C1].numOfPeople;
    G->arr[C1].numOfShortestPath = 1;

    //连接各个节点
    for(i = 0;i < M;i++){
        scanf("%d %d %d" , &start , &end , &length);
        constructNode(G , start , end , length);
        constructNode(G , end , start , length);
    }

    return G;
}

void constructNode(struct graph *G , int start , int end , int length){
    struct node *ptrToNode;

    //给节点分配内存
    ptrToNode = (struct node *)malloc(sizeof(struct node));
    //给节点增加信息，并插入到链表中
    ptrToNode->index = end;
    ptrToNode->length = length;
    ptrToNode->next = G->arr[start].ptrToNode;
    G->arr[start].ptrToNode = ptrToNode;
}

//最短路径算法
void findShortestPath(struct graph *G){
    int i;
    int current;
    int min;
    struct node *ptrToNode;
    int newDistance;
    int newNumOfPeople;

    while(1){
        min = INFINITY;
        //查找不在集合内的点并且路径最短的点
        for(i = 0;i < G->N;i++){
            if(G->arr[i].visited == 0 && G->arr[i].distance < min){
                min = G->arr[i].distance;
                current = i;
            }
        }

        // 全部点都在集合内，跳出循环
        if(min == INFINITY)
            break;

        // 将节点纳入集合
        G->arr[current].visited = 1;
        ptrToNode = G->arr[current].ptrToNode;
        // 依次访问相邻的点
        while(ptrToNode != NULL){
            // 节点不在集合内
            if(G->arr[ptrToNode->index].visited == 0){
                newDistance = G->arr[current].distance + ptrToNode->length; 
                // 如果当前节点的最短路径大于集合内的点的最短路径加两点的路长
                if(newDistance < G->arr[ptrToNode->index].distance){
                    // 更新最短路径
                    G->arr[ptrToNode->index].distance = newDistance;
                    // 更新最短路径数量
                    G->arr[ptrToNode->index].numOfShortestPath = G->arr[current].numOfShortestPath;
                    // 更新最大人数
                    G->arr[ptrToNode->index].maxNumOfPeople = G->arr[ptrToNode->index].numOfPeople + G->arr[current].maxNumOfPeople;
                }
                // 如果相等
                else if(newDistance == G->arr[ptrToNode->index].distance){
                    // 更新最短路径数量
                    G->arr[ptrToNode->index].numOfShortestPath += G->arr[current].numOfShortestPath;
                    newNumOfPeople = G->arr[ptrToNode->index].numOfPeople + G->arr[current].maxNumOfPeople;
                    // 如果当前的最大人数小于集合内点的最大人数加当前点的人数
                    if(newNumOfPeople > G->arr[ptrToNode->index].maxNumOfPeople)
                        G->arr[ptrToNode->index].maxNumOfPeople = newNumOfPeople;
                }
            }

            ptrToNode = ptrToNode->next;
        }
    }
}

void output(struct graph *G){
    printf("%d %d" , G->arr[G->end].numOfShortestPath , G->arr[G->end].maxNumOfPeople);
}
