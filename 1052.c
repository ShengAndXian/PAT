// PAT甲级1052 Linked List Sorting，原题地址：https://www.patest.cn/contests/pat-a-practise/1052
// 解题分析：
//  链表题。先构建一个结构体数组，然后用数组模拟链表，地址作为数组的索引。输入完成后，根据头节点的地址遍历整个链表，
//  将链表中的节点的flag设为1，并纪录总节点数。这么做的原因是输入的节点有些并不在链表中。不在链表中的节点的flag为
//  0。然后对整个数组排序，flag为1的在前，为0的在后，flag为1的序列再按key值排序。之后输出即可。如果头节点的地址为
//  －1，输出0 －1。
#include<stdio.h>
#include<stdlib.h>

struct node{
    long address;
    long key;
    long next;
    long flag;
};

int compare(const void *a , const void *b){
    struct node m , n;
    m = *(struct node *)a;
    n = *(struct node *)b;
    // 先根据flag排序
    if(m.flag == 0 || n.flag == 0)
        return n.flag - m.flag;
    // 如果flag都为1，则按key值排序
    else
        return m.key - n.key;
}

int main(){
    long n , head;
    long address , key , next;
    long i;
    long cnt = 0;
    struct node list[100000];

    scanf("%ld%ld" , &n , &head);
    for(i = 0;i < n;i++){
        scanf("%ld%ld%ld" , &address , &key , &next);
        list[address].address = address;
        list[address].key = key;
        list[address].next = next;
    }
    for(i = 0;i < 100000;i++)
        list[i].flag = 0;
    // 遍历链表
    for(i = head;i != -1;i = list[i].next){
        // 节点的flag设为1
        list[i].flag = 1;
        // 计数
        cnt++;
    }
    // 排序
    qsort(list , 100000 , sizeof(struct node) , compare);
    // 如果头地址是－1
    if(cnt == 0){
        printf("0 -1\n");
        return 0;
    }
    // 输出
    printf("%ld %05ld\n" , cnt , list[0].address);
    for(i = 0;i < cnt;i++){
        if(i != cnt - 1)
            printf("%05ld %ld %05ld\n" , list[i].address , list[i].key , list[i + 1].address);
        else
            printf("%05ld %ld %d\n" , list[i].address , list[i].key , -1);
    }
}