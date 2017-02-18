// PAT甲级1057 Stack，原题地址：https://www.patest.cn/contests/pat-a-practise/1057
// 解题分析：
//  这道题可以用树状数组解决，之前也没听说过这种数组，看了网上的一些资料才懂了大概。简单的来说，
//  当我们查找到某个数字时，我们需要知道栈中比它小的数有多少个，如果比它小的数刚好等于所有数的一半，
//  那么这个数就是中位数。因此，我们需要计算的就是每个数之前的数的个数，然后采用二分查找，直到找到一个
//  数，比它小的数的个数为所有数个数的一半。计算数的个数就需要通过树状数组来实现，具体的操作看代码会更加
//  清楚。
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define Max 100010

void update(long idx , long val);
void PeekMedian();
long read(long idx);

long stack[Max];
long top = -1;
long tree[Max];

int main(){
    long n;
    char s[15];
    long key;
    long i;

    scanf("%ld" , &n);
    for(i = 0;i < n;i++){
        scanf("%s" , s);
        // push操作
        if(s[1] == 'u'){
            scanf("%ld" , &key);
            // 入栈
            stack[++top] = key;
            // 更新树状数组
            update(key , 1);
        }
        // pop操作
        else if(s[1] == 'o'){
            // 栈为空
            if(top == -1)
                printf("Invalid\n");
            // 栈不为空
            else{
                printf("%ld\n" , stack[top]);
                // 更新树状数组
                update(stack[top] , -1);
                // 出栈
                top--;
            }
        }
        // peekmedian操作
        else{
            // 栈为空
            if(top == -1)
                printf("Invalid\n");
            else
                PeekMedian();
        }
    }
}

// 更新树状数组
void update(long idx , long val){
    while(idx < Max){
        tree[idx] += val;
        idx += (idx & -idx);
    }
}

// 查找中位数
void PeekMedian(){
    long left , right , mid;
    long k;
    long res;

    // 所有数的个数的一半
    k = top + 1;
    if(k % 2 == 0)
        k = k / 2;
    else    
        k = (k + 1) / 2;
    left = 0;
    right = Max - 1;
    // 二分查找
    while(left < right){
        mid = (left + right) / 2;
        // 计算中间数所对应的数的个数
        res = read(mid);
        // 如果比k大或等于k（该数出现的次数可能很多或0次）
        if(res >= k)
            right = mid;
        else    
            left = mid + 1;
    }
    printf("%ld\n" , left);
}

// 计算数的个数
long read(long idx){
    long sum = 0;
    while(idx > 0){
        sum += tree[idx];
        idx -= (idx & -idx);
    }
    return sum;     
}