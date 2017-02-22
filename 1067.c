// PAT甲级1067 Sort with Swap(0,*)，原题地址：https://www.patest.cn/contests/pat-a-practise/1067
// 解题分析：
//  建立一个数组，arr[i]＝j表示数i在j位置，交换两数其实就是交换两数的位置，也就是说交换i和j就是交换arr[i]和arr[j]。
//  每次都从数字0开始，如果0不在0位置，那么它一定占了别的数字的位置，把对应的数字和0交换，该数字归位，0移动到对应位置，
//  然后继续执行此步骤，直到0回到0的位置。然后遍历数组，查找还没有归位的数，将其和0交换，接着继续执行上面的步骤，如果
//  全部数字都归位了就输出交换次数，程序结束。需要注意的是，每次查找没有归位的数都需从上一次查找结束的点开始，否则会超时。
#include<stdio.h>
#include<stdlib.h>

int main(){
    long n;
    long i;
    long *arr;
    long num;
    long ans = 0;
    long temp;
    long k = 0;

    scanf("%ld" , &n);
    arr = (long *)malloc(sizeof(long) * n);
    for(i = 0;i < n;i++){
        scanf("%ld" , &num);
        arr[num] = i;
    }
    while(1){
        // 0不在0位置
        while(arr[0] != 0){
            // 交换
            temp = arr[arr[0]];
            arr[arr[0]] = arr[0];
            arr[0] = temp;
            ans++;
        }
        // 从上一次查找结束点开始查找没有归位的数
        for(i = k;i < n;i++)
            if(arr[i] != i){
                k = i;
                break;
            }
        // 全部数都归位了
        if(i == n)
            break;
        // 交换
        arr[0] = arr[i];
        arr[i] = 0;
        ans++;
    }
    printf("%ld\n" , ans);
}