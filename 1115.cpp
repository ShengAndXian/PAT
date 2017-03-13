// PAT甲级1115 Counting Nodes in a BST，原题地址：https://www.patest.cn/contests/pat-a-practise/1115
// 解题分析：
//  构建一个BST，然后层序遍历。注意BST的定义，相同的值要放在左子树，不是右子树。。。。
#include<iostream>
#include<queue>
using namespace std;

struct node{
    int key;
    struct node *left;
    struct node *right;
};

int pre , cur;
int n;

struct node *Insert(struct node *root , int key){
    if(root == NULL){
        struct node *ptr;
        ptr = new struct node;
        ptr->key = key;
        ptr->left = ptr->right = NULL;
        return ptr;
    }
    if(root->key >= key){
        root->left = Insert(root->left , key);
    }
    else{
        root->right = Insert(root->right , key);
    }
    return root;
}

void LevelOrder(struct node *root){
    queue<struct node *> q;

    q.push(root);
    while(1){
        cur = q.size();
        int cnt = cur;
        while(cnt){
            struct node  *t;
            t = q.front();
            q.pop();
            if(t->left != NULL){
                q.push(t->left);
            }
            if(t->right != NULL){
                q.push(t->right);
            }
            cnt--;
        }
        if(q.empty()){
            return;
        }
        else{
            pre = cur;
        }
    }
}

int main(){
    int i;
    struct node *root = NULL;

    cin >> n;
    for(i = 0;i < n;i++){
        int num;
        cin >> num;
        root = Insert(root , num);
    }
    LevelOrder(root);
    cout << cur << " + " << pre << " = " << cur + pre;
}