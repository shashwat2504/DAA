#include <iostream>
using namespace std;

class Node {
public:
    string key, meaning;
    Node* left;
    Node* right;
    int height;

    Node(string k, string m) {
        key = k;
        meaning = m;
        left = right = NULL;
        height = 1;
    }
};

class AVLDictionary {
    Node* root;

public:
    AVLDictionary() {
        root = NULL;
    }

    // Height
    int height(Node* node) {
        if (node == NULL) return 0;
        return node->height;
    }

    // Balance Factor
    int getBalance(Node* node) {
        if (node == NULL) return 0;
        return height(node->left) - height(node->right);
    }

    // Right Rotate
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    // Left Rotate
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    // Insert
    Node* insert(Node* node, string key, string meaning) {
        if (node == NULL)
            return new Node(key, meaning);

        if (key < node->key)
            node->left = insert(node->left, key, meaning);
        else if (key > node->key)
            node->right = insert(node->right, key, meaning);
        else {
            cout << "Keyword already exists! Use update.\n";
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        // AVL Cases
        // LL
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // RR
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // LR
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // Update meaning
    void update(Node* node, string key, string newMeaning) {
        if (node == NULL) {
            cout << "Keyword not found!\n";
            return;
        }

        if (key == node->key) {
            node->meaning = newMeaning;
            cout << "Updated successfully!\n";
        }
        else if (key < node->key)
            update(node->left, key, newMeaning);
        else
            update(node->right, key, newMeaning);
    }

    // Search with comparison count
    Node* search(Node* node, string key, int &comparisons) {
        if (node == NULL) return NULL;

        comparisons++;

        if (key == node->key)
            return node;
        else if (key < node->key)
            return search(node->left, key, comparisons);
        else
            return search(node->right, key, comparisons);
    }

    // Inorder (sorted)
    void inorder(Node* node) {
        if (node != NULL) {
            inorder(node->left);
            cout << node->key << " : " << node->meaning << endl;
            inorder(node->right);
        }
    }

    // Wrapper functions
    void add(string key, string meaning) {
        root = insert(root, key, meaning);
    }

    void updateMeaning(string key, string meaning) {
        update(root, key, meaning);
    }

    void display() {
        cout << "\nDictionary (Sorted):\n";
        inorder(root);
    }

    void find(string key) {
        int comparisons = 0;
        Node* result = search(root, key, comparisons);

        if (result)
            cout << "Found: " << result->meaning << endl;
        else
            cout << "Not Found\n";

        cout << "Comparisons required: " << comparisons << endl;
    }

    void maxComparisons() {
        cout << "Maximum comparisons (height of AVL tree): " << height(root) << endl;
    }
};

// MAIN
int main() {
    AVLDictionary dict;
    int choice;
    string key, meaning;

    do {
        cout << "\n--- AVL Dictionary Menu ---\n";
        cout << "1. Add Keyword\n2. Update Meaning\n3. Display\n4. Search\n5. Max Comparisons\n0. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter keyword: ";
            cin >> key;
            cout << "Enter meaning: ";
            cin.ignore();
            getline(cin, meaning);
            dict.add(key, meaning);
            break;

        case 2:
            cout << "Enter keyword: ";
            cin >> key;
            cout << "Enter new meaning: ";
            cin.ignore();
            getline(cin, meaning);
            dict.updateMeaning(key, meaning);
            break;

        case 3:
            dict.display();
            break;

        case 4:
            cout << "Enter keyword to search: ";
            cin >> key;
            dict.find(key);
            break;

        case 5:
            dict.maxComparisons();
            break;

        case 0:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}