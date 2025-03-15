#include <iostream>

class Node {
public:
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class LinkedList {
public:
    Node* head;

    LinkedList() {
        head = nullptr;
    }

    // Insert a new node at the end
    void insert(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Delete a specific node (O(n))
    void deleteNode(Node* nodeToDelete) {
        if (!head || !nodeToDelete) return;

        // If the node to be deleted is the head
        if (head == nodeToDelete) {
            head = head->next;
            delete nodeToDelete;
            return;
        }

        Node* prev = head;
        while (prev->next && prev->next != nodeToDelete) {
            prev = prev->next;
        }

        if (prev->next) {
            prev->next = nodeToDelete->next;
            delete nodeToDelete;
        }
    }

    // Print the list
    void printList() {
        Node* temp = head;
        while (temp) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "NULL\n";
    }
};

int main() {
    LinkedList list;

    // Insert elements
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);

    std::cout << "Original List: ";
    list.printList();

    // Delete a specific node
    list.deleteNode(list.head->next->next);  // Delete node with value 3

    std::cout << "After Deletion: ";
    list.printList();

    return 0;
}
