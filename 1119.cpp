// PAT甲级1119 Pre- and Post-order Traversals，原题地址：https://www.patest.cn/contests/pat-a-practise/1119
// 解题分析：
//  用中序和后序遍历得到的序列构建一个二叉树，二叉树可能并不唯一，大概的描述比较抽象，具体解释就直接写在注释里了。
#include<iostream>
using namespace std;

struct node{
    int key;
    struct node *left;
    struct node *right;
};

int preOrder[100] , postOrder[100];
int n;
int flag = 1;//flag标记二叉树是否唯一

// 递归构建二叉树
struct node *Construct(int index , int start , int end){
    struct node *ptr;

    // 递归出口
    if(index >= n || start > end){
        return NULL;
    }
    // 构建新结点
    ptr = new struct node;
    // 值为前序序列中对应的值
    ptr->key = preOrder[index];
    // 如果只有一个结点
    if(start == end){
        ptr->left = ptr->right = NULL;
        return ptr;
    }
    // 判断当前结点的后一个结点是否和后序序列的倒数第二个值相等，如果
    // 相等说明当前结点是后面所有结点的根结点，但当前结点可以是它的父
    // 结点的左孩子或右孩子
    if(postOrder[end - 1] == preOrder[index + 1]){
        // flag变为0
        flag = 0;
        // 假设是左孩子
        ptr->left = Construct(index + 1 , start , end - 1);
        ptr->right = NULL;
    }
    // 如果当前结点的后一个结点和后序序列的第一个值相等，则当前结点是它的父结点的左孩子，
    // 其他后面的结点全部位于它的父结点的右子树
    else if(postOrder[start] == preOrder[index + 1]){
        struct node *temp;
        temp = new struct node;
        temp->key = preOrder[index + 1];
        temp->left = temp->right = NULL;
        ptr->left = temp;
        // 构建右子树
        ptr->right = Construct(index + 2 , start + 1 , end - 1);
    }
    // 当前结点的后一个结点的值位于后序序列的中间
    else{
        int i;
        // 找到值的位置
        for(i = start + 1;i < end - 1;i++){
            if(postOrder[i] == preOrder[index + 1])
                break;
        }
        // 构建左子树
        ptr->left = Construct(index + 1 , start , i);
        // 构建右子树
        ptr->right = Construct(index + i - start + 2 , i + 1 , end - 1);
    }
    return ptr;
}

// 中序遍历
void Inorder(struct node *root){
    if(root == NULL)
        return;
    Inorder(root->left);
    if(flag){
        cout << root->key;
        flag = 0;
    }
    else{
        cout << " " << root->key;
    }
    Inorder(root->right);
}
int main(){
    int i;
    struct node *root;

    cin >> n;
    for(i = 0;i < n;i++){
        cin >> preOrder[i]; 
    }
    for(i = 0;i < n;i++){
        cin >> postOrder[i];
    }
    int index = 0;
    root = Construct(index , 0 , n - 1);
    if(flag){
        cout << "Yes" << endl;
    }
    else{
        cout << "No" << endl;
    }
    flag = 1;
    Inorder(root);
    cout << endl;
}