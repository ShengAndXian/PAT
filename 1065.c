// PAT甲级1065 A+B and C (64bit)，原题地址：https://www.patest.cn/contests/pat-a-practise/1065
// 解题分析：
//  利用溢出解决问题。如果两个数一个为正数，一个为负数，则两数相加一定不会溢出。如果两个数均为正数，则可能产生溢出，
//  溢出后的值在区间[-2^63 , -2]内。如果两数均为负值，则也可能产生溢出，溢出后的值的范围在区间[0 , 2^63 - 1]。
//  正数相加溢出，说明结果一定比c大，负数相加溢出，说明结果一定比c小。如果不溢出，则直接判断大小。
#include<stdio.h>

int main(){
    long long a , b , c;
    long long sum;
    int t , i;

    scanf("%d" , &t);
    for(i = 1;i <= t;i++){
        scanf("%lld%lld%lld" , &a , &b , &c);
        printf("Case #%d: " , i);
        sum = a + b;
        // 一正一负
        if((a > 0 && b < 0) || (a < 0 && b > 0)){
            if(sum > c)
                printf("true\n");
            else
                printf("false\n");
        }
        // 两个正数
        else if(a > 0 && b > 0){
            // 判断溢出
            if(sum < 0)
                printf("true\n");
            else if(sum > c)
                printf("true\n");
            else
                printf("false\n");
        }
        // 两个负数
        else if(a < 0 && b < 0){
            // 判断溢出，注意负数相加溢出后可以取到0
            if(sum >= 0)
                printf("false\n");
            else if(sum > c)
                printf("true\n");
            else
                printf("false\n");
        }
        // 有一数为0
        else{
            if(sum > c)
                printf("true\n");
            else
                printf("false\n");
        }
    }
}