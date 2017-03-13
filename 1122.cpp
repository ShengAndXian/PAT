// PAT甲级1122 Hamiltonian Cycle，原题地址：https://www.patest.cn/contests/pat-a-practise/1122
// 解题分析：
//  判断给出的路径是否是包含所有结点的环。
#include<iostream>
#include<vector>
using namespace std;

int main(){
    int n , m;
    int G[210][210];
    int k , q;
    int i , j;

    cin >> n >> m;
    for(i = 0;i < 210;i++){
        for(j = 0;j < 210;j++){
            G[i][j] = 0;
        }
    }
    // 建图
    for(i = 0;i < m;i++){
        int a , b;
        cin >> a >> b;
        G[a][b] = 1;
        G[b][a] = 1;
    }
    cin >> k;
    for(i = 0;i < k;i++){
        int arr[210];
        int flag[210];
        // flag用来记录结点是否被访问过
        for(j = 0;j < 210;j++){
            flag[j] = 0;
        }
        cin >> q;
        for(j = 0;j < q;j++){
            cin >> arr[j];
        }
        // 如果输入路径的结点数不等于n＋1，那一定不是符合要求的环
        if(q != n + 1){
            cout << "NO" << endl;
        }
        // 如果始末位置不同，一定不是环
        else if(arr[0] != arr[q - 1]){
            cout << "NO" << endl;
        }
        // 否则
        else{
            // 判断各点之间是否联通
            for(j = 0;j < q - 1;j++){
                if(G[arr[j]][arr[j + 1]] != 1){
                    cout << "NO" << endl;
                    break;
                }
                else{
                    // 标记结点被访问
                    flag[arr[j]] = 1;
                }
            }
            if(j < q - 1){
                continue;
            }
            // 判断所有结点是否被访问，可能有些路径会重复访问某个结点，因此要排除这种情况
            for(j = 1;j <= n;j++){
                if(flag[j] == 0){
                    cout << "NO" << endl;
                    break;
                }
            }
            // 符合条件
            if(j > n){
                cout << "YES" << endl;
            }
        }
    }
}
