// PAT甲级1092 To Buy or Not to Buy，原题地址：https://www.patest.cn/contests/pat-a-practise/1092
// 解题分析：
//  简单的一道题，输入第一个字符串的时候将每个字符转换成数组的下标，其对应的值加一。输入第二个的时候，同样把字符转成
//  下标，对应的值减一，如果对应的值是0，说明不满足需求，flag设为0，并记录还需要多少珠子。最后输出即可。
#include<iostream>
using namespace std;

int cnt[100];
int total , need;

int main(){
    char c;
    int index;
    int flag = 1;

    while((c = getchar()) != '\n'){
        if(c >= '0' && c <= '9')
            cnt[c - '0']++;
        else if(c >= 'a' && c <= 'z')
            cnt[c - 'a' + 10]++;
        else
            cnt[c - 'A' + 36]++;
        total++;
    }
    while((c = getchar()) != '\n'){
        if(c >= '0' && c <= '9')
            index = c - '0';
        else if(c >= 'a' && c <= 'z')
            index = c - 'a' + 10;
        else
            index = c - 'A' + 36;
        if(cnt[index] > 0){
            cnt[index]--;
            total--;
        }
        else{
            flag = 0;
            need++;
        }
    }
    if(flag)
        cout << "Yes " << total << endl;
    else
        cout << "No " << need << endl; 
}