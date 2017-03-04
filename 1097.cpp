// PAT甲级1097 Deduplication on a Linked List，原题地址：https://www.patest.cn/contests/pat-a-practise/1097
// 解题分析：
//  链表题。从头节点开始遍历整个链表，遇到一个节点，先在check里查询之前是否有相同绝对值的节点出现，如果没有则将该节点加入到第一个
//  结果数组里，并且将对应的check数组的值加一表示该绝对值出现过了，如果有则将该节点加入到第二个结果数组。最后依次输出即可。
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;

struct node{
    long address;
    long key;
    long next;
};

struct node arr[110000];
vector<struct node> res1;
vector<struct node> res2;
long check[11000];
long head , n;

int main(){
    long i;

    cin >> head >> n;
    for(i = 0;i < n;i++){
        long address , key , next;
        cin >> address >> key >> next;
        arr[address].address = address;
        arr[address].key = key;
        arr[address].next = next;
    }
    // 遍历链表
    for(i = head;i != -1;i = arr[i].next){
        long t = arr[i].key > 0 ? arr[i].key : -arr[i].key;
        // 如果没有出翔
        if(check[t] == 0){
            check[t]++;
            res1.push_back(arr[i]);
        }
        // 如果出现过
        else{
            res2.push_back(arr[i]);
        }
    }
    // 输出
    for(i = 0;i < res1.size();i++){
        printf("%05ld %ld " , res1[i].address , res1[i].key);        
        if(i != res1.size() - 1)
            printf("%05ld\n" , res1[i + 1].address);                
        else
            printf("-1\n");
    }
    for(i = 0;i < res2.size();i++){
        printf("%05ld %ld " , res2[i].address , res2[i].key);        
        if(i != res2.size() - 1)
            printf("%05ld\n" , res2[i + 1].address);                
        else    
            printf("-1\n");
    }
}