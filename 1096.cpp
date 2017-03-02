// PAT甲级1096 Consecutive Factors，原题地址：https://www.patest.cn/contests/pat-a-practise/1096
// 解题分析：
//  暴力搜索，每一种情况都计算过去，取最大的就行了。为了不超时，还要将n开一个根号。
#include<iostream>
#include<cmath>
using namespace std;

int main(){
    long n;
    long i;
    long temp;
    long index;
    long len = 0;
    long max = 0;

    cin >> n;
    // n需要开根号
    for(i = 2;i < sqrt(n);i++){
        len = 0;
        temp = i;
        // 如果n能被i整除
        if(n % i == 0){
            len++;
            // 尝试下一个连续值
            for(int j = i + 1;j < n;j++){
                temp *= j;
                // 如果能整除n，长度加一
                if(n % temp == 0)
                    len++;
                // 否则
                else
                    break;
            }
            // 如果长度比max大
            if(len > max){
                max = len;
                index = i;
            }
        }
    }
    // 2和3
    if(max == 0){
        max = 1;
        index = n;
    }
    // 输出
    cout << max << endl;
    for(i = 0;i < max;i++){
        if(i > 0)
            cout << "*" << index + i;
        else
            cout << index + i;
    }
    cout << endl;
}