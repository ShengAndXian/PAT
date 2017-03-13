// PAT甲级1127 ZigZagging on a Tree，原题地址：https://www.patest.cn/contests/pat-a-practise/1127
// 解题分析：
//  用后序遍历序列和中序遍历序列构建一个二叉树，然后层序遍历，这个zigzag输出也很简单，判断一下层数是奇数还是偶数
//  就可以了。。。
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct node{
    int key;
    struct node *left;
    struct node *right;
};

int preOrder[50];
int postOrder[50];
int n;
int Index;

// 构建二叉树
struct node *Construct(int start , int end){
    struct node *ptr;
    int i;

    if(start > end)
        return NULL;
    ptr = new struct node;
    ptr->key = postOrder[Index];
    for(i = start;i <= end;i++){
        if(preOrder[i] == postOrder[Index]) 
            break;
    }
    Index--;
    ptr->right = Construct(i + 1 , end);
    ptr->left = Construct(start , i - 1);
    return ptr;
}

// 层序遍历
void LevelOrder(struct node *root){
    int cnt = 1;
    int flag = 1;
    queue<struct node *> q;
    vector<int> v;

    q.push(root);
    while(!q.empty()){
        int t = q.size();
        v.clear();
        while(t > 0){
            struct node *ptr = q.front();
            q.pop();
            if(ptr->left != NULL)
                q.push(ptr->left);
            if(ptr->right != NULL)
                q.push(ptr->right);
            t--;
            v.push_back(ptr->key);
        }
        if(cnt % 2 != 0){
            for(int i = v.size() - 1;i >= 0;i--){
                if(flag){
                    flag = 0;
                }
                else{
                    cout << " ";
                }
                cout << v[i];
            }
        }
        else{
            for(int i = 0;i < v.size();i++){
                if(flag){
                    flag = 0;
                }
                else{
                    cout << " ";
                }
                cout << v[i];
            }
        }
        cnt++;
    }
}
int main(){
    int i;
    struct node *root = NULL;

    cin >> n;
    for(i = 0;i < n;i++){
        cin >> preOrder[i];
    }
    for(i = 0;i < n;i++){
        cin >> postOrder[i];
    }
    Index = n - 1;
    root = Construct(0 , n - 1);
    LevelOrder(root);
}