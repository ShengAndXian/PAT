// PAT甲级1021 Deepest Root，原题地址：https://www.patest.cn/contests/pat-a-practise/1021
// 解题分析：
//  无向图的联通分量的求解以及BFS的应用。由于内存的限制，只能使用邻接链表储存各条边，同时使用一个一维数组E储存
//  所有边。利用边集E和并查集就可以计算出联通分量的个数。然后再以任一个节点为根节点，宽度搜索遍历整张图，计算高度。
//  所有节点都依次作为根节点，有最大高度的节点储存在stack里，最后输出即可。
#include<stdio.h>
#include<stdlib.h>

#define Max 10001
#define INFINITY 100000
struct node{
    int index;
    struct node *next;
};//邻接链表的节点
struct edge{
    int start;
    int end;
};//边集中的一条边

void connect(struct node *G[] , int s1 , int s2);
int find_components(struct edge E[] , int n);
int find(int *union_find , int n);
int get_height(struct node *G[] , int v , int n);

int main(){
    struct node *G[Max];
    struct edge E[Max];
    int stack[Max];
    int top = -1;
    int max = -INFINITY;
    int n;
    int k;
    int s1 , s2;
    int i , j;
    int height;

    scanf("%d" , &n);
    // 初始化
    for(i = 1;i <= n;i++)
        G[i] = NULL;
    for(i = 0;i < n - 1;i++){
        scanf("%d %d" , &s1 , &s2);
        // 连接两个点
        connect(G , s1 , s2);
        connect(G , s2 , s1);
        // 将边存入边集
        E[i].start = s1;
        E[i].end = s2;
    }

    // 计算联通分量个数
    k = find_components(E , n);
    // 如果不为1，则输出error
    if(k != 1){
        printf("Error: %d components" , k);
        return 0;
    }
    // 遍历所有节点，每次都以一个节点作为根节点
    for(i = 1;i <= n;i++){
        // 计算高度
        height = get_height(G , i , n);
        // 如果高度比之前的高度大
        if(height > max){
            // 更新最大高度
            max = height;
            // 清空stack，并将当前点放入
            top = -1;
            stack[++top] = i;
        }
        // 如果高度与最大高度相等，则直接放入stack
        else if(height == max){
            stack[++top] = i;
        }
    }
    // 输出
    for(i = 0;i <= top;i++)
        printf("%d\n" , stack[i]);
}

// 连接两点
void connect(struct node *G[] , int s1 , int s2){
    struct node *ptr;

    ptr = (struct node*)malloc(sizeof(struct node));
    ptr->index = s2;
    ptr->next = G[s1];
    G[s1] = ptr;
}

// 计算联通分量个数
int find_components(struct edge E[] , int n){
    int *union_find;
    int i;
    int k = 0;
    int ancestor1 , ancestor2;

    // 建立并查集
    union_find = (int *)malloc(sizeof(int) * (n + 1));
    // 初始化并查集
    for(i = 1;i <= n;i++)
        union_find[i] = -1;
    // 遍历边集
    for(i = 0;i < n - 1;i++){
        // 查找两个端点的祖先
        ancestor1 = find(union_find , E[i].start);
        ancestor2 = find(union_find , E[i].end);
        // 如果两个端点的祖先不相等
        if(ancestor1 != ancestor2)
            // 合并
            union_find[ancestor1] = ancestor2;
    }
    // 计算联通分量个数
    for(i = 1;i <= n;i++)
        if(union_find[i] == -1)
            k++;
    return k;
}

// 在并查集中查找祖先，并且压缩路径
int find(int *union_find , int n){
    if(union_find[n] != -1)
        return union_find[n] = find(union_find , union_find[n]);
    return n;
}

// 计算高度
int get_height(struct node *G[] , int v , int n){
    int queue[Max];
    int front = 0 , rear = -1;
    int k;
    int i;
    int count;
    int visited[Max];
    int height = 0;
    struct node *ptr;

    for(i = 1;i <= n;i++)
        visited[i] = 0;
    
    // 将根节点放入队列
    queue[++rear] = v;
    while(1){
        // 计算每一层的节点个数
        count = rear - front + 1;
        // 如果节点个数不是正数，则遍历结束
        if(count <= 0)
            break;
        // 高度加一
        height++;
        // 遍历当前层的所有节点
        while(count-- > 0){
            // 出队
            k = queue[front++];
            // 设置为已访问
            visited[k] = 1;
            // 访问相邻的节点
            ptr = G[k];
            while(ptr != NULL){
                // 如果相邻的节点未被访问
                if(visited[ptr->index] == 0)
                    // 入队
                    queue[++rear] = ptr->index;
                ptr = ptr->next;
            }
        }
    }
    // 返回
    return height;
}