// PAT甲级1049 Counting Ones，原题地址：https://www.patest.cn/contests/pat-a-practise/1049
// 解题分析：
//  一道数学题，给定一个数，统计从1到该数区间内所有数字中的1的个数。从个位开始到最高位，依次计算每一位上
//  1出现的次数，然后累加即可。变量now表示当前位的数字，left表示当前位左边的数，right表示当前位右边的数，
//  a的值和当前位的位置有关，如果当前位为个位，a等于1，十位则为10，百位则为100，依次类推。
//  对于now的取值，有三种情况：
//  1、now等于0，左边的数从0到left时，now对于的位才可能等于1，因此一共有left次，又因为右边可以从0到999...
//  所以一共是left * a个1。
//  2、now等于1，相比于第一种情况，在左边数等于left的情况下，now对于的位仍然可以取到1，右边的数可以从0到right，
//  所以一共有left * a + right + 1个1。
//  3、now大于等于2，相比于第二种情况，当左边的数等于left，now等于1时，right可以从0到999...，，也就是right等于
//  a - 1，所以一共有(left + 1) * a个1。
#include<stdio.h>

int main(){
    long n , left , right , now , a = 1, ans = 0;

    scanf("%ld" , &n);
    while(n / a){
        left = n / (a * 10);
        right = n % a;
        now = n / a % 10;
        if(now == 0) ans += left * a;
        else if(now == 1) ans += left * a + right + 1;
        else ans += (left + 1) * a;
        a *= 10;
    }
    printf("%ld" , ans);
    return 0;
}