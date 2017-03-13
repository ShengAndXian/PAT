// PAT甲级1111 Online Map，原题地址：https://www.patest.cn/contests/pat-a-practise/1111
// 解题分析：
//  最短路径和DFS。整张图是一个有向图，特别的就是每一条边有两个权值，一个长度，一个时间，其实没太大差别，
//  就是代码会长一些。先用Dijkstra算出目的地的最短路径和最短时间，然后用两个DFS加剪枝就可以了。
#include<iostream>
#include<vector>
using namespace std;
#define INFINITY 10000000
#define Max 510

int L[Max][Max];
int T[Max][Max];
int Distance[Max];
int Time[Max];
int visitedDistance[Max];
int visitedTime[Max];
int fast = INFINITY , most = INFINITY;
int n , m;
int Start , End;
int currentLength , currentTime , cnt;
vector<int> v1 , v2;

// 计算最短路径和最短时间
void Dijkstra(){
    int i;
    int min1 , min2;
    int index1 , index2;

    while(1){
        min1 = INFINITY;
        min2 = INFINITY;
        // 选出当前路径最短的未访问点
        for(i = 0;i < n;i++){
            if(Distance[i] < min1 && visitedDistance[i] == 0){
                min1 = Distance[i];
                index1 = i;
            }
        }
        // 选出当前时间最短的未访问点
        for(i = 0;i < n;i++){
            if(Time[i] < min2 && visitedTime[i] == 0){
                min2 = Time[i];
                index2 = i;
            }
        }
        // 全部遍历
        if(min1 == INFINITY)
            break;
        visitedDistance[index1] = 1;
        visitedTime[index2] = 1;
        // 更新连接结点的最短路径
        for(i = 0;i < n;i++){
            if(L[index1][i] > 0 && visitedDistance[i] == 0 && L[index1][i] + Distance[index1] < Distance[i]){
                Distance[i] = L[index1][i] + Distance[index1];
            }
        }
        // 更新连接结点的最短时间
        for(i = 0;i < n;i++){
            if(T[index2][i] > 0 && visitedTime[i] == 0 && T[index2][i] + Time[index2] < Time[i]){
                Time[i] = T[index2][i] + Time[index2];
            }
        }
    }
}

// DFS
bool DFS1(int root){
    int i;
    bool flag = false;

    // 剪枝
    if(currentLength > Distance[End]){
        return false;
    }
    // 访问到目的地结点
    if(root == End){
        if(currentTime < fast){
            fast = currentTime;
            v1.clear();
            v1.push_back(root);
            return true;
        }
        else{
            return false;
        }
    }
    visitedDistance[root] = 1;
    // 依次搜索连接的结点
    for(i = 0;i < n;i++){
        currentLength += L[root][i];
        currentTime += T[root][i];
        if(L[root][i] > 0 && visitedDistance[i] == 0){
            if(DFS1(i)){
                v1.push_back(root);
                flag = true;
            }
        }
        currentLength -= L[root][i];
        currentTime -= T[root][i];
    }
    visitedDistance[root] = 0;
    return flag;
}

// 同理
bool DFS2(int root){
    int i;
    bool flag = false;

    if(currentTime > Time[End]){
        return false;
    }
    if(root == End){
        if(cnt < most){
            most = cnt;
            v2.clear();
            v2.push_back(root);
            return true;
        }
        else{
            return false;
        }
    }
    visitedTime[root] = 1;
    for(i = 0;i < n;i++){
        currentTime += T[root][i];
        cnt++;
        if(T[root][i] > 0 && visitedTime[i] == 0){
            if(DFS2(i)){
                v2.push_back(root);
                flag = true;
            }
        }
        currentTime -= T[root][i];
        cnt--;
    }
    visitedTime[root] = 0;
    return flag;
}

int main(){
    int i;
    int t1 , t2 , way , l , t;

    cin >> n >> m;
    for(i = 0;i < m;i++){
        cin >> t1 >> t2 >> way >> l >> t;
        L[t1][t2] = l;
        T[t1][t2] = t;
        if(way == 0){
            L[t2][t1] = l;
            T[t2][t1] = t;
        }
    }
    cin >> Start >> End;
    for(i = 0;i < n;i++){
        Distance[i] = INFINITY;
        Time[i] = INFINITY;
    }
    // 初始化出发点
    Distance[Start] = 0;
    Time[Start] = 0;
    // 计算最短路径和最短时间
    Dijkstra();
    for(i = 0;i < n;i++){
        visitedDistance[i] = 0;
        visitedTime[i] = 0;
    }
    // DFS
    DFS1(Start);
    currentTime = 0;
    DFS2(Start);
    // 输出
    bool flag = true;
    if(v1.size() != v2.size()){
        flag = false;
    }
    else{
        for(i = 0;i < v1.size();i++){
            if(v1[i] != v2[i]){
                flag = false;
            }
        }
    }
    // 两个路径不一样
    if(flag){
        cout << "Distance = " << Distance[End] << "; Time = " << Time[End] << ": ";
        for(i = v1.size() - 1;i >= 0;i--){
            cout << v1[i];
            if(i != 0){
                cout << " -> ";
            }
        }
        cout << endl;
    }
    // 两个路径一样
    else{
        cout << "Distance = " << Distance[End] << ": ";
        for(i = v1.size() - 1;i >= 0;i--){
            cout << v1[i];
            if(i != 0){
                cout << " -> ";
            }
        }
        cout << endl;
        cout << "Time = " << Time[End] << ": ";
        for(i = v2.size() - 1;i >= 0;i--){
            cout << v2[i];
            if(i != 0){
                cout << " -> ";
            }
        }
        cout << endl;
    }
    return 0;
}
