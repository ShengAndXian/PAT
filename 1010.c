// PAT甲级1010 Radix，原题地址：https://www.patest.cn/contests/pat-a-practise/1010
// 解题分析：
//  虽然输入数字的每一位都在0-35之间，但实际上radix的值可以非常的大（因为题目中只说了radix比每一位数字都大，理论上可以无限大）
//  因此将已知radix的那个数转换成十进制数，会得到一个非常大的值，为了使其不溢出，需要用long long类型的变量来储存。接下来就是
//  求未知的那个radix了。我们首先会想到的应该就是一个一个枚举。前面也说到了，radix的值可以非常大，因此最初将上限设置为36，结果
//  很多个测试点没有过去，就算人为的将上限设置成一个很大的数，就会超时。因此，借鉴网上的方法，采用二分查找来解决问题。
//  二分查找：
//  既然是二分查找，就必须确定上下界。下界很简单，就是找出待求值最大的一个数字然后加一，而上界就比较麻烦。对于多位数，最小的多位数是10，
//  所有比10大的数字的radix都必定10的radix小，而10的radix就等于已知radix的数字的十进制值，因此上界就是已知radix的数字的十进制值。
//  下界有可能比上界大，这种情况下只有一位数可能存在radix，一位数的radix就是它的下界。因此在二分查找时需要比较上下界的大小。
//  还需注意的两点是：
//  1、如果两个数都是1，则输出2
//  2、如果两个数相等，但不是1，则输出输入的radix
//  这两点可以特殊处理
#include<stdio.h>

#define Max 11

long long get_low(char *num);
long long get_target(char *num , long long radix);
long long compare(char *num , long long radix , long long target);
long long binary_search(char *num , long long low , long long high , long long target);

int main(){
    char num1[Max] , num2[Max];
    long long tag;
    long long radix;
    long long target_1 , target_2 , target;
    long long low;
    long long result;
    long long most;

    scanf("%s %s %lld %lld" , num1 , num2 , &tag , &radix);
    target_1 = get_target(num1 , 10);
    target_2 = get_target(num2 , 10);
    if(target_1 == target_2){
        if(target_1 == 1){
            printf("2");
        }
        else{
            printf("%lld" , radix);
        }
        return 0;
    }
    if(tag == 1){
        target = get_target(num1 , radix);
        low = get_low(num2);
        most = (low > target) ? low : target;
        result = binary_search(num2 , low , most , target);
    }
    else{
        target = get_target(num2 , radix);
        low = get_low(num1);
        most = (low > target) ? low : target;
        result = binary_search(num1 , low , most , target);
    }
    if(result != -1)
        printf("%lld" , result);
    else
        printf("Impossible");
}

long long get_low(char *num){
    long long i = 0;
    long long max = -1;
    long long value;

    while(num[i] != '\0'){
        if(num[i] >= '0' && num[i] <= '9')
            value = num[i] - '0';
        else 
            value = num[i] - 'a' + 10;
        if(value > max)
            max = value;
        i++;
    }

    return max + 1;
}

long long get_target(char *num , long long radix){
    long long i = 0;
    long long target = 0 , temp = 1;
    long long value;

    while(num[i] != '\0') i++;

    while(--i != -1){
        if(num[i] >= '0' && num[i] <= '9')
            value = num[i] - '0';
        else
            value = num[i] - 'a' + 10;
        target += temp * value;
        temp *= radix;
    }

    return target;
}

long long compare(char *num , long long radix , long long target){
    long long i = 0;
    long long result = 0, temp = 1;
    long long value;

    while(num[i] != '\0') i++;

    while(--i != -1){
        if(num[i] >= '0' && num[i] <= '9')
            value = num[i] - '0';
        else
            value = num[i] - 'a' + 10;
        result += temp * value;
        temp *= radix;
        if(result > target)
            return 1;
    }
    if(result < target)
        return -1;
    else
        return 0;
}

long long binary_search(char *num , long long low , long long high , long long target){
    long long mid;
    long long flag;

    while(low <= high){
        mid = (low + high) / 2;
        flag = compare(num , mid , target);
        if(flag == 1){
            high = mid - 1;
        }
        else if(flag == -1){
            low = mid + 1;
        }
        else{
            return mid;
        }
    }

    return -1;
}
