// PAT甲级1043 Is It a Binary Search Tree，原题地址：https://www.patest.cn/contests/pat-a-practise/1043
// 解题分析：
//  二叉搜索树的性质和遍历。刚做这道题的时候，我用了一种比较笨的方法，根据所给的序列直接按二叉搜索树的性质构建出整个树，
//  然后对其进行前序遍历，考察得到的序列是否和所给的序列一致，如果一致，则后序遍历树，然后输出，否则进行镜像的前序遍历，
//  也就是按根节点、右子树、左子树的顺序，得到序列之后就和之前的步骤一致了。如哟前序遍历的结果都和所给序列不符合，则输出
//  NO。
//  之后看了网上的大神的解答，发现根据二叉搜索树的性质，可以用很简洁的代码完成。具体的过程直接在程序中注释了。
#include<stdio.h>
#include<stdlib.h>

void getpost(int order[] , int start , int end);

// 默认is_mirror为0，即默认为BST
int is_mirror = 0;
int post[10000];
int count = 0;

int main(){
    int n;
    int i;
    int *order;

    scanf("%d" , &n);
    // 储存所给序列的数组
    order = (int *)malloc(sizeof(int) * n);
    // 输入
    for(i = 0;i < n;i++){
        scanf("%d" , &order[i]);
    }
    // 后序遍历
    getpost(order , 0 , n - 1);
    // 如果后序遍历的节点个数不等于全部节点个数，说明不是BST
    if(count != n){
        // 将is_mirror变量设为1
        is_mirror = 1;
        // 清空post数组
        count = 0;
        // 再次后序遍历
        getpost(order , 0 , n - 1);
    }
    // 如果count等于n，说明是BST或者镜像BST
    if(count == n){
        // 输出
        printf("YES\n");
        for(i = 0;i < count;i++){
            printf("%d" , post[i]);
            if(i != count - 1)
                printf(" ");
        }
    }
    // 否则
    else
        printf("NO\n");
}

void getpost(int order[] , int start , int end){
    int i = start + 1, j = end;
    if(start > end)
        return;
    // 假设是BST
    if(!is_mirror){
        // 确定左右子树的范围
        while(i <= end && order[start] > order[i]) i++;
        while(j > start && order[start] <= order[j]) j--;
    }
    // 假设是镜像BST
    else{
        // 确定左右子树的范围
        while(i <= end && order[start] <= order[i]) i++;
        while(j > start && order[start] > order[j]) j--;
    }
    // 如果i－j不等于1，说明一定不是BST或镜像BST
    if(i - j != 1)
        return;
    // 后序遍历左子树
    getpost(order , start + 1 , j);
    // 后序遍历右子树
    getpost(order , i , end);
    // 纪录当前节点
    post[count++] = order[start];
}