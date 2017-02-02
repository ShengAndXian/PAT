// PAT甲级1029 Median，原题地址：https://www.patest.cn/contests/pat-a-practise/1029
// 解题分析：
//  题目其实很简单，但有一些坑。刚开始的时候我直接定义了3个有百万级别元素个数的数组，结果一运行就段错误，
//  在网上查阅资料后，知道了本地变量存放在内存的栈空间，而栈空间比较小，因此定义了很大的数组后后爆栈。解决方法
//  是将数组变为全局变量或用malloc分配内存。由于本人不太喜欢用全局变量，因此选用了malloc。malloc分配的内存
//  位于内存的堆空间，堆空间的大小较大，因此不会爆掉。之后是排序问题，我没试过将两个序列合起来直接快排，看网上
//  试过的人说好像会超时，具体就自己写一遍吧。我的方法类似于归并排序，用两个指针或者说索引遍历两个数组，然后一个
//  一个排下来，最后输出中间值即可。
#include<stdio.h>
#include<stdlib.h>

int main(){
    long int n1 , n2;
    long int i , j , k = 0;
    long int *arr1 , *arr2;
    long int *result;

    // 输入
    scanf("%ld" , &n1);
    arr1 = (long int *)malloc(sizeof(long int) * n1);
    for(i = 0;i < n1;i++)
        scanf("%ld" , &arr1[i]);
    scanf("%ld" , &n2);
    arr2 = (long int *)malloc(sizeof(long int) * n2);
    for(i = 0;i < n2;i++)
        scanf("%ld" , &arr2[i]);
    result = (long int *)malloc(sizeof(long int) * (n1 + n2));
    // 遍历两个数组
    for(i = 0 , j = 0;i != n1 && j != n2;){
        // 如果第一个数组的元素比第二个数组的元素小
        if(arr1[i] < arr2[j]){
            // 将第一个数组的元素放入最终的数组
            result[k++] = arr1[i++];
        }
        // 否则将第二个数组的元素放入最终的数组
        else{
            result[k++] = arr2[j++];
        }
    }
    // 如果第一个数组遍历完成
    if(i == n1){
        // 将第二个数组的剩余元素加入数组
        while(j != n2)
            result[k++] = arr2[j++];
    }
    // 同理
    else{
        while(i != n1)
            result[k++] = arr1[i++];
    }
    // 输出
    printf("%ld" , result[(k-1) / 2]);
}