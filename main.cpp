//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

//test

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Tracking, remove later
    // for (int i = 0; i < 9; i++) {
    //     cout << leftArr[i] << " " << rightArr[i] << " " << charArr[i] << " " << weightArr[i] << endl;
    // }

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    // 1. Create a MinHeap object.
    // 2. Push all leaf node indices into the heap.
    // 3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap
    // 4. Return the index of the last remaining node (root)

    MinHeap heap;
    for (int i = 0; i < nextFree; i++) {
        heap.push(i, weightArr);
    }

    while (heap.size > 1) {
        // Gets index stored in next two smallest nodes assigning them to left/right
        int left = heap.pop(weightArr);
        int right = heap.pop(weightArr);

        // Adds the weights of the two nodes, combining them into one and assigns the left to leftArr and right to rightArr
        weightArr[nextFree] = weightArr[left] + weightArr[right];
        leftArr[nextFree] = left;
        rightArr[nextFree] = right;

        // Tracing, remove later
        // cout << nextFree << " " << weightArr[nextFree] << " Left: " << leftArr[nextFree] << " Right: " << rightArr[nextFree] << endl;

        // Pushes the parent and moves onto next free index
        heap.push(nextFree, weightArr);
        nextFree++;
    }

    return heap.pop(weightArr);
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.

    stack<pair<int, string>> stack;
    string curr_code;
    // Pushing our root index (from buildEncodingTree) and an empty string for our code
    stack.push({root, curr_code});

    int i = 0;
    while (!stack.empty()) {
        int curr_node = stack.top().first;
        curr_code = stack.top().second;
        stack.pop();

        cout << curr_node << ": left =" << leftArr[curr_node] << " right =" << rightArr[curr_node] << " char =" << charArr[curr_node] << endl;

        // If leftArr and rightArr contain -1, it is a leaf node so we record the code in codes
        if (leftArr[curr_node] == -1 && rightArr[curr_node] == -1) {
            codes[charArr[curr_node] - 'a'] = curr_code;
        } else {
            // Pushes the left node and then the right node into stack, the right will be processed first when we come back around to pop (stack is LIFO)
            stack.push({leftArr[curr_node],curr_code + "0"});
            stack.push({rightArr[curr_node],curr_code + "1"});
        }
    }


}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}