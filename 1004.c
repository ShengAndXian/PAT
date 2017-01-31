// PAT甲级1004 Counting Leaves，原题地址：https://www.patest.cn/contests/pat-a-practise/1004
// 解题分析：
//  树的层序遍历。非叶子节点的子节点用链表储存，所有节点储存在数组中。输入结束后，从根节点01开始层序遍历整棵树，
//  如果有节点没有子节点，则是叶子节点，count加一，每一层都输出该层的count即可。
#include<stdio.h>
#include<stdlib.h>

#define Max 100
struct node{
    int index;
    struct node *next;
};
struct tree{
    int N;
    struct node *arr[Max];
};

struct tree *initialize();
void levelOrderTraversal(struct tree *T);

int main(){
    struct tree *T;

    // 初始化
    T = initialize();
    // 层序遍历
    levelOrderTraversal(T);
}

// 初始化
struct tree *initialize(){
    int N , M;
    int parent , child , num;
    struct tree *T;
    int i , j;
    struct node *ptrToNode;

    // 构建树
    T = (struct tree *)malloc(sizeof(struct tree));
    scanf("%d %d" , &N , &M);
    T->N = N;
    for(i = 1;i <= N;i++){
        T->arr[i] = NULL;
    }
    for(i = 0;i < M;i++){
        scanf("%d %d" , &parent , &num);
        for(j = 0;j < num;j++){
            scanf("%d" , &child);
            // 纪录子节点
            ptrToNode = (struct node *)malloc(sizeof(struct node));
            ptrToNode->index = child;
            ptrToNode->next = T->arr[parent];
            T->arr[parent] = ptrToNode;
        }
    }

    return T;
}

// 层序遍历
void levelOrderTraversal(struct tree *T){
    int queue[Max];
    int front = 0 , rear = -1;
    int num;
    int current;
    struct node *ptrToNode;
    int count;
    int flag = 0;

    queue[++rear] = 1;
    while(1){
        count = 0;
        // 计算每一层的节点数量
        num = rear - front + 1;
        // 节点数量为0则遍历结束
        if(num == 0)
            break;
        while(num-- > 0){
            current = queue[front++];
            ptrToNode = T->arr[current];
            if(ptrToNode == NULL)
                count++;
            else{
                while(ptrToNode != NULL){
                    queue[++rear] = ptrToNode->index;
                    ptrToNode = ptrToNode->next;
                }
            }
        }
        if(flag == 0){
            printf("%d" , count);
            flag = 1;
        }
        else{
            printf(" %d" , count);
        }
    }
}