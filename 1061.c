// PAT甲级1061 Dating，原题地址：https://www.patest.cn/contests/pat-a-practise/1061
// 解题分析：
//  破解福尔摩斯码，前两个字符串要先找到第一个相同的大写字母并且大写字母要在A到G的范围内，找到之后
//  再从这个位置开始向后找两个相同的字母或数字，范围在0到9或A到N之间。第三个和第四个字符串要找到相同的
//  字母，并记录它的位置。都找到后输出即可。
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){
    char s1[65] , s2[65] , s3[65] , s4[65];
    int i , j;
    int day , hour , minute;
    char date[7][4] = {"MON" , "TUE" , "WED" , "THU" , "FRI" , "SAT" , "SUN"};

    scanf("%s%s%s%s" , s1 , s2 , s3 , s4);
    // 查找第一个相同的大写字母
    for(i = 0;s1[i] != '\0' && s2[i] != '\0';i++){
        if(s1[i] == s2[i]){
            // 大写字母要在A到G之内，否则也不能算
            if(s1[i] >= 'A' && s1[i] <= 'G')
                break;
        }
    }
    // 减去A之后得到的值是在数组date内的索引
    day = s1[i] - 'A';
    // 查找小时
    for(j = i+1;s1[j] != '\0' && s2[j] != '\0';j++){
        if(s1[j] == s2[j]){
            // 数字
            if(s1[j] >= '0' && s1[j] <= '9')
                hour = s1[j] - '0';
            // 大写字母要在A到N内
            else if(s1[j] >= 'A' && s1[j] <= 'N')
                hour = s1[j] - 'A' + 10;
            else
                continue;
            break;
        }
    }
    // 查找第三个字符串和第四个字符串中相同的字母
    for(i = 0;s3[i] != '\0' && s4[i] != '\0';i++){
        if(s3[i] == s4[i]){
            if(s3[i] >= 'a' && s3[i] <= 'z')
                break;
            else if(s3[i] >= 'A' && s3[i] <= 'Z')
                break;
        }
    }
    // 记录位置
    minute = i;
    printf("%s %02d:%02d\n" , date[day] , hour , minute);
}