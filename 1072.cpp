// PAT甲级1072 Gas Station，原题地址：https://www.patest.cn/contests/pat-a-practise/1072
// 解题分析：
//  Dijkstra算法的应用。将加油站和居民区看做同样的节点，加油站的索引为n+1到n+m，然后依次以各个加油站
//  为起点，求最短路径，然后遍历所有居民区，求它们的最短路径中的最小的最短路径，并计算所有最短路径的和，
//  如果从加油站无法到达居民区或到达某个居民区的最短路径超过给定的范围，该加油站就不可能是解决方案。所有
//  加油站都处理完之后，遍历所有所有的加油站，不可能的加油站直接跳过，可能的加油站里优先考虑最小最短路径
//  较大的（比较拗口，对应题目中的第一句话），如果相同，接着考虑平均最短路径较小的，如果还相同，考虑编号小的。
//  最后输出即可。
#include<iostream>
#include<string>
#include<sstream>
#include<stdio.h>
using namespace std;
#define Max 1100
#define INFINITY 10000000

// 纪录加油站信息
struct record{
    float minDis;
    float aveDis;
    bool possible;
};

int G[Max][Max];
int Distance[Max];
bool Visited[Max];
struct record R[11];
int n , m , k , d;

// 将输入的字符串转换成整数
void Convert(string &s , int &id){
    stringstream stream;

    if(s[0] != 'G'){
        stream << s;
        stream >> id;
    }
    else{
        if(s.length() == 3)
            id = n + 10;
        else{
            stream << s[1];
            stream >> id;
            id += n;
        }
    }
}

// 最短路径算法
void Dijkstra(int index){
    int i , j;
    int min;
    int temp;

    Distance[index] = 0;
    while(1){
        min = INFINITY;
        for(i = 1;i <= n + m;i++){
            if(Visited[i] == false && Distance[i] < min){
                min = Distance[i];
                temp = i;
            }
        }
        if(min == INFINITY)
            break;
        Visited[temp] = true;
        for(j = 1;j <= n + m;j++){
            if(j == temp || Visited[j] == true)
                continue;
            if(G[temp][j] > 0 && G[temp][j] + Distance[temp] < Distance[j])
                Distance[j] = G[temp][j] + Distance[temp];
        }
    }
}

int main(){
    string s1 , s2;
    int id1 , id2;
    int len;
    int i , j;
    int index = -1;
    float max;
    float sum;
    float min;

    // 输入
    cin >> n >> m >> k >> d;
    for(i = 0;i < k;i++){
        cin >> s1 >> s2 >> len;
        Convert(s1 , id1);
        Convert(s2 , id2);
        G[id1][id2] = len;
        G[id2][id1] = len;
    }
    // 每个加油站最初都可能是解决方案
    for(i = 1;i < 11;i++)
        R[i].possible = true;
    // 依次处理各个加油站
    for(i = n + 1;i <= n + m;i++){
        // 初始化visited数组和distance数组
        for(j = 1;j <= n + m;j++){
            Visited[j] = false;
            Distance[j] = INFINITY;
        }
        // 求最短路径
        Dijkstra(i);
        // 遍历居民区
        for(j = 1;j <= n;j++){
            // 无法到达某个居民区
            if(Visited[j] == false){
                R[i - n].possible = false;
                break;
            }
        }
        // 所有居民区都可到达
        if(j == n + 1){
            sum = 0;
            min = INFINITY;
            for(j = 1;j <= n;j++){
                // 到达某个居民区的最短路径超过限制
                if(Distance[j] > d){
                    R[i - n].possible = false;
                    break;
                }
                // 求最小最短路径
                if(Distance[j] < min){
                    min = Distance[j];
                }
                // 求最短路径的和
                sum += Distance[j];
            }
            R[i - n].minDis = min;
            R[i - n].aveDis = sum / n;
        }
    }
    // 遍历所有加油站
    for(i = 1;i <= m;i++){
        // 不可能的直接跳过
        if(R[i].possible == false)
            continue;
        // 最小最短路径较大的优先考虑
        if(R[i].minDis > max){
            max = R[i].minDis;
            index = i;
        }
        else if(R[i].minDis == max){
            // 接着考虑平均最短路径
            if(R[i].aveDis < R[index].aveDis)
                index = i;
        }
    }
    // 输出
    if(index == -1)
        printf("No Solution\n");
    else
        printf("G%d\n%.1f %.1f\n" , index , R[index].minDis , R[index].aveDis);
    return 0;
        
}
