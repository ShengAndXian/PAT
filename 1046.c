// PAT甲级1046 Shortest Distance，原题地址：https://www.patest.cn/contests/pat-a-practise/1046
// 解题分析：
//  模拟题。如果每次都通过遍历数组来计算两通道之间的距离，最后一个测试点会超时。因此，采用另一种算法，通过distance
//  数组储存从第一个点到第i个点的距离，再用sum储存所有距离之和。查询时，通过计算两者的distance之差即可得到一个距离值，
//  再用sum减去该值就可以得到另一个距离值，比较两者，选择较小的输出即可。需要注意的是，查询时所给的两点的顺序可能是反的，
//  需要将其颠倒过来。
#include<stdio.h>
#include<stdlib.h>

int main(){
    long n , m;
    long i , j;
    long *distance;
    long start , end;
    long sum = 0;
    long num;
    long min;
    long temp;

    scanf("%ld" , &n);
    distance = (long *)malloc(sizeof(long) * (n + 1));
    distance[1] = 0;
    for(i = 1;i <= n;i++){
        scanf("%ld" , &num);
        // distance[i]表示第一点到第i点的距离
        if(i != n)
            distance[i + 1] = distance[i] + num;
        // sum纪录所有距离和
        sum += num;
    }   
    scanf("%ld" , &m);
    // 查询
    for(i = 0;i < m;i++){
        scanf("%ld%ld" , &start , &end);
        // 如果顺序反了
        if(start > end){
            temp =start;
            start = end;
            end = temp;
        }
        // 计算亮点之间的距离
        temp = distance[end] - distance[start];
        // 选择较小的
        min = temp < (sum - temp) ? temp : (sum - temp);
        printf("%ld\n" , min);
    }
}