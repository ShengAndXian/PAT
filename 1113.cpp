// PAT甲级1113 Integer Set Partition，原题地址：https://www.patest.cn/contests/pat-a-practise/1113
// 解题分析：
//  水题。。。。。不解释了。
#include<iostream>
#include<algorithm>
using namespace std;


int main(){
    int *arr;
    int n;
    int i;
    int pre = 0;

    arr = new int[110000];
    cin >> n;
    for(i = 0;i < n;i++){
        cin >> arr[i];
    }
    sort(arr , arr + n);
    for(i = 0;i < n;i++){
        arr[i] += pre;
        pre = arr[i];
    }
    if(n % 2 == 0){
        cout << "0 ";
    }
    else{
        cout << "1 ";
    }
    cout << arr[n - 1] - 2 * arr[n / 2 - 1] << endl;
}