// PAT甲级1117 Eddington Numbe，原题地址：https://www.patest.cn/contests/pat-a-practise/1117
// 解题分析：
//  从大到小排序，取满足a[i] > i的最大的i。
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

bool cmp(int a , int b){
    return a > b;
}
int main(){
    int n;
    int i;
    int arr[100000];

    cin >> n;
    for(i = 1;i <= n;i++){
        cin >> arr[i];
    }
    sort(arr + 1 , arr + n + 1 , cmp);
    for(i = 1;i <= n && arr[i] > i;i++) ;
    cout << i - 1 << endl;
    return 0;
}