// PAT甲级1028 List Sorting，原题地址：https://www.patest.cn/contests/pat-a-practise/1028
// 解题分析：
//  一道简单的排序题，用qsort很轻松就可以解决。唯一需要注意的点是在对姓名或成绩排序时，有相同姓名或者成绩
//  的人，需要根据ID再次排序。
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student{
    char ID[7];
    char name[9];
    int grade;
};//储存学生信息

void sort_ID(struct student S[] , int n);
void sort_name(struct student S[] , int n);
void sort_grade(struct student S[] , int n);
int compare_ID(const void *a , const void *b);
int compare_name(const void *a , const void *b);
int compare_grade(const void *a , const void *b);


int main(){
    int n , c;
    struct student S[100000];
    char ID[7];
    char name[9];
    int grade;
    int i;

    // 输入
    scanf("%d %d" , &n , &c);
    for(i = 0;i < n;i++){
        scanf("%s %s %d" , ID , name , &grade);
        strcpy(S[i].ID , ID);
        strcpy(S[i].name , name);
        S[i].grade = grade;
    }

    // 根据不同的c做不同排序
    switch(c){
        case 1:sort_ID(S , n);break;
        case 2:sort_name(S , n);break;
        case 3:sort_grade(S , n);break;
    }
}

// 对ID排序
void sort_ID(struct student S[] , int n){
    int i;

    qsort(S , n , sizeof(struct student) , compare_ID);
    for(i = 0;i < n;i++){
        printf("%s %s %d\n" , S[i].ID , S[i].name , S[i].grade);
    }
}

// 对姓名排序
void sort_name(struct student S[] , int n){
    int i;
    int start , end;

    qsort(S , n , sizeof(struct student) , compare_name);
    // 用start和end标记有相同姓名的序列的开始和结束
    start = end = 0;
    for(i = 1;i < n;i++){
        // 如果当前的学生和之前的学生有相同的姓名，则加入序列
        if(strcmp(S[i].name , S[start].name) == 0){
            end = i;
        }
        // 否则
        else{
            // 先对前面的序列按ID排序
            qsort(S + start , end - start + 1 , sizeof(struct student) , compare_ID);
            // 更新start和end为当前序号
            start = end = i;
        }
    }
    // 如果拥有相同姓名的序列在整个序列的最后
    if(start != end)
        qsort(S + start , end - start + 1 , sizeof(struct student) , compare_ID);
    for(i = 0;i < n;i++){
        printf("%s %s %d\n" , S[i].ID , S[i].name , S[i].grade);
    }
}

// 对成绩排序，和对姓名排序类似
void sort_grade(struct student S[] , int n){
    int i;
    int start , end;

    qsort(S , n , sizeof(struct student) , compare_grade);
    start = end = 0;
    for(i = 1;i < n;i++){
        if(S[i].grade == S[start].grade){
            end = i;
        }
        else{
            qsort(S + start , end - start + 1 , sizeof(struct student) , compare_ID);
            start = end = i;
        }
    }   
    if(start != end)
        qsort(S + start , end - start + 1 , sizeof(struct student) , compare_ID);
    for(i = 0;i < n;i++){
        printf("%s %s %d\n" , S[i].ID , S[i].name , S[i].grade);
    }
}

int compare_ID(const void *a , const void *b){
    return strcmp((*(struct student *)a).ID , (*(struct student*)b).ID);
}

int compare_name(const void *a , const void *b){
    return strcmp((*(struct student *)a).name , (*(struct student*)b).name);
}

int compare_grade(const void *a , const void *b){
    return (*(struct student *)a).grade - (*(struct student *)b).grade;
}