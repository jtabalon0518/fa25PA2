//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()

        // Check if full
        if (size >= 64) return;

        data[size] = idx;
        upheap(size, weightArr);
        size++;


    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()

        if (size == 0) return -1;

        int popped = data[0];
        size--;
        data[0] = data[size];
        downheap(0, weightArr);

        return popped;

    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        // Parent: (i - 1) / 2, children: 2*i + 1, 2*i + 2.
        int parent = (pos - 1) / 2;
        while (pos > 0 && weightArr[data[pos]] < weightArr[data[parent]]) {
            if (weightArr[data[pos]] > weightArr[data[parent]]) {
                // Swapping, not sure if we are allowed helper functions here
                int temp = data[pos];
                data[pos] = data[parent];
                data[parent] = data[temp];


                pos = parent;
                parent = (pos - 1) / 2;
            }
        }

    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (true) {
            int left = pos * 2 + 1;
            int right = pos * 2 + 2;
            int smallest = pos;

            if (left < size && weightArr[data[left]] < weightArr[data[right]]) {
                smallest = left;
            }

            if (right < size && weightArr[data[right]] < weightArr[data[smallest]]) {
                smallest = right;
            }

            if (smallest != pos) {
                int temp = data[smallest];
                data[smallest] = data[pos];
                data[pos] = temp;
                pos = smallest;
            } else {
                break;
            }

        }
    }
};

#endif