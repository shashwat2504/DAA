#include <iostream>
using namespace std;

class User {
public:
    long long mobile;
    string name;
    float bill;

    void input() {
        cout << "Enter Mobile, Name, Bill: ";
        cin >> mobile >> name >> bill;
    }

    void display() {
        cout << "\nMobile: " << mobile;
        cout << "\nName: " << name;
        cout << "\nBill: " << bill << endl;
    }
};

// -------- Linear Search --------
int linearSearch(User u[], int n, long long key) {
    for (int i = 0; i < n; i++) {
        if (u[i].mobile == key)
            return i;
    }
    return -1;
}

// -------- Bubble Sort --------
void sortUsers(User u[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (u[j].mobile > u[j + 1].mobile) {
                User temp = u[j];
                u[j] = u[j + 1];
                u[j + 1] = temp;
            }
        }
    }
}

// -------- Iterative Binary --------
int binaryIterative(User u[], int n, long long key) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (u[mid].mobile == key)
            return mid;
        else if (u[mid].mobile < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}
 
// -------- Recursive Binary --------
int binaryRecursive(User u[], int left, int right, long long key) {
    if (left > right)
        return -1;

    int mid = (left + right) / 2;

    if (u[mid].mobile == key)
        return mid;
    else if (u[mid].mobile < key)
        return binaryRecursive(u, mid + 1, right, key);
    else
        return binaryRecursive(u, left, mid - 1, key);
}

int main() {
    User u[100];
    int n, choice;
    long long key;

    cout << "Enter number of users: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        u[i].input();
    }

    do {
        cout << "\n\n--- MENU ---";
        cout << "\n1. Linear Search";
        cout << "\n2. Iterative Binary Search";
        cout << "\n3. Recursive Binary Search";
        cout << "\n4. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "Enter mobile number to search: ";
            cin >> key;
            {
                int index = linearSearch(u, n, key);
                if (index != -1)
                    u[index].display();
                else
                    cout << "Not Found\n";
            }
            break;

        case 2:
            sortUsers(u, n); // important
            cout << "Enter mobile number to search: ";
            cin >> key;
            {
                int index = binaryIterative(u, n, key);
                if (index != -1)
                    u[index].display();
                else
                    cout << "Not Found\n";
            }
            break;

        case 3:
            sortUsers(u, n); // important
            cout << "Enter mobile number to search: ";
            cin >> key;
            {
                int index = binaryRecursive(u, 0, n - 1, key);
                if (index != -1)
                    u[index].display();
                else
                    cout << "Not Found\n";
            }
            break;

        case 4:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice\n";
        }

    } while (choice != 4);

    return 0;
}