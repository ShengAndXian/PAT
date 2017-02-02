// PAT甲级1024 Palindromic Number，原题地址：https://www.patest.cn/contests/pat-a-practise/1024
// 解题分析；
//  大整数相加运算。大整数貌似都当作字符串处理会比较简单。首先输入一个整数，存入字符数组。接着判断是否是Palindromic number，
//  如果是，则输出字符串和对应的执行次数，如果不是，则反转字符串，得到另一个字符串，然后两个字符串相加，再次执行相同的步骤。
//  执行次数不能超过k，超过k之后直接输出执行次数为k时的字符串和k。
#include<stdio.h>

int get_length(char s[]);
int is_parlindromic(char s[] , int length);
void reverse(char s[] , char r[] , int length);
void add(char s[] , char r[] , int length);
int main(){
    char s[100];
    char r[100];
    int k;
    int i;
    int length;

    scanf("%s %d" , s , &k);
    for(i = 0;i <= k;i++){
        // 计算字符串长度
        length = get_length(s);
        // 如果是palindromic number或者执行次数为k
        if(is_parlindromic(s , length) == 1 || i == k){
            // 输出字符串和执行次数
            printf("%s\n%d" , s , i); 
            // 返回
            return 0;
        }
        // 否则
        else{
            // 反转字符串，并存入r
            reverse(s , r , length);
            // 相加，并将结果存入s
            add(s , r , length);
        }
    }
}

// 计算字符串长度
int get_length(char s[]){
    int i = 0;
    while(s[i] != '\0') i++;
    return i;
}

// 判断是否为palindromic number
int is_parlindromic(char s[] , int length){
    int i , j;

    // 从头和尾开始比较，如有不相等的两个数字，则返回0，否则返回1
    for(i = 0,j = length - 1;i <= j;i++,j--){
        if(s[i] != s[j])
            return 0;
    }
    return 1;
}

// 反转字符串
void reverse(char s[] , char r[] , int length){
    int i , j = 0;

    for(i = length - 1;i >= 0;i--)
        r[j++] = s[i];
    r[j] = '\0';
}

// 相加两个字符串
void add(char s[] , char r[] , int length){
    int temp , temp1 , temp2;
    int flag = 0;
    int i , j = 0;
    char sum[100];
    int index = 0;

    // 从最后一位开始计算
    for(i = length - 1;i >= 0;i--){
        // 将字符转化成数字
        temp1 = s[i] - '0';
        temp2 = r[i] - '0';
        // 相加并加上进位
        temp = temp1 + temp2 + flag;
        // 如果结果大于等于10
        if(temp >= 10){
            // 进位
            flag = 1;
            // 结果减去10
            temp -= 10;
        }
        // 否则，无进位
        else    
            flag = 0;
        // 结果转换成字符存入sum
        sum[index++] = temp + '0';
    }
    // 如果有进位
    if(flag == 1)
        // 将字符1存入
        sum[index++] = '1';
    // 将结果放入到s
    for(i = index - 1;i >= 0;i--){
        s[j++] = sum[i];
    }
    s[j] = '\0';
}
