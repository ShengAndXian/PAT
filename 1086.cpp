// PAT甲级1086 Tree Traversals Again，原题地址：https://www.patest.cn/contests/pat-a-practise/1086
// 解题分析：
//  树的遍历。可以用栈来模拟中序遍历，也可以通过栈的push和pop顺序来还原树。用容器v作为栈，push的时候将输入的值放入v中，
//  然后将值插入到树中，重点在于，插入的时候要判断当前节点是否在栈中，如果在，则插在它的左子树，如果不在，则插在右子树。
//  pop的时候将值从v山中删除即可。然后简单的递归后序遍历树输出即可。
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

struct node{
    int index;
    struct node *left;
    struct node *right;
};

vector<int> v;
int flag = 1;

// 插入
struct node *Insert(struct node *root , int index){
    struct node *ptr;

    // 根节点为空，则新建一个节点后返回
    if(root == NULL){
        ptr = new struct node;
        ptr->index = index;
        ptr->left = ptr->right = NULL;
        root = ptr;
    }
    // 如果根节点不为空
    else{
        // 在v中查找根节点的值是否存在
        if(find(v.begin() , v.end() , root->index) != v.end()){
            // 如果存在，插在左子树
            root->left = Insert(root->left , index);
        }
        else{
            // 如果不存在，插在右子树
            root->right = Insert(root->right , index);
        }
    }
    return root;
}

// 后序遍历
void PostOrder(struct node *root){
    if(root == NULL)
        return;
    PostOrder(root->left);
    PostOrder(root->right);
    if(flag){
        flag = 0;
        cout << root->index;
    }
    else
        cout << " " << root->index;
}

int main(){
    struct node *root = NULL;
    int n;
    int i;
    int num;
    string s;

    cin >> n;
    for(i = 0;i < 2 * n;i++){
        cin >> s;
        // push
        if(s[1] == 'u'){
            cin >> num;
            v.push_back(num);
            root = Insert(root , num);
        }
        // pop
        else{
            // 删去最后一个元素
            v.resize(v.size() - 1);
        }
    }
    // 后序遍历
    PostOrder(root);
}