// PAT甲级1015 Reversible Primes，原题地址：https://www.patest.cn/contests/pat-a-practise/1015
// 解题分析：
//  首先判断输入的十进制树是否为质数，然后根据输入的进制转换改数字，并把转换来的数字反转，再将反转后的数字按
//  进制转换为十进制数，再判断其是否为质数，如果两个都是质数，则输出Yes，fouze输出No。
#include<stdio.h>

int if_prime(int result);
int reverse(int N , int D);

int main(){
    int N , D;
    int flag_1 , flag_2;

    while(1){
        // 输入
        scanf("%d" , &N);
        // 负数结束
        if(N < 0)
            break;
        scanf("%d" , &D);
        // 判断输入的十进制数是否为质数
        flag_1 = if_prime(N);
        // 反转十进制数
        N = reverse(N , D);
        // 判断反转后的十进制数是否是质数
        flag_2 = if_prime(N);
        // 两个都是
        if(flag_1 == 1 && flag_2 == 1)
            printf("Yes\n");
        // 否则
        else
            printf("No\n");
    }
}

// 判断十进制数是否为质数
int if_prime(int result){
    int i;
    // 0和1都不是质数
    if(result < 2)
        return 0;
    for(i = 2;i < result;i++){
        if(result % i == 0)
            break;
    }
    // 有可以整除该数的数存在，则不是质数
    if(i < result)
        return 0;
    // 否则，是质数
    else
        return 1;
}

// 反转
int reverse(int N , int D){
    int tmp = 1;
    int result = 0;
    int i;
    int arr[100000];

    // 按进制转换
    for(i = 0;N != 0;i++){
        arr[i] = N % D;
        N /= D;
    }
    i--;
    // 反转，并转换成新的十进制数
    while(i >= 0){
        result += arr[i] * tmp;
        tmp *= D;
        i--;
    }
    return result;
}