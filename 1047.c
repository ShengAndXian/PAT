// PAT甲级1047 Student List for Course，原题地址：https://www.patest.cn/contests/pat-a-practise/1047
// 解题分析：
//  模拟题。用一个二维数组name储存每一个学生的姓名，另外用一个二维数组course纪录每一门课程注册的学生信息，course的内容
//  对应name中的索引。对于每一门课程，将其对应的学生按字典序列排序。这里有一个陷阱，虽然每一个学生最多注册20门课程，但
//  并没有规定每一门课程的学生人数限制，因此二维数组course的长度是不确定的，最多可以达到40000，但如果这样定义，内存会超限，
//  程序中使用了500，最终通过，还是有点侥幸的，但C++中可以直接使用不定长数组。
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char name[40000][5];
long course[2501][500];
long count[2501];//纪录每一门课程的注册人数

int compare(const void *a , const void *b){
    long m , n;
    m = (*(long *)a);
    n = (*(long *)b);
    return strcmp(name[m] , name[n]);
}

int main(){
    long n , k , c;
    long index;
    long i , j;

    scanf("%ld%ld" , &n , &k);
    // 初始化count
    for(i = 0;i < 2501;i++)
        count[i] = 0;
    for(i = 0;i < n;i++){
        scanf("%s%ld" , name[i] , &c);
        for(j = 0;j < c;j++){
            scanf("%ld" , &index);
            // 将学生在name中的索引赋给对应的课程，课程计数加一
            course[index][count[index]++] = i;
        }
    }
    for(i = 1;i <= k;i++){
        printf("%ld %ld\n" , i , count[i]);
        // 按字典顺序排序
        qsort(course[i] , count[i] , sizeof(long) , compare);
        for(j = 0;j < count[i];j++)
            printf("%s\n" , name[course[i][j]]);
    }
}