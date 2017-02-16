// PAT甲级1053 Path of Equal Weight，原题地址：https://www.patest.cn/contests/pat-a-practise/1053
// 解题分析：
//  DFS的应用。用一个结构体数组储存整棵树，id作为数组索引，每一个结构体内有一个数组用来纪录孩子节点的id。题目的难点
//  在于输出的顺序，根据题目的意思，有两个序列，从头开始比较，两数相等则继续往后比较，直到一者比另一者大，那么数字较大
//  的序列必须先于数字较小的序列输出。为了在DFS的时候直接能够按照顺序输出，我们需要对每一个节点的子节点按权值从大到小
//  排序，这样每次我们都优先搜索权值较大的节点，如果最终路径上所有节点的权值和等于s，则直接输出路径上节点的权值即可。
#include<stdio.h>
#include<stdlib.h>

struct node{
    long w;
    long child[100];
    long cnt;
};

void DFS(long root);
int compare(const void *a , const void *b);

long n , m , s;
// 纪录当前路径上所有节点的权值和
long currentWeight = 0;
// 用来纪录路径上节点的权值
long stack[100];
long top = -1;
// 结构体数组
struct node T[100];

int main(){
    long i , j , k;
    long pid , cid;

    scanf("%ld%ld%ld" , &n , &m , &s);
    for(i = 0;i < n;i++){
        scanf("%ld" , &T[i].w);
        T[i].cnt = 0;
    }
    for(i = 0;i < m;i++){
        scanf("%ld%ld" , &pid , &k);
        for(j = 0;j < k;j++){
            scanf("%ld" , &cid);
            // 纪录子节点的id
            T[pid].child[T[pid].cnt++] = cid;
        }
        // 对子节点排序
        qsort(T[pid].child , T[pid].cnt , sizeof(long) , compare);
    }
    // 深度优先搜索
    DFS(0);
}

void DFS(long root){
    long flag = 0;
    long i;

    // 更新当前路径权值和
    currentWeight += T[root].w;
    // 如果大于s，直接返回
    if(currentWeight > s){
        currentWeight -= T[root].w;
        return;
    }
    // 将当前节点的权值储存起来
    stack[++top] = T[root].w;
    // 如果是叶子节点
    if(T[root].cnt == 0){
        // 判断权值和是否为s
        if(currentWeight == s){
            // 如果是，则输出
            for(i = 0;i <= top;i++){
                printf("%ld" , stack[i]);
                if(i != top)
                    printf(" ");
            }
            printf("\n");
        }
    }
    // 如果是非叶子节点
    else{
        // 继续深度搜索
        for(i = 0;i < T[root].cnt;i++)
            DFS(T[root].child[i]);
    }
    // 从当前节点返回时，要将当前节点的权值从数组中删除，并恢复路径的权值和
    top--;
    currentWeight -= T[root].w;
    return;
}

int compare(const void *a , const void *b){
    return T[(*(long *)b)].w - T[(*(long *)a)].w;
}