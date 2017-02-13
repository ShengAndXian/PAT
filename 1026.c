// PAT甲级1026 Table Tennis，原题地址：https://www.patest.cn/contests/pat-a-practise/1026
// 解题分析：
//  模拟题。玩家信息用一个结构体player储存，桌子信息用一个结构体table储存。首先，输入的玩家的到达时间是无序的，
//  因此先要对他们排序。接着，每次遍历一遍所有桌子，选择结束时间最早的桌子，然后在玩家队列中选择到达时间小于等于
//  最早结束时间的玩家，将其放入等待队列。因为方便对vip玩家的删除操作，所以程序中选择使用链表来模拟队列。所有符合
//  条件的玩家入队后，选择其中一个玩家出队。这里需要注意：
//  1、如果桌子是vip桌，则要在等待队列中搜索vip玩家，如果有，则桌子要给第一个vip玩家，否则给第一个等待的人
//  2、如果桌子不是vip桌，并且第一个等待的人不是vip，则直接将桌子给他
//  3、如果桌子不是vip桌，但第一个等待的人是vip，则要判断这个时间点是否有vip桌空余，如果有，则将vip玩家安排到vip桌，
//  否则，将vip玩家安排到当前桌。
//  如果等待队列中没有玩家，说明下一个玩家到达时已有空桌，如果该玩家是普通玩家，则安排序号最小的空桌，如果该玩家是vip玩家，
//  则先安排序号最小的vip桌，如果没有空余的vip桌，再安排序号最小的普通桌。
//  对于服务时间超过21点的，先假设对他们进行安排，但桌子的服务人数不更新。输出时按服务时间排序，服务时间超过21点的，不输出。
//  另外注意输出等待时间时要四舍五入，具体在程序中有注释。
#include<stdio.h>
#include<stdlib.h>

struct table{
    int vip;
    int current_time;
    int number;
};//储存桌子信息

struct player{
    int arrive_time;
    int play_time;
    int serve_time;
    float wait_time;
    int vip;
};//储存玩家信息

struct node{
    int index;
    struct node *next;
};//等待链表中的节点

void print_time(int n);
int compare_arrive(const void *a , const void *b);
int compare_serve(const void *a , const void *b);

