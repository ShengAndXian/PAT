// PAT甲级 Kuchiguse，原题地址：https://www.patest.cn/contests/pat-a-practise/1077
// 解题分析：
//  先将第一个字符串储存在res向量中，然后从第二个字符串开始比较，比较时从尾开始，一旦发现有不一样
//  的字符，更新res向量，继续下一个字符串比较，如果没有发现不一样的字符，但非res向量的字符串更短，
//  同样需要更新res向量。res向量为空时输出nai，否则输出res向量。
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    vector< vector<char> > v;
    vector<char> temp;
    vector<char> res(300);
    vector< vector<char> >::iterator it;
    char ch;
    int n;
    int i , j , k;
    int size1 , size2;

    cin >> n;
    // 输入
    getchar();
    for(i = 0;i < n;i++){
        while((ch = getchar()) != '\n'){
            temp.push_back(ch);
        }
        v.push_back(temp);
        temp.clear();
    }
    // 将第一个字符串拷贝到res中
    temp = *v.begin();
    copy(temp.begin() , temp.end() , res.begin());
    // 遍历其他字符串
    for(it = v.begin() + 1;it != v.end();it++){
        temp = *it;
        // 计算两个字符串的长度
        size1 = temp.size();
        for(i = 0,size2 = 0;res[i] != '\0';i++)
            size2++;
        // 从尾开始比较
        for(j = size1 - 1 , k = size2 - 1;j >= 0 && k >= 0;j--,k--){
            // 如果有字符不相等
            if(temp[j] != res[k]){
                // 如果第一个尾字符就不相等，说明没有共同的后缀，输出nai
                if(j == size1 - 1){
                    printf("nai\n");
                    return 0;
                }
                // 否则更新res
                else{
                    res.clear();
                    res.resize(300);
                    copy(temp.begin() + j + 1 , temp.end() , res.begin());
                }
                break;
            }
            // j等于0说明非res字符串更短，更新res
            if(j == 0){
                res.clear();
                res.resize(300);
                copy(temp.begin() , temp.end() , res.begin());
            }
        }
    }
    // 输出
    for(i = 0;i < res.size();i++)
        cout << res[i];
    cout << endl;
}