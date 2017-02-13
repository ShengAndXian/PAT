// PAT甲级1022 Digital Library，原题地址：https://www.patest.cn/contests/pat-a-practise/1022
// 解题分析：
//  这题最后一个测试点超时。。。看了自己的程序发现基本没有优化的空间，所以也就放弃了最后一个测试点，可能总体的思路有问题。
//  这个程序的总体思路是把标题、作者等信息分别用不同的数组存储，每当输入一个新的数据块，对于不同的信息在不同的数组搜索，
//  比如作者信息就在储存有所有作者的数组中搜索，如果发现该作者已经存在，则把ID插入，如果作者不存在，则将作者插入，接着把
//  ID插入。其他信息同理，对于关键词就把它拆成几个关键词，然后多次搜索。程序中搜索使用的是二分查找，本以为这样能省下很多时间
//  然而还是超时了。在此只把自己现在的思路说一下，以后可以重现思考以及和大家讨论。查询的话很简单，二分查找之后把对应的ID放到
//  另一个数组中，然后快排，再输出，没找到就输出Not Found。
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
    char ID[8];
    struct node *next;
};//储存ID信息
struct record{
    char s[81];
    struct node *ptr;
};//纪录各种信息，包括标题，作者等

int binary_search(struct record arr[] , int start , int end , char s[]);
void insert(struct record arr[] , int index , char s[] , char ID[] , int *end);
void search(struct record arr[] , int start , int end , char query[]);
int compare(const void *a , const void *b);

int main(){
    // 储存不同信息的数组定义
    struct record Title[10000];
    struct record Author[10000];
    struct record Keyword[1000];
    struct record Publisher[1000];
    struct record Pubyear[2001];
    int n , m;
    char ID[8] , title[81] , author[81] , keyword[81] , publisher[81] , pubyear[81];
    int s1 , e1 , s2 , e2 , s3 , e3 , s4 , e4 , s5 , e5;//不同信息的开始和结束索引
    char s[11];
    char query[84];
    int i , j , k , t;
    int index;

    // 索引初始化
    s1 = s2 = s3 = s4 = s5 = 0;
    e1 = e2 = e3 = e4 = e5 = -1;
    scanf("%d" , &n);
    // n个数据块
    for(i = 0;i < n;i++){
        // 输入ID
        scanf("%s" , ID);
        // 消去回车，不然会在接下来输入字符时被作为一个字符读入
        getchar();
        // 输入标题
        j = 0;
        do{
            scanf("%c" , &title[j]);
        }while(title[j++] != '\n');
        title[j - 1] = '\0';
        // 输入作者
        j = 0;
        do{
            scanf("%c" , &author[j]);
        }while(author[j++] != '\n');
        author[j - 1] = '\0';
        // 输入关键词
        j = 0;
        do{
            scanf("%c" , &keyword[j]);
        }while(keyword[j++] != '\n');
        keyword[j - 1] = '\0';
        // 输入出版商
        j = 0;
        do{
            scanf("%c" , &publisher[j]);
        }while(publisher[j++] != '\n');
        publisher[j - 1] = '\0';
        // 输入出版日期
        scanf("%s" , pubyear);
        getchar();
        // 在标题数组查找
        index = binary_search(Title , s1 , e1 , title);
        // 插入ID到标题数组
        insert(Title , index , title , ID , &e1);
        // 快速排序
        if(index == -1 && strcmp(Title[e1].s , Title[e1-1].s) < 0)
            qsort(Title , e1 - s1 + 1 , sizeof(struct record) , compare);
        // 在作者数组中查找
        index = binary_search(Author , s2 , e2 , author);
        // 插入ID到作者数组
        insert(Author , index , author , ID , &e2);
        // 快速排序
        if(index == -1 && strcmp(Author[e2].s , Author[e2-1].s) < 0)
            qsort(Author , e2 - s2 + 1, sizeof(struct record) , compare);
        // 拆分关键词
        for(j = 0 , k = -1;keyword[j] != '\0';j++){
            if(keyword[j] != ' ' && keyword[j+1] != '\0')
                continue;
            if(keyword[j+1] == '\0') j++;
            t = 0;
            for(k++;k < j;k++)
                s[t++] = keyword[k];
            s[t] = '\0';
            k = j;
            // 在关键词数组中查找
            index = binary_search(Keyword , s3 , e3 , s);
            // 插入ID到关键词数组
            insert(Keyword , index , s , ID , &e3);
            // 快速排序
            if(index == -1 && strcmp(Keyword[e3].s , Keyword[e3-1].s) < 0)
                qsort(Keyword , e3 - s3 + 1 , sizeof(struct record) , compare);
        }
        // 在出版商数组查找
        index = binary_search(Publisher , s4 , e4 , publisher);
        // 插入ID到出版商数组
        insert(Publisher , index , publisher , ID , &e4);
        // 快速排序
        if(index == -1 && strcmp(Publisher[e4].s , Publisher[e4-1].s) < 0)
            qsort(Publisher , e4 - s4 + 1 , sizeof(struct record) , compare);
        // 在出版日期数组中查找
        index = binary_search(Pubyear , s5 , e5 , pubyear);
        // 插入ID到出版日期数组
        insert(Pubyear , index , pubyear , ID , &e5);
        // 快速排序
        if(index == -1 && strcmp(Pubyear[e5].s , Pubyear[e5-1].s) < 0)
            qsort(Pubyear , e5 - s5 + 1 , sizeof(struct record) , compare);
    }

    scanf("%d" , &m);
    getchar();
    // m次查询
    for(i = 0;i < m;i++){
        // 输入查询字符串
        j = 0;
        do{
            scanf("%c" , &query[j]);
        }while(query[j++] != '\n');
        query[j - 1] = '\0';
        printf("%s\n" , query);
        // 根据字符串做不同查询
        switch(query[0]){
            case '1':search(Title , s1 , e1 , query + 3);break;
            case '2':search(Author , s2 , e2 , query + 3);break;
            case '3':search(Keyword , s3 , e3 , query + 3);break;
            case '4':search(Publisher , s4 , e4 , query + 3);break;
            case '5':search(Pubyear , s5 , e5 , query + 3);break;
        }
    }
}

