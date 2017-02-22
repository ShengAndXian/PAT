// PAT甲级1070 Mooncake，原题地址：https://www.patest.cn/contests/pat-a-practise/1070
// 解题分析：
//  贪心算法。每千吨收益最多的优先考虑，因此对输入的数据按每千吨收益从大到小排序，然后依次考虑，直到
//  满足需求或没有库存为止。需要注意的是库存可能是小数，而不一定是整数。
#include<stdio.h>
#include<stdlib.h>

struct record{
    float inv;
    float price;
    float profit;
};

int cmp(const void *a , const void *b);

int main(){
    struct record R[1000];
    int n , d;
    int i;
    float res = 0;

    scanf("%d%d" , &n , &d);
    for(i = 0;i < n;i++)
        scanf("%f" , &R[i].inv);
    for(i = 0;i < n;i++){
        scanf("%f" , &R[i].price);
        R[i].profit = R[i].price / R[i].inv;
    }
    // 按每千吨收益排序
    qsort(R , n , sizeof(struct record) , cmp);
    for(i = 0;i < n;i++){
        // 如果当前月饼的库存比需要的多
        if(R[i].inv >= d){
            res += d * R[i].price / R[i].inv;
            printf("%.2f\n" , res);
            return 0;
        }
        // 否则
        else{
            res += R[i].price;
            d -= R[i].inv;
        }
    }
    printf("%.2f\n" , res);
    return 0;
}

int cmp(const void *a , const void *b){
    return (*(struct record *)b).profit > (*(struct record *)a).profit;
}