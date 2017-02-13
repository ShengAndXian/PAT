// PAT甲级1040 Longest Symmetric String，原题地址：https://www.patest.cn/contests/pat-a-practise/1040
// 解题分析：
//  求一个字符串的最大对称子串的长度。对称的子串有两种，一是字符个数为奇数，中间数的两边对称，另一种字符个数为偶数，对称
//  中心两边对称。遍历整个字符串，如果遇到一个字符两边的字符相等，则向两边继续搜索，找到最大的对称子串，计算长度，如果比之前
//  的长度长，则更新最大长度，如果遇到一个字符，其和之后一个字符相等，则以这两个字符为中心，向两边继续搜索，步骤和之前的类似。
//  如果不存在对称字符串，则最大长度为1。
#include<stdio.h>

int main(){
    char s[1000];
    int count = 1;
    int i = 0 , j;
    int start , end;

    // 输入字符串
    do{
        scanf("%c" , &s[i]);
    }while(s[i++] != '\n');
    i -= 2;
    // 遍历字符串
    for(j = 0;j <= i;j++){
        // 如果当前字符的两边字符相等
        if(j != 0 && j != i && s[j - 1] == s[j + 1]){
            // 向两边继续搜索
            start = j - 1;
            end = j + 1;
            while(1){
                if(s[start] != s[end] || start < 0 || end > i)
                    break;
                start--;
                end++;
            }
            start++;
            end--;
            // 如果长度比最大长度大
            if(end - start + 1 > count)
                count = end - start + 1;
        }
        // 如果当前字符和下一个字符相等
        if(j != i && s[j] == s[j + 1]){
            // 向两边继续搜索
            start = j;
            end = j + 1;
            while(1){
                if(s[start] != s[end] || start < 0 || end > i)
                    break;
                start--;
                end++;
            }
            start++;
            end--;
            // 如果长度比最大长度大
            if(end - start + 1 > count)
                count = end - start + 1;
        }
    }
    printf("%d\n" , count);
}