// PAT甲级1020 Tree Traversals，原题地址：https://www.patest.cn/contests/pat-a-practise/1020
// 解题分析：
//  树的遍历。给出一个树的中序遍历序列和前序或后序遍历，即可构建出唯一的一个树。题目中给的是中序遍历序列和后序遍历序列。
//  后序遍历序列的最后一个节点是根节点，这个节点将中序遍历一分为二，左边的就是这个节点的左子树，右边的是右子树。在构建树
//  的时候我们先构建右子树，再构建左子树。通过递归就可以构建出这棵树了。然后再中序遍历构建出来的树即可。
#include<stdio.h>
#include<stdlib.h>

struct node{
    int index;
    struct node *left;
    struct node *right;
};//节点

struct node *construct(int postorder[] , int inorder[] , int start , int end);
void levelorder(struct node *root);

// 全局变量，节点的数量
int n;

int main(){
    int postorder[30] , inorder[30];
    int i;
    struct node *root;
    
    scanf("%d" , &n);
    for(i = 0;i < n;i++)
        scanf("%d" , &postorder[i]);
    for(i = 0;i < n;i++)
        scanf("%d" , &inorder[i]);
    
    // 建树
    root = construct(postorder , inorder , 0 , n - 1);
    // 中序遍历
    levelorder(root);
}

struct node *construct(int postorder[] , int inorder[] , int start , int end){
    struct node *ptr;
    int i;

    // 如果start大于end，则不需要构建子树，返回空节点
    if(start > end)
        return NULL;
    // 如果start小于end，构建新的节点
    ptr = (struct node *)malloc(sizeof(struct node));
    // 新节点的值就是当前postorder的最后一个值
    ptr->index = postorder[n - 1];
    // 在中序序列里查找新节点的值
    for(i = start;i <= end;i++)
        if(inorder[i] == postorder[n - 1])
            break;
    n--;//更新postorder最后一个值
    // 构建右子树
    ptr->right = construct(postorder , inorder , i + 1 , end);
    // 构建左子树
    ptr->left = construct(postorder , inorder , start , i -1);
    // 返回
    return ptr;
}

// 层序遍历，用队列很简单就解决了，就不注释了。。。。
void levelorder(struct node *root){
    struct node *queue[30];
    struct node *ptr;
    int rear = -1 , front = 0;
    int flag = 0;

    queue[++rear] = root;
    while(1){
        if(front > rear)
            break;
        ptr = queue[front++];
        if(ptr->left != NULL)
            queue[++rear] = ptr->left;
        if(ptr->right != NULL)
            queue[++rear] = ptr->right;
        if(flag == 0){
            printf("%d" , ptr->index);
            flag = 1;
        }
        else
            printf(" %d" , ptr->index);
    }
}