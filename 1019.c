// PAT甲级1019 General Palindromic Number，原题地址：General Palindromic Number
// 解题分析：
//  题目很简单。首先将所给十进制数转换为对应base下的数，将每一位存在数组，然后从头和尾开始比较即可，如有
//  不相等的数则flag为0，否则为1.然后输出对应结果即可。
#include<stdio.h>

int main(){
    long long n , b;
    long long arr[50];
    int i  = 0, j;
    int tmp;
    int flag = 1;

    scanf("%lld %lld" , &n , &b);
    // n为0时直接当做特殊情况输出即可
    if(n == 0){
        printf("Yes\n0");
        return 0;
    }
    // 将十进制数转换成对应base的数，并存入数组
    while(n != 0){
        arr[i++] = n % b;
        n /= b;
    }
    j = 0;
    i = i -1;
    tmp = i;
    // 从头和尾开始比较
    while(j <= i){
        // 如有不相等的数则flag等于0
        if(arr[j] != arr[i])
            flag = 0;
        j++;
        i--;
    }
    // flag为1则输出yes
    if(flag == 1)
        printf("Yes\n");
    // flag为0则输出no
    else
        printf("No\n");
    // 输出对应数字
    printf("%lld" , arr[tmp--]);
    for(;tmp >= 0;tmp--)
        printf(" %lld" , arr[tmp]);
}