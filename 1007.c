// PAT甲级1007 Maximum Subsequence Sum，原题地址：https://www.patest.cn/contests/pat-a-practise/1007
// 解题分析：
//  求最大子序列的和。如果全部值都是负数，则直接输出0，以及第一个和最后一个值。如果序列中有非负值，则计算最大子序列的和。
//  首先，从第一个元素开始，先找到一个正数，因为起始就是负数的序列一定不是最大的子序列。用start，end表示最大子序列的开始
//  和结束的索引，currentStart，currentEnd表示当前子序列的开始和结束的索引。开始时，4个变量值都为第一个正数的索引。接着
//  currentEnd开始向后搜索，并计算currentSum，如果其比sum大，则更新end、start、sum，如果其为负数，则当前序列不可能是
//  最大子序列，更新currentStart。重复此操作，currentEnd等于k。最后输出即可。
#include<stdio.h>

#define Max 10000
int main(){
    int K;
    int arr[Max];
    int i;
    int start , end , sum , currentStart , currentEnd , currentSum;

    // 输入
    scanf("%d" , &K);
    for(i = 0;i < K;i++){
        scanf("%d" , &arr[i]);
    }

    // 找到第一个正数
    for(i = 0;i < K;i++){
        if(arr[i] >= 0)
            break;
    }
    // 全是负数
    if(i == K){
        printf("0 %d %d" , arr[0] , arr[K-1]);
        return 0;
    }

    // 初始化
    start = currentStart = i;
    end = currentEnd = i;
    sum = currentSum = arr[i];

    while(1){
        // 扩展当前子序列
        currentEnd++;
        // 查找结束
        if(currentEnd == K)
            break;
        // 计算当前子序列的和
        currentSum += arr[currentEnd];
        // 如果比最大子序列的和大
        if(currentSum > sum){
            // 更新start、end、sum
            sum = currentSum;
            start = currentStart;
            end = currentEnd;
        }
        // 如果是负数
        else if(currentSum < 0){
            // 更新currentStart
            currentStart = currentEnd + 1;
            // currentSum为0
            currentSum = 0;
        }
    }

    printf("%d %d %d" , sum , arr[start] , arr[end]);

}