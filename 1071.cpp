// PAT甲级1071 Speech Patterns，原题地址：https://www.patest.cn/contests/pat-a-practise/1071
// 解题分析：
//  这题用C++中的string类可以很好的解决，只需要将每个单词分离出来，然后排序，最后计算相同的字符串有几个，输出
//  最大的即可。如果用c的话，一个单词的长度没有给定，很难直接定义字符数组的大小，开太大了容易内存超限，所以c++
//  更方便。
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
#define Max 1100000

string s[Max];

// 检测字符是否是数字或字母
bool Check(char c){
    if((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return true;
    else    
        return false;
}

int main(){
    char c;
    char pre = '\n';
    long cnt = 0;
    long max = -1;
    long index;
    long start , end;

    do{
        c = getchar();
        // 如果是数字或字母，则接到字符串后面
        if(Check(c)){
            if(c >= 'A' && c <='Z')
                c = c - 'A' + 'a';
            s[cnt] += c;
        }
        // 如果不是数字或字母，但前一个字符是，说明上一个单词已经读取完成了
        else if(Check(pre))
            cnt++;
        pre = c;
    }while(c != '\n');
    // 排序
    sort(s , s + cnt);
    // 计算相同的字符串的个数
    for(start = 0;start < cnt;start++){
        end = start;
        while(s[end] == s[end + 1])
            end++;
        // 选择个数最多的
        if(end - start + 1 > max){
            max = end - start + 1;
            index = start;
        }
        start = end;
    }
    // 输出
    cout << s[index] << " " << max << endl;
}