// PAT甲级1109 Group Photo，原题地址：https://www.patest.cn/contests/pat-a-practise/1109
// 解题分析：
//  先把所有人按身高从小到大排列，身高相同的按姓名从大到小排列。接着计算每一排要排多少人，这里注意要四舍五入，
//  最后一排人数没有限制。然后从第一排开始排，先排身高最高的，把他放在中间，然后是第二高的放在左边（实际上
//  就是他的右边，但对于我们来说就是左边，也就是序号小的那一边），接着把第三个放在左边，以此类推。排最后一排的
//  时候要重新计算那一排的人数。排完之后依次输出即可。
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

struct record{
    string name;
    int height;
};

struct record people[11000];
string group[20][11000];
int n , k;

bool cmp(struct record a , struct record b){
    if(a.height != b.height)
        return a.height < b.height;
    else
        return a.name > b.name;
}

int main(){
    int i , j;
    int m;
    int pre = 0;

    cin >> n >> k;
    for(i = 0;i < n;i++){
        cin >> people[i].name >> people[i].height;
    }
    // 排序
    sort(people , people + n , cmp);
    // 计算每一排的人数
    m = (int)((float)n / k + 0.5);
    for(i = 1;i <= k;i++){
        // 最后一排要重新计算人数
        if(i == k){
            m = n - pre;
        }
        // 中间点位置
        int pos = m / 2 + 1;
        int t = 0 , tmp = 1;
        bool flag = true;
        // 依次排列
        for(j = pre + m - 1;j >= pre;j--){
            group[i][pos + t] = people[j].name;
            // 下一次放左边
            if(flag){
                t = -tmp;
                flag = false;
            }
            // 下一次放右边
            else{
                t = tmp;
                tmp++;
                flag = true;
            }
        }
        // 前m个排列结束
        pre += m;
    }
    // 输出
    for(i = k;i >= 1;i--){
        for(j = 1;group[i][j] != "";j++){
            cout << group[i][j];
            if(group[i][j + 1] != "")
                cout << " ";
        }
        cout << endl;
    }
}