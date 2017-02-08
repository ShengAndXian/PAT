// PAT甲级1034 Head of a Gang，原题地址：https://www.patest.cn/contests/pat-a-practise/1034
// 解题分析：
//  图的遍历和DFS。代码有点乱，我试着讲清楚。。。看到运行时间限制为100ms的时候，我就费劲心思想怎么使运行时间
//  最短，然后就想到在构建整张图的时候不同的方法的效率各不相同，这个时间相差是很大的。当输入一条信息之后，我们
//  可以根据第一个字符串在已有的点中遍历搜索，如果找到一个点的字符串和这个字符串相等，那就直接插入第二个字符串，
//  否则先创建记录用来保存第一个字符串，然后插入第二个字符串。由于图是无向图，因此需要对第二个字符串重复同样的
//  步骤。如果每一条信息的两端点都不在之后的信息中出现，那么这种方法构建图的时间复杂度为O（n^2），在题目中存在
//  这种情况的测试点，因此这种方法不能说很好。我们考虑其他方法，可以这样设想，通过字符串，我们可以直接得到其在
//  邻接表中的索引，这样一来效率就会得到很大的提高。实现的方法是，构建一个哈希表，对字符串进行hash，得到其在哈希表
//  中的索引，这里我们采用拉链法解决冲突，因此，在索引对应的链表中查找字符串，如果找到则返回字符串在邻接表中的索引，
//  否则返回－1。这样一来，虽然我也不太清楚时间是否是常数时间，但至少已经优化了很多。根据返回的索引，如果是正数，
//  则插入另一个字符串，如果是－1，则新建一个记录后，插入另一个字符串。对于另一个字符春，执行相同的操作。插入的操作
//  在程序有详细的解释。
//  图构建好之后，接下来就是用DFS遍历整张图了，由于图可能并不是联通图，所以在程序中要保证所有节点都被访问过。全局变量
//  total和num分别用来纪录总权重和总节点数量，max和head分别用来纪录最大权重和有最大权重的节点在邻接表中的索引。每次
//  遍历一个联通分量时都要对这些全局变量初始化。当访问到一个节点时，将该节点设为已访问，下次就不需要访问这个点，num加一
//  ，并和head点的权重比较，如果比它大，则更新max和head，当向下一个节点搜索时，如果从访问到边权重为0的点，则直接跳过，
//  否则更新total，将连接的边的权重设置为0，这样可以防止一条边的权重被重复加到total里，接着，如果下一个节点没有被访问过，
//  则往下继续搜索，否则，考察其他相邻的点。每访问一个联通分量，将对应的head的字符串和节点数量存入数组gang，最后排序输出
//  即可。
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define Max 2001

struct node{
    char s[4];
    int weight;
    struct node *next;
};//邻接表中的链表对应的节点
struct vertex{
    char s[4];
    int total_weight;
    struct node *ptr;   
};//邻接表中的元素
struct hash_node{
    char s[4];
    int index;
    struct hash_node *next;
};//哈希表中的链表对应的节点
struct gang_node{
    int num;
    char s[4];
};//储存结果

int get_hash(char s[]);
int get_index(struct hash_node *H[] , char s[]);
void insert(struct vertex G[] , struct hash_node *H[] , int index , char s1[] , char s2[] , int weight);
void DFS(struct vertex G[] , struct hash_node *H[] , int start);
int compare(const void *a , const void *b);

// 全局变量定义
int count = 0;//所有节点数量
int visited[Max];//纪录各个节点的访问的情况
int num;//纪录联通分量中的节点个数
int total;//纪录联通分量中的总权重
int max;//纪录联通分量中的最大权重
int head;//纪录最大权重对应的节点索引

