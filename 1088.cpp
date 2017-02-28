// PAT甲级1088 Rational Arithmetic，原题地址：https://www.patest.cn/contests/pat-a-practise/1088
// 解题分析：
//  这题最后一个测试点没过，找了很久没有找到原因就先不管了。。。(如果有同学能帮我找到原因可以给我留言，万分感谢！)
#include<cstdio>

long long gcd(long long a , long long b){
    long long c;

    a = a > 0 ? a : -a;
    b = b > 0 ? b : -b;
    while(a % b != 0){
        c = a % b;
        a = b;
        b = c;
    }
    return b;
}

long long GetCommon(long long a , long long b){
    long long t;

    t = gcd(a , b);
    return a * b / t;
}

void Simplify(long long &a , long long &b){
    int t;

    if(b == 0)
        return;
    t = gcd(a , b);
    a /= t;
    b /= t;
}

void Output(long long a , long long b){
    if(a >= 0 && b >= 0){
        if(a % b == 0)
            printf("%lld" , a / b);
        else if(a < b)
            printf("%lld/%lld" , a , b);
        else
            printf("%lld %lld/%lld" , a / b , a % b , b);
    }
    else{
        printf("(-");
        if(a < 0)
            a = -a;
        if(b < 0)
            b = -b;
        if(a % b == 0)
            printf("%lld" , a / b);
        else if(a < b)
            printf("%lld/%lld" , a , b);
        else
            printf("%lld %lld/%lld" , a / b , a % b , b);
        printf(")");
    }
}

int main(){
    long long c1 , p1 , c2 , p2;
    long long cres , pres;

    scanf("%lld/%lld %lld/%lld" , &c1 , &p1 , &c2 , &p2);
    Simplify(c1 , p1);
    Simplify(c2 , p2);

    pres = GetCommon(p1 , p2);
    cres = pres / p1 * c1 + pres / p2 * c2;
    Simplify(cres , pres);
    Output(c1 , p1);
    printf(" + ");
    Output(c2 , p2);
    printf(" = ");
    Output(cres , pres);
    printf("\n");

    pres = GetCommon(p1 , p2);
    cres = pres / p1 * c1 - pres / p2 * c2;
    Simplify(cres , pres);
    Output(c1 , p1);
    printf(" - ");
    Output(c2 , p2);
    printf(" = ");
    Output(cres , pres);
    printf("\n");

    pres = p1 * p2;
    cres = c1 * c2;
    Simplify(cres , pres);
    Output(c1 , p1);
    printf(" * ");
    Output(c2 , p2);
    printf(" = ");
    Output(cres , pres);
    printf("\n");

    pres = p1 * c2;
    cres = c1 * p2;
    Simplify(cres , pres);
    Output(c1 , p1);
    printf(" / ");
    Output(c2 , p2);
    printf(" = ");
    if(pres == 0)
        printf("Inf");
    else
        Output(cres , pres);
    printf("\n");

}