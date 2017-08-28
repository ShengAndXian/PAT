#include <iostream>
using namespace std;

struct Item {
    int index;
    int times;
};

int main() {
    int n;
    int k;

    cin >> n >> k;

    int count[50010] = {0};
    Item list[10];

    for (int i = 0;i < 10;i++) {
        list[i].index = 0;
        list[i].times = 0;
    }

    for (int i = 0;i < n;i++) {
        int index;

        cin >> index;

        if (i > 0) {
            cout << index << ":";

            for (int j = 0;j < k;j++) {
                if (list[j].index == 0) {
                    break;
                }
                cout << " " << list[j].index; 
            }

            cout << endl;
        }

        count[index]++;

        for (int j = 0;j < 10;j++) {
            if (list[j].index == index) {
                for (int t = j;t < 9;t++) {
                    list[t] = list[t + 1];
                }
                
                list[9].index = 0;
                list[9].times = 0;
            }
        }

        Item item = *(new Item());

        item.index = index;
        item.times = count[index];

        int t;

        for (t = 9;t >= 0;t--) {
            if (list[t].times > item.times || (list[t].times == item.times && list[t].index < item.index)) {
                break;
            }
        }

        for (int j = 9;j > t + 1;j--) {
            list[j] = list[j - 1];
        }

        list[t + 1] = item;
    }
}