#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

enum Color {White, Gray, Black};

struct Node {
    int index;
    int line;
    Node* next;
};

struct Vertex {
    vector<int> lines;
    Color color;
    int distance;
    Node* ptr;
};

Vertex* list[10000];
int numOfStations;
int startStation;
int preLine;
int numOfTransfers;
int currentNumOfTransfers;
vector<int> transfers;
vector<int> lineRecord;

void connect(int index1, int index2, int line) {
    Node* node = new Node();

    node->index = index2;
    node->next = NULL;
    node->line = line;

    if (list[index1]->ptr != NULL) {
        node->next = list[index1]->ptr;
    }

    list[index1]->ptr = node;
}

void BFS(int start, int end) {
    queue<Vertex*> queue1;

    queue1.push(list[start]);

    while (!queue1.empty()) {
        Vertex* v = queue1.front();
        queue1.pop();


        Node* p = v->ptr;

        while (p != NULL) {
            if (list[p->index]->color == White) {
                list[p->index]->color = Gray;
                list[p->index]->distance = v->distance + 1;

                queue1.push(list[p->index]);
            }

            p = p->next;
        }

        v->color = Black;
    }
}

bool DFS(int start, int end) {
    if (numOfStations + 1 > list[end]->distance) {
        return false;
    }

    if (start == end) {
        if (currentNumOfTransfers < numOfTransfers) {
            numOfTransfers = currentNumOfTransfers;

            transfers.clear();
            lineRecord.clear();

            transfers.push_back(end);

            return true;
        } else {
            return false;
        }
    }

    numOfStations++;
    
    list[start]->color = Gray;

    Node* p = list[start]->ptr;
    bool flag = false;
    int pre = preLine;

    while (p != NULL) {
        if (list[p->index]->color == White) {
            if (p->line != pre)
                currentNumOfTransfers++;
                
            preLine = p->line;

            if (DFS(p->index, end)) {
                flag = true;

                if (p->line != pre || start == startStation) {
                    transfers.push_back(start);
                    lineRecord.push_back(p->line);
                }
            }

            if (p->line != pre)
                currentNumOfTransfers--;
        }

        p = p->next;
    }

    numOfStations--;

    list[start]->color = White;

    return flag;
}

int main() {
    int numOfLines;

    cin >> numOfLines;

    for (int i = 0;i < 10000;i++) {
        list[i] = NULL;
    }

    for (int i = 1;i <= numOfLines;i++) {
        int numOfStations;

        cin >> numOfStations;

        int pre = -1;

        for (int j = 0;j < numOfStations;j++) {
            int stationIndex;

            cin >> stationIndex;

            if (list[stationIndex] == NULL) {
                Vertex* v = new Vertex();
                
                v->lines.push_back(i);
                v->ptr = NULL;

                list[stationIndex] = v;
            } else if (list[stationIndex]->lines[0] != i){
                list[stationIndex]->lines.push_back(i);
            }

            if (pre != -1) {
                connect(pre, stationIndex, i);
                connect(stationIndex, pre, i);
            }

            pre = stationIndex;
        }
    }

    int queryTimes;

    cin >> queryTimes;

    for (int i = 0;i < queryTimes;i++) {
        int start;
        int end;

        cin >> start >> end;

        for (int j = 0;j < 10000;j++) {
            if (list[j] != NULL) {
                list[j]->color = White;
                list[j]->distance = 10000;
            }
        }

        list[start]->color = Gray;
        list[start]->distance = 1;

        BFS(start, end);

        startStation = start;
        preLine = 0;
        numOfTransfers = 10000;
        currentNumOfTransfers = 0;
        numOfStations = 0;
        transfers.clear();

        for (int j = 0;j < 10000;j++) {
            if (list[j] != NULL) {
                list[j]->color = White;
            }
        }

        DFS(start, end);

        cout << list[end]->distance - 1 << endl;

        for (int i = 0;i < lineRecord.size();i++) {
            printf("Take Line#%d from %04d to %04d.\n", lineRecord[lineRecord.size() - 1 - i], transfers[transfers.size() - 1 - i], transfers[transfers.size() - 2 - i]);
         }
    }
}