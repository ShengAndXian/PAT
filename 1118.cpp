// PAT甲级1118 Birds in Forest，原题地址：https://www.patest.cn/contests/pat-a-practise/1118
// 解题分析：
//  考察并查集。
#include<iostream>
using namespace std;

int Find(int *arr , int n){
    if(arr[n] == -1){
        return n;
    }
    return arr[n] = Find(arr , arr[n]);
}

void Union(int *arr , int a , int b){
    arr[b] = a;
}

int main(){
    int n , k , q;
    int i , j;
    int root1 , root2;
    int unionSet[11000];
    int max = 0;
    int cnt = 0;

    for(i = 0;i < 11000;i++){
        unionSet[i] = -1;
    }
    cin >> n;
    for(i = 0;i < n;i++){
        cin >> k;
        int id;
        cin >> id;
        if(id > max){
            max = id;
        }
        root1 = Find(unionSet , id);
        for(j = 1;j < k;j++){
            cin >> id;
            if(id > max){
                max = id;
            }
            root2 = Find(unionSet , id);
            if(root1 != root2){
                Union(unionSet , root1 , root2);
            }
        }
    }   
    for(i = 1;i <= max;i++){
        if(unionSet[i] == -1){
            cnt++;
        }
    }
    cout << cnt << " " << max << endl;
    cin >> q;
    for(i = 0;i < q;i++){
        int a , b;
        cin >> a >> b;
        root1 = Find(unionSet , a);
        root2 = Find(unionSet , b);
        if(root1 == root2){
            cout << "Yes" << endl;
        }
        else{
            cout << "No" << endl;
        }
    }
    return 0;
}