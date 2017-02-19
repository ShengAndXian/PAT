// PAT甲级1063 Set Similarity，原题地址：https://www.patest.cn/contests/pat-a-practise/1063
// 解题地址：
//  计算两个集合的相似度。同一个集合内，所有相同的数都看作只有一个这样的数，计算所有不同的数的个数时，两个集合
//  每两个相同的数都算一个，其他不同的数就依次统计即可，计算相同的数的个数只需依次统计即可。在统计前，需要对集合
//  进行排序，然后从下标0开始，如果一个集合的数比另一个集合小，则该集合的下标加一，纪录不同数的个数的变量dist加一，
//  如果两个集合的数相等，则两个集合的下标均加一，dist加一，纪录相同数的个数的变量com也加一。最后计算输出即可。
#include<stdio.h>
#include<stdlib.h>

struct record{
    int cnt;
    long arr[10000];
};

int cmp(const void *a , const void *b){
    return (*(long *)a) - (*(long *)b);
}

int main(){
    struct record R[51];
    int n , m , k;
    long num;
    int i , j;
    int com , dist;
    int s1 , e1 , s2 , e2 , prev1 , prev2;
    int set1 , set2;
    int flag;

    scanf("%d" , &n);
    for(i = 1;i <= n;i++){
        scanf("%d" , &m);
        R[i].cnt = 0;
        for(j = 0;j < m;j++){
            scanf("%ld" , &num);
            R[i].arr[R[i].cnt++] = num;
        }
        // 排序
        qsort(R[i].arr , R[i].cnt , sizeof(long) , cmp);
    }
    scanf("%d" , &k);
    for(i = 0;i < k;i++){
        scanf("%d%d" , &set1 , &set2);
        // 初始化
        s1 = s2 = 0;
        prev1 = prev2 = -1;
        com = dist = 0;
        while(1){
            // 循环结束条件
            if(s1 == R[set1].cnt || s2 == R[set2].cnt)
                break;
            // 如果集合1的下标移动了
            if(s1 != prev1){
                // 重新计算含有相同值的区间，e1为区间右边界
                for(e1 = s1 + 1;e1 < R[set1].cnt;e1++)
                    if(R[set1].arr[e1] != R[set1].arr[s1])
                        break;
                e1--;
            }
            // 如果集合2的下标移动了
            if(s2 != prev2){
                // 重新计算含有相同值的区间
                for(e2 = s2 + 1;e2 < R[set2].cnt;e2++)
                    if(R[set2].arr[e2] != R[set2].arr[s2])
                        break;
                e2--;
            }
            // 纪录当前的下标，用于判断下标是否移动，防止重复计算含有相同值的区间
            prev1 = s1;
            prev2 = s2;
            // 如果两个集合的值相等
            if(R[set1].arr[s1] == R[set2].arr[s2]){
                // 下标移动到下一个不相等的值处
                s1 = e1 + 1;
                s2 = e2 + 1;
                // 相应变量更新
                com++;
                dist++;
            }
            // 如果集合1的值大于集合2的值
            else if(R[set1].arr[s1] > R[set2].arr[s2]){
                // 更新集合2的下标
                s2 = e2 + 1;
                // dist加一
                dist++;
            }
            // 类似情况
            else{
                s1 = e1 + 1;
                dist++;
            }
        }
        // 如果集合2有剩余的数未和集合1比较
        if(s1 == R[set1].cnt && s2 != R[set2].cnt){
            flag = 1;
            for(e2 = s2;e2 < R[set2].cnt;e2++){
                if(e2 == s2){
                    if(flag){
                        flag = 0;
                        dist++;
                    }
                }
                else{
                    dist++;
                    s2 = e2;
                }
            }
        }
        // 如果集合1有剩余的数未和集合2比较
        if(s1 != R[set1].cnt && s2 == R[set2].cnt){
            flag = 1;
            for(e1 = s1;e1 < R[set1].cnt;e1++){
                if(e1 == s1){
                    if(flag){
                        flag = 0;
                        dist++;
                    }
                }
                else{
                    dist++;
                    s1 = e1;
                }
            }
        }
        // 输出
        printf("%.1f%%\n" , (float)com / dist * 100);
    }
}