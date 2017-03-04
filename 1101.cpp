// PAT甲级1101 Quick Sort，原题地址：https://www.patest.cn/contests/pat-a-practise/1101
// 解题分析：
//  题目跟快排也没太大关系。。。先从左到右维护一个最大值，每遇到一个元素，看下该元素是否比这个最大值大，
//  如果比它大说明它有可能是pivot，我们对它做一个标记，然后更新下最大值。再从右到左维护一个最小值，每
//  遇到一个元素，看下是否比最小值小，比它小说明有可能是pivot，否则即使之前该元素被标记，我们也要取消标记。
//  最后再遍历一遍输出即可。还有一点是INFINITY要比10的9次方要大，否则会有错误。
#include<iostream>
#include<algorithm>
using namespace std;
#define INFINITY 1100000000
#define Max 110000

long arr[Max];
long check[Max];
long n;

int main(){
    long i;

    cin >> n;
    for(i = 0;i < n;i++)
        cin >> arr[i];
    long max = -1 , min = INFINITY;
    // 从左到右
    for(i = 0;i < n;i++){
        if(arr[i] > max){
            check[i] = 1;
            max = arr[i];
        }
    }
    // 从右到左
    for(i = n - 1;i >= 0;i--){
        if(arr[i] < min)
            min = arr[i];
        else if(check[i] == 1)
            check[i] = 0;
    }
    // 计数
    int cnt = 0;
    for(i = 0;i < n;i++){
        if(check[i] == 1)
            cnt++;
    }
    // 输出
    cout << cnt << endl;
    for(i = 0;i < n;i++){
        if(check[i] == 1){
            cout << arr[i];
            if(--cnt)
                cout << " ";
        }
    }
    cout << endl;
    return 0;
}