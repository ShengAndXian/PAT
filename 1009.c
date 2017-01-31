// PAT甲级1009 Product of Polynomials，原题地址：https://www.patest.cn/contests/pat-a-practise/1009
// 解题分析：
//  多项式乘法运算。多项式用数组处理会非常方便，指数做索引，内容为系数。先用一个数组储存第一次输入的多项式，第二次输入的
//  多项式不需要储存，直接和第一个多项式进行计算即可。计算结果放入另一个数组。第二次输入时，每输入一项，就遍历一次第一个
//  多项式，以两指数之和做索引，系数之积做内容，更新结果数组。最后遍历一次结果数组，计算项数，再和多项式一起输出即可。
#include<stdio.h>

#define Max 10001
int main(){
    double polynomial[Max];
    double result_polynomial[Max];
    int K;
    int i , j;
    int exponent;
    double coefficient;
    int count = 0;

    // 初始化
    for(i = 0;i < Max;i++){
        polynomial[i] = 0;
        result_polynomial[i] = 0;
    }

    // 输入第一个多项式
    scanf("%d" , &K);
    for(i = 0;i < K;i++){
        scanf("%d %lf" , &exponent , &coefficient);
        polynomial[exponent] = coefficient;
    }
    scanf("%d" , &K);
    // 输入第二个多项式并遍历数组
    for(i = 0;i < K;i++){
        scanf("%d %lf" , &exponent , &coefficient);
        for(j = 0;j < Max;j++){
            if(polynomial[j] != 0){
                // 以两指数之和为索引，两系数之积为内容
                result_polynomial[j + exponent] += polynomial[j] * coefficient;
            }
        }
    }
    // 计算项数
    for(i = 0;i < Max;i++){
        if(result_polynomial[i] != 0)
            count++;
    }
    // 输出
    printf("%d" , count);
    for(i = Max - 1;i >= 0;i--){
        if(result_polynomial[i] != 0){
            printf(" %d %.1lf" , i , result_polynomial[i]);
        }
    }
}