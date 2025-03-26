class Node :
    def __init__(self,data):
        self.data = data
        self.left = None
        self.right = None

class BinaryTree :
    def __init__(self):
        self.root = None   
    
    def insert(self,data):
        self.root = self.insertHelper(self.root,data)
    
    def insertHelper(self,root,data):
        if root is None :
            return Node(data)
        if data < root.data :
            root.left = self.insertHelper(root.left,data)
        else:
            root.right = self.insertHelper(root.right,data)

        return root

    def display(self):
        self.displayHelper(self.root)
        print()

    def displayHelper(self,root):
        if root :
            self.displayHelper(root.left)
            print(root.data,end=" ")
            self.displayHelper(root.right)
    def search(self,data):
        return self.searchHelper(self.root,data)

    def searchHelper(self,root,data):
        if root is None :
            return False
        if root.data == data :
            return True
        if data < root.data:
            return self.searchHelper(root.left, data)
        else:
            return self.searchHelper(root.right, data)
    
    def remove(self,data):
        if self.search(data):
            self.root = self.removeHelper(self.root,data)
        else :
            print("Couldn't find the data.")

    def removeHelper(self,root,data):
        if root is None :
            return root
        if data < root.data :
            root.left = self.removeHelper(root.left,data)
        elif data > root.data :
            root.right = self.removeHelper(root.right,data)
        else :
            if root.left is None and root.right is None :
                return None
            elif root.right is not None :
                root.data = self.successor(root)
                root.right = self.removeHelper(root.right,root.data)
            else :
                root.data = self.predecessor(root)
                root.left = self.removeHelper(root.left,root.data)
        return root
    
    def successor(self,root) :
        root = root.right
        while(root.left is not None) :
            root = root.left
        return root.data
    
    def predecessor(self,root):
        root = root.left
        while root.right is not None :
            root = root.right
        return root.data
    
if __name__ == "__main__" :
    tree = BinaryTree()
    for value in [5,1,9,2,7,3,6,4,8] :
        tree.insert(value)
    
    tree.remove(4)
    tree.display()
    print(tree.search(4))

    
