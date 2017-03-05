// PAT甲级1104 Sum of Number Segments，原题地址：https://www.patest.cn/contests/pat-a-practise/1104
// 解题分析：
//  计算每个值在所有区间内出现的次数，然后和值乘起来再加到sum里就好了。
#include<cstdio>
using namespace std;

int main(){
    long n;
    double sum = 0;
    long i;

    scanf("%ld" , &n);
    for(i = 1;i <= n;i++){
        double t;
        scanf("%lf" , &t);
        sum += t * i * (n - i + 1); 
    }
    printf("%.2lf" , sum);
}