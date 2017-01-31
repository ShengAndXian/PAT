// PAT甲级1008 Elevator，原题地址：https://www.patest.cn/contests/pat-a-practise/1008
// 解题分析：
//  简单的计算即可。用prev变量储存上一次的层数，根据flag的正负进行不同的计算。
#include<stdio.h>

int main(){
    int N;
    int floorNum;
    int i;
    int prev = 0;
    int flag;
    int result = 0;

    scanf("%d" , &N);
    for(i = 0;i < N;i++){
        scanf("%d" , &floorNum);
        flag = floorNum - prev;
        if(flag > 0){
            result += flag * 6 + 5;
        }
        else{
            flag = -flag;
            result += flag * 4 + 5;
        }
        prev = floorNum;
    }

    printf("%d" , result);
}