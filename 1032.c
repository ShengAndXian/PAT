// PAT甲级1032 Sharing，原题地址：https://www.patest.cn/contests/pat-a-practise/1032
// 解题分析：
//  链表题。用数组来模拟链表，地址就是数组的索引，数组的内容中储存下一个节点的地址。全部内容输入完毕
//  后，先根据第一个链表的首地址遍历一遍第一个链表，所有被遍历到的节点的flag设置为1，接着根据第二个
//  链表的首地址遍历第二个链表，如果遍历时发现节点的flag为1，则直接输出地址，结束程序，否则在遍历结束
//  后输出－1。
#include<stdio.h>
#include<stdlib.h>

#define Max 100000
struct node{
    char data;
    long int next;
    int flag;
};
int main(){
    long int w1 , w2 , n;
    long int i;
    long int address , next;
    char data;
    struct node *list;

    scanf("%ld%ld%ld" , &w1 , &w2 , &n);
    list = (struct node *)malloc(sizeof(struct node) * Max);
    for(i = 0;i < n;i++){
        scanf("%ld %c %ld" , &address , &data , &next);
        list[address].data = data;
        list[address].next = next;
        list[address].flag = 0;
    }
    // 第一遍遍历
    for(i = w1;i != -1;i = list[i].next)
        // flag设置为1
        list[i].flag = 1;
    // 第二遍遍历
    for(i = w2;i != -1;i = list[i].next){
        // 遇到flag为1的节点直接输出其地址，并返回
        if(list[i].flag == 1){
            printf("%05ld" , i);
            return 0;
        }
    }
    // 遍历结束输出－1
    printf("-1");
    return 0;
}