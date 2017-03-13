// PAT甲级1114 Integer Set Partition，原题地址：https://www.patest.cn/contests/pat-a-practise/1113
// 解题分析：
//  DFS的简单应用。
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#define INFINITY 10000000
#define Max 11000
using namespace std;

struct record{
    int id;
    int cnt;
    double avgSets;
    double avgArea;
};

vector<int> G[Max];
int visited[Max];
int estate[Max];
int area[Max];
int cntFamily , cntPeople;
int totalSet , totalArea;
int minId;
int n;

void DFS(int root){
    int i;

    if(root == -1)
        return;
    visited[root] = 1;
    totalSet += estate[root];
    totalArea += area[root];
    cntPeople++;
    if(root < minId)
        minId = root;
    for(i = 0;i < G[root].size();i++){
        if(visited[G[root][i]] == 0){
            DFS(G[root][i]);
        }
    }
}

bool cmp(struct record a , struct record b){
    if(a.avgArea > b.avgArea)
        return true;
    else if(a.avgArea < b.avgArea)
        return false;
    else
        return a.id < b.id;
}

int main(){
    int i;
    int id , fid , mid , k , cid;
    int s , a;
    vector<struct record> t;

    cin >> n;
    // 输入
    for(i = 0;i < n;i++){
        cin >> id >> fid >> mid >> k;
        G[id].push_back(fid);
        G[id].push_back(mid);
        if(fid != -1)
            G[fid].push_back(id);
        if(mid != -1)
            G[mid].push_back(id);
        for(int j = 0;j < k;j++){
            cin >> cid;
            G[id].push_back(cid);
            G[cid].push_back(id);
        }
        cin >> s >> a;
        estate[id] = s;
        area[id] = a;
    }
    // 遍历
    for(i = 0;i < Max;i++){
        minId = INFINITY;
        totalSet = 0;
        totalArea = 0;
        cntPeople = 0;
        // 如果未被访问并且与其他点相连
        if(visited[i] == 0 && !G[i].empty()){
            DFS(i);
            cntFamily++;
            struct record R;
            R.id = minId;
            R.cnt = cntPeople;
            R.avgSets = (double)totalSet / cntPeople;
            R.avgArea = (double)totalArea / cntPeople;
            t.push_back(R);
        }
    }
    sort(t.begin() , t.end() , cmp);
    // 输出
    printf("%d\n" , cntFamily);
    for(i = 0;i < t.size();i++){
        printf("%04d %d %.3lf %.3lf\n" , t[i].id , t[i].cnt , t[i].avgSets , t[i].avgArea);
    }
}