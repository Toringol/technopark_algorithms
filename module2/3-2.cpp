/*
* Дано число N < 106 и последовательность пар целых чисел из [-231..231] длиной N.
* Построить декартово дерево из N узлов, характеризующихся парами чисел {Xi, Yi}.
* Каждая пара чисел {Xi, Yi} определяет ключ Xi и приоритет Yi в декартовом дереве.
* Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
* При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом. 
* Затем разбейте найденное поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x, а во втором больше или равны x. 
* Получившиеся два дерева сделайте дочерними для нового узла (x, y). Новый узел вставьте на место узла P.
* Построить также наивное дерево поиска по ключам Xi методом из задачи 2.
* Вычислить количество узлов в самом широком слое декартового дерева и количество узлов в самом широком слое наивного дерева поиска. 
* Вывести их разницу. Разница может быть отрицательна.
*/

#include <iostream>
#include <queue>

struct TreeNode {
	int data;
	int priority;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int _data, int _priority = 0) : data(_data), priority(_priority), left(NULL), right(NULL) {}
	~TreeNode() {
		delete left;
		delete right;
	}
};

class NaiveBinaryTree {
public:
	NaiveBinaryTree() : root(NULL) {}
	~NaiveBinaryTree() { delete root; }
	void Insert(int value);
	int countMaxWidth();

private:
	TreeNode* root;
};

void NaiveBinaryTree::Insert(int value) {
	TreeNode* newNode = new TreeNode(value);

	if (root == NULL) {
		root = newNode;
		return;
	}

	TreeNode* nextNode = root;
	while (true) {
		if (value < nextNode->data) {
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

int NaiveBinaryTree::countMaxWidth() {
	int maxWidth = 0, currentWidth = 0;
	
	std::queue<TreeNode*> layerNodes;
	TreeNode *current = NULL;
	layerNodes.push(root);

	while (!layerNodes.empty()) {
		if ((currentWidth = layerNodes.size()) > maxWidth) {
			maxWidth = currentWidth;
		}

		for (size_t i = 0; i < currentWidth; i++) {
			current = layerNodes.front();
			if (current->left != NULL) {
				layerNodes.push(current->left);
			}
			if (current->right != NULL) {
				layerNodes.push(current->right);
			}
			layerNodes.pop();
		}
	}

	return maxWidth;
}

class TreapTree {
public:
	TreapTree() : root(NULL) {}
	~TreapTree() { delete root; }
	void split(TreeNode* currentNode, int data, TreeNode *&left, TreeNode *&right);
	void Insert(int value, int priority);
	int countMaxWidth();
private:
	TreeNode* root;
};

void TreapTree::split(TreeNode* currentNode, int data, TreeNode *&left, TreeNode *&right) {
	if (currentNode == 0) {
		left = 0;
		right = 0;
	}
	else if (currentNode->data <= data) {
		split(currentNode->right, data, currentNode->right, right);
		left = currentNode;
	}
	else {
		split(currentNode->left, data, left, currentNode->left);
		right = currentNode;
	}
}

void TreapTree::Insert(int value, int priority) {
	TreeNode *newNode = new TreeNode(value, priority),
		*currentNode = root, *prevNode = root;
	
	if (currentNode == NULL) {
		root = newNode;
		return;
	}

	while (currentNode != NULL && priority <= currentNode->priority) {
		prevNode = currentNode;
		if (value <= currentNode->data) {
			currentNode = currentNode->left;
		}
		else {
			currentNode = currentNode->right;
		}
	}

	split(currentNode, value, newNode->left, newNode->right);

	if (currentNode == root) {
		root = newNode;
	}
	else if (value <= prevNode->data) {
		prevNode->left = newNode;
	}
	else {
		prevNode->right = newNode;
	}
}

int TreapTree::countMaxWidth() {
	int maxWidth = 0,
		curWidth = 0;

	std::queue<TreeNode*> layerNodes;
	TreeNode* cur = NULL;
	layerNodes.push(root);

	while (!layerNodes.empty()) {
		if ((curWidth = layerNodes.size()) > maxWidth) {
			maxWidth = curWidth;
		}

		for (size_t i = 0; i < curWidth; i++) {
			cur = layerNodes.front();
			if (cur->left != NULL) {
				layerNodes.push(cur->left);
			}
			if (cur->right != NULL) {
				layerNodes.push(cur->right);
			}
			layerNodes.pop();
		}
	}

	return maxWidth;
}

int main() {
	NaiveBinaryTree naiveBinaryTree;
	TreapTree treapTree;

	int numberOfNodes = 0;
	std::cin >> numberOfNodes;

	int data = 0;
	int priority = 0;

	for (int i = 0; i < numberOfNodes; i++) {
		if (std::cin >> data >> priority) {
			naiveBinaryTree.Insert(data);
			treapTree.Insert(data, priority);
		}
	}

	std::cout << (treapTree.countMaxWidth() - naiveBinaryTree.countMaxWidth());

	return 0;
}
