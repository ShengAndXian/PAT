// PAT甲级1058 A+B in Hogwarts，原题地址：https://www.patest.cn/contests/pat-a-practise/1058
// 解题分析：
//  题目没难度，但有些坑。输入的时候每一位上的值不一定在规定的范围内，因此先全部转换成Kunt，然后相加，再转换
//  成标准形式。
#include<stdio.h>

int main(){
    long num1 , num2 , num3 , num4 , num5 , num6;
    long long res;
    long long t;

    scanf("%ld.%ld.%ld%ld.%ld.%ld" , &num1 , &num2 , &num3 , &num4 , &num5 , &num6);
    res = (num1 + num4) * 17 * 29 + (num2 + num5) * 29 + (num3 + num6);
    t = res / (17 * 29);
    res %= 17 * 29;
    printf("%lld.%lld.%lld\n" , t , res / 29 , res % 29);
}