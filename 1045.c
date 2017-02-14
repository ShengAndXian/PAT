// PAT甲级1045 Favorite Color Stripe，原题地址：https://www.patest.cn/contests/pat-a-practise/1045
// 解题分析：
//  动态规划中的最长不下降子序列问题。首先将喜欢的颜色作为索引，索引指向的内容作为它的顺序，输入条纹颜色时，先剔除
//  不喜欢的颜色，将喜欢的颜色放入数组。接着用i遍历数组，用j访问0到i－1之间的元素，如果c[j]所表示的颜色的顺序在c[i]
//  所表示的颜色之前，则判断dp[j]和max的大小，取其中较大的。得到最大的max后，更新dp[i]。dp[i]表示第i个元素所对应的
//  最大不下降子序列的长度。最后遍历dp数组，输出最大值。
#include<stdio.h>
#include<stdlib.h>

int main(){
    int n , m , l;
    int i , j;
    int f[201];
    int c[10000];
    int count = 0;
    int dp[10000];
    int max;
    int num;
    
    scanf("%d%d" , &n , &m);
    for(i = 1;i <= m;i++)
        f[i] = 0;
    for(i = 1;i <= m;i++){
        scanf("%d" , &num);
        f[num] = i;
    }
    scanf("%d" , &l);
    for(i = 0;i < l;i++){
        scanf("%d" , &num);
        // 剔除不喜欢的颜色
        if(f[num]){
            c[count++] = num;
        }
    }
    for(i = 0;i < 10000;i++)
        dp[i] = 1;
    // 遍历所有颜色
    for(i = 0;i < count;i++){
        max = 0;
        for(j = 0;j < i;j++){
            // 如果c[j]对应的颜色出现在c[i]对应的颜色之前
            if(f[c[j]] <= f[c[i]])
                max = dp[j] > max ? dp[j] : max;
        }
        // 更新dp[i]
        dp[i] = max + 1;
    }
    // 输出
    max = 1;
    for(i = 0;i < count;i++)
        if(dp[i] > max)
            max = dp[i];
    printf("%d\n" , max);
        
}