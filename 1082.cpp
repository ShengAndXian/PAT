// PAT甲级1082 Read Number in Chinese，原题地址：https://www.patest.cn/contests/pat-a-practise/1082
// 解题分析：
//  分长度讨论，0的情况特殊处理，输出的时候注意空格就好了。
#include<iostream>
#include<string>
using namespace std;

int main(){
    string s;
    string num[10] = {"ling" , "yi" , "er" , "san" , "si" , "wu" , "liu" , "qi" , "ba" , "jiu"};
    string loc[10] = {" " , " " , "Shi" , "Bai" , "Qian" , "Wan" , "Shi" , "Bai" , "Qian" , "Yi"};
    int len;
    int i = 0;
    int flag;
    int temp;

    cin >> s;
    len = s.length();
    // 负数
    if(s[0] == '-'){
        cout << "Fu";
        len--;
    }
    while(s[i] == '-' || s[i] == '0')
        i++;
    temp = i;
    // 遍历各个位的数
    for(;i < s.length();i++){
        // 0的情况
        if(s[i] == '0'){
            flag = 0;
            int j;
            // 寻找之后有没有非0的数
            for(j = i + 1;j < s.length();j++){
                if(s[j] != '0'){
                    flag = 1;
                    break;   
                }
            }
            // 如果之后有非0的数
            if(flag){
                cout << " ling";
                len -= j - i;
                i = j - 1;
            }
            // 如果没有非0的数
            else{
                cout << endl;
                return 0;
            }
        }
        // 非0的情况
        else{
            // 注意空格的输出
            if(i != temp || s[0] == '-')
                cout << " ";
            // 输出数字
            cout << num[s[i] - '0'];
            // 长度为9
            if(len == 9){
                cout << " Yi";
            }
            // 长度在5和8之间
            if(len > 5 && len <= 8){
                cout << " ";
                flag = 0;
                int j;
                for(j = i + 1;j < s.length() - 4;j++){
                    if(s[j] != '0')
                        flag = 1;
                }
                if(flag)
                    cout << loc[len];
                else
                    cout << loc[len] << " " << "Wan";
            }
            // 长度在1和5之间
            if(len > 1 && len <= 5){
                cout << " ";
                cout << loc[len];
            }
            // 长度为1
            if(len == 1){
                cout << endl;
                return 0;
            }
            len--;
        }
    }
    // 输入为0
    cout << "ling" << endl;
    return 0;
}