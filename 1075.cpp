// PAT甲级1075 PAT Judge，原题地址：https://www.patest.cn/contests/pat-a-practise/1075
// 解题分析：
//  排序题。对于每一个用户，我们需要纪录他的id、每一题的得分、每一题的提交次数、总分以及通过的题数。
//  初始时将总分设为－1，每一题得分设为－1，如果没有提交过任何题目或者没有一道题通过编译，那么总分
//  始终是－1，排序后直接舍弃即可。排序时先根据总分，总分相同则按通过的题数，如果也相同再按id。输出时
//  需要注意，如果有用户提交过题目并且至少有一题通过了编译，则该用户需要被输出，如果其还提交了其他题目，
//  但没有通过编译，输出0，否则输出相应的分数。
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

// 储存用户信息
struct record{
    int id;
    int score[6];
    int submit[6];
    int total;
    int perfect;
};

struct record R[11000];
int problem[6];

// 排序
bool cmp(struct record a , struct record b){
    // 先根据总分
    if(a.total > b.total)
        return true;
    else if(a.total < b.total)
        return false;
    // 再根据通过的题数
    else{
        if(a.perfect > b.perfect)
            return true;
        else if(a.perfect < b.perfect)
            return false;
        // 最后根据id
        else
            return a.id < b.id;
    }
}

int main(){
    int n , k;
    int uid , pid , score;
    long m;
    long i , j;
    long start , end;
    int rank = 1;

    cin >> n >> k >> m;
    for(i = 1;i <= k;i++)
        cin >> problem[i];
    // 舒适化
    for(i = 1;i <= n;i++){
        R[i].id = i;
        R[i].total = -1;
        R[i].perfect = 0;
        for(j = 1;j <= k;j++){
            R[i].score[j] = -1;
            R[i].submit[j] = 0;
        }
    }
    // 输入
    for(i = 0;i < m;i++){
        cin >> uid >> pid >> score;
        // 如果分数大于原来的分数
        if(score > R[uid].score[pid]){
            // 如果总分为－1
            if(R[uid].total == -1)
                R[uid].total = 0;
            // 如果之前的分数是－1，则总分直接加上现在的得分即可
            if(R[uid].score[pid] == -1){
                R[uid].total += score;
            }
            // 否则需要加上二者之差
            else{
                R[uid].total += score - R[uid].score[pid];
            }
            // 纪录得分
            R[uid].score[pid] = score;
            // 如果通过该题
            if(score == problem[pid])
                R[uid].perfect++;
        }
        // 该题提交次数加一
        R[uid].submit[pid]++;
    }
    // 排序
    sort(R + 1 , R + n + 1 , cmp);
    // 输出
    for(start = 1;start <= n && R[start].total >= 0;start = end + 1){
        end = start + 1;
        while(end <= n && R[end].total == R[start].total)
            end++;
        end--;
        for(i = start;i <= end;i++){
            printf("%d %05d %d" , rank , R[i].id , R[i].total);
            for(j = 1;j <= k;j++){
                if(R[i].submit[j] == 0)
                    printf(" -");
                else if(R[i].score[j] == -1)
                    printf(" 0");
                else
                    printf(" %d" , R[i].score[j]);
            }
            printf("\n");
        }
        rank += end - start + 1;
    }
    return 0;
}