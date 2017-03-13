// PAT甲级1116 Come on! Let's C，原题地址：https://www.patest.cn/contests/pat-a-practise/1116
// 解题分析：
//  水题，不解释。
#include<iostream>
#include<cstdio>
using namespace std;

int arr[10000];
int flag[10000];

bool IsPrime(int n){
    int i;

    if(n == 1)
        return false;
    for(i = 2;i < n;i++){
        if(n % i == 0)
            return false;
    }
    return true;
}

int main(){
    int n , k;
    int i;
    int id;
    int cnt = 1;

    cin >> n;
    for(i = 0;i < n;i++){
        cin >> id;
        arr[id] = cnt;
        cnt++;
    }

    cin >> k;
    for(i = 0;i < k;i++){
        cin >> id;
        printf("%04d: " , id);
        if(flag[id] == 1){
            cout << "Checked" << endl;
        }
        else if(arr[id] == 0){
            cout << "Are you kidding?" << endl;
        }
        else{
            flag[id] = 1;
            if(arr[id] == 1){
                cout << "Mystery Award" << endl;
            }
            else if(IsPrime(arr[id])){
                cout << "Minion" << endl;
            }
            else{
                cout << "Chocolate" << endl;
            }
        }
    }
}