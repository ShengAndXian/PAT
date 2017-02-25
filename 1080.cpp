// PAT甲级1080 Graduate Admission，原题地址：https://www.patest.cn/contests/pat-a-practise/1080
// 解题分析：
//  这题不想解释了，排序模拟一下即可。
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int g[40000][2] , c[40000][5] , cnt[100];
long ans[40000];
vector<long> s[100];
long n , m , k;

bool cmp(long a , long b){
    return g[a][1] == g[b][1] ? g[a][0] > g[b][0] : g[a][1] > g[b][1];
}

int main(){
    long i , j;

    cin >> n >> m >> k;
    for(i = 0;i < m;i++)
        cin >> cnt[i];
    for(i = 0;i < n;i++){
        cin >> g[i][0] >> g[i][1];
        g[i][1] += g[i][0];
        for(j = 0;j < k;j++)
            cin >> c[i][j];
        ans[i] = i;
    }
    // 排序
    sort(ans , ans + n , cmp);
    // 一个一个处理
    for(i = 0;i < n;i++){
        // 处理每个志愿
        for(j = 0;j < k;j++){
            int x = c[ans[i]][j];
            // 有空位
            if(s[x].size() < cnt[x]){
                s[x].push_back(ans[i]);
                break;
            }
            else{
                int temp = s[x][s[x].size() - 1];
                // 排名相等
                if(g[temp][1] == g[ans[i]][1] && g[temp][0] == g[ans[i]][0]){
                    s[x].push_back(ans[i]);
                    break;
                }
            }
        }
    }
    // 输出
    for(i = 0;i < m;i++){
        if(s[i].size() == 0)
            cout << endl;
        else{
            // 排序
            sort(s[i].begin() , s[i].end());
            for(j = 0;j < s[i].size();j++){
                if(j != 0)
                    cout << " ";
                cout << s[i][j];
            }
            cout << endl;
        }
    }
}