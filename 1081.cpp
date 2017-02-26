// PAT甲级1081 Rational Sum，原题地址：https://www.patest.cn/contests/pat-a-practise/1081
// 解题分析：
//  计算分数的和，一个一个加就可以了，计算两个分数的和时先计算分母的最小公倍数，再计算出结果。输出前先把
//  分子分母简化，再输出。
#include<cstdio>

// 计算最小公倍数
long GetCommon(long a , long b){
    if(a >= b && a % b == 0)
        return a;
    else if(a < b && b % a == 0)
        return b;
    else
        return a * b;
}

// 简化分子分母
void DeleteCommon(long &a , long &b){
    int i;

    for(i = 2;i <= a && i <= b;){
        if(a % i == 0 && b % i == 0){
            a /= i;
            b /= i;
        }
        else
            i++;
    }
}
int main(){
    long n[100] , d[100];
    long nres = 0 , dres = 1;
    long temp;
    int m;
    int i;

    scanf("%d" , &m);
    for(i = 0;i < m;i++){
        scanf("%ld/%ld" , &n[i] , &d[i]);
        // 计算两个分数的和
        temp = GetCommon(dres , d[i]);
        nres *= temp / dres;
        n[i] *= temp / d[i];
        dres = temp;
        nres = nres + n[i];
    }
    DeleteCommon(nres , dres);
    // 输出
    if(nres % dres == 0)
        printf("%ld\n" , nres / dres);
    else if(nres / dres == 0)
        printf("%ld/%ld\n" , nres , dres);
    else
        printf("%ld %ld/%ld\n" , nres / dres , nres % dres , dres);
}