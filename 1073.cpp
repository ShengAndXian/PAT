// PAT甲级1073 Scientific Notation，原题地址：https://www.patest.cn/contests/pat-a-practise/1073
// 解题分析：
//  科学技术法转成普通表示法，注意小数点位置即可。
#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;

int main(){
    char s1[20000];
    string s2;
    int i , j;
    int temp = 0;
    int point;

    scanf("%s" ,s1);
    if(s1[0] == '-')
        printf("-");
    for(i = 1;s1[i] != 'E';i++){
        if(s1[i] != '.')
            s2 += s1[i];
    }
    for(j = i + 2;s1[j] != '\0';j++)
        temp = temp * 10 + s1[j] - '0';
    if(s1[i + 1] == '-')
        temp = -temp;
    if(temp < 0){
        cout << "0.";
        temp = -temp;
        for(i = 0;i < temp - 1;i++)
            cout << "0";
        cout << s2;
    }
    else if(temp >= 0){
        for(i = 0;i < s2.length() && i < temp + 1;i++)
            cout << s2[i];
        if(i == s2.length()){
            for(;i < temp + 1;i++)
                cout << "0";
        }
        else{
            cout << ".";
            for(;i < s2.length();i++)
                cout << s2[i];
        }
    }
    cout << endl;
    return 0;
}   