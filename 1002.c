// PAT甲级1002 A+B for polynomial，原题地址：https://www.patest.cn/contests/pat-a-practise/1002
// 解题分析：
//  题目意思比较清晰，就是计算两个多项式的和多项式。给了系数和指数，用数组表示比较简单直观。指数作为数组的索引，数组的内容则是
//  系数。这道题只需要一个数组就够了，第二个多项式在输入的时候可以直接和原来存在数组里的多项式相加从而更新结果多项式。这里我
//  犯了一个错误，本来想在输入第二个多项式时，只要对应索引的数组值为0就说明多了一项，从而只要在第一个k的基础上加一就可以了，但
//  最后有一些测试点通不过，后来一想多项式的系数可以是负数，因此可能会把一些项给消掉。于是我们需要多遍历一遍才能算出最终的项数。
#include<stdio.h>

int main(){
    double arr[1001];
    int k , i;
    int n;
    double a;
    int count = 0;
    
    for(i = 0;i < 1001;i++)
        arr[i] = 0;
    
    scanf("%d" , &k);
    for(i = 0;i < k;i++){
        scanf("%d %lf" , &n , &a);
        arr[n] += a;//将第一个多项式存入数组
    }
    scanf("%d" , &k);
    for(i = 0;i < k;i++){
        scanf("%d %lf" , &n , &a);
        arr[n] += a;//叠加第二个多项式
    }
    //遍历数组计算项数
    for(i = 1000;i >= 0;i--){
        if(arr[i] != 0)
            count++;
    }
    printf("%d" , count);
    //按指数降序输出多项式
    for(i = 1000;i >= 0 ;i--){
        if(arr[i] != 0){
            printf(" %d %.1lf" , i , arr[i]);
        }
}
}