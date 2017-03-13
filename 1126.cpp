// PAT甲级1126 Eulerian Path，原题地址：https://www.patest.cn/contests/pat-a-practise/1126
// 解题分析：
//  判断是否是欧拉回路。首先要判断图是否是联通的，如果不联通则输出Non-Eulerian，如果联通在判断度为奇数的
//  结点数量。
#include<iostream>
using namespace std;

int n , m;
int G[510][510];
int visited[510];

void DFS(int index){
    int i;

    visited[index] = 1;
    for(i = 1;i <= n;i++){
        if(visited[i] == 0 && G[index][i] == 1)
            DFS(i);
    }
}

int main(){
    int i , j;
    int degree;
    int cnt = 0;

    cin >> n >> m;
    for(i = 0;i < m;i++){
        int a , b;
        cin >> a >> b;
        G[a][b] = 1;
        G[b][a] = 1;
    }
    // 计算输出每个结点的度
    for(i = 1;i <= n;i++){
        degree = 0;
        for(j = 1;j <= n;j++){
            if(G[i][j] == 1){
                degree++;
            }
        }
        // 度为奇数
        if(degree % 2 != 0){
            cnt++;
        }
        cout << degree;
        if(i != n)
            cout << " ";
    }
    cout << endl;
    // DFS遍历判断图是否联通
    DFS(1);
    for(i = 1;i <= n;i++){
        // 不联通
        if(visited[i] == 0){
            cout << "Non-Eulerian" << endl;
            return 0;
        }
    }
    // 判断度为奇数的结点数量
    if(cnt == 0){
        cout << "Eulerian" << endl;
    }
    else if(cnt == 2){
        cout << "Semi-Eulerian" << endl;
    }
    else{
        cout << "Non-Eulerian" << endl;
    }
}