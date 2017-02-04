// PAT甲级1033 To Fill or Not to Fill，原题地址：https://www.patest.cn/contests/pat-a-practise/1033
// 解题分析：
//  贪心算法。首先输入n个加油站，之后把终点当作一个价格为0，距离为终点距离的加油站，对这n＋1个加油站按离杭州的距离
//  升序排序。为了花最少的钱，我们应该这样做，如果我们当前处在一个加油站，而该加油站前方（可能隔了好几个加油站）的加
//  油站的价格比这个加油站的价格低，那么我们更希望去那个加油站加油，这时我们需要计算那个加油站离目前所处位置的距离，
//  如果这个我们可以用剩余的油开到，那么在现在的这个加油站我们就直接开过去，如果剩下的油不够，我们需要在当前的加油站
//  加油，那么加多少油呢？此时我们需要计算需要多少油才能开到那个加油站，如果需要的油超过了油缸的容量，则说明即使加满
//  了也不能一次开到，中间肯定还要加油，但中间的加油站的价格比现在这个还贵，所以我们在这个加油站一定要把油加满。如果
//  需要的油小于等于油缸的容量，说明我们加油后可以开到那个加油站，中间不需要加油，因此我们需要加的油量等于开到那个
//  加油站需要的油量减去剩余的油量。知道需要加的油量后更新费用。到达下一个加油站时，更新剩余油量，如果剩余油量为负，说明
//  到达不了终点，计算最大距离，输出。如果剩余油量为正，并且当前加油站不是终点站，执行之前的步骤即可。否则，直接输出费用。
#include<stdio.h>
#include<stdlib.h>

struct station{
    double price;
    double distance;
};

int compare(const void *a , const void *b){
    return (*(struct station *)a).distance - (*(struct station *)b).distance;
}

int main(){
    struct station *S;
    int n;
    int i , j;
    double c , d , a;
    double price;
    double distance;
    double remain = 0;
    double cost = 0;
    double temp;
    double need;
    double prev = 0;

    scanf("%lf %lf %lf %d" , &c , &d , &a , &n);
    S = (struct station *)malloc(sizeof(struct station) * (n + 1));
    // 输入n个加油站信息
    for(i = 0;i < n;i++){
        scanf("%lf %lf" , &price , &distance);
        S[i].price = price;
        S[i].distance = distance;
    }
    // 将终点当作一个加油站
    S[i].price = 0;
    S[i].distance = d;
    // 对n＋1个加油站排序
    qsort(S , n + 1 , sizeof(struct station) , compare);

    // 依次经过所有加油站
    for(i = 0;i <= n;i++){
        // 计算剩余油量
        temp = remain - (S[i].distance - prev) / a;
        // 如果剩余油量小于0
        if(temp < 0){
            // 计算最大距离
            temp = prev + remain * a;//把a写成12，调试了一个多小时，我真是太蠢了。。。。
            printf("The maximum travel distance = %.2lf" , temp);
            return 0;
        }
        // 如果剩余油量大于0
        else{
            // 如果当前的加油站不是终点站
            if(i != n){
                remain = temp;
            }
            // 否则
            else{
                printf("%.2lf" , cost);
                return 0;
            }
        }
        // 查找最近的价格比当前加油站价格低的加油站
        for(j = i + 1;j <= n;j++){
            if(S[j].price < S[i].price)
                break;
        }
        // 计算两者之间距离
        temp = S[j].distance - S[i].distance;
        // 如果剩下的油不够
        if(remain * a < temp){
            // 计算需要多少油
            need = temp / a;
            // 超过容量则则按容量计算
            if(need > c)
                need = c;
            // 计算费用
            cost += S[i].price * (need - remain);
            // 更新剩余油量
            remain = need;
        }
        // 记录当前加油站的距离，便于下一个加油站计算
        prev = S[i].distance;
    }
}