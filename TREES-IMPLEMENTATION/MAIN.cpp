#include <iostream>
#include<Windows.h>

using namespace std;

class Node {
public:
    int data;
    Node* right;
    Node* left;

    static int NofNodes;

    Node(int data) {
        this->data = data;
        this->right = nullptr;
        this->left = nullptr;
        NofNodes++;
    }
};

int Node::NofNodes = 0;

class Tree {
    Node* root;

    Node* insert(Node* node, int value) {
        if (!node) {
            return new Node(value);
        }
        if (value <= node->data) {
            node->left = insert(node->left, value);
        }
        else {
            node->right = insert(node->right, value);
        }
        return node;
    }

    void inOrderTraversal(Node* node) {
        if (!node) return;
        inOrderTraversal(node->left);
        cout << node->data << " ";
        inOrderTraversal(node->right);
    }

    void preOrderTraversal(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preOrderTraversal(node->left);
        preOrderTraversal(node->right);
    }

    void postOrderTraversal(Node* node) {
        if (!node) return;
        postOrderTraversal(node->left);
        postOrderTraversal(node->right);
        cout << node->data << " ";
    }

public:
    Tree() : root(nullptr) {}

    void insert(int value) {
        root = insert(root, value);
    }

    void inOrderTraversal() {
        system("CLS");
        cout << "In-Order Traversal: ";
        inOrderTraversal(root);
        cout << endl;
    }

    void preOrderTraversal() {
        system("CLS");
        cout << "Pre-Order Traversal: ";
        preOrderTraversal(root);
        cout << endl;
    }

    void postOrderTraversal() {
        system("CLS");
        cout << "Post-Order Traversal: ";
        postOrderTraversal(root);
        cout << endl;
    }

    void search(int value) {
        Node* current = root;
        Node* parent = nullptr;
        system("CLS");
        while (current) {
            if (current->data == value) {
                cout << "\n Value " << value << " found in the tree.";
                if (current->left)
                    cout << "\n Left child: " << current->left->data;
                else
                    cout << "\n Left child: NULL";

                if (current->right)
                    cout << "\n Right child: " << current->right->data ;
                else
                    cout << "\n Right child: NULL ";

                if (parent)
                    cout << "\n Parent: " << parent->data;
                else
                    cout << "\n Parent: NULL (root node)";
                return;
            }
            parent = current;
            current = (value < current->data) ? current->left : current->right;
        }

        cout << "\n Value " << value << " not found in the tree.";
    }
};

int main() {
    Tree tr;
    int option;

    while (true) {
       
        cout << "\n-------------- Menu -----------------"
            << "\n 1. Insert value into the tree."
            << "\n 2. Search value in the tree."
            << "\n 3. In-Order Traversal."
            << "\n 4. Pre-Order Traversal."
            << "\n 5. Post-Order Traversal."
            << "\n 6. Exit."
            << "\n Enter an option: ";
        cin >> option;

        switch (option) {
        case 1: {
            int value;
            cout << "\n Enter values to insert (-1 to stop): ";
            while (true) {
                cin >> value;
                if (value == -1) break;
                tr.insert(value);
            }
                system("CLS");
            break;
        }
        case 2: {
            int value;
            cout << "\n Enter value to search: ";
            cin >> value;
            tr.search(value);
            cin.clear();
            
            
            break;
        }
        case 3:
            tr.inOrderTraversal();
            
            break;
        case 4:
            tr.preOrderTraversal();
            
            break;
        case 5:
            tr.postOrderTraversal();
            break;
        case 6:
            cout << "\n Exiting program....";
            return 0;
        default:
            cout << "\n Invalid option. Please try again.";
        }
    }
}