int main(){
    struct player P[10000];
    struct table T[100];
    struct node *head;
    struct node *ptr , *rear;
    struct node *ptr1;
    int n;
    int hour , minute , second;
    int play_time;
    int vip;
    int k , m , vip_index;
    int i;
    int min;
    int temp;
    int start = 0;
    int index;
    int flag;

    // 输入玩家信息
    scanf("%d" , &n);
    for(i = 0;i < n;i++){
        scanf("%d:%d:%d %d %d" , &hour , &minute , &second , &play_time , &vip);
        // 时间转换成秒
        P[i].arrive_time = hour * 3600 + minute * 60 + second;
        // 玩的时间超过两小时要压缩成两小时
        if(play_time > 120)
            play_time = 120;
        P[i].play_time = play_time * 60;
        P[i].vip = vip;
    }
    // 输入桌子信息
    scanf("%d %d" , &k , &m);
    for(i = 1;i <= k;i++){
        T[i].vip = 0;
        T[i].number = 0;
        // 从8点开始
        T[i].current_time = 8 * 3600;
    }
    // 输入vip桌子序号
    for(i = 0;i < m;i++){
        scanf("%d" , &vip_index);
        T[vip_index].vip = 1;
    }

    // 对玩家序列排序
    qsort(P , n , sizeof(struct player) , compare_arrive);
    // 构建等待队列
    head = (struct node *)malloc(sizeof(struct node));
    head->next = NULL;
    rear = head;
    // 处理玩家
    while(1){
        // 找出结束时间最早的桌子
        temp = 1;
        min = T[1].current_time;
        for(i = 2;i <= k;i++){
            if(T[i].current_time < min){
                min = T[i].current_time;
                temp = i;
            }
        }
        // 将玩家队列中到达时间比最小结束时间早的玩家加入等待队列
        for(i = start;i < n;i++){
            if(P[i].arrive_time <= min){
                ptr = (struct node *)malloc(sizeof(struct node));
                ptr->index = i;
                ptr->next = NULL;
                rear->next = ptr;
                rear = ptr;
            }
            else
                break;
        }
        start = i;
        // 如果等待队列为空
        if(rear == head){
            // start等于n说明所有玩家已经处理，结束循环
            if(start >= n)
                break;
            // 如果还有玩家没有处理
            flag = 0;
            // 如果下一个玩家是vip
            if(P[start].vip){
                // 先安排序号最小vip桌
                for(i = 1;i <= k;i++){
                    if(T[i].vip && P[start].arrive_time >= T[i].current_time){
                        flag = 1;
                        temp = i;
                    }
                }
            }
            // 如果玩家不是vip玩家或者是vip玩家但没有空余vip桌子
            if(flag == 0){
                // 安排序号最小的桌子
                for(i = 1;i <= k;i++){
                    if(P[start].arrive_time >= T[i].current_time){
                        temp = i;
                        break;
                    }
                }
            }
            // 更新玩家信息
            P[start].serve_time = P[start].arrive_time;
            P[start].wait_time = 0;
            // 如果服务时间早于21点，则桌子的服务人数加一
            if(P[start].serve_time < 21 * 3600)
                T[temp].number++;
            // 更新桌子的结束时间
            T[temp].current_time = P[start].arrive_time + P[start].play_time;
            start++;
        }
        // 如果等待队列不为空
        else{
            flag = 0;
            // 如果是vip桌子，则搜索等待队列中是否有vip玩家，如果有，则flag等于1
            if(T[temp].vip == 1){
                ptr = head->next;
                ptr1 = head;
                while(ptr != NULL){
                    if(P[ptr->index].vip == 1){
                        flag = 1;
                        break;
                    }
                    ptr = ptr->next;
                    ptr1 = ptr1->next;
                }
            }
            // 如果是普通桌子
            else{
                ptr = head->next;
                // 先判断第一个等待的玩家是否是vip玩家，如果是，则更新当前桌子的序号为vip桌
                if(P[ptr->index].vip == 1){
                    for(i = 1;i <= k;i++){
                        if(T[i].vip && P[ptr->index].arrive_time >= T[i].current_time){
                            temp = i;
                            break;
                        }
                    }

                }
            }
            // 如果是普通桌子或者是vip桌但等待队列中没有vip玩家
            if(flag == 0){
                ptr1 = head;
                ptr = head->next;
            }
            // 获取玩家序号
            index = ptr->index;
            if(ptr == rear){
                ptr1->next = NULL;
                rear = ptr1;
            }
            else
                ptr1->next = ptr->next;
            free(ptr);
            // 更新玩家和桌子信息
            P[index].serve_time = T[temp].current_time;
            P[index].wait_time = P[index].serve_time - P[index].arrive_time;
            if(P[index].serve_time < 21 * 3600)
                T[temp].number++;
            T[temp].current_time += P[index].play_time;
        }
    }

    // 对所有玩家按服务时间排序
    qsort(P , n , sizeof(struct player) , compare_serve);
    // 输出
    for(i = 0;i < n;i++){
        // 如果服务时间小于21点，则输出
        if(P[i].serve_time < 21 * 3600){
            print_time(P[i].arrive_time);
            print_time(P[i].serve_time);
            // 对等待时间做四舍五入处理
            printf("%d\n" , (int)(P[i].wait_time / 60 + 0.5));
        }
    }
    // 输出桌子的服务人数
    printf("%d" , T[1].number);
    for(i = 2;i <= k;i++)
        printf(" %d" , T[i].number);
}

void print_time(int n){
    int hour , minute , second;

    hour = n / 3600;
    n = n % 3600;
    minute = n / 60;
    n = n % 60;
    second = n;
    printf("%02d:%02d:%02d " , hour , minute , second);
}

int compare_arrive(const void *a , const void *b){
    return (*(struct player *)a).arrive_time - (*(struct player *)b).arrive_time;
}

int compare_serve(const void *a , const void *b){
    return (*(struct player *)a).serve_time - (*(struct player *)b).serve_time;
}