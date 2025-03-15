#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

void traverseAndPrint(Node* head) {
    Node* current = head;
    while (current) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "null" << endl;
}

void deleteNodeByValue(Node*& head, int value) {
    if (!head) return;
    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }
    Node* current = head;
    while (current->next && current->next->data != value) {
        current = current->next;
    }
    if (!current->next) return;
    Node* temp = current->next;
    current->next = current->next->next;
    delete temp;
}

void deleteNodeByPosition(Node*& head, int position) {
    if (!head || position < 1) return;
    Node* temp = head;
    if (position == 1) {
        head = head->next;
        delete temp;
        return;
    }
    Node* prev = head;
    for (int i = 1; i < position - 1; i++) {
        if (!prev->next) return;
        prev = prev->next;
    }
    if (!prev->next) return;
    temp = prev->next;
    prev->next = temp->next;
    delete temp;
}

int main() {
    Node* head = new Node(7);
    head->next = new Node(3);
    head->next->next = new Node(2);
    head->next->next->next = new Node(9);

    cout << "Original List: " << endl;
    traverseAndPrint(head);

    deleteNodeByValue(head, 3);
    cout << "After deleting value 3: " << endl;
    traverseAndPrint(head);

    deleteNodeByPosition(head, 2);
    cout << "After deleting node at position 2: " << endl;
    traverseAndPrint(head);

    return 0;
}
