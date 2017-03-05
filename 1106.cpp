// PAT甲级1106 Lowest Price in Supply Chain，原题地址：https://www.patest.cn/contests/pat-a-practise/1106
// 解题分析：
//  简单的DFS。用DFS计算出每个零售商的溢价率，取最低的即可，同时统计最低溢价率的零售商个数。输出时用溢价率乘上原始价格即可。
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;

vector<vector<long> > G;
long flag[110000];
long n;
long cnt;
double p , r;
double res = 100000;

void DFS(long index , double rate){
    if(index != 0)
        rate = rate * (1 + r / 100);
    if(flag[index]){
        if(rate < res){
            res = rate;
            cnt = 1;
        }
        else if(rate == res){
            cnt++;
        }
        return;
    }
    for(int i = 0;i < G[index].size();i++)
        DFS(G[index][i] , rate);
}
int main(){
    long k , i , j;
    vector<long> v;

    cin >> n >> p >> r;
    for(i = 0;i < n;i++){
        cin >> k;
        if(k == 0)
            flag[i] = 1;
        v.clear();
        for(j = 0;j < k;j++){
            long t;
            cin >> t;
            v.push_back(t);
        }
        G.push_back(v);
    }
    DFS(0 , 1);
    printf("%.4lf %ld\n" , res * p , cnt);   
}