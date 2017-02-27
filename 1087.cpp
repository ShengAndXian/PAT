// PAT甲级1087 All Roads Lead to Rome，原题地址：https://www.patest.cn/contests/pat-a-practise/1087
// 解题分析：
//  Dijkstra加DFS。先用Dijkstra求出Rome的最短路径，然后从起点出发DFS，搜索时保存走过的路长，如果比Rome的最短路径长
//  直接返回，以此减少程序的运行时间。搜索到Rome时，需要和之前的最优路径，如果happy值比它高，则最优路径为当前路径，如果
//  相等，再比较平均happy值，如果比它高，则最优路径也为当前路径。用容器储存路径上的点，最后输出即可。
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
#define Max 210
#define INFINITY 100000

int G[Max][Max];
int hp[Max];
int Distance[Max];
int Visited[Max];
int currentDistance;
int currentFun , fun , avfun;
int cnt , num;
int t;
vector<string> v1;
vector<string> v2;   
int n , k;

// 最短路径算法，太常用了就不解释了
void Dijkstra(){
    int i;
    int index , min;

    while(1){
        min = INFINITY;
        for(i = 0;i < n;i++){
            if(Visited[i] == 0 && Distance[i] < min){
                min = Distance[i];
                index = i;
            }
        }
        if(min == INFINITY)
            break;
        Visited[index] = 1;
        for(i = 0;i < n;i++){
            if(G[index][i] > 0 && Visited[i] == 0 && G[index][i] + Distance[index] < Distance[i])
                Distance[i] = G[index][i] + Distance[index];
        }
    }
}

// DFS
bool DFS(int start){
    bool flag = false;
    int i;

    // 剪枝
    if(currentDistance > Distance[t])
        return false;
    
    // 更新一些全局变量
    num++;
    currentFun += hp[start];
    Visited[start] = 1;
    // 如果是Rome点
    if(start == t){
        // 路径条数加一
        cnt++;
        // 如果happy比它大
        if(currentFun > fun){
            fun = currentFun;
            avfun = fun / (num - 1);
            v2.clear();
            v2.push_back(v1[start]);
            flag = true;
        }
        // 如果happy值相等，但平均happy比它大
        else if(currentFun == fun && currentFun / (num - 1) > avfun){
            avfun = currentFun / (num - 1);
            v2.clear();
            v2.push_back(v1[start]);
            flag = true;
        }
    }
    // 不是Rome点
    else{
        for(i = 0;i < n;i++){
            // 遍历其他点
            if(G[start][i] > 0 && Visited[i] == 0){
                currentDistance += G[start][i];
                if(DFS(i))
                    flag = true;
                currentDistance -= G[start][i];
            }
        }
        // 如果当前点在路径上
        if(flag)
            v2.push_back(v1[start]);
    }
    
    // 重新更新全局变量
    num--;
    currentFun -= hp[start];
    Visited[start] = 0;
    if(flag)
        return true;
    else
        return false;
}
int main(){
    string s , a , b;
    int i;
    int temp;
    int t1 , t2;

    cin >> n >> k >> s;
    v1.push_back(s);
    for(i = 1;i <= n - 1;i++){
        cin >> s >> temp;
        // v1容器保存字符串
        v1.push_back(s);
        // hp数组保存happy值
        hp[i] = temp;
    }
    for(i = 0;i < k;i++){
        cin >> a >> b >> temp;
        // 求出对应字符串的序列号
        t1 = find(v1.begin() , v1.end() , a) - v1.begin();
        t2 = find(v1.begin() , v1.end() , b) - v1.begin();
        // 储存图信息
        G[t1][t2] = temp;
        G[t2][t1] = temp;
    }
    // 初始化
    for(i = 0;i < n;i++){
        Distance[i] = INFINITY;
        Visited[i] = 0;
    }
    // 求最短路径
    Distance[0] = 0;
    Dijkstra();
    // Rome的索引
    t = find(v1.begin() , v1.end() , "ROM") - v1.begin();
    for(i = 0;i < n;i++)
        Visited[i] = 0;
    // DFS
    DFS(0);
    // 输出
    cout << cnt << " " << Distance[t] << " " << fun << " " <<  avfun << endl;
    for(i = v2.size() - 1;i >= 0;i--){
        cout << v2[i];
        if(i != 0)
            cout << "->";
    }
}
