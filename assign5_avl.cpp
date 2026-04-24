#include <iostream>
using namespace std;

class node {
public:
    string word, mean;
    node *l, *r;

    node(string w, string m) {
        word = w;
        mean = m;
        l = r = NULL;
    }
};

class tree {
    node *root;

public:
    tree() {
        root = NULL;
    }

    // HEIGHT
    int height(node *root) {
        if (root == NULL) return 0;

        int lh = height(root->l);
        int rh = height(root->r);

        return max(lh, rh) + 1;
    }

    // BALANCE FACTOR
    int diff(node *root) {
        return height(root->l) - height(root->r);
    }

    // LL (Right rotation)
    node* ll(node *parent) {
        node *temp = parent->l;
        parent->l = temp->r;
        temp->r = parent;
        return temp;
    }

    // RR (Left rotation)
    node* rr(node *parent) {
        node *temp = parent->r;
        parent->r = temp->l;
        temp->l = parent;
        return temp;
    }

    // LR
    node* lr(node *parent) {
        parent->l = rr(parent->l);
        return ll(parent);
    }

    // RL
    node* rl(node *parent) {
        parent->r = ll(parent->r);
        return rr(parent);
    }

    // BALANCE FUNCTION
    node* balance(node *root) {
        int bf = diff(root);

        // Left heavy
        if (bf > 1) {
            if (diff(root->l) >= 0)
                return ll(root);   // LL
            else
                return lr(root);   // LR
        }

        // Right heavy
        if (bf < -1) {
            if (diff(root->r) <= 0)
                return rr(root);   // RR
            else
                return rl(root);   // RL
        }

        return root;
    }

    // INSERT
    node* insert(node *root, string word, string mean) {
        if (root == NULL)
            return new node(word, mean);

        if (word < root->word)
            root->l = insert(root->l, word, mean);

        else if (word > root->word)
            root->r = insert(root->r, word, mean);

        else {
            cout << "Duplicate word not allowed\n";
            return root;
        }

        return balance(root);
    }

    // UPDATE
    void update(node *root, string word, string newMean) {
        if (root == NULL) {
            cout << "Word not found\n";
            return;
        }

        if (word == root->word) {
            root->mean = newMean;
            cout << "Updated successfully\n";
        }
        else if (word < root->word)
            update(root->l, word, newMean);
        else
            update(root->r, word, newMean);
    }

    // DISPLAY (Ascending)
    void inorder(node *root) {
        if (root == NULL) return;

        inorder(root->l);
        cout << root->word << " : " << root->mean << endl;
        inorder(root->r);
    }

    // WRAPPER FUNCTIONS
    void add(string word, string mean) {
        root = insert(root, word, mean);
    }

    void updateMeaning(string word, string mean) {
        update(root, word, mean);
    }

    void display() {
        cout << "\nDictionary (Ascending Order):\n";
        inorder(root);
    }
};

// MAIN
int main() {
    tree t;
    int choice;
    string word, mean;

    do {
        cout << "\n1. Insert\n2. Update\n3. Display\n0. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter word: ";
            cin >> word;
            cout << "Enter meaning: ";
            cin >> mean;
            t.add(word, mean);
            break;

        case 2:
            cout << "Enter word: ";
            cin >> word;
            cout << "Enter new meaning: ";
            cin >> mean;
            t.updateMeaning(word, mean);
            break;

        case 3:
            t.display();
            break;
        }

    } while (choice != 0);

    return 0;
}