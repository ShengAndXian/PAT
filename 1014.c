// PAT甲级1014 Waiting in Line，原题地址：https://www.patest.cn/contests/pat-a-practise/1014
// 解题分析：
//  模拟题。不同窗口都有一个队列，因此可以使用一个二维数组来模拟。每一个窗口都有一个front和rear，用于记录队列的起始和
//  结束。变量count用于记录当前服务的顾客的序号。初始时，先把每个窗口依次排满。然后依次处理k个顾客。我们需要记录每个
//  窗口的当前时间，每次我们遍历一遍所有窗口，选择所对应的队列中的第一个顾客的业务处理时间最短的窗口，将第一个顾客出队，
//  其业务结束时间即为窗口的当前时间加上业务处理事件，并更新窗口的当前时间，然后将下一个顾客入队，同时更新其他窗口的当前
//  时间和对应队列中第一个顾客的业务处理时间。一直执行该步骤直到所有用户都已处理完成。输出时对于业务开始办理时间超过17点的，
//  输出Sorry，否则输出业务完成时间。
#include<stdio.h>

int main(){
    int queue[20][1000];
    int front[20] , rear[20];
    int prev_time[20];
    int count = 1;
    int stay_time[1001];
    int stay_time_1[1001];
    int leave_time[1001];
    int N , M , K , Q;
    int i , j;
    int min_time , transaction_time;
    int flag;
    int num , tmp;
    int hour , minute;

    // 输入
    scanf("%d %d %d %d" , &N , &M , &K , &Q);
    for(i = 1;i <= K;i++){
        scanf("%d" , &stay_time[i]);
        stay_time_1[i] = stay_time[i];
    }
    // 队列初始化，各个窗口的当前时间初始化（假设是0点，最后输出时时间加上8即可）
    for(i = 0;i < 20;i++){
        front[i] = 0;
        rear[i] = -1;
        prev_time[i] = 0;
    }
    // 将每个窗口一次排满
    for(i = 0;i < M;i++){
        for(j = 0;j < N;j++){
            queue[j][i] = count++;
            rear[j]++;
        }
    }
    
    // 处理所有客户
    for(j = 0;j < K;j++){
        // 选择对应队列的第一个客户业务处理时间最短的窗口
        min_time = 100000;
        for(i = 0;i < N;i++){
            tmp = queue[i][front[i]];
            // 客户序号大于k的直接跳过
            if(tmp > K)
                continue;
            transaction_time = stay_time[tmp];
            if(transaction_time < min_time){
                min_time = transaction_time;
                flag = i;
            }
        }
        // 第一个客户出队
        num = queue[flag][front[flag]++];
        // 下一个客户入队
        queue[flag][++rear[flag]] = count++;
        // 出队的客户的业务结束时间等于该窗口的当前时间加上客户的业务处理时间
        leave_time[num] = stay_time[num] + prev_time[flag];
        // 更新当前窗口的当前时间
        prev_time[flag] += stay_time[num];
        // 更新其他窗口的当前时间和对应队列中的第一个客户的业务处理时间
        for(i = 0;i < N;i++){
            if(flag == i)
                continue;
            tmp = queue[i][front[i]];
            // 客户序号为k则直接跳过
            if(tmp > K)
                continue;
            // 更新客户的业务处理时间
            stay_time[tmp] -= stay_time[num];
            // 更新窗口的当前时间
            prev_time[i] += stay_time[num];
        }
    }

    // 输出
    for(i = 0;i < Q;i++){
        scanf("%d" , &tmp);
        // 业务受理时间大于17点的输出Sorry
        if(leave_time[tmp] - stay_time_1[tmp] >= 9 * 60)//坑，输出sorry的应该是业务开始办理时间在17:00之后的，而不是结束时间在17:00之后的
            printf("Sorry\n");
        // 否则，输出业务结束时间
        else{   
            // 因为初始时间是0点，因此最终时间加8个小时
            hour = leave_time[tmp] / 60 + 8;
            minute = leave_time[tmp] % 60;
            printf("%02d:%02d\n" , hour , minute);
        }
    }
}