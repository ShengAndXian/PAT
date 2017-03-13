// PAT甲级1124 Raffle for Weibo Followers，原题地址：https://www.patest.cn/contests/pat-a-practise/1124
// 解题分析：
//  简单题。
#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main(){
    int m , n , s;
    int i , j;
    string s1[1100];
    vector<string> s2;

    cin >> m >> n >> s;
    for(i = 1;i <= m;i++){
        cin >> s1[i];
    }
    if(m < s){
        cout << "Keep going..." << endl;
    }
    else{
        int index = s;
        for(;index <= m;){
            for(j = 0;j < s2.size();j++){
                if(s1[index] == s2[j]){
                    break;
                }
            }
            if(j < s2.size()){
                index++;
            }
            else{
                cout << s1[index] << endl;
                s2.push_back(s1[index]);
                index += n;
            }
        }
    }
    return 0;
}