// PAT甲级1051 Pop Sequence，原题地址：https://www.patest.cn/contests/pat-a-practise/1051
// 解题分析：
//  栈的FIFO性质。对于push的序列为1，2，3，....，任意pop出来的序列满足以下性质：
//  1、对于序列中的任一元素，其后如果存在比其小的值，那么该元素和这些值构成一个子序列
//  2、满足性质1的子序列是从栈中一次性pop出来的，因此序列的长度一定不大于栈的容量
//  3、栈中元素是按递增顺序存放的，因此一次性pop出来的子序列必定是递减的
//  根据这些性质就可以判断出序列是否是pop出来的了。
#include<stdio.h>
#include<stdlib.h>

int main(){
    int m , n , k;
    int i , j;
    int start , end;
    int *sequence;
    int flag;

    scanf("%d%d%d" , &m , &n , &k);
    sequence = (int *)malloc(sizeof(int) * n);
    for(i = 0;i < k;i++){
        // 假设序列是pop出来的
        flag = 1;
        for(j = 0;j < n;j++)
            scanf("%d" , &sequence[j]);
        // j = end + 1是因为如果一个子序列满足pop序列的性质，那么子序列中的其他元素也
        // 一定满足，因此不需要对这些元素进行判断
        for(j = 0;j < n;j = end + 1){
            // 从当前元素开始
            start = end = j;
            // 如果后面有元素比当前元素小
            while(end < n && sequence[end] <= sequence[start]) end++;
            end--;
            // 判断子序列长度是否大于m
            if(end - start + 1 > m)
                flag = 0;
            start++;
            // 判断序列是否是递减的
            while(start <= end){
                if(sequence[start] > sequence[start - 1]){
                    flag = 0;
                    break;
                }
                start++;
            }
        }
        if(flag)
            printf("YES\n");
        else
            printf("NO\n");
    }
}