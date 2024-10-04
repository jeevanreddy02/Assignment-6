#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

// A Huffman Tree node
struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode *leftChild, *rightChild;

    HuffmanNode(char character, int frequency) {
        leftChild = rightChild = nullptr;
        this->character = character;
        this->frequency = frequency;
    }
};

// Comparison object to order the priority queue
struct CompareNodes {
    bool operator()(HuffmanNode* leftChild, HuffmanNode* rightChild) {
        return (leftChild->frequency > rightChild->frequency);
    }
};

// Print the Huffman codes in preorder traversal
void printHuffmanCodes(HuffmanNode* rootNode, string code) {
    if (!rootNode)
        return;

    // If it's a leaf node, print the character and its code
    if (rootNode->character != '#')
        cout << rootNode->character << ": " << code << "\n";

    printHuffmanCodes(rootNode->leftChild, code + "0");
    printHuffmanCodes(rootNode->rightChild, code + "1");
}

// Build the Huffman Tree and print codes
void generateHuffmanTree(const string &characters, const vector<int> &frequencies) {
    HuffmanNode *leftChild, *rightChild, *newNode;

    // Create a priority queue to store the nodes of the Huffman tree
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> minHeap;

    // Create a leaf node for each character and add it to the priority queue
    for (int i = 0; i < characters.size(); i++) {
        minHeap.push(new HuffmanNode(characters[i], frequencies[i]));
    }

    // Iterate until the size of the heap is reduced to 1
    while (minHeap.size() != 1) {
        // Extract the two nodes of lowest frequency
        leftChild = minHeap.top();
        minHeap.pop();

        rightChild = minHeap.top();
        minHeap.pop();

        // Create a new internal node with a frequency equal to the sum of the two nodes
        newNode = new HuffmanNode('#', leftChild->frequency + rightChild->frequency);

        // Assign the extracted nodes as left and right children
        newNode->leftChild = leftChild;
        newNode->rightChild = rightChild;

        // Add the new node to the priority queue
        minHeap.push(newNode);
    }

    // The remaining node is the root of the Huffman Tree
    printHuffmanCodes(minHeap.top(), "");
}

int main() {
    string characters = "abcdef";
    vector<int> frequencies = {5, 9, 12, 13, 16, 45};

    generateHuffmanTree(characters, frequencies);

    return 0;
}

Output:

f: 0
c: 100
d: 101
a: 1100
b: 1101
e: 111
