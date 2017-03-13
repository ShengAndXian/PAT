// PAT甲级1120 Friend Numbers，原题地址：https://www.patest.cn/contests/pat-a-practise/1120
// 解题分析：
//  水题，不解释啦。。
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int GetId(int n){
    int sum = 0;

    while(n > 0){
        sum += n % 10;
        n /= 10;
    }
    return sum;
}
int main(){
    int arr[100];
    int i;
    int n;
    int t;
    int cnt = 0;
    vector<int> v;

    for(i = 0;i < 100;i++){
        arr[i] = 0;
    }
    cin >> n;
    for(i = 0;i < n;i++){
        int num;
        cin >> num;
        t = GetId(num);
        arr[t]++;
    }
    for(i = 0;i < 100;i++){
        if(arr[i] > 0){
            cnt++;
            v.push_back(i);
        }
    }
    sort(v.begin() , v.end());
    cout << cnt << endl;
    for(i = 0;i < v.size();i++){
        cout << v[i];
        if(i != v.size() - 1)
            cout << " ";
    }
    cout << endl;
}