int main(){
    struct hash_node *H[Max];
    struct gang_node gang[Max];
    struct vertex G[Max];
    int index1 , index2;
    int n , k;
    int i , j = 0;
    char s1[4] , s2[4];
    int weight;

    // 输入
    scanf("%d %d" , &n , &k);
    // 初始化
    for(i = 0;i < Max;i++){
        G[i].total_weight = 0;
        G[i].ptr = NULL;
        H[i] = NULL;
        visited[i] = 0;
    }
    // 输入
    for(i = 0;i < n;i++){
        scanf("%s %s %d" , s1 , s2 , &weight);
        // 在哈希表中查找字符串在邻接表中的索引
        index1 = get_index(H , s1);
        index2 = get_index(H , s2);
        // 插入另一个字符串
        insert(G , H , index1 , s1 , s2 , weight);
        insert(G , H , index2 , s2 , s1 , weight);
    }
    // 遍历整张图
    for(i = 0;i < count;i++){
        // 如果节点已被访问，则跳过该节点
        if(visited[i] == 1)
            continue;
        // 初始化
        num = 0;
        total = 0;
        max = -1;
        // 深度搜索
        DFS(G , H , i);
        // 如果节点数量大于2并且总权重大于k
        if(num > 2 && total > k){
            // 将信息加入gang数组
            gang[j].num = num;
            strcpy(gang[j].s , G[head].s);
            j++;
        }
    }
    // 对结果数组排序
    qsort(gang , j , sizeof(struct gang_node) , compare);
    // 输出
    printf("%d\n" , j);
    for(i = 0;i < j;i++){
        printf("%s %d\n" , gang[i].s , gang[i].num);
    }
}

// 得到哈希值
int get_hash(char s[]){
    int i = 0;
    int h = 0;

    while(s[i] != '\0'){
        h = 31 * h + s[i];
        i++;
    }

    return h % Max;
}

// 得到字符串在邻接表中的索引
int get_index(struct hash_node *H[] , char s[]){
    int h;
    struct hash_node *ptr;

    h = get_hash(s);
    ptr = H[h];
    while(ptr != NULL){
        if(strcmp(ptr->s , s) == 0)
            return ptr->index;
        ptr = ptr->next;
    }
    return -1;
}

// 插入
void insert(struct vertex G[] , struct hash_node *H[] , int index , char s1[] , char s2[] , int weight){
    int h;
    int flag = 0;
    struct hash_node *ptr;
    struct node *ptr1;

    // 如果索引为－1
    if(index == -1){
        // 在哈希表中插入一个新节点，纪录该字符串
        ptr = (struct hash_node *)malloc(sizeof(struct hash_node));
        // 复制字符串
        strcpy(ptr->s , s1);
        // 索引为当前的count值
        ptr->index = count;
        // 插入新节点
        h = get_hash(s1);
        ptr->next = H[h];
        H[h] = ptr;
        // 在邻接表中新开一个纪录
        index = count;
        // count加一
        count++;
        // 复制字符串给邻接表中的新纪录
        strcpy(G[index].s , s1);
    }
    // 如果索引为正数
    else{
        // 搜索另一个字符串
        ptr1 = G[index].ptr;
        while(ptr1 != NULL){
            if(strcmp(ptr1->s , s2) == 0){
                // 找到则flag为1
                flag = 1;
                break;
            }
            ptr1 = ptr1->next;
        }
    }

    // 如果建立了新纪录或在节点对应的链表中没有找到另一个字符串
    if(flag == 0){
        // 新建一个节点插入到纪录的链表中
        ptr1 = (struct node *)malloc(sizeof(struct node));
        strcpy(ptr1->s , s2);
        ptr1->weight = weight;
        ptr1->next = G[index].ptr;
        G[index].ptr = ptr1;
        G[index].total_weight += weight;
    }
    // 否则
    else{
        // 更新对应边的权重和节点的权重
        ptr1->weight += weight;
        G[index].total_weight += weight;
    }
}

// 深度搜索
void DFS(struct vertex G[] , struct hash_node *H[] , int start){
    struct node *ptr , *ptr1;
    int index;

    // 将当前节点设为已访问
    visited[start] = 1;
    // 节点数量加一
    num++;
    // 和max相比较，如果比其大
    if(G[start].total_weight > max){
        // 更新max和head
        max = G[start].total_weight;
        head = start;
    }
    // 遍历相邻的点
    ptr = G[start].ptr;
    while(ptr != NULL){
        // 如果边权重为0，则直接跳过
        if(ptr->weight == 0){
            ptr = ptr->next;
            continue;
        }
        // 更新total
        total += ptr->weight;
        // 将边权重设为0
        index = get_index(H , ptr->s);
        ptr1 = G[index].ptr;
        while(ptr1 != NULL){
            if(strcmp(ptr1->s , G[start].s) == 0)
                break;
            ptr1 = ptr1->next;
        }
        ptr1->weight = 0;
        // 如果下一节点没有被访问，则继续往下搜索
        if(visited[index] == 0)
            DFS(G , H , index);
        ptr = ptr->next;
    }
}

int compare(const void *a , const void *b){
    return strcmp((*(struct gang_node *)a).s , (*(struct gang_node *)b).s);
}