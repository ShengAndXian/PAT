// PAT甲级1078 Hashing，原题地址：https://www.patest.cn/contests/pat-a-practise/1078
// 解题分析：
//  哈希表的平方探测法。首先简单处理一下素数，更新表的大小。然后对每个输入的值，用平方探测找到对应的
//  位置，返回位置的索引，如果没找到返回－1。平方探测最多探测m次，m次之内没探测到就是没有位置。
#include<iostream>
#include<vector>
using namespace std;
#define Max 11000

int hashTable[Max];

// 判断素数
bool IsPrime(int n){
    int i;
    if(n == 0 || n == 1)
        return false;
    for(i = 2;i < n;i++)
        if(n % i == 0)
            return false;
    return true;
}

int Insert(int n , int m){
    int h;

    h = n % m;
    // 有空位的话插入即可
    if(hashTable[h] == 0){
        hashTable[h] = 1;
        return h;
    }
    else{
        int temp = h;
        // 平方探测，最多探测m次
        for(int i = 1;i < m;i++){
            h = (temp + i * i) % m;
            if(hashTable[h] == 0){
                hashTable[h] = 1;
                return h;
            }
        }
        return -1;
    }
}
int main(){
    int m , n;
    int i;
    int num;
    int index;
    vector<int> v;
    
    cin >> m >> n;
    while(!IsPrime(m))
        m++;
    for(i = 0;i < n;i++){
        cin >> num;
        // 插入哈希表
        index = Insert(num , m);
        v.push_back(index);
    }
    // 输出
    for(vector<int>::iterator it = v.begin();it != v.end();it++){
        if(it != v.begin())
            cout << " ";
        if(*it == -1)
            cout << "-";
        else
            cout << *it;
    }
    cout << endl;
    return 0;
}

