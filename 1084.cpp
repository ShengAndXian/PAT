// PAT甲级1084 Broken Keyboard，原题地址：https://www.patest.cn/contests/pat-a-practise/1084
// 解题分析：
//  遍历第二个字符串，其中每一个字符都在第一个字符串中搜索，这样就可以获得一个区间，对区间内的字符，首先在
//  容器v中搜索，如果没有就将它放入，如果有则跳过。第二个字符串遍历完之后，如果第一个字符串还有剩余，执行区间
//  内字符相同的操作。
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    string str1 , str2;
    vector<char> v;
    int start , end;
    int i, j;

    cin >> str1 >> str2;
    start = end = 0;
    // 遍历第二个字符串
    for(i = 0;i < str2.length();i++){
        // 划分区间
        while(str1[end] != str2[i])
            end++;
        // 遍历区间内的字符
        for(j = start;j < end;j++){
            // 小写变成大写
            if(str1[j] >= 'a'&& str1[j] <= 'z')
                str1[j] = str1[j] - 'a' + 'A';
            // 在v查找
            if(find(v.begin(), v.end() , str1[j]) == v.end())
                v.push_back(str1[j]);
        }
        start = end + 1;
        end = start;
    }
    // 第一个字符串还有剩余
    while(start <str1.length()){
        if(str1[start] >= 'a' && str1[start] <= 'z')
            str1[start] = str1[start] - 'a' + 'A';
        if(find(v.begin(), v.end() , str1[start]) == v.end())
            v.push_back(str1[start]);
        start++;
    }
    // 输出
    for(i = 0;i < v.size();i++)
        cout << v[i];
    cout << endl;
}