// PAT甲级1089 Insert or Merge，原题地址：https://www.patest.cn/contests/pat-a-practise/1089
// 解题分析：
//  插入排序和归并排序。插入排序很简单，遍历所有的元素，一个一个插入就行了，每插入一个元素检查是否和所给的序列
//  相等，如果是则再执行一次排序后返回。归并排序有些复杂，这里不能用递归来写归并排序，因为如果用递归写归并的话，
//  每次排序的元素个数是2、2、4、2、2、4、8，这跟题目的要求不符合，从题目中我们可以看到，它每次排序的元素个数是
//  2、4、8，因此我们需要用归并排序的非递归方法来解题，这一点明确后题目就不难了。
#include<iostream>
#include<vector>
using namespace std;

vector<int> v1;
vector<int> v2;
vector<int> t;
int n;

// 归并两个排好序的序列
void merge(int start , int end , int len){
    vector<int> temp;
    int mid = start + len / 2 - 1;
    int i , j;

    // 比较两个序列中的元素大小，然后依次放入temp中
    for(i = start , j = mid + 1;i <= mid && j <= end;){
        if(t[i] < t[j]){
            temp.push_back(t[i]);
            i++;
        }
        else{
            temp.push_back(t[j]);
            j++;
        }
    }

    // 处理剩下的元素
    while(i <= mid){
        temp.push_back(t[i]);
        i++;
    }
    while(j <= end){
        temp.push_back(t[j]);
        j++;
    }

    // 修改t
    for(i = 0;i < temp.size();i++){
        t[start++] = temp[i];
    }
}

// 判断是否和给定序列相等
bool IsEqual(){
    int i;

    for(i = 0;i < n;i++){
        if(t[i] != v2[i])
            return false;
    }
    return true;
}

// 判断是否是插入排序
bool IsInsertion(){
    int i , j , k;
    int temp;
    int flag = 0;

    t.clear();
    for(i = 0;i < n;i++)
        t.push_back(v1[i]);
    for(i = 1;i < n;i++){
        // 找到元素插入的位置
        for(j = 0;j < i;j++){
            if(t[j] > t[i])
                break;
        }
        temp = t[i];
        // 移动元素
        for(k = i - 1;k >= j;k--)
            t[k + 1] = t[k];
        // 插入
        t[j] = temp;
        if(flag)
            return true;
        if(IsEqual())
            flag = 1;
    }
    return false;
}

// 判断是否是归并排序
bool IsMerge(){
    int i;
    int start , end;
    int flag = 0;

    t.clear();
    for(i = 0;i < n;i++)
        t.push_back(v1[i]);
    // 每次排序的元素个数是2、4、8
    for(i = 2;i <= n;i *= 2){
        // 划分区间
        for(start = 0;start < n;start = end + 1){
            end = start + i - 1;
            if(end >= n)
                end = n - 1;
            // 排序
            merge(start , end , i);
        }
        if(flag)
            return true;
        if(IsEqual())
            flag = 1;
    }
    return false;
}

int main(){
    int num;
    int i;

    // 输入
    cin >> n;
    for(i = 0;i < n;i++){
        cin >> num;
        v1.push_back(num);
    }
    for(i = 0;i < n;i++){
        cin >> num;
        v2.push_back(num);
    }
    // 判断
    if(IsInsertion()){
        cout << "Insertion Sort" << endl;
        for(i = 0;i < n;i++){
            if(i != n - 1)
                cout << t[i] << " ";
            else
                cout << t[i];
        }
    }
    else if(IsMerge()){
        cout << "Merge Sort" << endl;
        for(i = 0;i < n;i++){
            if(i != n - 1)
                cout << t[i] << " ";
            else
                cout << t[i];
        }
    }
}