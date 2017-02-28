// PAT甲级1090 Highest Price in Supply Chain，原题地址：https://www.patest.cn/contests/pat-a-practise/1090
// 解题分析：
//  题目其实很简单，用DFS遍历一遍算出最高的溢价率就可以了。但问题在于花费的时间，每次搜索到一个点，我们都需要找到这个点的子节点，
//  如果我们每次都通过简单遍历来得到子节点，那么时间复杂度为O(N^2)，提交上去会超时。因此，我们需要换一种方法来查找，最简单的就是
//  二分查找，使用二分查找能将时间复杂度降低到O(NlogN)，可以通过测试。
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

typedef long long ll;
struct node{
    ll v;
    ll p;
};

ll n;
double p , r;
vector<struct node> c;
double Max;
ll cnt;
ll t;

// 二分查找
ll BinarySearch(ll value){
    ll start = 0 , end = n - 1 , mid;

    while(start <= end){
        mid = (start + end) / 2;
        if(c[mid].v == value)
            return mid;
        else if(c[mid].v > value)
            end = mid - 1;
        else
            start = mid + 1;
    }
    return -1;
}

// 深度搜索
void DFS(ll root , double rate){
    ll i;
    ll index;
    ll start , end;
    bool flag = false;

    // 根节点的溢价率为0，因此不需要计算
    if(root != c[0].p)
        rate *= (1 + r / 100);
    // 找到子节点在c中的索引
    index = BinarySearch(root);
    // 没找到说明是零售商
    if(index < 0){
        // 比较溢价率和最大溢价率，比它大就把它更新
        if(rate > Max){
            Max = rate;
            cnt = 1;
        }
        // 跟它相等计数加一
        else if(rate == Max)
            cnt++;
        return;
    }
    // 获取所有字节点
    start = index - 1;
    end = index + 1;
    while(start >= 0 && c[start].v == root) start--;
    while(end < n && c[end].v == root) end++;
    // 继续搜索
    for(i = start + 1;i < end;i++)
        DFS(c[i].p , rate);
}

bool cmp(struct node a , struct node b){
    return a.v < b.v;
}

int main(){
    ll i;
    ll num;
    struct node R;

    cin >> n >> p >> r;
    for(i = 0;i < n;i++){
        cin >> num;
        R.v = num;
        R.p = i;
        c.push_back(R);
    }
    // 排序，以便使用二分查找
    sort(c.begin() , c.end() , cmp);
    DFS(c[0].p , 1);
    printf("%.2lf %lld\n" , Max * p , cnt);
}