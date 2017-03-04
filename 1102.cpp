// PAT甲级1102 Invert a Binary Tree，原题地址：https://www.patest.cn/contests/pat-a-practise/1102
// 解题分析：
//  翻转二叉树。给定一个二叉树，我们要怎么做才能把它翻转呢？我们可以反中序(右、中、左的顺序)和反前序(中、右、左的顺序)
//  遍历原二叉树，得到两个序列，再用这两个序列按照正常的构建二叉树的步骤就可以构建出翻转后的二叉树了。这道题简单一点，没有
//  让我们真的构建出翻转后的二叉树，只要输出遍历序列即可，也就是构建翻转二叉树的第一步。那么现在问题就变成原二叉树是什么样的？
//  我们不知道根节点是哪个，因此在输入的时候，每输入一个数字，对应的check数组的值变为1，之后遍历check数组，值为0的就是根节点，
//  因为只有根节点没有父节点。有了根节点之后，我们就直接层序遍历和中序遍历输出即可。
#include<iostream>
#include<queue>
using namespace std;

int check[10];
int Left[10];
int Right[10];
int flag = 1;

// 层序遍历
void LevelOrder(int root){
    queue<int> q;

    q.push(root);
    while(!q.empty()){
        int t;
        t = q.front();
        q.pop();
        if(flag){
            cout << t;
            flag = 0;
        }
        else
            cout << " " << t;
        if(Right[t] != -1)
            q.push(Right[t]);
        if(Left[t] != -1)
            q.push(Left[t]);
    }
}

// 中序遍历
void InOrder(int root){
    if(root == -1)
        return;
    InOrder(Right[root]);
    if(flag){
        cout << root;
        flag = 0;
    }
    else
        cout << " " << root;
    InOrder(Left[root]);
}

int main(){
    int n;
    int i;
    char ch;

    cin >> n;
    getchar();
    // 输入
    for(i = 0;i < n;i++){
        ch = getchar();
        getchar();
        if(ch != '-'){
            Left[i] = ch - '0';
            check[ch - '0'] = 1;
        }
        else
            Left[i] = -1;
        ch = getchar();
        getchar();
        if(ch != '-'){
            Right[i] = ch - '0';
            check[ch - '0'] = 1;
        }
        else
            Right[i] = -1;
    }
    int root;
    // 得到根节点
    for(i = 0;i < n;i++)
        if(check[i] == 0){
            root = i;
            break;
        }
    // 遍历
    LevelOrder(root);
    cout << endl;
    flag = 1;
    InOrder(root);
    cout << endl;
}
