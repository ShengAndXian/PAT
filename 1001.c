// PAT甲级1001 A+B Format，原题地址：https://www.patest.cn/contests/pat-a-practise/1001
// 解题分析：
//  题目很简单，就是计算两个值的和，然后从最后一位开始，每三位为一组，三位之前还有数则用逗号隔开。大致思路是先计算两数之和，
//  0的话直接输出0即可，对于负数，先输出一个负号，然后将其转为正数。对于正数，先通过取余把每一位数组转化成字符，存储在一个数组中，
//  然后检查和的位数是否大于等于3，如果不是则直接输出，如果是，则再检查是否是3的整数倍，如果是则一组一组输出，如果不是则先把最高
//  几位输出，再一组一组输出。
#include<stdio.h>

int main(){
    long a , b;
    long result;
    long temp;
    int flag1 , flag2;
    char s[7];
    int i = 0 , j;
    int count = 0;

    scanf("%ld %ld" , &a , &b);
    result = a + b;//计算两数之和
    if(result == 0){
        printf("0");//如果结果为0，直接输出0
        return 0;
    }
    if(result < 0){
        printf("-");//如果结果为负数，输出符号
        result = 0 - result;//转换成正数
    }
    temp = result;
    while(temp != 0){
        s[i++] = temp % 10 + '0';//将每一位数存入数组（逆序）
        temp /= 10;
    }
    flag1 = i / 3;//整除3
    flag2 = i % 3;//对3取余
    if(flag1 == 0){//如果位数小于3
        printf("%ld" , result);//直接输出结果
        return 0;
    }
    else if(flag2 != 0){//如果位数大于3并且不是3的整数倍
            for(j = 0;j < flag2;j++){
                printf("%c" , s[--i]);//输出最高的几位
            }
            printf(",");//逗号隔开
        }
    // 按3个一组一次输出
    while(1){
        printf("%c" , s[--i]);
        count++;
        if(count == 3){
            if(i == 0)//全部输出，返回
                return 0;
            else{
                printf(",");//逗号隔开
                count = 0;//count归零
            }
        }
    }

}