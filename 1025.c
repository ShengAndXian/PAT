// PAT甲级1025 PAT Ranking，原题地址：https://www.patest.cn/contests/pat-a-practise/1025
// 解题分析：
//  排序问题。用库函数qsort可以轻松解决。首先在输入一个地区的参加者的信息之后，要对同一地区的参赛者排序，计算
//  出本地排名，然后对所有参赛者排序，计算最终排名。计算排名时注意类似于1 1 3这样的排名。对于成绩相同的参赛者，
//  其排名相同，输出时按注册账号排序。
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct record{
    char reg_number[14];
    int score;
    int rank;
    int location_number;
    int local_rank;
};//储存参赛者信息

void rank_local(struct record arr[] , int n);
void rank_total(struct record arr[] , int n);
void output(struct record arr[] , int n);
int compare_score(const void *a , const void *b);
int compare_name(const void *a , const void *b);

int main(){
    int n , k;
    int i , j;
    int count = 1;
    int num = 0;
    char reg_number[14];
    int score;
    struct record list[30000];

    scanf("%d" , &n);
    // 分别输入n个地区的参赛者信息
    for(i = 1;i <= n;i++){
        scanf("%d" , &k);
        // 输入k个参赛者的信息
        for(j = 0;j < k;j++){
            scanf("%s %d" , list[j + num].reg_number , &list[j + num].score);
            // 当前参赛地区编号为count
            list[j + num].location_number = count;
        }
        // 对同一地区参赛者排序
        qsort(list + num , k , sizeof(struct record) , compare_score);
        // 计算本地排名
        rank_local(list + num , k);
        // 地区编号加一
        count++;
        // 更新参赛人数
        num += k;
    }
    // 对所有参赛者排序
    qsort(list , num , sizeof(struct record) , compare_score);
    // 计算总排名
    rank_total(list , num);
    // 输出
    output(list , num);
}

// 计算本地排名
void rank_local(struct record arr[] , int n){
    int i;

    // 第一个排名为1
    arr[0].local_rank = 1;
    // 从第二个参赛者开始
    for(i = 1;i < n;i++){
        // 如果当前参赛者的成绩和前一个参赛者成绩不同
        if(arr[i].score != arr[i-1].score)
            // 本地排名等于i加一
            arr[i].local_rank = i + 1;
        // 否则，本地排名于前一个参赛者排名相同
        else
            arr[i].local_rank = arr[i-1].local_rank;
    }
}

// 计算总排名
void rank_total(struct record arr[] , int n){
    int start = 0, end = 0;
    int i;

    // 第一个排名为1
    arr[0].rank = 1;
    // 从第二个开始
    for(i = 1;i < n;i++){
        // 如果当前参赛者的成绩和之前的参赛者成绩不同
        if(arr[i].score != arr[i - 1].score){
            // 总排名等于i加一
            arr[i].rank = i + 1;
            // 对之前成绩相同的参赛者按注册账号排序
            qsort(arr + start , end - start + 1 , sizeof(struct record) , compare_name);
            // 重置start，end
            start = i;
            end = i;
        }
        // 否则
        else{
            // 总排名等于前一个参赛者的排名
            arr[i].rank = arr[i-1].rank;
            // end等于当前参赛者的索引
            end = i;
        }
    }
}

// 输出
void output(struct record arr[] , int n){
    int i;

    printf("%d\n" , n);
    for(i = 0;i < n;i++)
        printf("%s %d %d %d\n" , arr[i].reg_number , arr[i].rank , arr[i].location_number , arr[i].local_rank);
}

int compare_score(const void *a , const void *b){
    return (*(struct record *)b).score - (*(struct record *)a).score;
}

int compare_name(const void *a , const void *b){
    return strcmp((*(struct record *)a).reg_number , (*(struct record *)b).reg_number);
}