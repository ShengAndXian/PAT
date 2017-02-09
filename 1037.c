// PAT甲级1037 Magic Coupon，原题地址：https://www.patest.cn/contests/pat-a-practise/1037
// 解题分析：
//  简单题，输入数据之后对两个序列进行从大到小排序，然后从头开始，把正数和正数相乘，加到money里面，遇到
//  负数结束。接着从尾开始，把负数和负数相乘，加到money里面，遇到正数结束。最后输出即可。
#include<stdio.h>
#include<stdlib.h>

int compare(const void *a , const void *b){
    return (*(long int *)b) - (*(long int *)a);
}

int main(){
    long nc , np;
    long i , j;
    long coupons[100000] , products[100000];
    long long money = 0;

    // 输入
    scanf("%ld" , &nc);
    for(i = 0;i < nc;i++){
        scanf("%ld" , &coupons[i]);
    }
    scanf("%ld" , &np);
    for(i = 0;i < np;i++){
        scanf("%ld" , &products[i]);
    }
    // 从大到小排序
    qsort(coupons , nc , sizeof(long int) , compare);
    qsort(products , np , sizeof(long int) , compare);
    // 从头开始
    i = j = 0;
    while(1){
        // 如果两者均为正数，则相乘加入到money
        if(coupons[i] > 0 && products[j] > 0){
            money += coupons[i] * products[j];
            i++;
            j++;
        }
        // 否则结束
        else
            break;
    }
    // 从尾开始
    i = nc - 1;
    j = np - 1;
    while(1){
        // 如果两者均为负数，则相乘加入到money
        if(coupons[i] < 0 && products[j] < 0){
            money += coupons[i] * products[j];
            i--;
            j--;
        }
        // 否则结束
        else
            break;
    }
    // 输出
    printf("%lld\n" , money);
}