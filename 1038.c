// PAT甲级1038 Recover the Smallest Number，原题地址：https://www.patest.cn/contests/pat-a-practise/1038
// 解题分析：
//  贪心算法。这题一开始的想法是每次遍历所有数字，选择第一个数字最小的，如果有相等的，再进行一系列的比较，提交之后很多测试点
//  都超时了。看了网上的解法，不得不说这些人怎么会这么机智啊！用qsort可以完美解决这道题，关键就是比较函数。在比较函数中拼接
//  两个字符串，比较两种顺序拼接出来的字符串，然后对两个字符串进行排序。排序完成后直接一个一个输出就可以了，注意全是0串的时候
//  要输出0，开头的0不输出。
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// 比较函数
int cmp(const void *a , const void *b){
    char *m = (char *)a;
    char *n = (char *)b;
    char temp1[20] , temp2[20];
    strcpy(temp1 , m);
    strcpy(temp2 , n);
    // 拼接字符串
    strcat(temp1 , n);
    strcat(temp2 , m);
    return strcmp(temp1 , temp2);
}

int main(){
    int n;
    int i , j;
    char s[10000][9];
    int flag = 0;

    scanf("%d" , &n);
    for(i = 0;i < n;i++)
        scanf("%s" , s[i]);
    qsort(s , n , sizeof(char) * 9 , cmp);
    for(i = 0;i < n;i++){
        for(j = 0;s[i][j] != '\0';j++){
            if(!flag && s[i][j] == '0')
                continue;
            else{
                flag = 1;
                printf("%c" , s[i][j]);
            }
        }
    }
    if(!flag)
        printf("0\n");
}