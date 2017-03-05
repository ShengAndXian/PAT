// PAT甲级1105 Spiral Matrix，原题地址：https://www.patest.cn/contests/pat-a-practise/1105
// 解题分析：
//  首先要计算m和n，i从N的开方开始，一直往上加，j从i开始，一直往下减，一旦i乘j等于N，说明i和j就是我们要求
//  的m和n，这是因为m必须比n大（或相等），并且m-n要求最小。然后就是把排好序的序列放到矩阵里面，先从一个坐标点
//  开始，先往左一直搜索，碰壁后（边界或者遇到已访问过的点）再往下一直搜索，然后是往左再往上，这样就搜索完一圈了，
//  然后以结束点的右边的点开始，做相同的操作，直到所有的值都被填进去。最后输出即可。
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

int G[1000][1000];
int visited[1000][1000];
int m , n;
vector<int> v;

// 搜索
void Spiral(int x , int y , int &index){
    // 所有值都已填入
    if(index == v.size())
        return;
    // 往右搜索
    while(y < n && visited[x][y] == 0){
        G[x][y] = v[index];
        visited[x][y] = 1;
        index++;
        y++;
    }
    y--;
    x++;
    // 往下搜索
    while(x < m && visited[x][y] == 0){
        G[x][y] = v[index];
        visited[x][y] = 1;
        index++;
        x++;
    }
    x--;
    y--;
    // 往左搜索
    while(y >= 0 && visited[x][y] == 0){
        G[x][y] = v[index];
        visited[x][y] = 1;
        index++;
        y--;
    }
    y++;
    x--;
    // 往上搜索
    while(x >= 0 && visited[x][y] == 0){
        G[x][y] = v[index];
        visited[x][y] = 1;
        index++;
        x--;
    }
    x++;
    y++;
    // 递归搜索
    Spiral(x , y , index);
}

bool cmp(int a , int b){
    return a > b;
}

int main(){
    int N;
    int i , j;

    cin >> N;
    for(i = 0;i < N;i++){
        int num;
        cin >> num;
        v.push_back(num);
    }
    // 排序
    sort(v.begin() , v.end() , cmp);
    // 计算m和n
    for(i = sqrt(N);i <= N;i++){
        for(j = i;j >= 1;j--){
            if(i * j == N)
                break;
        }
        if(j >= 1)
            break;
    }
    m = i;
    n = j;
    int index = 0;
    // 搜索
    Spiral(0 , 0 , index);
    // 输出
    for(i = 0;i < m;i++){
        for(j = 0;j < n;j++){
            if(j != n - 1)
                cout << G[i][j] << " ";
            else    
                cout << G[i][j] << endl;
        }
    }
}