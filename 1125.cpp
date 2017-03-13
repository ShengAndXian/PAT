// PAT甲级1125 Chain the Ropes，原题地址：https://www.patest.cn/contests/pat-a-practise/1125
// 解题分析：
//  贪心算法。先对各部分的长度按从小到大顺序排序，每一次都连接长度最小的两段，这样就可以使长度损失降到最低，
//  从而使得最后的长度最长。动态规划理论上也可以解，但需要内存太大了，不可行。
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    int n;
    int i;
    vector<double> v;

    cin >> n;
    for(i = 0;i < n;i++){
        int num;
        cin >> num;
        v.push_back(num);
    }
    sort(v.begin() , v.end());
    int ans = (v[0] + v[1]) / 2;
    for(i = 2;i < n;i++){
        ans = (ans + v[i]) / 2;
    }
    cout << (int)ans << endl;
}