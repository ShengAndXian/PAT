#include <iostream>
using namespace std;

struct Node {
    string data;
    int leftChild;
    int rightChild;
};

Node list[21];
int hasParent[21] = {0};
int rootOfTree;

void inorderTraversal(int root) {
    if (root == -1)
        return;

    if (list[root].leftChild == -1 && list[root].rightChild == -1) {
        cout << list[root].data;
        return;
    }

    if (root != rootOfTree) 
        cout << "(";

    inorderTraversal(list[root].leftChild);

    cout << list[root].data;

    inorderTraversal(list[root].rightChild);

    if (root != rootOfTree)
        cout << ")";
}

int main() {
    int n;

    cin >> n;

    for (int i = 1;i <= n;i++) {
        Node* ptrToNode = new Node();

        cin >> ptrToNode->data >> ptrToNode->leftChild >> ptrToNode->rightChild;

        if (ptrToNode->leftChild != -1)
            hasParent[ptrToNode->leftChild] = 1;
        if (ptrToNode->rightChild != -1)
            hasParent[ptrToNode->rightChild] = 1;

        list[i] = *ptrToNode;
    }

    for (int i = 1;i <= n;i++) {
        if (hasParent[i] == 0) {
            rootOfTree = i;
            break;
        }
    }

    inorderTraversal(rootOfTree);

    return 0;
}