// PAT甲级1035 Password，原题地址：https://www.patest.cn/contests/pat-a-practise/1035
// 解题分析：
//  一道简单的字符串处理题。
#include<stdio.h>
#include<string.h>

struct record{
    char name[11];
    char password[11];
};

int main(){
    struct record R[1000];
    int arr[1000];
    int n;
    int i , j;
    int count = 0;
    char name[11];
    char password[11];
    int flag;

    scanf("%d" , &n);
    for(i = 0;i < n;i++){
        // 输入
        scanf("%s %s" , name , password);
        // 输入的时候就开始处理
        flag = 0;
        // 遍历密码中的每一个字符，如果要修改，则flag为1
        for(j = 0;password[j] != '\0';j++){
            switch(password[j]){
                case '1':{
                    password[j] = '@';
                    flag = 1;
                };break;
                case '0':{
                    password[j] = '%';
                    flag = 1;
                };break;
                case 'l':{
                    password[j] = 'L';
                    flag = 1;
                };break;
                case 'O':{
                    password[j] = 'o';
                    flag = 1;
                };break;
            }
        }
        // arr数组储存被修改的用户在R数组中的索引
        if(flag == 1){
            arr[count++] = i;
        }
        // 将输入的信息拷贝给R数组中的元素
        strcpy(R[i].name , name);
        strcpy(R[i].password , password);
    }
    // 对于不同情况分类讨论
    if(count == 0){
        if(n == 1)
            printf("There is 1 account and no account is modified\n");
        else
            printf("There are %d accounts and no account is modified\n" , n);
    }
    else{
        printf("%d\n" , count);
        for(i = 0;i < count;i++)
            printf("%s %s\n" , R[arr[i]].name , R[arr[i]].password);
    }

}