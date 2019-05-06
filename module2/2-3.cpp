/*
* Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
* Требуется построить бинарное дерево, заданное наивным порядком вставки.
* Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, 
* то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
* Рекурсия запрещена.
* 
* Выведите элементы в порядке post-order (снизу вверх).
*/

#include <iostream>
#include <stack>

#define MAX_SIZE 100

struct BinaryTreeNode {
	int Data;
	BinaryTreeNode* left;
	BinaryTreeNode* right;

	BinaryTreeNode(int d) : Data(d), left(0), right(0) {}
	~BinaryTreeNode() {
		delete left;
		delete right;
	}
};

class BinaryTree {
public:
	BinaryTree() : root(0) {}
	~BinaryTree() { delete root; }
	void Insert(int value);
	void postOrderIterative() {
		postOrderIterative(root);
	}

private:
	BinaryTreeNode* root; 
	void postOrderIterative(BinaryTreeNode* root);
};
  
class Stack {
public:
	int size;
	int top;
	BinaryTreeNode** array;
};

BinaryTreeNode* newNode(int data)
{
	BinaryTreeNode* node = new BinaryTreeNode(0);
	node->Data = data;
	node->left = node->right = NULL;
	return node;
}
 
Stack* createStack(int size) {
	Stack* stack = new Stack();
	stack->size = size;
	stack->top = -1;
	stack->array = new BinaryTreeNode*[(stack->size * sizeof(BinaryTreeNode*))];
	return stack;
}
 
int isFull(Stack* stack) {
	return stack->top - 1 == stack->size;
}

int isEmpty(Stack* stack) {
	return stack->top == -1;
}

void push(Stack* stack, BinaryTreeNode* node) {
	if (isFull(stack))
		return;
	stack->array[++stack->top] = node;
}

BinaryTreeNode* pop(Stack* stack) {
	if (isEmpty(stack))
		return NULL;
	return stack->array[stack->top--];
}

void BinaryTree::Insert(int value) {
	BinaryTreeNode* newNode = new BinaryTreeNode(value);

	if (root == 0) {
		root = newNode;
		return;
	}

	BinaryTreeNode* nextNode = root;
	while (true) {
		if (value < nextNode->Data) {
			if (nextNode->left != 0) {
				nextNode = nextNode->left;
			}
			else {
				nextNode->left = newNode;
				return;
			}
		}
		else {
			if (nextNode->right != 0) {
				nextNode = nextNode->right;
			}
			else {
				nextNode->right = newNode;
				return;
			}
		}
	}
}

void BinaryTree::postOrderIterative(BinaryTreeNode* root) {
	if (root == NULL)
		return;

	std::stack<BinaryTreeNode*> stack;

	do {
		while (root) {
			if (root->right)
				stack.push(root->right);
			stack.push(root);
			root = root->right;
		}
		root = stack.top();
		stack.pop();
		if (root->right && stack.top() == root->right) {
			stack.pop();
			stack.push(root);
			root = root->right;
		}
		else {
			std::cout << root->Data << " ";
			root = NULL;
		} 
	} while (!stack.empty());
}

int main() {
	size_t elementsNumber = 0;
	
	std::cin >> elementsNumber;
	if (elementsNumber == 0) {
		return 1;
	}

	BinaryTree tree;

	for (size_t i = 0; i < elementsNumber; i++) {
		int data = 0;
		std::cin >> data;
		tree.Insert(data);
	}

	tree.postOrderIterative();

	return 0;
}
