// PAT甲级1048 Find Coins，原题地址：https://www.patest.cn/contests/pat-a-practise/1048
// 解题分析：
//  题目的意思很简单，给定一个序列和一个值，从序列中找到两个数，这两个数相加的和等于给定的值。首先要对整个
//  序列进行升序排序，然后i从0开始，j从n－1开始，如果两变量对应的值相加大于给定的值，则j减一，如果小于，则
//  i加一，如果等于，则直接输出并返回。整个循环在i大于等于j时结束，如果循环正常结束，说明没有找到对应的两个数
//  输出No Solution。
#include<stdio.h>
#include<stdlib.h>

int compare(const void *a , const void *b){
    return (*(long *)a) - (*(long *)b);
}
int main(){
    long n , m;
    long i , j;
    long *arr;

    scanf("%ld%ld" , &n , &m);
    arr = (long *)malloc(sizeof(long) * n);
    for(i = 0;i < n;i++)
        scanf("%ld" , &arr[i]);
    // 排序
    qsort(arr , n , sizeof(long) , compare);
    // 从头和尾同时开始
    for(i = 0 , j = n - 1;i < j;){
        // 如果两个数相加大于m
        if(arr[i] + arr[j] > m)
            j--;
        // 如果两个数相加小于m
        else if(arr[i] + arr[j] < m)
            i++;
        // 如果两个数相加等于m
        else{
            printf("%ld %ld\n" , arr[i] , arr[j]);
            return 0;
        }
    }
    printf("No Solution\n");
}