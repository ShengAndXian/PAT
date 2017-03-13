// PAT甲级1120 Damn Single，原题地址：https://www.patest.cn/contests/pat-a-practise/1121
// 解题分析：
//  简单二分查找。
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdio>
using namespace std;

bool IsSingle(int *arr , int n , int m){
    int start = 0 , end = m - 1;
    int mid;

    while(start <= end){
        mid = (start + end) / 2;
        if(arr[mid] == n){
            return false;
        }
        else if(n < arr[mid]){
            end = mid - 1;
        }
        else{
            start = mid + 1;
        }
    }
    return true;
}

int main(){
    int flag[110000];
    int arr[11000];
    int n , m;
    int i;
    vector<int> v;

    for(i = 0;i < 110000;i++){
        flag[i] = -1;
    }
    cin >> n;
    for(i = 0;i < n;i++){
        int id1 , id2;
        cin >> id1 >> id2;
        flag[id1] = id2;
        flag[id2] = id1;
    }
    cin >> m;
    for(i = 0;i < m;i++){
        cin >> arr[i];
    }
    sort(arr , arr + m);
    for(i = 0;i < m;i++){
        if(flag[arr[i]] == -1){
            v.push_back(arr[i]);
        }
        else{
            if(IsSingle(arr , flag[arr[i]] , m)){
                v.push_back(arr[i]);
            }
        }
    }
    cout << v.size() << endl;
    for(i = 0;i < v.size();i++){
        printf("%05d" , v[i]);
        if(i != v.size() - 1){
            printf(" ");
        }
    }
}