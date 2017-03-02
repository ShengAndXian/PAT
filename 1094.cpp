// PAT甲级1094 The Largest Generation，原题地址：https://www.patest.cn/contests/pat-a-practise/1094
// 解题分析：
//  简单的BFS，对于队列中的元素，我们要一层一层处理，不能一个一个处理，其他就不解释了。
#include<iostream>
#include<queue>
using namespace std;
#define Max 110

int G[Max][Max];
int visited[Max];
int n , m;
int cnt , lev;

void BFS(int root){
    queue<int> q;
    int ccnt , clev = 1;
    int index;

    q.push(root);
    visited[root] = 1;
    while(!q.empty()){
        ccnt = q.size();
        if(ccnt > cnt){
            cnt = ccnt;
            lev = clev;
        }
        while(ccnt > 0){
            index = q.front();
            q.pop();
            for(int i = 1;i <= n;i++){
                if(G[index][i] == 1 && visited[i] == 0){
                    q.push(i);
                    visited[i] = 1;
                }
            } 
            ccnt--;
        }
        clev++;
    }
}

int main(){
    int i , j , k;
    int pid , cid;

     cin >> n >> m;
     for(i = 0;i < m;i++){
         cin >> pid >> k;
         for(j = 0;j < k;j++){
             cin >> cid;
             G[pid][cid] = 1;
         }
     }
     BFS(1);
     cout << cnt << " " << lev << endl;
}