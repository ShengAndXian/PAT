// PAT甲级1093 Count PAT's，原题地址：https://www.patest.cn/contests/pat-a-practise/1093
// 解题分析：
//  动态规划问题。假设我们有一个编号为0到n的序列，长度为n+1，我们从最后一个元素开始考虑，如果这个元素是
//  T，那么PAT[n + 1]（表示长度为n+1的序列的PAT的个数）等于PAT[n]加上PA[n]（表示长度为n的序列的PA的
//  个数）。如果这个元素是A，那么PA[n + 1]等于PA[n]加上P[n]（表示长度为n的序列的P的个数）。如果这个元素
//  是P，那么P[n + 1]等于P[n] + 1。有了这些关系，我们就可以自底向上求解出长度为n+1时PAT的个数。另外，可以
//  在输入的时候直接判断出最后一个T的位置，这样能减少一些不必要的运算。
#include<iostream>
#define Max 110000
using namespace std;
typedef long long ll;

char s[Max];
ll P[Max];
ll PA[Max];
ll PAT[Max];
ll n;

int main(){
    ll i;
    char c;

    i = 0;
    while((c = getchar()) != '\n'){
        s[i] = c;
        // 得到最后一个T的位置
        if(c == 'T')
            n = i;
        i++;
    }
    // 自底向上求解
    for(i = 1;i <= n + 1;i++){
        // 元素为P
        if(s[i - 1] == 'P'){
            P[i] = P[i - 1] + 1;
            PA[i] = PA[i - 1];
            PAT[i] = PAT[i - 1];
        }
        // 元素为A
        if(s[i - 1] == 'A'){
            PA[i] = PA[i - 1] + P[i - 1];
            P[i] = P[i - 1];
            PAT[i] = PAT[i - 1];
        }
        // 元素为T
        if(s[i - 1] == 'T'){
            PAT[i] = PAT[i - 1] + PA[i - 1];
            P[i] = P[i - 1];
            PA[i] = PA[i - 1];
        }
    }
    cout << PAT[n + 1] % 1000000007;
}