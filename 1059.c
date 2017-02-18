// PAT甲级1059 Prime Factors，原题地址：https://www.patest.cn/contests/pat-a-practise/1059
// 解题分析：
//  根据算数基本定理，任何大于1的自然数都可以写成质数相乘的形式，因此i从2开始，如果n能够被i整除，j加一，
//  n变为i整除n，接着判断是否能被i整除，一直执行此步骤，直到不能被整除为止，如果j大于0，说明i是质因数，
//  按照规定格式输出即可。
#include<stdio.h>

int main(){
    long n;
    long i , j;
    long flag = 0;

    scanf("%ld" , &n);
    printf("%ld=" , n);
    // 从2开始
    for(i = 2;i <= n;i++){
        // 如果能被i整除，j加一，n变为n/i
        for(j = 0;n % i == 0;n /= i) j++;
        // 如果j大于0说明n能被i整除
        if(j){
            if(flag)
                printf("*");
            else
                flag = 1;
            if(j == 1)
                printf("%ld" , i);
            else    
                printf("%ld^%ld" , i , j);
        }
    }
    // flag为0，对应n等于1的情况
    if(!flag)
        printf("%ld" , n);
    printf("\n");
}