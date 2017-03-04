// PAT甲级1100 Mars Numbers，原题地址：https://www.patest.cn/contests/pat-a-practise/1100
// 解题分析：
//  进制转换。需要注意的是输入的数字是13的倍数时，输出结果应该是一位，最低位的0不需要输出，字符串转数字同理。
#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main(){
    string arr[25] = {"tret","jan","feb","mar","apr","may","jun","jly","aug","sep","oct","nov","dec","tam","hel","maa","huh","tou","kes","hei","elo","syy","lok","mer","jou"};
    char ch;
    vector<char> v;
    int n , i;
    int flag;

    cin >> n;
    getchar();
    for(i = 0;i < n;i++){
        v.clear();
        flag = 0;
        // 输入
        while((ch = getchar()) != '\n'){
            v.push_back(ch);
            if(ch == ' ')
                flag = 1;
        }
        // 如果是数字
        if(v[0] >= '0' && v[0] <= '9'){
            int res = 0 , t = 1;
            // 计算数字大小
            for(int j = v.size() - 1;j >= 0;j--){
                res += (v[j] - '0') * t;
                t *= 10;
            }
            // 如果在0到12之间
            if(res >= 0 && res <= 12)
                cout << arr[res] << endl;
            // 如果是13的倍数
            else if(res % 13 == 0)
                cout << arr[res / 13 + 12] << endl;
            // 否则
            else
                cout<< arr[res / 13 + 12] << " " << arr[res % 13] << endl;
        }
        // 如果是字符串
        else{
            string s;
            int res = 0;
            int j , k;
            // 有两个字符串（有空格）
            if(flag){
                // 第一个字符串
                for(j = 0;v[j] != ' ';j++)
                    s += v[j];
                // 计算
                for(k = 13;k < 25;k++)
                    if(arr[k] == s){
                        res += (k - 12) * 13;
                        break;
                    }
                // 第二个字符串
                s = "";
                for(k = j + 1;k < v.size();k++)
                    s += v[k];
                // 计算
                for(k = 0;k < 13;k++)
                    if(arr[k] == s){
                        res += k;
                        break;
                    }
                // 输出
                cout << res << endl;
            }
            // 只有一个字符串
            else{
                // 计算
                for(j = 0;j < v.size();j++)
                    s += v[j];
                // 输出
                for(j = 0;j < 13;j++)
                    if(arr[j] == s){
                        cout << j << endl;
                        break;
                    }
                for(j = 13;j < 25;j++)
                    if(arr[j] == s){
                        cout << (j - 12) * 13 << endl;
                        break;
                    }
            }
        }
    }
}
