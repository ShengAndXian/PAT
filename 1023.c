// PAT甲级1023 Have Fun with Numbers，原题地址：https://www.patest.cn/contests/pat-a-practise/1023
// 解题分析：
//  大整数运算。20位的整数用unsigned long long都无法全部表示出来，因此将大整数当作一个字符串来处理。使用一个check数组
//  纪录每一个数字的使用情况，如果最终每一个数组值都是0，则输出Yes，否则输出No。从字符串最后一位开始处理，先将原值对应的
//  数组值加一，然后乘2并加上进位，如果最后结果大于等于10，则flag等于1，相当于进位，并更新结果值，即减十，再将结果对应的数组值减一。
//  如果最终flag等于1或者check数组内有非0值，则输出No，否则输出Yes，并且如果flag等于1，输出1（进位）.最后输出结果即可。
#include<stdio.h>

int main(){
    char s[21];
    int flag = 0, flag1 = 0;
    int check[20];
    int i = 0, j;
    int temp;

    scanf("%s" , s);
    // 初始化check
    for(j = 0;j < 20;j++) check[j] = 0;
    // 计算字符串长度
    while(s[i+1] != '\0') i++;
    // 从最后一位开始处理
    for(j = i;j >= 0;j--){
        // 将字符转换成数字
        temp = s[j] - '0';
        // 对应check加一
        check[temp]++;
        // 乘2并加上进位
        temp = temp * 2 + flag;
        // 如果结果大于等于10
        if(temp >= 10){
            // 进位
            flag = 1;
            // 结果减10
            temp -= 10;
        }
        // 否则，无进位
        else
            flag = 0;
        // 结果对应的check减一
        check[temp]--;
        // 将结果转换成字符放入字符串
        s[j] = temp + '0';
    }
    // 检查check是否有非0值
    for(j = 0;j < 20;j++)
        if(check[j] != 0)
            flag1 = 1;
    // 如果check有非0值或有进位，输出No
    if(flag == 1 || flag1 == 1)
        printf("No\n");
    // 否则输出Yes
    else    
        printf("Yes\n");
    // 如果有进位，输出1
    if(flag == 1)
        printf("1");
    // 输出结果
    for(j = 0;j <= i;j++)
        printf("%c" , s[j]);
}