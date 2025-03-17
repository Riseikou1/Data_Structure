class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

class BinaryTree:
    def __init__(self):
        self.root = None

    def insert(self, data):
        self.root = self._insert_helper(self.root, data)

    def _insert_helper(self, root, data):
        if root is None:
            return Node(data)
        if data < root.data:
            root.left = self._insert_helper(root.left, data)
        else:
            root.right = self._insert_helper(root.right, data)
        return root

    def display(self):
        self._display_helper(self.root)
        print()

    def _display_helper(self, root):
        if root:
            self._display_helper(root.left)
            print(root.data, end=" ")
            self._display_helper(root.right)

    def search(self, data):
        return self._search_helper(self.root, data)

    def _search_helper(self, root, data):
        if root is None:
            return False
        if root.data == data:
            return True
        return self._search_helper(root.left, data) if data < root.data else self._search_helper(root.right, data)

    def remove(self, data):
        if self.search(data):
            self.root = self._remove_helper(self.root, data)
        else:
            print("Couldn't find the data.")

    def _remove_helper(self, root, data):
        if root is None:
            return root
        if data < root.data:
            root.left = self._remove_helper(root.left, data)
        elif data > root.data:
            root.right = self._remove_helper(root.right, data)
        else:
            if root.left is None and root.right is None:
                return None
            elif root.right is not None:
                root.data = self._successor(root)
                root.right = self._remove_helper(root.right, root.data)
            else:
                root.data = self._predecessor(root)
                root.left = self._remove_helper(root.left, root.data)
        return root

    def _successor(self, root):
        root = root.right
        while root.left is not None:
            root = root.left
        return root.data

    def _predecessor(self, root):
        root = root.left
        while root.right is not None:
            root = root.right
        return root.data


if __name__ == "__main__":
    tree = BinaryTree()
    for value in [5, 1, 9, 2, 7, 3, 6, 4, 8]:
        tree.insert(value)

    tree.remove(4)
    tree.display()
    print(tree.search(4))
