// PAT甲级1056 Mice and Rice，原题地址：https://www.patest.cn/contests/pat-a-practise/1056
// 解题分析：
//  用变量cnt储存当前轮的参赛人数，prev数组储存上一轮的胜利者，current数组储存当前轮的胜利者，当前轮结束
//  后将current数组复制给prev数组。用一个变量group储存当前轮的组数，然后依次遍历每一组，每一组中输了的人
//  的排名为group加一，赢了的人放入current数组。遍历完成后更新cnt，当人数为1时，输出结果。
#include<stdio.h>
#include<stdlib.h>

int main(){
    int p , g;
    int w[1000];
    int prev[1000];
    int current[1000];
    int res[1000];
    int i , j;
    int cnt;
    int group;
    int start , end;
    int temp;
    int max;
    int index;

    scanf("%d%d" , &p , &g);
    for(i = 0;i < p;i++)
        scanf("%d" , &w[i]);
    for(i = 0;i < p;i++)
        scanf("%d" , &prev[i]);
    for(cnt = p;cnt > 0;cnt = group){
        // 计算组数
        group = cnt / g;
        // 如果人数不等于g的倍数，则剩下的人组成一组
        if(cnt % g != 0)
            group++;
        temp = group;
        start = 0;
        j = 0;
        // 遍历每一组
        while(temp > 0){
            end = start + g - 1;
            // end不能超过cnt
            if(end >= cnt)
                end = cnt - 1;
            max = w[prev[start]];
            index = start;
            // 人数为1时输出结果
            if(cnt == 1){
                res[prev[start]] = 1;
                for(i = 0;i < p;i++){
                    printf("%d" , res[i]);
                    if(i != p - 1)
                        printf(" ");
                }
                printf("\n");
                return 0;
            }
            // 遍历一组内的所有人，找到最大者
            for(i = start + 1;i <= end;i++){
                if(w[prev[i]] > max){
                    max = w[prev[i]];
                    index = i;
                }
            }
            // 再次遍历
            for(i = start;i <= end;i++){
                // 赢了的人
                if(i == index)
                    current[j++] = prev[i];
                // 输了的人
                else
                    res[prev[i]] = group + 1;
            }
            start = end + 1;
            // 组数减一
            temp--;
        }
        // 将current数组复制给prev数组
        for(i = 0;i < j;i++)
            prev[i] = current[i];
    }
}