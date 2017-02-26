// PAT甲级1083 List Grades，原题地址：https://www.patest.cn/contests/pat-a-practise/1083
// 解题分析：
//  把不符合条件的剔除，剩下的简单的排下序就好了。
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

struct record{
    string name;
    string id;
    int grade;
};

vector<struct record> v;
vector<struct record> ans;
long n;
int b1 , b2;

bool cmp(struct record a , struct record b){
    return a.grade > b.grade;
}
int main(){
    struct record R;
    string name , id;
    int grade;
    int i;
    int flag = 0;

    cin >> n;
    for(i = 0;i < n;i++){
        cin >> name >> id >> grade;
        R.name = name;
        R.id = id;
        R.grade = grade;
        v.push_back(R);
    }
    cin >> b1 >> b2;
    for(i = 0;i < n;i++){
        if(v[i].grade >= b1 && v[i].grade <= b2)
            ans.push_back(v[i]);
    }
    sort(ans.begin() , ans.end() , cmp);
    for(i = 0;i < ans.size();i++){
        if(ans[i].grade >= b1 && ans[i].grade <= b2){
            flag = 1;
            cout << ans[i].name << " " << ans[i].id << endl;
        }
        else{
            break;
        }
    }
    if(!flag)
        cout << "NONE" << endl;
    return 0;
}