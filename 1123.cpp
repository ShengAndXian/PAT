// PAT甲级1123 Is It a Complete AVL Tree，原题地址：https://www.patest.cn/contests/pat-a-practise/1123
// 解题分析：
//  AVL树的插入以及层序遍历，遍历时判断是否是完全二叉树。
#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;


struct node{
    int key;
    struct node *left;
    struct node *right;
};

// 计算高度
int GetHeight(struct node *root){
    if(root == NULL)
        return -1;
    int lh , rh;
    lh = GetHeight(root->left);
    rh = GetHeight(root->right);
    return lh > rh ? lh + 1 : rh + 1;
}

// 右旋
struct node *RoateWithLeft(struct node *root){
    struct node *ptr;

    ptr = root->left;
    root->left = ptr->right;
    ptr->right = root;
    return ptr;
}

// 左旋
struct node *RoateWithRight(struct node *root){
    struct node *ptr;

    ptr = root->right;
    root->right = ptr->left;
    ptr->left = root;
    return ptr;
}

// 左边两次旋转
struct node *DoubleRoateWithLeft(struct node *root){
    root->left = RoateWithRight(root->left);
    return RoateWithLeft(root);
}

// 右边两次旋转
struct node *DoubleRoateWithRight(struct node *root){
    root->right = RoateWithLeft(root->right);
    return RoateWithRight(root);
}

// 插入
struct node *Insert(struct node *root , int key){
    if(root == NULL){
        root = new struct node;
        root->key = key;
        root->left = root->right = NULL;
    }
    else{
        if(key < root->key){
            root->left = Insert(root->left , key);
        }
        else{
            root->right = Insert(root->right , key);
        }
        int lh , rh;
        lh = GetHeight(root->left);
        rh = GetHeight(root->right);
        if(lh - rh > 1){
            if(key < root->left->key){
                root = RoateWithLeft(root);
            }
            else{
                root = DoubleRoateWithLeft(root);
            }
        }
        if(rh - lh > 1){
            if(key > root->right->key){
                root = RoateWithRight(root);
            }
            else{
                root = DoubleRoateWithRight(root);
            }
        }
    }
    return root;
}

// 层序遍历
void LevelOrder(struct node *root){
    int dep = 0;
    int flag = 1;
    queue<struct node*> q;
    vector<struct node*> v;

    q.push(root);
    while(!q.empty()){
        int cnt = q.size();
        int temp = cnt;
        // 当前层不满
        if(temp != pow(2 , dep)){
            // 先从上一层判断
            for(int i = 0;i < v.size();i++){
                if(v[i]->left == NULL && v[i]->right != NULL){
                    flag = 0;
                }
                else if(i != 0 && v[i]->left != NULL && v[i - 1]->right == NULL){
                    flag = 0;
                }
            }
        }
        v.clear();
        // 处理当前层结点
        while(cnt){
            struct node *ptr;
            ptr = q.front();
            q.pop();
            if(ptr->left != NULL){
                q.push(ptr->left);
                // 当前层不满，但下一层还有结点
                if(temp != pow(2 , dep)){
                    flag = 0;
                }
            }
            if(ptr->right != NULL){
                q.push(ptr->right);
                if(temp != pow(2 , dep)){
                    flag = 0;
                }
            }
            cnt--;
            // v记录上一层结点，以便以后用了判断是否完全二叉
            v.push_back(ptr);
            cout << ptr->key;
            if(!q.empty())
                cout << " ";
            else    
                cout << endl;
        }
        // 层数加一
        dep++;
    }
    if(flag)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}

int main(){
    int n;
    int i;
    struct node *root = NULL;

    cin >> n;
    for(i = 0;i < n;i++){
        int t;
        cin >> t;
        root = Insert(root , t);
    }
    LevelOrder(root);
}