// PAT甲级1055 The World's Richest，原题地址：https://www.patest.cn/contests/pat-a-practise/1055
// 解题分析：
//  排序题。如果先对所有人的年龄进行排序，然后每次查询时先找出所有符合年龄区间的人，再对这些人再按财富值排序，
//  第二个测试点会超时。原因在于，如果每次的年龄区间给的很大，那么满足这个条件的人将会很多，甚至可能是所有人，
//  因此每一次查询可能都要遍历一遍原数组，而原数组大小为10的5次方，查询次数是10的3次方，两者相乘会得到一个很大
//  的值，因此时间会很长。
//  比较好的做法是，先对所有人按财富值排序，财富值相同再按年龄排序，都相同则按姓名排序。用一个book数组纪录每一个年龄
//  的人数，遍历原数组，如果元素对应的年龄的人数小于100，则将元素放入新的数组T，如果人数大于100，则忽略。这么做的原因
//  是，每次查询时输出的人数最多为100，因此一个年龄的人数如果超过100，则最多只能输出前100名，后面的都是无效的，而年龄
//  的范围是1到200，因此数组T的元素个数最多20000。查询时，遍历数组T，输出对应的结果即可。显然，遍历一个20000的数组比
//  遍历一个100000的数组少花很多时间。
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct record{
    char name[9];
    long age;
    long worth;
};

int cmp(const void *a , const void *b){
    struct record m , n;
    m = (*(struct record *)a);
    n = (*(struct record *)b);
    if(m.worth != n.worth)
        return n.worth - m.worth;
    else if(m.age != n.age)
        return m.age - n.age;
    else    
        return strcmp(m.name , n.name);
}

int main(){
    struct record R[100000];
    struct record T[20000];
    long book[201];
    long n , k , m;
    long minAge , maxAge;
    long i , j;
    long cnt = 0;
    long temp;

    scanf("%ld%ld" , &n , &k);
    for(i = 0;i < n;i++){
        scanf("%s%ld%ld" , R[i].name , &R[i].age , &R[i].worth);
    }
    // 按财富值排序
    qsort(R , n , sizeof(struct record) , cmp);
    for(i = 1;i < 201;i++)
        book[i] = 0;
    for(i = 0;i < n;i++){
        // 如果对于年龄的人数小于100，则放入数组T
        if(book[R[i].age] < 100)
            T[cnt] = R[i];
        cnt++;
        book[R[i].age]++;
    }
    for(i = 1;i <= k;i++){
        scanf("%ld%ld%ld" , &m , &minAge , &maxAge);
        printf("Case #%ld:\n" , i);
        // 遍历数组T
        for(j = 0 , temp = 0;j < cnt;j++){
            // 输出符合的元素
            if(temp < m && T[j].age >= minAge && T[j].age <= maxAge){
                printf("%s %ld %ld\n" , T[j].name , T[j].age , T[j].worth);
                temp++;
            }
            if(temp == m)
                break;
        }
        // 没有符合的元素
        if(temp == 0)
            printf("None\n");
    }
}