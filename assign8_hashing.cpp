#include <iostream>
#include <fstream>
using namespace std;

#define SIZE 10

class Student {
public:
    int roll;
    char name[20];
    float marks;

    Student() {
        roll = -1;
    }
};

int hashFunction(int r) {
    return r % SIZE;
}

// ---------- CREATE ----------
void create() {
    ofstream file("data.dat", ios::binary);
    Student s;

    for (int i = 0; i < SIZE; i++)
        file.write((char*)&s, sizeof(s));

    file.close();
    cout << "File created\n";
}

// ---------- ADD ----------
void add() {
    fstream file("data.dat", ios::in | ios::out | ios::binary);
    Student s, temp;

    cout << "Enter roll name marks: ";
    cin >> s.roll >> s.name >> s.marks;

    int index = hashFunction(s.roll);

    int choice;
    cout << "1.Without Replacement\n2.With Replacement\nChoose: ";
    cin >> choice;

    // -------- WITHOUT REPLACEMENT --------
    if (choice == 1) {
        for (int i = 0; i < SIZE; i++) {
            int pos = (index + i) % SIZE;

            file.seekg(pos * sizeof(s));
            file.read((char*)&temp, sizeof(temp));

            if (temp.roll == -1) {
                file.seekp(pos * sizeof(s));
                file.write((char*)&s, sizeof(s));
                break;
            }
        }
    }

    // -------- WITH REPLACEMENT --------
    else {
        file.seekg(index * sizeof(s));
        file.read((char*)&temp, sizeof(temp));

        // if empty
        if (temp.roll == -1) {
            file.seekp(index * sizeof(s));
            file.write((char*)&s, sizeof(s));
        }
        else {
            // simple replacement logic
            if (hashFunction(temp.roll) != index) {
                file.seekp(index * sizeof(s));
                file.write((char*)&s, sizeof(s));
                s = temp;
            }

            // insert remaining using linear probing
            for (int i = 1; i < SIZE; i++) {
                int pos = (index + i) % SIZE;

                file.seekg(pos * sizeof(s));
                file.read((char*)&temp, sizeof(temp));

                if (temp.roll == -1) {
                    file.seekp(pos * sizeof(s));
                    file.write((char*)&s, sizeof(s));
                    break;
                }
            }
        }
    }

    file.close();
}

// ---------- DISPLAY ----------
void display() {
    ifstream file("data.dat", ios::binary);
    Student s;

    cout << "\nIndex\tRoll\tName\tMarks\n";

    for (int i = 0; i < SIZE; i++) {
        file.read((char*)&s, sizeof(s));

        cout << i << "\t";
        if (s.roll == -1)
            cout << "Empty";
        else
            cout << s.roll << "\t" << s.name << "\t" << s.marks;

        cout << endl;
    }

    file.close();
}

// ---------- SEARCH ----------
void search() {
    ifstream file("data.dat", ios::binary);
    Student s;
    int roll;

    cout << "Enter roll: ";
    cin >> roll;

    int index = hashFunction(roll);

    for (int i = 0; i < SIZE; i++) {
        int pos = (index + i) % SIZE;

        file.seekg(pos * sizeof(s));
        file.read((char*)&s, sizeof(s));

        if (s.roll == roll) {
            cout << "Found: " << s.name << " " << s.marks << endl;
            file.close();
            return;
        }
    }

    cout << "Not found\n";
    file.close();
}

// ---------- MODIFY ----------
void modify() {
    fstream file("data.dat", ios::in | ios::out | ios::binary);
    Student s;
    int roll;

    cout << "Enter roll: ";
    cin >> roll;

    int index = hashFunction(roll);

    for (int i = 0; i < SIZE; i++) {
        int pos = (index + i) % SIZE;

        file.seekg(pos * sizeof(s));
        file.read((char*)&s, sizeof(s));

        if (s.roll == roll) {
            cout << "Enter new name marks: ";
            cin >> s.name >> s.marks;

            file.seekp(pos * sizeof(s));
            file.write((char*)&s, sizeof(s));

            cout << "Updated\n";
            file.close();
            return;
        }
    }

    cout << "Not found\n";
    file.close();
}

// ---------- MAIN ----------
int main() {
    int ch;

    do {
        cout << "\n1.Create\n2.Display\n3.Add\n4.Search\n5.Modify\n6.Exit\n";
        cin >> ch;

        switch (ch) {
            case 1: create(); break;
            case 2: display(); break;
            case 3: add(); break;
            case 4: search(); break;
            case 5: modify(); break;
        }

    } while (ch != 6);

    return 0;
}