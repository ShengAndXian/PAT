// PAT甲级1036 Boys vs Girls，原题地址：https://www.patest.cn/contests/pat-a-practise/1036
// 解题分析：
//  排序题。将男生和女生分别存储在不同的数组中，对他们按成绩从小到大排序，女生最大成绩在末尾，男生最小成绩
//  在开端，用变量male_count纪录男生的人数，female_count纪录女生的人数，如果变量值为0，则输出Absent，
//  否则输出姓名和ID。如果两个变量都不为0，最后输出最大成绩和最小成绩的差值，否则输出NA。
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct record{
    char name[11];
    char gender;
    char ID[11];
    int grade;
};//纪录学生信息

int compare(const void *a , const void *b){
    return (*(struct record *)a).grade - (*(struct record *)b).grade;
}

int main(){
    int n;
    int i;
    char name[11];
    char gender;
    char ID[11];
    int grade;
    struct record *male;
    struct record *female;
    int male_count = 0 , female_count = 0; 
    int flag = 0;

    scanf("%d" , &n);
    // 构建两个数组
    male = (struct record *)malloc(sizeof(struct record) * n);
    female = (struct record *)malloc(sizeof(struct record) * n);
    for(i = 0;i < n;i++){
        scanf("%s %c %s %d" , name , &gender , ID , &grade);
        // 如果输入的学生是男生
        if(gender == 'M'){
            // 添加纪录
            strcpy(male[male_count].name , name);
            male[male_count].gender = gender;
            strcpy(male[male_count].ID , ID);
            male[male_count].grade = grade;
            // 计数加一
            male_count++;
        }
        // 如果是女生
        else{
            // 添加纪录
            strcpy(female[female_count].name , name);
            female[female_count].gender = gender;
            strcpy(female[female_count].ID , ID);
            female[female_count].grade = grade;
            // 计数加一
            female_count++;
        }
    }
    // 排序
    qsort(male , male_count , sizeof(struct record) , compare);
    qsort(female , female_count , sizeof(struct record) , compare);
    // 如果女生人数为0
    if(female_count == 0){
        printf("Absent\n");
        flag = 1;
    }
    // 如果女生人数不为0
    else{
        printf("%s %s\n" , female[female_count - 1].name , female[female_count - 1].ID);
    }
    // 如果男生人数为0
    if(male_count == 0){
        printf("Absent\n");
        flag = 1;
    }
    // 如果男生人数不为0
    else{
        printf("%s %s\n" , male[0].name , male[0].ID);
    }
    // 如果有一方人数为0
    if(flag == 1)
        printf("NA\n");
    // 否则
    else
        printf("%d\n" , female[female_count - 1].grade - male[0].grade);

}