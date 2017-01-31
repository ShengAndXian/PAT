// PAT甲级1006 Sign In and Sign Out，原题地址：https://www.patest.cn/contests/pat-a-practise/1006
// 解题分析：
//  题目很简单，分别找到来的最早的和走的最晚的即可。时间转换成秒即可。
#include<stdio.h>
#include<string.h>

#define INFINITY 1000000
int main(){
    int M;
    char ID[16];
    char earliest[16] , latest[16];
    int minTime = INFINITY , maxTime = -INFINITY;
    int hour , minute , second;
    int inTime , outTime;
    int i;

    scanf("%d" , &M);
    for(i = 0;i < M;i++){
        scanf("%s" , ID);
        scanf("%d:%d:%d" , &hour , &minute , &second);
        // 转换成秒
        inTime = hour * 3600 + minute * 60 + second;
        // 找到最小的到来的时间，并存入earliest
        if(inTime < minTime){
            minTime = inTime;
            strcpy(earliest , ID);
        }
        scanf("%d:%d:%d" , &hour , &minute , &second);
        // 转换成秒
        outTime = hour * 3600 + minute * 60 + second;
        // 找到最大的离开的时间，并存入latest
        if(outTime > maxTime){
            maxTime = outTime;
            strcpy(latest , ID);
        }
    }

    printf("%s %s" , earliest , latest);
}