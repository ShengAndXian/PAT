// PAT甲级1060 Are They Equal，原题地址：https://www.patest.cn/contests/pat-a-practise/1060
// 解题分析：
//  有些繁琐的题目。首先，计算小数标准形式的指数时，有三种情况：
//  1、指数为正数，比如12.345
//  2、指数为负数，比如0.001
//  3、指数为0，比如0.000。
//  比较两个小数时，先比较它们的指数是否相等，如果不等，那两个截断后的两个小数也一定不等，如果相等，则有三种情况：
//  1、n比两个小数的位数都小，这种情况下，只要前n位数字相等，那截断后的两数相等
//  2、n比两个小数的位数都大，且两个小数位数相等，则只要每一位数字都相等，截断后的两数相等
//  3、两个小数位数不相等，n比较小位数大，这种情况下，不仅需要判断每一位数字是否相等，而且需要判断较长位数的小数
//  在区间［较小位数，n（或较长位数）］内是否全为0，如果全为0，则截断后的两数相等，否则不相等。
//  最后按格式输出即可。
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int GetCnt(char f[]);
int IsEuqal(char f1[] , char f2[] , int n);
void Output(char f[] , int n);

int main(){
    int n;
    char f1[11000] , f2[11000];

    scanf("%d%s%s" , &n , f1 , f2);
    if(IsEuqal(f1 , f2 , n)){
        printf("YES ");
        Output(f1 , n);
        printf("\n");
    }
    else{
        printf("NO ");
        Output(f1 , n);
        printf(" ");
        Output(f2 , n);
        printf("\n");
    }
}

// 计算指数
int GetCnt(char f[]){
    int i , j;
    int cnt;
    
    // 获取小数点下标
    for(i = 0;f[i] != '\0';i++)
        if(f[i] == '.')
            break;
    // 获取第一个数字的下标
    for(j = 0;f[j] == '0' || f[j] == '.';j++) ;
    // 全部为0
    if(f[j] == '\0')
        return 0;
    // 形如0.1,0.01
    if(i < j)
        return i - j + 1;
    // 形如1.0,10.0
    else
        return i - j;
}

// 判断两数阶段后是否相等
int IsEuqal(char f1[] , char f2[] , int n){
    int p , q;
    int cnt = 0;
    int cnt1 , cnt2;
    int i;

    // 获取两数的指数
    cnt1 = GetCnt(f1);
    cnt2 = GetCnt(f2);
    // 如果两数的指数相等
    if(cnt1 != cnt2)
        return 0;
    // 从第一个数字开始
    for(p = 0;f1[p] == '0' || f1[p] == '.';p++) ;
    for(q = 0;f2[q] == '0' || f2[q] == '.';q++) ;
    for(;cnt < n && f1[p] != '\0' && f2[q] != '\0';p++,q++,cnt++){
        // 小数点跳过
        if(f1[p] == '.'){
            // cnt记录已经比较的位数
            cnt--;
            continue;
        }
        // 不相等返回0
        if(f1[p] != f2[q])
            return 0;
    }
    // 如果小数位数均小于n
    if(cnt == n)
        return 1;
    // 如果小数位数大于n，但两数一样长
    else if(f1[p] == '\0' && f2[q] == '\0')
        return 1;
    // 否则
    else{
        // 如果第一个小数较短
        if(f1[p] == '\0'){
            // 判断第二个小数
            for(i = p;i < p + n - cnt && f2[i] != '\0';i++)
                // 有不为0的位则返回0
                if(f2[i] != '0')
                    return 0;
            return 1;
        }
        // 如果第二个小数较短
        else{
            for(i = q;i < q + n - cnt && f2[i] != '\0';i++)
                if(f1[i] != '0')
                    return 0;
            return 1;
        }
    }
}

// 输出
void Output(char f[] , int n){
    int i;
    int cnt;
    int temp;

    for(i = 0;f[i] == '0' || f[i] == '.';i++) ;
    printf("0.");
    for(temp = 0;temp < n && f[i] != '\0';i++,temp++){
        if(f[i] == '.'){
            temp--;
            continue;
        }
        printf("%c" , f[i]);
    }
    if(temp < n)
        for(i = 0;i < n - temp;i++)
            printf("0");
    cnt = GetCnt(f);
    printf("*10^%d" , cnt);
}