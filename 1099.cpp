// PAT甲级1099 Build A Binary Search Tree，原题地址：https://www.patest.cn/contests/pat-a-practise/1099
// 解题分析：
//  给定一个序列和一个BST结构，可以构建一个唯一的BST。构建BST的关键是要计算出每一个节点它的左子树的节点个数，然后对序列排序
//  后递归构建BST。构建好BST后层序遍历输出即可。
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

struct node{
    int key;
    struct node *Left;
    struct node *Right;
};       

int arr[110];
int Left[110];
int Right[110];
int LeftNum[110];
int RightNum[110];
int n;

// 构建BST
struct node *Construct(int index , int start , int end){
    struct node *ptr;
    int t;

    if(index == -1)
        return NULL;
    t = start + LeftNum[index];
    ptr = new struct node;
    ptr->key = arr[t];
    ptr->Left = Construct(Left[index] , start , t - 1);
    ptr->Right = Construct(Right[index] , t + 1 , end);
    return ptr;
}

// 层序遍历
void LevelOrder(struct node *root){
    queue<struct node> q;
    struct node temp;
    int flag = 1;

    q.push(*root);
    while(!q.empty()){
        temp = q.front();
        q.pop();
        if(temp.Left != NULL)
            q.push(*temp.Left);
        if(temp.Right != NULL)
            q.push(*temp.Right);
        if(flag){
            cout << temp.key;
            flag = 0;
        }
        else
            cout << " " << temp.key;
    }
    cout << endl;
}

// 计算每一个节点的左子树的节点个数
int Calculate(int index){
    if(index == -1)
        return 0;
    LeftNum[index] = Calculate(Left[index]);
    RightNum[index] = Calculate(Right[index]);
    return LeftNum[index] + RightNum[index] + 1;
}

int main(){
    struct node *root;
    int i;

    cin >> n;
    for(i = 0;i < n;i++){
        cin >> Left[i] >> Right[i];
    }
    for(i = 0;i < n;i++){
        cin >> arr[i];
    }
    Calculate(0);
    sort(arr , arr + n);
    root = Construct(0 , 0 , n - 1);
    LevelOrder(root);
}