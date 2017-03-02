// PAT甲级1095 Cars on Campus，原题地址：https://www.patest.cn/contests/pat-a-practise/1095
// 解题分析：
//  排序题。先把所有数据排序，首先按车牌号排序，如果车牌号相同再按时间排序，排好后删去没有配对的记录，得到一个
//  新纪录，这个过程中我们可以得到停留时间最长的车和最长停留时间。然后将新得到的记录表按时间排序，每次查询都在
//  上次查询的结束位置开始，有车进来num就加一，有车出去就减一，最后输出即可。
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

struct record{
    string plate;
    int t;
    int status;
};

vector<struct record> v1;
vector<struct record> v2;
vector<string> l;
int pre , num;
int Max;
long n , k;

// 配对
void Update(){
    int i;
    int sum = 0;

    for(i = 0;i < n;i++){
        // 如果下一辆车的车牌号跟当前的不同，说明车牌号相同的车已经全部找到了
        if(i == n - 1 || v1[i + 1].plate != v1[i].plate){
            // 将该车牌号的车的停留时间和最长停留时间比较
            if(sum > Max){
                Max = sum;
                l.clear();
                l.push_back(v1[i].plate);
            }
            else if(sum == Max){
                l.push_back(v1[i].plate);
            }
            sum = 0;
        }
        // 如果下一辆车的车牌号跟当前的相同，并且当前的车为进入，下一辆为出去，说明可配对。
        else if(v1[i].status == 1 && v1[i + 1].status == 0){
            // 将可配对的记录加入到新纪录中
            v2.push_back(v1[i]);
            v2.push_back(v1[i + 1]);
            // 计算停留时间
            sum += v1[i + 1].t - v1[i].t;
        }
    }
}

// 查询
void Query(int t){
    int i;

    // 从上一次结束的位置开始查询
    for(i = pre;i < v2.size() && v2[i].t <= t;i++){
        // 进入
        if(v2[i].status == 1)
            num++;
        // 出去
        else
            num--;
    }
    pre = i;
    printf("%d\n" , num);
}

bool cmp1(struct record a , struct record b){
    if(a.plate != b.plate)
        return a.plate < b.plate;
    else
        return a.t < b.t;
}

bool cmp2(struct record a , struct record b){
    return a.t < b.t;
}

int main(){
    int hour , minute , second;
    int t;
    long i;
    string plate;
    string status;
    struct record R;

    scanf("%ld%ld" , &n , &k);
    // 输入
    for(i = 0;i < n;i++){
        cin >> plate;
        scanf("%d:%d:%d" , &hour , &minute , &second);
        cin >> status;

        R.plate = plate;
        R.t = hour * 3600 + minute * 60 + second;
        R.status = status[0] == 'i' ? 1 : 0;
        v1.push_back(R);
    }
    // 排序
    sort(v1.begin() , v1.end() , cmp1);
    // 更新记录，删去不配对记录
    Update();
    // 排序
    sort(v2.begin() , v2.end() , cmp2);
    // 查询
    for(i = 0;i < k;i++){
        scanf("%d:%d:%d" , &hour , &minute , &second);
        t = hour * 3600 + minute * 60 + second;
        Query(t);
    }
    // 输出
    for(i = 0;i < l.size();i++)
        cout << l[i] << " ";
    printf("%02d:%02d:%02d\n" , Max / 3600 , Max % 3600 / 60 , Max % 3600 % 60);
}