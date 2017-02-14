// PAT甲级1044 Shopping in Mars，原题地址：https://www.patest.cn/contests/pat-a-practise/1044
// 解题分析：
//  刚开始的时候，我采用模拟的方法，对每一个选定的元素，向后遍历直到它们的和大于等于给定的值为止，最后有两个
//  测试点超时，因为可能给的数很大，每次都需要遍历后面所有的数，时间复杂度达到了O（n^2）。以下代码参考了网上
//  大神的代码，感觉充满了代码的简洁之美，真的很佩服！首先，sum数组里的元素sum［i］表示1-i所有数的和，是一个
//  递增的数组。程序中通过变量i来遍历sum数组，变量j表示区间的右边界，如果当前区间的和比给定的值小，则j向后移动
//  直到区间的和比给定的值大（或相等）。由于i－j区间的和恰好比给定的值大（或相等），因此i+1到j区间的和一定比给定
//  的值小。所以当i访问到下一个数时，不会存在i到某个小于j的数这个区间内的和大于或等于给定值的情况，也就是说当遍历
//  完整个sum数组后，我们一定能得到所有大于或等于给定值的区间的和。选择所有区间和中最小的值存入变量min。接着，我们
//  用同样的方法再遍历一次sum数组，只不过这次比较的值变成了min，一旦发现区间和等于min的区间，输出两端的索引。
#include<stdio.h>
#include<stdlib.h>

int main(){
    long n , m;
    long i , j;
    long *sum;
    long min;
    long num;

    scanf("%ld %ld" , &n , &m);
    sum = (long *)malloc(sizeof(long) * (n + 1) );
    sum[0] = 0;
    for(i = 1;i <= n;i++){
        scanf("%ld" , &num);
        // 计算1-i的和
        sum[i] = sum[i - 1] + num;
    }
    min = sum[n];
    // 第一次遍历
    for(i = 1 , j = 1;i <= n;i++){
        // 如果区间的和比m小，右边界增大
        while(sum[j] - sum[i - 1] < m && j <= n) j++;
        // 如果区间的和比m大或相等，则从min和它之间选择较小的一个
        if(sum[j] - sum[i - 1] >= m) min = (sum[j] - sum[i - 1]) < min ? (sum[j] - sum[i - 1]) : min;
    }
    // 第二次遍历
    for(i = 1 , j = 1;i <= n;i++){
        // 如果区间的和比min小，右边界增大
        while(sum[j] - sum[i - 1] < min && j<= n) j++;
        // 如果区间和等于min，输出两端点索引
        if(sum[j] - sum[i - 1] == min) printf("%ld-%ld\n" , i , j);
    }
    return 0;
}