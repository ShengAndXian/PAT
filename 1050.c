// PAT甲级1050 String Subtraction，原题地址：https://www.patest.cn/contests/pat-a-practise/1050
// 解题分析：
//  字符哈希。第一个字符串直接存储在数组中，第二个字符串将每一个字符哈希之后放入哈希表，接着遍历第一个字符串，
//  输出字符之前，将字符哈希，然后在哈希表中查找，如果找到，则不输出，否则输出。
#include<stdio.h>
#include<stdlib.h>

#define Max 10010
struct record{
    char c;
    int flag;
};

void Insert(struct record h[] , char c);
int isInS2(struct record h[] , char c);

int main(){
    char s[Max];
    struct record h[400];
    char c;
    int i;
    int cnt = 0;

    for(i = 0;i < 400;i++)
        h[i].flag = 0;
    // 输入第一个字符串
    while(1){
        scanf("%c" , &c);
        if(c != '\n')
            s[cnt++] = c;
        else
            break;
    }
    // 输入第二个字符串
    while(1){
        scanf("%c" , &c);
        if(c != '\n')
            // 插入哈希表
            Insert(h , c);
        else    
            break;
    }
    for(i = 0;i < cnt;i++){
        // 判断是否字符是否存在于第二个字符串
        if(!isInS2(h , s[i]))
            printf("%c" , s[i]);
    }
    printf("\n");
    return 0;
}

void Insert(struct record h[] , char c){
    int index = c + 0;
    int temp;
    int i;

    // 如果位置上没有元素，则直接插入
    if(h[index].flag == 0){
        h[index].c = c;
        h[index].flag = 1;
    }
    // 如果有元素
    else if(h[index].c != c){
        temp = index;
        // 平方探测
        for(i = 1;;i++){
            index = (temp + i * i) % 400;
            // 找到空位插入
            if(h[index].flag == 0){
                h[index].c = c;
                h[index].flag = 1;
                break;
            }
            // 发现一样的字符则直接返回
            else if(h[index].c == c)
                break;
        }
    }
}

// 与插入操作类似
int isInS2(struct record h[] , char c){
    int index = c + 0;
    int temp;
    int i;

    if(h[index].flag == 0)
        return 0;
    else if(h[index].c != c){
        temp = index;
        for(i = 1;;i++){
            index = (temp + i * i) % 400;
            if(h[index].flag == 0)
                return 0;
            else if(h[index].c == c)   
                return 1;
        }
    }
    else    
        return 1;
}