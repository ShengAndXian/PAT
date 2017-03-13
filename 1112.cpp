// PAT甲级1112 Stucked Keyboard，原题地址：https://www.patest.cn/contests/pat-a-practise/1112
// 解题分析：
//  遍历字符串所有重复的连续序列，如果序列中的字符不是k的倍数，说明不是坏了的，flag标记为0，否则说明可能是坏了
//  的，flag标记为1（暂时的），并且在容器v中搜索字符，如果没有找到则将字符放入v中。遍历结束后，flag标记仍然为
//  1的就是坏了的，flag为0的是好的。然后依次输出v中的字符（先检查对于的flag是否为1，如果为1再输出，否则不输出）。
//  接着输出原字符串，注意坏了的字符每k个输出一个，通过flag检查是否是坏的。
#include<iostream>
#include<vector>
using namespace std;

int flag[37];
string s;
vector<char> v;

// 将字符转换成对于的数组下标
int Convert(char c){
    int t;
    if(c >= '0' && c <= '9'){
        t = c - '0';
    }
    else if(c >= 'a' && c <= 'z'){
        t = c - 'a' + 10;
    }
    else{
        t = 36;
    }
    return t; 
}
int main(){
    int i , j;
    int k;

    cin >> k;
    cin >> s;
    for(i = 0;i < 37;i++){
        flag[i] = 1;
    }
    for(i = 0;i < s.length();i = j + 1){
        // 搜索重复序列
        j = i + 1;
        while(j < s.length() && s[j] == s[i]) j++;
        j--;
        // 重复序列长度
        int cnt = j - i + 1;
        // 转换
        int t = Convert(s[i]);
        // 好的
        if(cnt % k != 0){
            flag[t] = 0;
        }
        // 坏了，并且之前的序列也显示坏的
        else if(flag[t] == 1){
            int k;
            for(k = 0;k < v.size();k++){
                if(v[k] == s[i]){
                    break;
                }
            }
            if(k == v.size()){
                v.push_back(s[i]);
            }
        }
    }
    // 输出坏了的字符
    for(i = 0;i < v.size();i++){
        int t;
        t = Convert(v[i]);
        // 检查flag
        if(flag[t] == 1){
            cout << v[i];
        }
    }
    cout << endl;
    // 输出原字符串
    for(i = 0;i < s.length();i = j + 1){
        j = i + 1;
        while(j < s.length() && s[j] == s[i]) j++;
        j--;
        int t = Convert(s[i]);
        if(flag[t] == 0){
            while(i <= j){
                cout << s[i];
                i++;
            }
        }
        else{
            t = (j - i + 1) / k;
            while(t > 0){
                cout << s[i];
                t--;
            }
        }
    }
    cout << endl;
    return 0;
}