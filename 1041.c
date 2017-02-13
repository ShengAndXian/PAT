// PAT甲级1041 Be Unique，原题地址：https://www.patest.cn/contests/pat-a-practise/1041
// 解题分析：
//  排序和查找。输入的数据用一个数组来储存，同时拷贝一份到另一个数组，输入结束后，对另一个数组进行排序，
//  之后遍历原数组，对每一个元素，都在排好序的数组中进行二分查找，并且考察是否相邻的两个数字中至少有一个
//  和所查找的数字相等，如果都不相等，则说明该数字是唯一的，返回1，否则返回0。如果数字是唯一的，则直接输出
//  该数字，结束程序，否则继续往下遍历。
#include<stdio.h>
#include<stdlib.h>

int if_unique(long a , long arr[] , long n);
int compare(const void *a , const void *b);

int main(){
    long n;
    long i;
    long flag;
    long *arr;
    long *temp;

    scanf("%ld" , &n);
    // 构建两个数组
    arr = (long *)malloc(sizeof(long) * n);
    temp = (long *)malloc(sizeof(long) * n);
    // 输入
    for(i = 0;i < n;i++){
        scanf("%ld" , &arr[i]);
        temp[i] = arr[i];
    }
    // 对temp数组按升序排序
    qsort(temp , n , sizeof(long) , compare);
    // 遍历原数组
    for(i = 0;i < n;i++){
        // 判断是否是唯一的
        flag = if_unique(arr[i] , temp , n);
        // 如果是
        if(flag == 1){
            printf("%ld\n" , arr[i]);
            return 0;
        }
    }
    // 都不唯一
    printf("None\n");
    return 0;
}

// 判断数字是否唯一
int if_unique(long a , long arr[] , long n){
    long start = 0 , end = n - 1;
    long mid;

    // 基于二分查找
    while(1){
        mid = (start + end) / 2;
        // 找到该数字
        if(arr[mid] == a){
            // 判断相邻的数字是否与该数字相等
            if(arr[mid + 1] != a && arr[mid - 1] != a)
                return 1;
            else
                return 0;
        }
        else if(arr[mid] > a)
            end = mid - 1;
        else    
            start = mid + 1;
    }
}

int compare(const void *a , const void *b){
    return (*(long *)a) - (*(long *)b);
}