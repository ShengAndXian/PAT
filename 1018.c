// PAT甲级1018 Public Bike Management，原题地址：https://www.patest.cn/contests/pat-a-practise/1018
// 解题分析：
//  Dijkstra算法和DFS的综合应用。程序中使用二维数组存储每一条道路，用一个一维数组储存每一个节点的信息（车的数量和最短路径）。
//  首先从PBMC节点开始计算每一个点的最短路径，再用DFS遍历整张图。遍历过程中，用length纪录走过的路长，如果超过了目的地节点的最短路径
//  则不继续往下搜索，否则继续往下搜索。往下搜索时要将当前点的visited设置为1，防止重复搜索造成死循环，从当前点返回时要将其设置为0，以便从其他点继续访问。
//  current_send用来纪录当前需要从PBMC发出的车的数量，current_take用来纪录当前需要带回的车的数量，send表示最小的从PBMC发出的车的数量，
//  take是与send相对应的需要带回的车的数量（不一定最小）。遍历过程中保持更新current_send和current_take，当访问到目的地节点时比较current_send和send，
//  以及current_take和take。如果current_send小于send或者current-send等于send但current_take小于take，则更新更新send和take
//  同时清空stack，并把目的地节点放入stack，返回1.否则返回0.如果有一个后续节点返回为1，则将当前节点放入栈中，接着返回1.否则，返回0。
//  最后输出send和take，以及栈中的序号。
#include<stdio.h>
#include<stdlib.h>

#define INFINITY 10000
struct info{
    int num;
    int distance;
    int visited;
};//结构体储存节点的信息

void dijkstra(struct info *all_info , int graph[][501]);
int DFS(struct info *all_info , int index , int graph[][501]);
void output();

//全局变量定义，虽然定义了很多全局变量，但这样会方便很多
int capacity , n , end , m;
int send = INFINITY , take = INFINITY , current_send , current_take;
int length;
int stack[501];
int top = -1;

int main(){
    int graph[501][501];
    struct info all_info[501];
    int i , j;
    int s1 , s2 , t;
    
    scanf("%d %d %d %d" , &capacity , &n , &end , &m);
    // 初始化道路
    for(i = 0;i < 501;i++)
        for(j = 0;j < 501;j++)
            graph[i][j] = -1;
    // 初始化节点
    for(i = 1;i <= n;i++){
        scanf("%d" , &all_info[i].num);
        all_info[i].distance = INFINITY;
        all_info[i].visited = 0;
    }
    // 输入道路信息
    for(i = 0;i < m;i++){
        scanf("%d %d %d" , &s1 , &s2 , &t);
        graph[s1][s2] = t;
        graph[s2][s1] = t;
    }
    // 将0点设置为PBMC节点
    all_info[0].distance = 0;
    all_info[0].visited = 0;
    // 计算最短路径
    dijkstra(all_info , graph);
    // 将所有节点设置为未访问
    for(i = 0;i <= n;i++)
        all_info[i].visited = 0;
    // 深度搜索
    DFS(all_info , 0 , graph);
    // 输出
    output();
}

// 最短路径算法，都是套路就不注释了。。。。
void dijkstra(struct info *all_info , int graph[][501]){
    int i;
    int min;
    int tmp;

    while(1){
        min = INFINITY;
        for(i = 0;i <= n;i++){
            if(all_info[i].visited == 0 && all_info[i].distance < min){
                min = all_info[i].distance;
                tmp = i;
            }
        }
        if(min == INFINITY)
            break;
        all_info[tmp].visited = 1;
        for(i = 0;i <= n;i++){
            if(graph[tmp][i] > 0 && all_info[i].visited == 0){
                if(min + graph[tmp][i] < all_info[i].distance)
                    all_info[i].distance = min + graph[tmp][i];
            }
        }
    }
}

// 深度搜索
int DFS(struct info *all_info , int index , int graph[][501]){
    int i;
    int flag = 0;
    int tmp1 , tmp2;

    // 如果当前节点是目的地节点
    if(index == end){
        if(current_send < send || (current_send == send && current_take < take)){
            // 更新send和take  
            send = current_send;
            take = current_take;
            // 清空stack，并将节点放入栈中
            top = -1;
            stack[++top] = end;
            // 返回1
            return 1;
        }
        // 不需要更新send和take则返回0
        return 0;
    }
    // 将当前节点设置为已访问
    all_info[index].visited = 1;
    for(i = 0;i <= n;i++){
        // 如果与当前节点相连的节点未被访问，并且路长小于目的地的最短路径
        if(graph[index][i] > 0 && all_info[i].visited == 0 && length + graph[index][i] <= all_info[end].distance){
            // 保存当前的current_send以及current_take
            tmp1 = current_send;
            tmp2 = current_take;
            // 更新length
            length += graph[index][i];
            // 如果后续节点的车的数量小于一半capacity
            if(all_info[i].num < capacity / 2){
                // 如果当前所要带回的车的数量加上已有的车的数量大于等于一半capacity
                if(current_take + all_info[i].num >= capacity / 2){
                    // 更新当前所要带回车的数量
                    current_take -= capacity / 2 - all_info[i].num;
                }
                // 否则
                else{
                    // 更新当前需要从PBMC发出的车的数量
                    current_send += capacity / 2 - all_info[i].num - current_take;
                    // 当前带回的车的数量为0
                    current_take = 0;
                }
            }
            // 否则
            else{
                // 更新当前所要带回的车的数量
                current_take += all_info[i].num - capacity / 2;
            }
            // 往下搜索，如果返回为1
            if(DFS(all_info , i , graph)){
                // 将当前点放入栈
                stack[++top] = index;
                // flag设置为1
                flag = 1;
            }
            // 重置length和current_send和current_take，以便访问后续的节点
            length -= graph[index][i];
            current_send = tmp1;
            current_take = tmp2;
        }
    }
    // 返回前将当前节点设置为未被访问
    all_info[index].visited = 0;
    // 如果flag等于1
    if(flag == 1)
        // 返回1
        return 1;
    else
        // 否则返回0
        return 0;
}

void output(){
    int i;

    printf("%d 0" , send);
    for(i = top - 1;i >= 0;i--){
        printf("->%d" , stack[i]);
    }
    printf(" %d" , take);
}