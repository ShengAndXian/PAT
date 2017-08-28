#include <iostream>
using namespace std;

int main() {
    int k;

    cin >> k;

    for (int i = 0;i < k;i++) {
        int n;

        cin >> n;

        int count[1100] = {0};
        int arr[1100];
        bool flag = true;

        for (int j = 1;j <= n;j++) {
            cin >> arr[j];

            count[arr[j]]++;

            if (count[arr[j]] > 1) {
                flag = false;
            }
        }

        if (!flag) {
            cout << "NO" << endl;
            continue;
        }

        flag = true;

        for (int j = 1;j <= n;j++) {
            for (int t = 1;j - t > 0 && arr[j] - t > 0;t++) {
                if (arr[j - t] == arr[j] - t) {
                    flag = false;
                    break;
                }
            }

            if (!flag) {
                break;
            }

            for (int t = 1;j + t <= n && arr[j] + t <= n;t++) {
                if (arr[j + t] == arr[j] + t) {
                    flag = false;
                    break;
                }
            }

            if (!flag) {
                break;
            }
        }

        if (flag) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}