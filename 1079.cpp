// PAT甲级1079 Total Sales of Supply Chain，原题地址：https://www.patest.cn/contests/pat-a-practise/1079
// 解题分析：
//  DFS。从根节点出发，深度优先搜索整张图，就可以计算出每个节点卖出商品时比原价高多少百分比。然后将每个零售商的商品数量乘以
//  单价再乘上对应的溢价百分比，就可以得到最终的销售额了。
#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;
#define Max 110000

struct record{
    long id;
    double amount;
};

vector< vector<long> > G;
vector<struct record> retailers;
long n;
double p , r;
double rate[Max];

// 深度优先搜索
void DFS(long n , double currentRate){
    double temp;
    
    // 供应商卖出商品时就是以原价卖出，不加价
    if(n == 0)
        temp = 1;
    // 其他商户都要加价
    else
        temp = currentRate * (1 + r / 100);
    // 储存溢价比
    rate[n] = temp;
    // 如果是零售商则直接返回
    if(G[n].size() == 0)
        return;
    // 如果是经销商，则继续搜索
    for(vector<long>::iterator it = G[n].begin();it != G[n].end();it++)
        DFS(*it , temp);
}
int main(){
    long i , j;
    long k , id;
    double amount;
    double res = 0;
    vector<long> temp;
    struct record R;

    cin >> n >> p >> r;
    for(i = 0;i < n;i++){
        cin >> k;
        // 储存零售商信息
        if(k == 0){
            cin >> amount;
            R.id = i;
            R.amount = amount;
            retailers.push_back(R);
        }
        // 储存整个销售网络
        for(j = 0;j < k;j++){
            cin >> id;
            temp.push_back(id);
        }
        G.push_back(temp);
        temp.clear();
    }
    // 搜索
    DFS(0 , 1);
    // 计算输出
    for(vector<struct record>::iterator it = retailers.begin();it != retailers.end();it++)
        res += (*it).amount * p * rate[(*it).id];
    printf("%.1f\n" , res);
}   