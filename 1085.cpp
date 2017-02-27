// PAT甲级1085 Perfect Sequence，原题地址：https://www.patest.cn/contests/pat-a-practise/1085
// 解题分析：
//  用两个指针循环，可以得到所有符合条件的序列，选择其中最长的即可。
#include<iostream>
#include<algorithm>
using namespace std;
#define Max 100000

int main(){
    long n , p;
    long arr[Max];
    long i , j;
    long ans = 0;

    cin >> n >> p;
    for(i = 0;i < n;i++)
        cin >> arr[i];
    sort(arr , arr + n);
    for(i = 0;i < n;i++){
        while(j < n && arr[j] <= arr[i] * p) j++;
        ans = ans > j - i ? ans : j - i;
    }
    cout << ans << endl;
}