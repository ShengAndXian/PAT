// PAT甲级1017 Queueing at Bank，原题地址：https://www.patest.cn/contests/pat-a-practise/1017
// 解题分析：
//  模拟题。姥姥好像对银行排队问题很感兴趣。。。首先所有窗口的起始时间是8点，对于输入的用户先按时间顺序排序。
//  然后每次选取业务结束时间最早的窗口，下一位客户将在该窗口办理业务。如果客户到达时间晚于窗口的业务结束时间
//  则客户不需要等待，处理完该客户之后更新窗口的业务结束时间。如果客户到达时间早于窗口的业务结束时间，则客户
//  的等待时间为窗口的业务结束时间减去客户的到达时间，更新窗口的业务结束时间。一直执行该步骤知道所有客户处理
//  完毕。之后用所有客户的等待时间除客户人数即可得到平均等待时间。这里要注意所有客户不包括到达时间晚于17点的
//  人。另外，业务办理需要两个小时的需要将时间压缩成两个小时。
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct {
    int hour;
    int minute;
    int second;
    int total_time;
    int process_time;
} info;

int compare(const void *a , const void *b){
    return (*(info *)a).total_time - (*(info *)b).total_time;
}

int main(){
    info arr[10000];
    int window[100];
    int n , k;
    int i , j , tmp;
    int min;
    int hour , minute , second;
    int process_time;
    int count = 0;
    float wait_time = 0;

    scanf("%d %d" , &n , &k);
    // 初始化所有窗口，时间开始为8点
    for(i = 0;i < k;i++){
        window[i] = 8 * 3600;
    }
    // 输入
    for(i = 0;i < n;i++){
        scanf("%d:%d:%d %d" , &hour , &minute , &second , &process_time);
        // 到达时间超过17点的不受理
        if(hour * 3600 + minute * 60 + second > 17 * 3600)
            continue;
        // count记录所有被受理业务的客户人数
        count++;
        arr[count - 1].hour = hour;
        arr[count - 1].minute = minute;
        arr[count - 1].second = second;
        arr[count - 1].total_time = hour * 3600 + minute * 60 + second;
        // 业务办理时间超过两小时要压缩成两小时
        if(process_time > 60)
            process_time = 60;
        arr[count - 1].process_time = process_time;
    }
    // 对客户排序
    qsort(arr , count , sizeof(info) , compare);
    
    // 依次处理所有客户
    for(i = 0;i < count;i++){
        // 选择业务结束时间最早的窗口
        min = window[0];
        tmp = 0;
        for(j = 1;j < k;j++){
            if(window[j] < min){
                min = window[j];
                tmp = j;
            }
        }
        // 如果客户到达时间晚于业务结束时间
        if(window[tmp] <= arr[i].total_time){
            // 窗口的业务结束时间等于客户到达时间加上业务处理时间
            window[tmp] = arr[i].total_time + arr[i].process_time * 60;
        }
        // 否则
        else{
            // 客户的等待时间等于窗口的业务结束时间减去客户到达时间，并加到总的等待时间中
            wait_time += window[tmp] - arr[i].total_time;
            // 窗口的业务结束时间等于当前时间加上业务办理时间
            window[tmp] += arr[i].process_time * 60;
        }
    }

    // 没有客户在17点之前到达
    if(count == 0)
        printf("0.0");
    else
        printf("%.1f" , wait_time / 60 / count);
}