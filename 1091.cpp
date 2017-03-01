// PAT甲级1091 Acute Stroke，原题地址：https://www.patest.cn/contests/pat-a-practise/1091
// 解题分析：
//  题目意思有些难以理解，大致是说大脑里有很多个片段，每个片段有很多个像素点，这些像素点构成的是一个m*n的
//  矩阵，片段是竖直叠加起来的，因此在空间上是三维结构。题目中的图片的意思是每一个像素点，它的上下左右前后
//  的点和它相连，以此类推可以得到一片区域，我们要做的就是计算区域内的1的个数，如果比下限大，就加到总数里面。
//  为了实现这个目的，我们需要用BFS对一个点进行搜索，并在搜索的时候标记已经搜索过的点，避免重复搜索。遍历所有的
//  像素点，使用BFS就可以得到总数了。
#include<cstdio>
#include<queue>
using namespace std;

struct record{
    long i;
    long j;
    long k;
};
int G[1300][130][70];
int visited[1300][130][70];
queue<struct record> q;
long cnt;
long m , n , l , t;

void BFS(long i , long j , long k){
    long temp = 0;
    long a , b , c;
    struct record R;

    R.i = i;
    R.j = j;
    R.k = k;
    q.push(R);
    visited[i][j][k] = 1;
    // 队列不为空
    while(!q.empty()){
        R = q.front();
        q.pop();
        temp++;
        a = R.i;
        b = R.j;
        c = R.k;
        // 后
        if(a - 1 >= 0 && G[a - 1][b][c] == 1 && visited[a - 1][b][c] == 0){
            R.i = a - 1;
            R.j = b;
            R.k = c;
            q.push(R);
            visited[R.i][R.j][R.k] = 1;
        }
        // 前
        if(a + 1 < m && G[a + 1][b][c] == 1 && visited[a + 1][b][c] == 0){
            R.i = a + 1;
            R.j = b;
            R.k = c;
            q.push(R);
            visited[R.i][R.j][R.k] = 1;
        }
        // 左
        if(b - 1 >= 0 && G[a][b - 1][c] == 1 && visited[a][b - 1][c] == 0){
            R.i = a;
            R.j = b - 1;
            R.k = c;
            q.push(R);
            visited[R.i][R.j][R.k] = 1;
        }
        // 右
        if(b + 1 < n && G[a][b + 1][c] == 1 && visited[a][b + 1][c] == 0){
            R.i = a;
            R.j = b + 1;
            R.k = c;
            q.push(R);
            visited[R.i][R.j][R.k] = 1;
        }
        // 下
        if(c - 1 >= 0 && G[a][b][c - 1] == 1 && visited[a][b][c - 1] == 0){
            R.i = a;
            R.j = b;
            R.k = c - 1;
            q.push(R);
            visited[R.i][R.j][R.k] = 1;
        }
        // 上
        if(c + 1 < l && G[a][b][c + 1] == 1 && visited[a][b][c + 1] == 0){
            R.i = a;
            R.j = b;
            R.k = c + 1;
            q.push(R);
            visited[R.i][R.j][R.k] = 1;
        }
    }
    if(temp >= t)
        cnt += temp;
}
int main(){
    long i , j , k;

    scanf("%ld%ld%ld%ld" , &m , &n , &l , &t);
    // 输入
    for(k = 0;k < l;k++){
        for(i = 0;i < m;i++)
            for(j = 0;j < n;j++)
                scanf("%d" , &G[i][j][k]);
    }    
    // 遍历搜索点
    for(k = 0;k < l;k++){
        for(i = 0;i < m;i++)
            for(j = 0;j < n;j++)
                if(visited[i][j][k] == 0 && G[i][j][k] == 1)
                    BFS(i , j , k);
    }
    printf("%ld\n" , cnt);
}