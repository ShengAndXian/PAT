// PAT甲级1103 Integer Factorization，原题地址：https://www.patest.cn/contests/pat-a-practise/1103
// 解题分析：
//  DFS。用DFS穷举所有可能的情况，选择因子和最大的作为结果。穷举时，因子的值由大变小，并且下一个因子的值必须小于或等于
//  当前的因子值，否则会造成重复搜索，这样我们会得到所有的组合，并且这些组合都是以非升序排列的。递归k次后，判断和是否等于n
//  ，如果是则接着判断因子和是否是最大的，如果都满足，则该序列为结果序列。还需要注意的是，为了防止超时，不能每次都一个因子的
//  p次方进行计算，应该先计算好，然后遇到的时候直接查表，这样就不会超时了。
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

vector<int> v;
int check[500];
int Max = -1 , current;
int cnt;
int pre;
int n , k , p;

// DFS
bool Factorization(int d){
    int i;
    bool flag = false;

    //  已经递归k次
    if(cnt == k){
        // 如果序列和等于n并且因子和比最大值大
        if(d == 0 && current > Max){
            Max = current;
            v.clear();
            return true;
        }
        else
            return false;
    }
    // 穷举所有可能的因子
    for(i = pre;i >= 1;i--){
        // i的p次方不能比d大
        if(check[i] > d)
            continue;
        cnt++;
        current += i;
        pre = i;
        // 递归，如果得到一个结果序列则将当前因子放入v
        if(Factorization(d - check[i])){
            v.push_back(i);
            flag = true;
        }
        cnt--;
        current -= i;
    }
    return flag;
}
int main(){
    int i;

    cin >> n >> k >> p;
    // 计算所有可能因子的p次方，并放入表中
    for(i = 1;;i++){
        if(pow(i , p) <= n)
            check[i] = pow(i , p);
        else
            break;
    }
    pre = i - 1;
    // 输出
    if(Factorization(n)){
        cout << n << " = ";
        for(i = v.size() - 1;i >=0;i--){
            cout << v[i] << "^" << p;
            if(i > 0)
                cout << " + ";
        }
        cout << endl;
    }
    else{
        cout << "Impossible" << endl;
    }
}
