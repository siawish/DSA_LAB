#include <iostream>

using namespace std;
struct Node {
    int data;
    Node* left;
    Node* right;
};

class BinarySearchTree {
private:
    Node* root;

    Node* createNode(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->left = newNode->right = nullptr;
        return newNode;
    }

    Node* insert(Node* node, int value) {
        if (!node) return createNode(value);
        if (value < node->data) node->left = insert(node->left, value);
        else if (value > node->data) node->right = insert(node->right, value);
        return node;
    }

    Node* deleteNode(Node* root, int value) {
        if (!root) return root;
        if (value < root->data) root->left = deleteNode(root->left, value);
        else if (value > root->data) root->right = deleteNode(root->right, value);
        else {
            if (!root->left) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (!root->right) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }

    Node* findMin(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int value) {
        root = insert(root, value);
        cout << "Value " << value << " inserted successfully.\n";
    }

    void deleteValue(int value) {
        root = deleteNode(root, value);
        cout << "Value " << value << " deleted successfully.\n";
    }

    void displayInOrder() {
        inorder(root);
        cout << endl;
    }

    void displayPreOrder() {
        preorder(root);
        cout << endl;
    }

    void displayPostOrder() {
        postorder(root);
        cout << endl;
    }
};

class Graph {
private:
    int vertices;
    int** adjacencyMatrix;

public:
    Graph(int v) : vertices(v) {
        adjacencyMatrix = new int* [vertices];
        for (int i = 0; i < vertices; i++) {
            adjacencyMatrix[i] = new int[vertices];
            for (int j = 0; j < vertices; j++) {
                adjacencyMatrix[i][j] = (i == j) ? 0 : INT_MAX;
            }
        }
    }

    ~Graph() {
        for (int i = 0; i < vertices; i++) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }

    void addEdge(int src, int dest, int weight) {
        adjacencyMatrix[src][dest] = weight;
        cout << "Edge from " << src << " to " << dest << " with weight " << weight << " added successfully.\n";
    }

    void dijkstra(int src, int dest) {
        bool* visited = new bool[vertices];
        int* dist = new int[vertices];
        for (int i = 0; i < vertices; i++) {
            dist[i] = INT_MAX;
            visited[i] = false;
        }
        dist[src] = 0;

        for (int i = 0; i < vertices - 1; i++) {
            int u = findMinDistance(dist, visited);
            visited[u] = true;
            for (int v = 0; v < vertices; v++) {
                if (!visited[v] && adjacencyMatrix[u][v] != INT_MAX &&
                    dist[u] != INT_MAX && dist[u] + adjacencyMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjacencyMatrix[u][v];
                }
            }
        }

        if (dist[dest] == INT_MAX) {
            cout << "No path from " << src << " to " << dest << endl;
        }
        else {
            cout << "Shortest path from " << src << " to " << dest << " is " << dist[dest] << endl;
        }
        delete[] visited;
        delete[] dist;
    }

private:
    int findMinDistance(int* dist, bool* visited) {
        int min = INT_MAX, minIndex = -1;
        for (int v = 0; v < vertices; v++) {
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                minIndex = v;
            }
        }
        return minIndex;
    }
};

void merge(int arr[], int left, int mid, int right, int& comparisons, int& swaps) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        }
        else {
            arr[k++] = R[j++];
            swaps++;
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right, int& comparisons, int& swaps) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, comparisons, swaps);
        mergeSort(arr, mid + 1, right, comparisons, swaps);
        merge(arr, left, mid, right, comparisons, swaps);
    }
}

int partition(int arr[], int low, int high, int& comparisons, int& swaps) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        comparisons++;
        if (arr[j] < pivot) {
            swaps++;
            swap(arr[++i], arr[j]);
        }
    }
    swaps++;
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high, int& comparisons, int& swaps) {
    if (low < high) {
        int pi = partition(arr, low, high, comparisons, swaps);
        quickSort(arr, low, pi - 1, comparisons, swaps);
        quickSort(arr, pi + 1, high, comparisons, swaps);
    }
}

int getValidInt() {
    int value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter an integer: ";
    }
    return value;
}

int main() {
    BinarySearchTree bst;
    Graph* graph = nullptr;
    int choice;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Binary Search Tree Operations\n";
        cout << "2. Graph Pathfinding\n";
        cout << "3. Sorting Algorithms\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        choice = getValidInt();

        switch (choice) {
        case 1: {
            int bstChoice, value;
            cout << "1. Insert\n2. Delete\n3. Inorder Traversal\n4. Preorder Traversal\n5. Postorder Traversal\nEnter choice: ";
            bstChoice = getValidInt();
            switch (bstChoice) {
            case 1:
                cout << "Enter value to insert: ";
                value = getValidInt();
                bst.insert(value);
                break;
            case 2:
                cout << "Enter value to delete: ";
                value = getValidInt();
                bst.deleteValue(value);
                break;
            case 3:
                bst.displayInOrder();
                break;
            case 4:
                bst.displayPreOrder();
                break;
            case 5:
                bst.displayPostOrder();
                break;
            default:
                cout << "Invalid choice.\n";
            }
            break;
        }
        case 2: {
            int v, src, dest, weight;
            if (!graph) {
                cout << "Enter number of vertices: ";
                v = getValidInt();
                graph = new Graph(v);
            }
            cout << "1. Add Edge\n2. Find Shortest Path\nEnter choice: ";
            int graphChoice;
            graphChoice = getValidInt();
            switch (graphChoice) {
            case 1:
                cout << "Enter source, destination, and weight: ";
                src = getValidInt();
                dest = getValidInt();
                weight = getValidInt();
                graph->addEdge(src, dest, weight);
                break;
            case 2:
                cout << "Enter source and destination: ";
                src = getValidInt();
                dest = getValidInt();
                graph->dijkstra(src, dest);
                break;
            default:
                cout << "Invalid choice.\n";
            }
            break;
        }
        case 3: {
            int n;
            cout << "Enter number of elements in array: ";
            n = getValidInt();
            int* arr1 = new int[n];
            int* arr2 = new int[n];
            cout << "Enter elements: ";
            for (int i = 0; i < n; i++) {
                cin >> arr1[i];
                arr2[i] = arr1[i];
            }
            int comparisons = 0, swaps = 0;
            mergeSort(arr1, 0, n - 1, comparisons, swaps);
            cout << "Merge Sort: Comparisons = " << comparisons << ", Swaps = " << swaps << "\n";
            comparisons = swaps = 0;
            quickSort(arr2, 0, n - 1, comparisons, swaps);
            cout << "Quick Sort: Comparisons = " << comparisons << ", Swaps = " << swaps << "\n";
            delete[] arr1;
            delete[] arr2;
            break;
        }
        case 4:
            cout << "Exiting the program.\n";
            delete graph;
            return 0;
        default:
            cout << "Invalid choice.\n";
        }
    }
}
