// PAT甲级1074 Reversing Linked List，原题地址：https://www.patest.cn/contests/pat-a-practise/1074
// 解题分析：
//  用数组储存链表，通过头节点遍历链表，需要注意的是不是所有输入的节点都在链表中，每访问一个节点，将其放入temp数组中，
//  当遍历k个节点后，将temp数组中的数据翻转后放入res数组，清空temp数组，重新计算访问过的节点数。遍历完成后，需要检查
//  是否存在多余的节点，如果存在，将它们按原来顺序放入res数组。最后输出即可。
#include<iostream>
#include<stdio.h>
using namespace std;
#define Max 100000

struct node{
    long data;
    long next;
};

struct record{
    long data;
    long address;
};

struct node L[Max];
struct record temp[Max];
struct record res[Max];

int main(){
    long head , n , k;
    long ad , d , next;
    long i , j;
    long cnt1 = 0 , cnt2 = 0 , cnt3 = 0;

    cin >> head >> n >> k;
    for(i = 0;i < n;i++){
        cin >> ad >> d >> next;
        L[ad].data = d;
        L[ad].next = next;
    }
    for(i = head;i != -1;i = L[i].next){
        // 访问过的节点数量加一
        cnt1++;
        // 将节点放入temp数组
        temp[cnt2].data = L[i].data;
        temp[cnt2].address = i;
        cnt2++;
        // 如果访问了k个节点
        if(cnt1 == k){
            // 将temp数组的数据翻转后放入res数组
            for(j = cnt2 - 1;j >= 0;j--)
                res[cnt3++] = temp[j];
            // 清空temp数组，并重新计算已访问的节点数
            cnt1 = cnt2 = 0;
        }
    }
    // 如果有剩余节点
    if(cnt1 < k){
        for(j = 0;j < cnt2;j++)
            res[cnt3++] = temp[j];
    }
    // 输出
    for(i = 0;i < cnt3;i++){
        printf("%05ld %ld " , res[i].address , res[i].data);
        if(i != cnt3 - 1)
            printf("%05ld\n" , res[i + 1].address);
        else
            printf("-1\n");
    }
}