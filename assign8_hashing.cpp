#include <iostream>
#include <fstream>
using namespace std;

#define SIZE 10

// ===== RECORD =====
class Record {
public:
    int roll;
    char name[20];
    int marks;

    void input() {
        cout << "Enter Roll: ";
        cin >> roll;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() {
        cout << roll << "\t" << name << "\t" << marks << endl;
    }
};

// ===== HASH TABLE ENTRY =====
class Hash {
public:
    int roll;
    int pos;

    Hash() {
        roll = -1;
        pos = -1;
    }
};

// ===== MAIN CLASS =====
class DB {
    Hash table[SIZE];
    fstream file;

public:

    DB() {
        file.open("data.dat", ios::out | ios::binary);
        file.close();
    }

    int hashFunc(int r) {
        return r % SIZE;
    }

    // ===== COMMON FUNCTION TO WRITE IN FILE =====
    int writeToFile(Record &r) {
        file.open("data.dat", ios::app | ios::binary);
        int pos = file.tellp() / sizeof(Record);
        file.write((char*)&r, sizeof(r));
        file.close();
        return pos;
    }

    // ================= WITHOUT REPLACEMENT =================
    void insertWithout() {
        Record r;
        r.input();

        int index = hashFunc(r.roll);

        // linear probing
        while (table[index].pos != -1) {
            index = (index + 1) % SIZE;
        }

        int pos = writeToFile(r);

        table[index].roll = r.roll;
        table[index].pos = pos;

        cout << "Inserted (Without Replacement)\n";
    }

    // ================= WITH REPLACEMENT =================
    void insertWith() {
        Record r;
        r.input();

        int index = hashFunc(r.roll);

        // CASE 1: empty
        if (table[index].pos == -1) {
            int pos = writeToFile(r);
            table[index].roll = r.roll;
            table[index].pos = pos;
        }

        // CASE 2: collision
        else {
            // if existing element is NOT at home position
            if (hashFunc(table[index].roll) != index) {

                // swap
                int oldRoll = table[index].roll;
                int oldPos  = table[index].pos;

                int pos = writeToFile(r);
                table[index].roll = r.roll;
                table[index].pos = pos;

                // reinsert old element
                int newIndex = (index + 1) % SIZE;
                while (table[newIndex].pos != -1) {
                    newIndex = (newIndex + 1) % SIZE;
                }

                table[newIndex].roll = oldRoll;
                table[newIndex].pos = oldPos;
            }

            // normal probing
            else {
                while (table[index].pos != -1) {
                    index = (index + 1) % SIZE;
                }

                int pos = writeToFile(r);
                table[index].roll = r.roll;
                table[index].pos = pos;
            }
        }

        cout << "Inserted (With Replacement)\n";
    }

    // ================= DISPLAY =================
    void display() {
        Record r;
        file.open("data.dat", ios::in | ios::binary);

        cout << "\nRoll\tName\tMarks\n";

        while (file.read((char*)&r, sizeof(r))) {
            r.display();
        }

        file.close();
    }

    // ================= SEARCH =================
    void search() {
        int roll;
        cout << "Enter Roll: ";
        cin >> roll;

        int index = hashFunc(roll);
        int start = index;

        while (table[index].roll != -1) {

            if (table[index].roll == roll) {
                Record r;

                file.open("data.dat", ios::in | ios::binary);
                file.seekg(table[index].pos * sizeof(Record));
                file.read((char*)&r, sizeof(r));
                file.close();

                cout << "Found:\n";
                r.display();
                return;
            }

            index = (index + 1) % SIZE;
            if (index == start) break;
        }

        cout << "Not Found\n";
    }

    // ================= MODIFY =================
    void modify() {
        int roll;
        cout << "Enter Roll: ";
        cin >> roll;

        int index = hashFunc(roll);
        int start = index;

        while (table[index].roll != -1) {

            if (table[index].roll == roll) {
                Record r;
                cout << "Enter new data:\n";
                r.input();

                file.open("data.dat", ios::in | ios::out | ios::binary);
                file.seekp(table[index].pos * sizeof(Record));
                file.write((char*)&r, sizeof(r));
                file.close();

                cout << "Updated\n";
                return;
            }

            index = (index + 1) % SIZE;
            if (index == start) break;
        }

        cout << "Not Found\n";
    }
};

// ===== MAIN =====
int main() {
    DB db;
    int ch;

    do {
        cout << "\n1.Insert Without Replacement";
        cout << "\n2.Insert With Replacement";
        cout << "\n3.Display";
        cout << "\n4.Search";
        cout << "\n5.Modify";
        cout << "\n6.Exit";

        cout << "\nEnter choice: ";
        cin >> ch;

        switch (ch) {
            case 1: db.insertWithout(); break;
            case 2: db.insertWith(); break;
            case 3: db.display(); break;
            case 4: db.search(); break;
            case 5: db.modify(); break;
        }

    } while (ch != 6);

    return 0;
}