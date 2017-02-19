// PAT甲级1062 Talent and Virtue，原题地址：https://www.patest.cn/contests/pat-a-practise/1062
// 解题分析：
//  排序题。这题重点就在于qsort的比较函数，比较的流程如下：
//  1、判断是否有一个为圣人，如果有，接着判断是否两个都是，如果都是则根据排序规则排序，如果不是，则圣人排在非圣人前面
//  2、如果两个都不是圣人，判断是否一个为君子，如果有，接着判断两个是否都是，如果都是则根据排序规则排序，如果不是，则
//  君子排在非君子之前
//  3、如果两者都不是圣人、君子，则判断是否有一个为小人，如果有，则接着判断是否两个都是，如果都是则根据排序规则排序，如果
//  不是，则非小人排在小人前面
//  4、如果都不满足前面的条件，则两人都是愚人，直接按照排序规则排序
//  最后输出即可。
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct record{
    char id[9];
    long virtue;
    long talent;
};

int cmp(const void *a ,const void *b);

long n , l , h;

int main(){
    long i;
    long cnt = 0;
    char id[9];
    long virtue;
    long talent;
    struct record *R;

    scanf("%ld%ld%ld" , &n , &l , &h);
    R = (struct record *)malloc(sizeof(struct record) * n);
    for(i = 0;i < n;i++){
        scanf("%s%ld%ld" , id , &virtue , &talent);
        // 输入时，talent和virtue都在l之下的直接忽略
        if(virtue >= l && talent >= l){
            R[cnt].virtue = virtue;
            R[cnt].talent = talent;
            strcpy(R[cnt].id , id);
            cnt++;
        }
    }
    // 排序
    qsort(R , cnt , sizeof(struct record) , cmp);
    // 输出
    printf("%ld\n" , cnt);
    for(i = 0;i < cnt;i++)
        printf("%s %ld %ld\n" , R[i].id , R[i].virtue , R[i].talent);
}

int cmp(const void *a , const void *b){
    struct record m , n;
    long sum1 , sum2;
    m = (*(struct record *)a);
    n = (*(struct record *)b);
    sum1 = m.virtue + m.talent;
    sum2 = n.virtue + n.talent;
    // 两个之间至少有一个为圣人
    if((m.virtue >= h && m.talent >= h) || (n.virtue >= h && n.talent >= h)){
        // 两者都是圣人
        if((m.virtue >= h && m.talent >= h) && (n.virtue >= h && n.talent >= h)){
            // 和不同
            if(sum1 != sum2)
                return sum2 - sum1;
            // 和相同，virtue不同
            else if(m.virtue != n.virtue)
                return n.virtue - m.virtue;
            // 和相同，virtue相同
            else 
                return strcmp(m.id , n.id);
        }
        // m为圣人
        else if(m.virtue >= h && m.talent >= h)
            return -1;
        // n为圣人
        else
            return 1;
    }
    // 两者之间至少有一个为君子
    else if(m.virtue >= h || n.virtue >= h){
        // 两者都是君子
        if(m.virtue >= h && n.virtue >= h){
            if(sum1 != sum2)
                return sum2 - sum1;
            else if(m.virtue != n.virtue)
                return n.virtue - m.virtue;
            else    
                return strcmp(m.id , n.id);
        }
        // m为君子
        else if(m.virtue >= h)
            return -1;
        // n为君子
        else
            return 1;
    }
    // 两者之间至少有一个为小人
    else if(m.talent > m.virtue || n.talent > n.virtue){
        // 两者都是小人
        if(m.talent > m.virtue && n.talent > n.virtue){
            if(sum1 != sum2)
                return sum2 - sum1;
            else if(m.virtue != n.virtue)
                return n.virtue - m.virtue;
            else
                return strcmp(m.id , n.id);
        }
        // m为小人
        else if(m.talent > m.virtue)
            return 1;
        // n为小人
        else
            return -1;
    }
    // 两者都是愚人
    else{
        if(sum1 != sum2)
            return sum2 - sum1;
        else if(m.virtue != n.virtue)
            return n.virtue - m.virtue;
        else    
            return strcmp(m.id , n.id);
    }
}