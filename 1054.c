// PAT甲级 1054The Dominant Color，原题地址：https://www.patest.cn/contests/pat-a-practise/1054
// 解题分析：
//  数组开的足够大即可，输入的时候对应的计数加一，如果超过一半就直接输出。
#include<stdio.h>

long color[20000000];

int main(){
    long m , n;
    long i;
    long temp;

    scanf("%ld%ld" , &m , &n);
    for(i = 0;i < m * n;i++){
        scanf("%ld" , &temp);
        color[temp]++;
        if(color[temp] > m * n / 2){
            printf("%ld\n" , temp);
            break;
        }
    }
    return 0;
}