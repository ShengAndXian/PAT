// PAT甲级1012 The Best Rank，原题地址：https://www.patest.cn/contests/pat-a-practise/1012
// 解题分析：
//  排序题。为方便查询，用4个数组储存信息，输入完毕后对4个数组按A、C、M、E分别排序，然后在4个数组分别查询
//  所输入的ID对应的排名，注意1 2 2这样的排名序号不连续的情况，得到4个排名后，如果排名是－1，则输出N/A，
//  否则，选取最大的排名输出，并输出对应的项目。
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node{
    char ID[7];
    int A;
    int C;
    int M;
    int E;
};//储存用户信息
// 查找ID，获取排名
int search(char *ID , struct node *info , int N , int mode){
    int i = 0 , j = 0;
    int rank;

    // 如果ID不存在，则返回－1
    while(strcmp(info[i].ID , ID) != 0){
        if(i == N)
            return -1;
        i++;
    }
    // 如果前面不存在于和当前ID相同的排名，咋排名等于序号加一
    rank = i + 1;
    // 如果前面存在和当前ID相同的排名，则每存在一个相同排名，当前ID的排名减一
    while(strcmp(info[j].ID , ID) != 0){
        // 根据模式比较不同的项目
        if(mode == 0 && info[j].A == info[i].A)
            rank--;
        if(mode == 1 && info[j].C == info[i].C)
            rank--;
        if(mode == 2 && info[j].M == info[i].M)
            rank--;
        if(mode == 3 && info[j].E == info[i].E)
            rank--;
        j++;
    }
    return rank;
}

int compare_1(const void *a , const void *b){
    return (*(struct node*)b).A - (*(struct node*)a).A;
}

int compare_2(const void *a , const void *b){
    return (*(struct node*)b).C - (*(struct node*)a).C;
}

int compare_3(const void *a , const void *b){
    return (*(struct node*)b).M - (*(struct node*)a).M;
}

int compare_4(const void *a , const void *b){
    return (*(struct node*)b).E - (*(struct node*)a).E;
}

int main(){
    struct node *info_1 , *info_2 , *info_3 , *info_4;
    int N , T;
    int i , j;
    char ID[7];
    int C , M , E;
    int rank[4];
    int best;
    int flag;

    scanf("%d %d" , &N , &T);
    // 构建4个数组
    info_1 = (struct node *)malloc(sizeof(struct node) * N);
    info_2 = (struct node *)malloc(sizeof(struct node) * N);
    info_3 = (struct node *)malloc(sizeof(struct node) * N);
    info_4 = (struct node *)malloc(sizeof(struct node) * N);
    // 输入用户信息
    for(i = 0;i < N;i++){
        scanf("%s %d %d %d" , ID , &C , &M , &E);
        strcpy(info_1[i].ID , ID);
        strcpy(info_2[i].ID , ID);
        strcpy(info_3[i].ID , ID);
        strcpy(info_4[i].ID , ID);
        info_1[i].C = info_2[i].C = info_3[i].C = info_4[i].C = C;
        info_1[i].M = info_2[i].M = info_3[i].M = info_4[i].M = M;
        info_1[i].E = info_2[i].E = info_3[i].E = info_4[i].E = E;
        info_1[i].A = info_2[i].A = info_3[i].A = info_4[i].A = (C + M + E) / 3;
    }

    // 排序
    qsort(info_1 , N , sizeof(struct node) , compare_1);
    qsort(info_2 , N , sizeof(struct node) , compare_2);
    qsort(info_3 , N , sizeof(struct node) , compare_3);
    qsort(info_4 , N , sizeof(struct node) , compare_4);

    // 查询
    for(i = 0;i < T;i++){
        // 输入所要查询的用户ID
        scanf("%s" , ID);
        // 获取当前用户4个项目的排名
        rank[0] = search(ID , info_1 , N , 0);
        rank[1] = search(ID , info_2 , N , 1);
        rank[2] = search(ID , info_3 , N , 2);
        rank[3] = search(ID , info_4 , N , 3);
        // 如果ID不存在，则输出N/A
        if(rank[0] == -1 || rank[1] == -1 || rank[2] == -1 || rank[3] == -1){
            printf("N/A\n");
            continue;
        }
        // 查找最高排名，并纪录对应的项目
        best = rank[0];
        flag = 0;
        for(j = 1;j < 4;j++){
            if(rank[j] < best){
                best = rank[j];
                flag = j;
            }
        }
        // 输出最高排名以及对应的项目
        printf("%d " , best);
        switch(flag){
            case 0:printf("A\n");break;
            case 1:printf("C\n");break;
            case 2:printf("M\n");break;
            case 3:printf("E\n");break;
        }
    }
}