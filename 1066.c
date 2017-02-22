// PAT甲级1066 Root of AVL Tree，原题地址：https://www.patest.cn/contests/pat-a-practise/1066
// 解题分析：
//  AVL树的插入。AVL树也是一种二叉搜索树，插入时按照二叉搜索树的插入方法插入，在返回时判断是否平衡，如果不平衡，
//  通过旋转调整子树至平衡状态。
#include<stdio.h>
#include<stdlib.h>

struct node{
    int key;
    struct node *left;
    struct node *right;
};

struct node *Insert(struct node *root , int key);
int GetHeight(struct node *root);
struct node *RoateWithLeft(struct node *root);
struct node *RoateWithRight(struct node *root);
struct node *DoubleRoateWithLeft(struct node *root);
struct node *DoubleRoateWithRight(struct node *root);

int main(){
    struct node *root = NULL;
    int n;
    int key;
    int i;

    scanf("%d" , &n);
    for(i = 0;i < n;i++){
        scanf("%d" , &key);
        root = Insert(root , key);
    }
    printf("%d\n" , root->key);
}

// 插入key
struct node *Insert(struct node *root , int key){
    int lh , rh;
    struct node *ptr;

    // 根节点为空，构造节点后直接返回
    if(root == NULL){
        ptr = (struct node *)malloc(sizeof(struct node));
        ptr->key = key;
        ptr->left = NULL;
        ptr->right = NULL;
        return ptr;
    }
    // 如果根节点的key大于要插入的key
    if(root->key > key)
        // 递归插入
        root->left = Insert(root->left , key);
    // 如果根节点的key小于要插入的key
    else
        // 递归插入
        root->right = Insert(root->right , key);  
    
    // 计算根节点两个子树的高度
    lh = GetHeight(root->left);
    rh = GetHeight(root->right);
    // 左子树高度比右子树高度大1以上
    if(lh - rh > 1){
        // 计算左子树根节点的左右子树的高度
        lh = GetHeight(root->left->left);
        rh = GetHeight(root->left->right);
        // LL型
        if(lh > rh)
            root = RoateWithLeft(root);
        // LR型
        else
            root = DoubleRoateWithLeft(root);
    }
    // 右子树高度比左子树高度大1以上
    if(rh - lh > 1){
        // 计算右子树根节点的左右子树的高度
        lh = GetHeight(root->right->left);
        rh = GetHeight(root->right->right);
        // RR型
        if(lh < rh)
            root = RoateWithRight(root);
        // RL型
        else
            root = DoubleRoateWithRight(root);
    }
    return root;
}

// 计算树的高度
int GetHeight(struct node *root){
    int lh , rh;

    if(root == NULL)
        return -1;
    lh = GetHeight(root->left);
    rh = GetHeight(root->right);
    return (lh + 1) > (rh + 1) ? (lh + 1) : (rh + 1);
}

// LL型旋转
struct node *RoateWithLeft(struct node *root){
    struct node *newRoot;

    newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    return newRoot;
}

// RR型旋转
struct node *RoateWithRight(struct node *root){
    struct node *newRoot;

    newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    return newRoot;
}

// LR型旋转
struct node *DoubleRoateWithLeft(struct node *root){
    root->left = RoateWithRight(root->left);
    return RoateWithLeft(root);
}

// RL型旋转
struct node *DoubleRoateWithRight(struct node *root){
    root->right = RoateWithLeft(root->right);
    return RoateWithRight(root);
}