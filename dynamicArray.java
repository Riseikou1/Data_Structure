class TreeNode:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
        self.height = 1

class AVLTree:
    def getHeight(self, node):
        return node.height if node else 0

    def getBalance(self, node):
        return self.getHeight(node.left) - self.getHeight(node.right) if node else 0

    def rightRotate(self, y):
        x = y.left
        T2 = x.right

        x.right = y
        y.left = T2

        y.height = 1 + max(self.getHeight(y.left), self.getHeight(y.right))
        x.height = 1 + max(self.getHeight(x.left), self.getHeight(x.right))

        return x

    def leftRotate(self, x):
        y = x.right
        T2 = y.left

        y.left = x
        x.right = T2

        x.height = 1 + max(self.getHeight(x.left), self.getHeight(x.right))
        y.height = 1 + max(self.getHeight(y.left), self.getHeight(y.right))

        return y

    def insert(self, node, data):
        if not node:
            return TreeNode(data)

        if data < node.data:
            node.left = self.insert(node.left, data)
        elif data > node.data:
            node.right = self.insert(node.right, data)
        else:
            return node  # Duplicate keys not allowed

        node.height = 1 + max(self.getHeight(node.left), self.getHeight(node.right))
        return self.balance(node)

    def minValueNode(self, node):
        while node.left:
            node = node.left
        return node

    def delete(self, node, data):
        if not node:
            return node

        if data < node.data:
            node.left = self.delete(node.left, data)
        elif data > node.data:
            node.right = self.delete(node.right, data)
        else:
            if not node.left:
                return node.right
            elif not node.right:
                return node.left

            temp = self.minValueNode(node.right)
            node.data = temp.data
            node.right = self.delete(node.right, temp.data)

        node.height = 1 + max(self.getHeight(node.left), self.getHeight(node.right))
        return self.balance(node)

    def balance(self, node):
        balance = self.getBalance(node)

        if balance > 1:
            if self.getBalance(node.left) < 0:
                node.left = self.leftRotate(node.left)
            return self.rightRotate(node)
        
        if balance < -1:
            if self.getBalance(node.right) > 0:
                node.right = self.rightRotate(node.right)
            return self.leftRotate(node)

        return node

    def inOrderTraversal(self, node):
        if node:
            self.inOrderTraversal(node.left)
            print(node.data, end=" ")
            self.inOrderTraversal(node.right)

# Example usage
tree = AVLTree()
root = None

for num in [10, 20, 30, 40, 50, 25]:
    root = tree.insert(root, num)

tree.inOrderTraversal(root)  # Output: 10 20 25 30 40 50
