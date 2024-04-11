#include <iostream>
#include <string>
#include <queue>
using namespace std;

const int ascii = 256; // ASCII characters total

// Node structure for Huffman tree
struct Node {
    char data;
    int freq;
    Node *left, *right;

// Initializes object
    Node(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

// Comparison function for priority queue
struct cNodes {
    bool operator()(const Node* a, const Node* b) const {
        return a->freq > b->freq;
    }
};

// Function to build Huffman tree and return the root
Node* buildHuffmanTree(const string& input) {
  
    // Calculate the frequency of each character in the input string
    int freq[ascii] = {0};
    for (char c : input) {
        freq[static_cast<unsigned char>(c)]++;
    }

    // Create leaf nodes for characters with non-zero frequency
    priority_queue<Node*, vector<Node*>, cNodes> pq;
    for (int i = 0; i < ascii; ++i) {
        if (freq[i] > 0) {
            pq.push(new Node(static_cast<char>(i), freq[i]));
        }
    }

    // Greedy method: Merge nodes with lowest frequencies until only one node remains
    while (pq.size() > 1) {
        // Extract the two nodes with the lowest frequency
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        // Create a new internal node with the sum of the frequencies
        Node* newNode = new Node('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        // Add the new node back to the priority queue
        pq.push(newNode);
    }

    // Root of the Huffman tree (remaining Node)
    return pq.top();
}

// Function to generate Huffman codes for each character
void genHuffCodes(Node* root, string code, string huffCodes[]) {
    if (root == nullptr) {
        return;
    }

    // If leaf node, store the code in array
    if (!root->left && !root->right) {
        huffCodes[static_cast<unsigned char>(root->data)] = code;
    }

    // Recursively generate codes for left and right subtrees
    genHuffCodes(root->left, code + "0", huffCodes);
    genHuffCodes(root->right, code + "1", huffCodes);
}

int main() {
    string input;
    cout << "Enter a string of text: ";
    cin >> input;

  
    // Build the Huffman tree
    Node* root = buildHuffmanTree(input);

    // Generate Huffman codes for each character
    string huffmanCodes[ascii];
    genHuffCodes(root, "", huffmanCodes);

    // Print the Huffman codes
    cout << "Huffman Codes Generated:\n";
    for (int i = 0; i < ascii; ++i) {
        if (!huffmanCodes[i].empty()) {
            cout << static_cast<char>(i) << " : " << huffmanCodes[i] << endl;
//The static_cast operator is used in C++ for explicit type conversions. 
//For static_cast<char>(i), it converts the integer i to a char -> access the character at the corresponding index in the huffmanCodes array.
          
        }
    }

    return 0;
}

