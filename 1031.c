// PAT甲级1031 Hello World for U，原题地址：https://www.patest.cn/contests/pat-a-practise/1031
// 解题分析：
//  很有意思的一道题，给定一个字符串然后按要求打印出一个U形，解题的关键就是题目中所给的那几个关系式，n1和n3相等
//  ，n1=n3=max{k|k <= n2}这个关系告诉我们k一定不会大于n2，不管n2取什么值，而n1和n3小于等于k，因此n1和n3一定
//  小于或等于n2，接着我们从n1+n2+n3-2 = N考虑，如果n2比较小，则n1可能会比n2大，这和之前的条件矛盾，因此我们使n2
//  从最小值开始逐渐增大，直到计算出的n1小于等于n2，此时的n2就是最终的n2。n2的初始值与字符串长度有关，如果其为偶数则从
//  4开始，为奇数则从3开始。之后从头和尾开始，依次输出即可。
#include<stdio.h>

int main(){
    char s[81];
    int i , j , t;
    int count = 0;
    int is_even = 0;
    int n;

    scanf("%s" , s);
    // 计算字符串长度
    for(i = 0;s[i] != '\0';i++) count++;
    // 如果字符串长度是偶数，则is_even设置为1
    if(count % 2 == 0)
        is_even = 1;
    // 如果is_even为1，n从4开始
    if(is_even)
        n = 4;
    // 否则从3开始
    else
        n = 3;
    // 计算n
    while((count + 2 - n) / 2 > n) 
        n += 2;
    // 从头和尾开始，依次输出
    i = 0;
    j = count - 1;
    // 如果剩余字符串长度大于n
    while(count > n){
        // 输出左边的字符
        printf("%c" , s[i]);
        // 输出空格
        for(t = 0;t < n - 2;t++)
            printf(" ");
        // 输出右边的字符
        printf("%c\n" , s[j]);
        i++;
        j--;
        // 剩余字符串数目减2
        count -= 2;
    }
    // 输出底端的字符
    while(i <= j){
        printf("%c" , s[i]);
        i++;
    }
}