// PAT甲级1011 World Cup Betting，原题地址：https://www.patest.cn/contests/pat-a-practise/1011
// 解题分析：
//  水题。从每一组数据选一个最大的，并纪录对应的是’W'，‘T’，还是‘L'。输出格式控制为两位小数。
#include<stdio.h>

int main(){
    double max;
    int i, j;
    double num;
    int flag[3] , count;
    double result = 1;

    for(i = 0;i < 3;i++){
        count = 0;
        max = -1;
        for(j = 0;j < 3;j++){
            scanf("%lf" , &num);
            if(num > max){
                max = num;
                flag[i] = count;
            }
            count++;
        }
        result *= max;
    }
    for(i = 0;i < 3;i++){
        switch(flag[i]){
            case 0:printf("W ");break;
            case 1:printf("T ");break;
            case 2:printf("L ");break;
        }
    }
    result = (result * 0.65 - 1) * 2;
    printf("%.2f" , result);
}