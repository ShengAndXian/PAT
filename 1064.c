// PAT甲级1064 Complete Binary Search Tree，原题地址：https://www.patest.cn/contests/pat-a-practise/1064
// 解题分析：
//  完全二叉搜索树。先对输入的序列从小到大排序，由于是完全二叉树，因此可以根据节点的总数计算出左子树所有节点的数量，当前树
//  的根节点就是排在这些节点后的第一个节点（根据二叉搜索树的性质），因此就可以得到根节点的索引，递归求得左子树和右子树的根
//  节点的索引，把它们储存起来，递归完整棵树之后，宽度优先搜索输出树的层序遍历序列。
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct node{
    int key;
    int left;
    int right;
};//储存节点信息

int cmp(const void *a , const void *b);
int Construct(struct node T[] , int start , int end);

int main(){
    struct node T[1000];
    int n;
    int root;
    int i;
    int queue[1000];
    int front = 0 , rear = -1;
    int temp;
    int flag = 1;

    scanf("%d" , &n);
    for(i = 0;i < n;i++)
        scanf("%d" , &T[i].key);
    // 排序
    qsort(T , n , sizeof(struct node) , cmp);
    // 获取根节点的索引
    root = Construct(T , 0 , n - 1);
    // 层序遍历
    queue[++rear] = root;
    while(front <= rear){
        temp = queue[front++];
        if(flag){
            printf("%d" , T[temp].key);
            flag = 0;
        }
        else{
            printf(" %d" , T[temp].key);
        }
        if(T[temp].left != -1)
            queue[++rear] = T[temp].left;
        if(T[temp].right != -1)
            queue[++rear] = T[temp].right;
    }
    printf("\n");
    return 0;
}

int Construct(struct node T[] , int start , int end){
    int cnt = end - start + 1;
    int h;
    int left;
    int i;
    int root;

    // start大于end直接返回－1
    if(start > end)
        return -1;
    // 计算树的高度，起始高度设为1
    for(h = 1;pow(2 , h) - 1 < cnt;h++) ;
    // 如果树的高度为1，则是叶子节点
    if(h == 1){
        T[start].left = -1;
        T[end].right = -1;
        return start;
    }
    // 计算左子树节点数量
    left = pow(2 , h - 2) - 1;
    if(cnt - 2 * left - 1 > pow(2 , h - 2))
        left += pow(2 , h - 2);
    else
        left += cnt - 2 * left - 1;
    // 根节点排在左子树所有节点后面
    root = start + left;
    // 递归获取左子树和右子树的根节点
    T[root].left = Construct(T , start , root - 1);
    T[root].right = Construct(T , root + 1 , end);
    return root;
}

int cmp(const void *a , const void *b){
    return (*(struct node *)a).key - (*(struct node *)b).key;
}