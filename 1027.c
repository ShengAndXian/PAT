// PAT1027 Colors in Mars，原题地址：https://www.patest.cn/contests/pat-a-practise/1027
// 解题分析：
//  水题，就不解释了。。。。
#include<stdio.h>

void get_rgb(int n , char s[]);

int main(){
    int n1 , n2 , n3;
    char s1[3] , s2[3] , s3[3];

    scanf("%d %d %d" , &n1 , &n2 , &n3);
    get_rgb(n1 , s1);
    get_rgb(n2 , s2);
    get_rgb(n3 , s3);
    printf("#%s%s%s" , s1 , s2 , s3);
}

void get_rgb(int n , char s[]){
    int i = 0;
    int temp;
    char s1[2];

    if(n == 0){
        s[0] = s[1] = '0';
        s[2] = '\0';
        return;
    }

    while(n != 0){
        temp = n % 13;
        if(temp < 10)
            s1[i] = temp + '0';
        else{
            switch(temp){
                case 10:s1[i] = 'A';break;
                case 11:s1[i] = 'B';break;
                case 12:s1[i] = 'C';break;
            }
        }
        n /= 13;
        i++;
    }

    if(i == 1){
        s1[i] = '0';
    }
    s[0] = s1[1];
    s[1] = s1[0];
    s[2] = '\0';
}