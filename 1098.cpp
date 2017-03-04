// PAT甲级1098 Insertion or Heap Sort，原题地址：https://www.patest.cn/contests/pat-a-practise/1098
// 解题分析：
//  插入排序和堆排序。难度不是很大，但堆排序比较繁琐，需要自己建堆，然后再写一个Delete函数，注意细节即可。
#include<iostream>
#include<vector>
using namespace std;

// 建堆
void ConstructHeap(vector<int> &v){
    int i;

    for(i = v.size() / 2 - 1;i >= 0;i--){
        int parent , child;
        for(parent = i;parent * 2 + 1 < v.size();parent = child){
            child = parent * 2 + 1;
            if(child != v.size() - 1 && v[child + 1] > v[child])
                child = child + 1;
            if(v[child] > v[parent]){
                int t;
                t = v[child];
                v[child] = v[parent];
                v[parent] = t;
            }
            else    
                break;
        }
    }
}

// 删除顶部元素并返回其值
int Delete(vector<int> &v , int cnt){
    int ans;
    int t;
    int child;
    int i;

    ans = v[0];
    t = v[v.size() - cnt];
    for(i = 0;i * 2 + 1 < v.size() - cnt;i = child){
        child = i * 2 + 1;
        if(child != v.size() - cnt && v[child + 1] > v[child])
            child = child + 1;
        if(v[child] > t)
            v[i] = v[child];
        else
            break;
    }
    v[i] = t;
    return ans;
}

// 判断两个序列是否相等
bool IsEqual(vector<int> v1 , vector<int> v2){
    int i;

    for(i = 0;i < v1.size();i++)
        if(v1[i] != v2[i])
            return false;
    return true;
}

// 是否是插入排序
bool IsInsertionSort(vector<int> &v1 , vector<int> &v2 , vector<int> &res){
    int i , j;
    bool flag = false;

    res.clear();
    for(i = 0;i < v1.size();i++)
        res.push_back(v1[i]);
    for(i = 1;i < res.size();i++){
        int t = res[i];
        for(j = i - 1;j >= 0;j--){
            if(res[j] > t)
                res[j + 1] = res[j];
            else
                break;
        }
        res[j + 1] = t;
        if(flag)
            return true;
        if(IsEqual(v2 , res))
            flag = true;
    }
    return false;
}

// 是否是堆排序
bool IsHeapSort(vector<int> &v1 , vector<int> &v2 , vector<int> &res){
    int i;
    bool flag = false;

    res.clear();
    for(i = 0;i < v1.size();i++)
        res.push_back(v1[i]);
    ConstructHeap(res);
    for(i = 1;i <= res.size();i++){
        int t = Delete(res , i);
        res[res.size() - i] = t;
        if(flag)
            return true;
        if(IsEqual(v2 , res))
            flag = true;
    }
    return false;
}

int main(){
    vector<int> v1;
    vector<int> v2;
    vector<int> res;
    int n;
    int i;
    int num;

    cin >> n;
    for(i = 0;i < n;i++){
        cin >> num;
        v1.push_back(num);
    }
    for(i = 0;i < n;i++){
        cin >> num;
        v2.push_back(num);
    }
    // 判断是否是插入排序
    if(IsInsertionSort(v1 , v2 , res)){
        cout << "Insertion Sort" << endl;
        for(i = 0;i < n;i++){
            if(i != n - 1)
                cout << res[i] << " ";
            else
                cout << res[i] << endl;
        }
    }
    // 判断是否是堆排序
    else if(IsHeapSort(v1 , v2 , res)){
        cout << "Heap Sort" << endl;
        for(i = 0;i < n;i++){
            if(i != n - 1)
                cout << res[i] << " ";
            else
                cout << res[i] << endl;
        }
    }
}