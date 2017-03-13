// PAT甲级1110 Complete Binary Tree，原题地址：https://www.patest.cn/contests/pat-a-practise/1110
// 解题分析：
//  层序遍历整棵树，计算每一层的节点数，如果没满，先检查当前层下面一层是否全部为空结点，如果有非空结点，说明不是完全二叉的，
//  再从上一层检查当前层的结点是否符合完全二叉树，如果符合则是，否则不是。
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;

int Left[20] , Right[20];
int flag[20];
int n;
int res;

bool LevelOrder(int root){
    int height = 0;
    int cnt;
    int t;
    vector<int> v;
    queue<int> q;

    q.push(root);
    // 层序遍历
    while(!q.empty()){
        // 一层的结点数
        cnt = q.size();
        // 如果没满
        if(cnt != pow(2 , height)){
            // 检查下一层
            for(int i = 0;i < cnt;i++){
                t = q.front();
                q.pop();
                if(Left[t] != -1 || Right[t] != -1){
                    return false;
                }
            }
            int pre = 3;
            // 从上一层检查
            for(int i = 0;i < v.size();i++){
                int current = 0;
                if(Left[v[i]] == -1 && Right[v[i]] != -1){
                    return false;
                }
                if(Left[v[i]] != -1){
                    current++;
                }
                if(Right[v[i]] != -1){
                    current++;
                }
                if(current > pre){
                    return false;
                }
                else{
                    pre = current;
                }
            }
            res = t;
            return true;
        }
        // 如果满了
        else{
            v.clear();
            for(int i = 0;i < cnt;i++){
                t = q.front();
                q.pop();
                // v储存上一层的结点
                v.push_back(t);
                if(Left[t] != -1){
                    q.push(Left[t]);
                }
                if(Right[t] != -1){
                    q.push(Right[t]);
                }
            }
            height++;
        }
    }
    res = t;
    return true;
}
int main(){
    int i;
    string s;

    cin >> n;
    for(i = 0;i < n;i++){
        cin >> s;
        if(s[0] == '-'){
            Left[i] = -1;
        }
        else{
            int t = stod(s);
            Left[i] = t;
            flag[t] = 1;
        }
        cin >> s;
        if(s[0] == '-'){
            Right[i] = -1;
        }
        else{
            int t = stod(s);
            Right[i] = t;
            flag[t] = 1;
        }
    }
    int root;
    for(i = 0;i < n;i++){
        if(flag[i] == 0){
            root = i;
            break;
        }
    }
    if(LevelOrder(root)){
        cout << "YES " << res << endl;
    }
    else{
        cout << "NO " << root << endl; 
    }
}