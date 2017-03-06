// PAT甲级1108 Finding Average，原题地址：https://www.patest.cn/contests/pat-a-practise/1108
// 解题分析：
//  用字符串读入一个数，如果这个数的小数点超过一个或小数点后数字超过2个或包含其他不是数字的字符，则这个数不是
//  实数，另外如果该数比1000大或比－1000小，也不是实数。
#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main(){
    string s;
    vector<double> v;   
    int cnt = 0;
    int temp;
    int n , i , j;
    int flag;

    cin >> n;
    for(i = 0;i < n;i++){
        // 输入
        cin >> s;
        flag = 0;
        temp = 0;
        // 检查
        for(j = 0;j < s.length();j++){
            // 符号忽略（测试数据中的符号均在第一位）
            if(s[j] == '-')
                continue;
            // 如果是小数点
            if(s[j] == '.'){
                // 如果前面已经有一个小数点，退出循环
                if(flag){
                    break;
                }
                // 否则
                else{
                    flag = 1;
                }
            }
            // 如果是数字
            else if(s[j] >= '0' && s[j] <= '9'){
                // 如果是小数点后的数字
                if(flag){
                    temp++;
                    // 数字多于两个
                    if(temp > 2)
                        break;
                }
            }
            // 其他非数字非小数点字符
            else{
                break;
            }
        }
        // 不合法
        if(j != s.length()){
            cout << "ERROR: " << s << " is not a legal number" << endl;
        }
        else{
            // stod函数可以讲字符串转换成小数
            double num = stod(s);
            // 检查
            if(num >= -1000 && num <= 1000){
                v.push_back(num);
                cnt++;
            }
            // 不合法
            else{
                cout << "ERROR: " << s << " is not a legal number" << endl;
            }
        }
    }
    // 没有数字合法
    if(cnt == 0){
        cout << "The average of 0 numbers is Undefined" << endl;
    }
    // 有一个数字合法
    else if(cnt == 1){
        printf("The average of 1 number is %.2lf\n" , v[0]);
    }
    // 有多个数字合法
    else{
        double sum = 0;
        for(i = 0;i < v.size();i++)
            sum += v[i];
        printf("The average of %d numbers is %.2lf\n" , cnt , sum / cnt);
    }
}