// 二分查找
int binary_search(struct record arr[] , int start , int end , char s[]){
    int mid;

    while(start <= end){
        mid = (start + end) / 2;
        if(strcmp(arr[mid].s , s) < 0)
            start = mid + 1;
        else if(strcmp(arr[mid].s , s) > 0)
            end = mid - 1;
        else
            return mid;
    }

    return -1;
}

// 插入ID
void insert(struct record arr[] , int index , char s[] , char ID[] , int *end){
    struct node *ptr;

    // 新建一个结构块
    ptr = (struct node *)malloc(sizeof(struct node));
    strcpy(ptr->ID , ID);
    // 如果index等于－1，则没有查找到相应的字符串
    if(index == -1){
        // 将相应的字符串插入
        strcpy(arr[++(*end)].s , s);
        // 插入ID
        ptr->next = NULL;
        arr[*end].ptr = ptr;
    }
    // 否则直接插入ID
    else{
        ptr->next = arr[index].ptr;
        arr[index].ptr = ptr;
    }
}

// 查找
void search(struct record arr[] , int start , int end , char query[]){
    int index;
    struct record result[10000];
    struct node *ptr;
    int i = 0 , j;

    // 二分查找获取索引
    index = binary_search(arr , start , end , query);
    // 没有找到则输出Not Found
    if(index == -1)
        printf("Not Found\n");
    // 如果找到
    else{
        // 获取所有ID
        ptr = arr[index].ptr;
        while(ptr != NULL){
            strcpy(result[i++].s , ptr->ID);
            ptr = ptr->next;
        }
        // 排序
        qsort(result , i , sizeof(struct record) , compare);
        // 输出
        for(j = 0;j < i;j++)
            printf("%s\n" , result[j].s);
    }
}

int compare(const void *a , const void *b){
    return strcmp((*(struct record *)a).s , (*(struct record *)b).s);
}