// PAT甲级1042 Shuffling Machine，原题地址：https://www.patest.cn/contests/pat-a-practise/1042
// 解题分析：
//  模拟题。
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    int order[55];
    int start[55] , end[55];
    int k;
    int i , j;
    char s[6];

    scanf("%d" , &k);
    for(i = 1;i <= 54;i++){
        scanf("%d" , &order[i]);
        end[i] = i;
    }
    for(i = 1;i <= k;i++){
        for(j = 1;j < 55;j++)
            start[j] = end[j];
        for(j = 1;j < 55;j++)
            end[order[j]] = start[j];
    }
    strcpy(s , "SHCDJ");
    end[1] -= 1;
    printf("%c%d" , s[end[1] / 13] , end[1] % 13 + 1);  
    for(i = 2;i < 55;i++){
        end[i] -= 1;
        printf(" %c%d" , s[end[i] / 13] , end[i] % 13 + 1);
    }
    printf("\n");
    return 0;
}