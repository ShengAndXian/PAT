// PAT甲级1039 Course List for Student，原题地址：https://www.patest.cn/contests/pat-a-practise/1039
// 解题分析：
//  排序题。先把所有数据存入数组，然后按姓名排序，搜索时使用二分查找法搜索，如果没找到则输出0，否则根据二分法得到的索引
//  前后继续搜索，得到该同学全部的课程信息，对其按课程号排序，然后输出。
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define Max 500001
struct record{
    char name[5];
    int course;
};//纪录学生的名字和课程号

int binary_search(char s[] , struct record student[] , int count);
int compare_1(const void *a , const void *b);
int compare_2(const void *a , const void *b);

int main(){
    int n , k;
    int i , j;
    int course , num;
    char name[5];
    struct record *student;
    int count = 0;
    int index;
    int start , end;

    // 构建数组
    student = (struct record *)malloc(sizeof(struct record) * Max);
    scanf("%d %d" , &n , &k);
    // k门课程
    for(i = 1;i <= k;i++){
        scanf("%d %d" , &course , &num);
        for(j = 0;j < num;j++){
            scanf("%s" , name);
            // 将学生信息放入数组
            student[count].course = course;
            strcpy(student[count].name , name);
            // 总人数加一
            count++;
        }
    }
    // 按姓名排序
    qsort(student , count , sizeof(struct record) , compare_1);
    for(i = 0;i < n;i++){
        scanf("%s" , name);
        printf("%s " , name);
        // 二分查找
        index = binary_search(name , student , count);
        // 没有找到
        if(index == -1)
            printf("0\n");
        // 找到了
        else{
            // 前后搜索该同学的所有课程
            start = end = index;
            while(start >= 0 && strcmp(student[start].name , student[index].name) == 0) 
                start--;
            while(end < count && strcmp(student[end].name , student[index].name) == 0)
                end++;
            start++;
            end--;
            // 按课程号排序
            qsort(student + start , end - start + 1 , sizeof(struct record) , compare_2);
            // 输出
            printf("%d" , end - start + 1);
            for(j = start;j <= end;j++)
                printf(" %d" , student[j].course);
            printf("\n");
        }
    }
}

// 二分查找
int binary_search(char s[] , struct record student[] , int count){
    int start = 0 , end = count - 1;
    int mid;
    int flag;

    while(1){
        if(start > end)
            return -1;
        mid = (start + end) / 2;
        flag = strcmp(student[mid].name , s);
        if(flag == 0)
            return mid;
        else if(flag > 0)
            end = mid - 1;
        else
            start = mid + 1;
    }
}   

int compare_1(const void *a , const void *b){
    return strcmp((*(struct record *)a).name , (*(struct record *)b).name);
}

int compare_2(const void *a , const void *b){
    return (*(struct record *)a).course - (*(struct record *)b).course;
}

