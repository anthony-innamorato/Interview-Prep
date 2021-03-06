import random
class Node:
    def __init__(self, data = None, left = None, right = None):
        self.data = data
        self.left = left
        self.right = right

def insert(root, data):
        if data == root.data:
            print("node replicated")
            return
        if data < root.data:
            if root.left == None:
                root.left = Node(data)
            else:
                insert(root.left, data)
        else: #data > root
            if root.right == None:
                root.right = Node(data)
            else:
                insert(root.right, data)

def valInTree(root, data):
    if root is None:
        return False
    if root.data == data:
        return True
    else:
        if valInTree(root.left, data) or valInTree(root.right, data):
            return True
        return False

def bstCount(root):
    if root is None:
        return 0
    else:
        return 1 + bstCount(root.left) + bstCount(root.right)

#a little dumb, improved below
"""def minMax(root):
    if root.left is None and root.right is None:
        return root.data, root.data
    elif root.left is not None and root.right is not None:
        leftMin, leftMax = minMax(root.left)
        rightMin, rightMax = minMax(root.right)
        return min(leftMin, rightMin, root.data), max(leftMax, rightMax, root.data)
    else:
        if root.left is None:
            rightMin, rightMax = minMax(root.right)
            return min(rightMin, root.data), max(rightMax, root.data)
        else:
            leftMin, leftMax = minMax(root.left)
            return min(leftMin, root.data), max(leftMax, root.data)"""

def minMax(root):
    if root.left is None and root.right is None:
        return root.data, root.data
    leftMin, leftMax = float('inf'), float('-inf')
    rightMin, rightMax = float('inf'), float('-inf')
    if root.left is not None:
        leftMin, leftMax = minMax(root.left)
    if root.right is not None:
        rightMin, rightMax = minMax(root.right)
    return min(leftMin, rightMin, root.data), max(leftMax, rightMax, root.data)


def sum(root):
    if root is None:
        return 0
    else:
        return root.data + sum(root.left) + sum(root.right)

def height(root):
    if root is None:
        return 0
    else:
        return 1 + max(height(root.left), height(root.right))

def isBalanced(root):
    if root is None:
        return (True, 0)
    else:
        leftBal = isBalanced(root.left)
        rightBal = isBalanced(root.right)
        if (leftBal[0] == False or rightBal[0] == False):
            return (False, 1 + max(leftBal[1], rightBal[1]))
        else:
            if abs(leftBal[1] - rightBal[1]) > 1:
                return (False,  1 + max(leftBal[1], rightBal[1]))
            else:
                return (True, 1 + max(leftBal[1], rightBal[1]))

def inorder(root):
    if root.left != None:
        yield from inorder(root.left)
    yield root.data
    if root.right != None:
        yield from inorder(root.right)

def preorder(root):
    yield root.data
    if root.left != None:
        yield from preorder(root.left)
    if root.right != None:
        yield from preorder(root.right)

def postorder(root):
    if (root.left != None):
        yield from postorder(root.left)
    if (root.right != None):
        yield from postorder(root.right)
    yield root.data

def printIterator(iter):
    string = ""
    for elem in iter:
        string += str(elem) + " "
    print(string)

def leavesList(root):
    if root is None:
        return []
    else:
        prevLeavesLst = leavesList(root.left) + leavesList(root.right)
        if root.left == None and root.right == None:
            prevLeavesLst.append(root.data)
        return prevLeavesLst

def findNode(root, data):
    if root == None:
        return None
    elif root.data == data:
        return root
    else:
        left = findNode(root.left, data)
        right = findNode(root.right, data)
        if left != None:
            return left
        else:
            return right

#because python does not support by reference passing on of variables,
#to get deleting to work I would have to wrap all nodes on a collection
#in order to modify by reference. Correct implementation is viewable in
#c++ implementation of bst, basic algo is detailed here for convience sake however

#way to get around this would be to store a unique ID to each node
#and store each object in a hash table so match the copie's ID to the object
#in the hash tables ID could lead to directly modyfying the object
"""
def disconnectFromParent(root, node):
    if root == None:
        return
    if root.left == node:
        root.left = None
    elif root.right == node:
        root.right = None
    else:
        disconnectFromParent(root.left, node)
        disconnectFromParent(root.right, node)

def findMaxNode(root):
    if root.right == None:
        return root
    else:
        return findMaxNode(root.right)

def findMinNode(root):
    if root.left == None:
        return root
    else:
        return findMinNode(root.left)

def delNodeFromTree(root, data):
    nodeToBeDeleted = findNode(root, data)
    if nodeToBeDeleted == None:
        return False
    if nodeToBeDeleted.left == None and nodeToBeDeleted.right == None:
        disconnectFromParent(root, nodeToBeDeleted)
        return True
    elif nodeToBeDeleted.left != None:
        maxNode = findMaxNode(nodeToBeDeleted.left)
        nodeToBeDeleted.data, maxNode.data = maxNode.data, nodeToBeDeleted.data
        disconnectFromParent(root, maxNode)
        return True
    else:
        minNode = findMinNode(nodeToBeDeleted.right)
        nodeToBeDeleted.data, minNode.data = minNode.data, nodeToBeDeleted.data
        disconnectFromParent(root, minNode)
        return True

def deleteNode(root, data):
    if delNodeFromTree(root, data):
        print("Node: " + str(data) + " succesfully deleted")
    else:
        print("Node: " + str(data) + " not found in tree")
"""

print("=============EXAMPLE A=============")
a = Node(70)
insert(a, 100)
insert(a, 23)
insert(a, 5)
insert(a, 4)
insert(a, 6)

print("TESTING TREE TRAVERSALS")
print("Inorder")
printIterator(inorder(a))
print("Preorder")
printIterator(preorder(a))
print("Postorder")
printIterator(postorder(a))
print()

print("TESTING VAL IN TREE")
print(valInTree(a, 70))
print(valInTree(a, 100))
print(valInTree(a, 23))
print(valInTree(a, 5))
print(valInTree(a, 4))
print(valInTree(a, 6))
print(valInTree(a, 54))
print()

print("TESTING BSTCOUNT")
print(bstCount(a))
print()

print("TESTING MINMAX")
print(minMax(a))
print()

print("TESTING SUM")
print(sum(a))
print()

print("TESTING HEIGHT")
print(height(a))
print()

print("TESTING ISBALANCED")
print(isBalanced(a)[0])

print("TESTING LEAVES LST")
print(leavesList(a))

for i in range(2):
    print()

print("=============EXAMPLE B=============")
b = Node (50)
lst = [b.data]
totalInLst = 50
for i in range(9):
    num = random.randint(0,100)
    if num not in lst:
        lst.append(num)
        insert(b, num)
        totalInLst += num
print(lst)

print("TESTING TREE TRAVERSALS")
print("Inorder")
printIterator(inorder(b))
print("Preorder")
printIterator(preorder(b))
print("Postorder")
printIterator(postorder(b))
print()

print("TESTING BSTCOUNT")
print(bstCount(b))
print()

print("TESTING MINMAX")
print(minMax(b))
print()

print("TESTING SUM")
print(sum(b), totalInLst)
print()

print("TESTING HEIGHT")
print(height(b))
print()

print("TESTING ISBALANCED")
print(isBalanced(b)[0])

print("TESTING LEAVES LST")
print(leavesList(b))
print()
print()
