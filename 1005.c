// PAT甲级1005 Spell It Right，原题地址：https://www.patest.cn/contests/pat-a-practise/1005
// 解题分析：
//  题目很简单，首先将输入的各个数字当作字符处理，输入完成时即可计算出所有数字之和。然后通过对10取余和对10整除，
//  即可得到结果的各个位的数字，输出相应的英文即可。
#include<stdio.h>

int main(){
    char num;
    int result = 0;
    int temp;
    int arr[5];
    int count = 0;
    int remain;
    int flag = 0;

    // 输入
    while(1){
        scanf("%c" , &num);
        // 回车结束
        if(num == '\n')
            break;
        // 计算各个数字之和
        result += num - '0';
    }
    temp = result;
    // 结果为0，则输出zero
    if(temp == 0){
        printf("zero");
        return 0;
    }
    // 对10取余，对10整除，得到结果的各个位的数字
    while(temp != 0){
        remain = temp % 10;
        temp = temp / 10;
        arr[count++] = remain;
    }
    // 输出每一个数字对应的英文
    while(--count >= 0){
        if(flag == 1)
            printf(" ");
        else
            flag = 1;
        switch(arr[count]){
            case 0:printf("zero");break;
            case 1:printf("one");break;
            case 2:printf("two");break;
            case 3:printf("three");break;
            case 4:printf("four");break;
            case 5:printf("five");break;
            case 6:printf("six");break;
            case 7:printf("seven");break;
            case 8:printf("eight");break;
            case 9:printf("nine");break;
        }
    }
}