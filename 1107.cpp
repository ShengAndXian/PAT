// PAT甲级1107 Social Clusters，原题地址：https://www.patest.cn/contests/pat-a-practise/1107
// 解题分析：
//  DFS。首先我们要维护一个数组，数组的下标对应一种兴趣，数组内容是有同样兴趣的用户序列。我们从第一个兴趣开始，
//  遍历所有该兴趣的用户，遍历到一个用户时，查找他的所有兴趣，从他的第一个兴趣开始，执行和之前一样的操作，直到一个
//  群组被遍历完之后结束。为了在遇到一个用户时能快速找到他的所有兴趣，我们还需要维护一个数组来保存每一个用户的所有
//  兴趣。同时为了在DFS的时候不重复搜索，需要用两个visited数组来标记是否已被访问。全部遍历结束后我们就能得到群组
//  个数和对应的人数了，然后输出即可。
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define Max 1100000

vector<int> user[Max];
vector<int> hobby[Max];
vector<int> v;
int visitedUser[Max];
int visitedHobby[Max];
int total , cnt;
int n;

// DFS
void DFS(int index){
    int i;

    // 如果当前兴趣没有对应的用户或当前兴趣已被访问
    if(hobby[index].empty() || visitedHobby[index] == 1)
        return;
    // 否则，当前兴趣设为已访问
    visitedHobby[index] = 1;
    // 遍历所有有该兴趣的用户
    for(i = 0;i < hobby[index].size();i++){
        int temp = hobby[index][i];
        // 如果该用户没有被访问过
        if(visitedUser[temp] == 0){
            // 设为已访问
            visitedUser[temp] = 1;
            // 计数加一
            total++;
            // 遍历该用户的所有兴趣，每一个兴趣都DFS
            for(int j = 0;j < user[temp].size();j++){
                DFS(user[temp][j]);
            }
        }
    }
}

bool cmp(int a , int b){
    return a > b;
}

int main(){
    int i , k;
    int max = -1;

    // 输入
    cin >> n;
    for(i = 1;i <= n;i++){
        cin >> k;
        getchar();
        int num;
        for(int j = 0;j < k;j++){
            cin >> num;
            user[i].push_back(num);
            hobby[num].push_back(i);
            // 记录最大兴趣编号
            if(num > max)
                max = num;
        }
    }
    // 遍历所有兴趣
    for(i = 1;i <= max;i++){
        total = 0;
        // 没有访问过的兴趣
        if(visitedHobby[i] == 0){
            DFS(i);
            // 兴趣对应人数不为0
            if(total != 0){
                v.push_back(total);
                cnt++;
            }
        }
    }
    // 输出
    cout << cnt << endl;
    sort(v.begin() , v.end() , cmp);
    for(i = 0;i < v.size();i++){
        cout << v[i];
        if(i != v.size() - 1)
            cout << " ";
    }
    cout << endl;
    return 0;
}