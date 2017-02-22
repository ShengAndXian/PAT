// PAT甲级1069 The Black Hole of Numbers，原题地址：https://www.patest.cn/contests/pat-a-practise/1069
// 解题分析：
//  被这题坑了。。。。其实是很简单的一道题，但要注意输入可以不是四位数，不满四位要补0，当输入为6174时，要输出7641 - 1467 = 6147.
#include<stdio.h>
#include<stdlib.h>

int DecreaseOrder(int n);
int IncreaseOrder(int n);
int cmp1(const void *a , const void *b);
int cmp2(const void *a , const void *b);

int main(){
    int res;
    int n1 , n2;

    scanf("%d" , &res);
    do{
        n1 = DecreaseOrder(res);
        n2 = IncreaseOrder(res);
        res = n1 - n2;
        printf("%04d - %04d = %04d\n" , n1 , n2 , res);
    }while(res != 6174 && res);
    return 0;
}

int DecreaseOrder(int n){
    int s[10];
    int i;
    int res = 0;
    int temp = 1;

    for(i = 0;i < 4;i++){
        s[i] = n % 10;
        n /= 10;
    }
    qsort(s , 4 , sizeof(int) , cmp1);
    i--;
    while(i >= 0){
        res += s[i] * temp;
        temp *= 10;
        i--;
    }
    return res;
}

int IncreaseOrder(int n){
    int s[10];
    int i;
    int res = 0;
    int temp = 1;

    for(i = 0;i < 4;i++){
        s[i] = n % 10;
        n /= 10;
    }
    qsort(s , 4 , sizeof(int) , cmp2);
    i--;
    while(i >= 0){
        res += s[i] * temp;
        temp *= 10;
        i--;
    }
    return res;
}

int cmp1(const void *a , const void *b){
    return (*(int *)b) - (*(int *)a);
}

int cmp2(const void *a , const void *b){
    return (*(int *)a) - (*(int *)b);
}