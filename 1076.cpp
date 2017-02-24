// PAT甲级1076 Forwards on Weibo，原题地址：https://www.patest.cn/contests/pat-a-practise/1076
// 解题分析：
//  BFS。整个网络其实就是一个有向图，一个节点可以指向一些节点，这些节点就是关注他的人。用二维数组储存有向图，
//  然后根据查询的值，宽度有限搜索直到搜索的层次等于规定的层次或者没有节点可以搜索为止。需要注意的是，将节点
//  加入到队列中时，就需要将该节点设为已被访问，否则可能出现队列中有重复的节点。
#include<iostream>
#include<queue>
using namespace std;
#define Max 1100

int G[Max][Max];
int visited[Max];
queue<int> Q;
int n , l;

int main(){
    int i , j;
    int k;
    int m;
    int u;
    int cnt;
    int level;
    int temp;
    int forward;

    cin >> n >> l;
    for(i = 1;i <= n;i++){
        cin >> m;
        // 储存图
        for(j = 0;j < m;j++){
            cin >> u;
            G[u][i] = 1;
        }
    }
    cin >> k;
    // 查询
    for(i = 0;i < k;i++){
        cin >> u;
        // 初始化
        level = 0;
        forward = 0;
        // 全部节点设为未访问
        for(j = 1;j <= n;j++)
            visited[j] = 0;
        // 将根节点加入队列
        Q.push(u);
        visited[u] = 1;
        // 搜索层次不能超过l
        while(level < l){
            // 如果没有节点可以搜索则退出循环
            if(Q.empty())
                break;
            cnt = Q.size();
            // 遍历一层内所有节点
            while(cnt > 0){
                temp = Q.front();
                Q.pop();
                cnt--;
                // 将子节点加入队列
                for(j = 1;j <= n;j++){
                    if(G[temp][j] == 1 && visited[j] == 0){
                        visited[j] = 1;
                        Q.push(j);
                        forward++;
                    }
                }
            }
            // 一层结束level加一
            level++;
        }
        // 清空队列
        while(!Q.empty())
            Q.pop();
        cout << forward << endl;
    }
}