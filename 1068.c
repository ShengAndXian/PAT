// PAT甲级1068 Find More Coins，原题地址：https://www.patest.cn/contests/pat-a-practise/1068
// 解题分析：
//  动态规划中的01背包问题。将要付的钱看作背包的容量，每一个硬币的值既为它的体积，同时也是它的价值。一个背包
//  里所有硬币的体积相加不会超过背包的容量，因此背包内所有硬币的最大价值也不会超过背包的容量，即最大价值为背包
//  的容量，也就是要付的钱。所以，通过求解最大价值，判断其是否等于要付的钱，如果等于则说明有解，否则无解。
//  对于输入的硬币的值，先将它们按从大到小的顺序排序，然后依次放入背包，用二维数组select纪录它们放入的情况，
//  遍历完之后，通过dp[m]判断是否有解，如果有解，再依次输出序列。
#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a , const void *b);

int n , m;
int dp[110];
int w[10010];
int select[10010][110];

int main(){
    int i , j;
    int t , v;
    int flag = 1;

    scanf("%d%d" , &n , &m);
    for(i = 0;i < n;i++)
        scanf("%d" , &w[i]);
    // 从大到小排序
    qsort(w , n , sizeof(int) , cmp);
    // 依次放入背包
    for(i = 0;i < n;i++){
        for(j = m;j >= w[i];j--){
            // 放入后得到更大的价值
            if(dp[j] <= dp[j - w[i]] + w[i]){
                // 更新当前背包容量对应的最大价值
                dp[j] = dp[j - w[i]] + w[i];
                // 纪录放入信息
                select[i][j] = 1;
            }
        }
    }
    // 判断是否有解
    if(dp[m] != m){
        printf("No Solution\n");
        return 0;
    }
    // 输出
    t = n - 1;
    v = m;
    while(v > 0){
        if(select[t][v] == 1){
            if(flag){
                printf("%d" , w[t]);
                flag = 0;
            }
            else{
                printf(" %d" , w[t]);
            }
            v -= w[t];
        }
        t--;
    }
    printf("\n");
    return 0;
}

int cmp(const void *a , const void *b){
    return (*(int *)b) - (*(int *)a); 
}