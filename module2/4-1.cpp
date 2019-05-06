/*
* Использование АВЛ-дерева
* Солдаты. В одной военной части решили построить в одну шеренгу по росту. 
* Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, 
* а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. 
* Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, 
* а в конце – самые низкие. За расстановку солдат отвечал прапорщик, 
* который заметил интересную особенность – все солдаты в части разного роста. 
* Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, 
* а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится. 
* Требуемая скорость выполнения команды - O(log n).
* Формат входных данных.
* Первая строка содержит число N – количество команд (1 ≤ N ≤ 30 000). 
* В каждой следующей строке содержится описание команды: число 1 и X если солдат приходит в строй 
* (X – рост солдата, натуральное число до 100 000 включительно) и число 2 и Y если солдата, 
* стоящим в строе на месте Y надо удалить из строя. Солдаты в строе нумеруются с нуля.
* Формат выходных данных.
* На каждую команду 1 (добавление в строй) вы должны выводить число K – номер позиции, 
* на которую должен встать этот солдат (все стоящие за ним двигаются назад).
*/

#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>

struct AVLNode {
    size_t key;
	size_t height;
	size_t nodes;
    AVLNode *left;
	AVLNode *right;

	AVLNode(int _key) : key(_key), height(1), nodes(1), left(0), right(0) {}
	~AVLNode() {
		delete left;
		delete right;
	}
};

class AVLTree {
public:
	AVLTree() : root(NULL) {}
	~AVLTree() { delete root; }
	void Insert(size_t key, size_t &position) {
		root = InternalInsert(root, key, position);
	}
	void Remove(int position) {
		root = InternalRemove(root, position);
	}
private:
	AVLNode* root;
	size_t Height(AVLNode *node);
	size_t Nodes(AVLNode *node);
	int BalanceFactor(AVLNode *node);
	void FixHeight(AVLNode *node);
	void FixNodes(AVLNode *node);
	AVLNode* Rotateright(AVLNode *p);
	AVLNode* Rotateleft(AVLNode *p);
	AVLNode* Balance(AVLNode *p);
	AVLNode* FindMin(AVLNode *p);
	AVLNode* RemoveMin(AVLNode *p);
	AVLNode* InternalInsert(AVLNode *p, size_t key, size_t &position);
	AVLNode* InternalRemove(AVLNode *p, size_t position);
};

size_t AVLTree::Height(AVLNode *node) {
	return (node == NULL) ? 0 : node->height;
}

size_t AVLTree::Nodes(AVLNode *node) {
	return (node == NULL) ? 0 : node->nodes;
}

int AVLTree::BalanceFactor(AVLNode *node) {
	return Height(node->right) - Height(node->left);
}

void AVLTree::FixHeight(AVLNode *node) {
	int HL = Height(node->left);
	int HR = Height(node->right);

	node->height = (HL > HR) ? HL + 1 : HR + 1;
}

void AVLTree::FixNodes(AVLNode *node) {
	int nodes_left = Nodes(node->left);
	int nodes_right = Nodes(node->right);

	node->nodes = nodes_left + nodes_right + 1;
}

AVLNode* AVLTree::Rotateright(AVLNode *p) {
	AVLNode *new_node = p->left;

	p->left = new_node->right;
	new_node->right = p;

	FixNodes(p);
	FixNodes(new_node);

	FixHeight(p);
	FixHeight(new_node);

	return new_node;
}

AVLNode* AVLTree::Rotateleft(AVLNode *p) {
	AVLNode *new_node = p->right;

	p->right = new_node->left;
	new_node->left = p;

	FixNodes(p);
	FixNodes(new_node);

	FixHeight(p);
	FixHeight(new_node);

	return new_node;
}

AVLNode* AVLTree::Balance(AVLNode *p) {
	FixHeight(p);

	if (BalanceFactor(p) == -2) {
		if (BalanceFactor(p->left) > 0) {
			p->left = Rotateleft(p->left);
		}

		return Rotateright(p);
	} else if (BalanceFactor(p) == 2) {
		if (BalanceFactor(p->right) < 0) {
			p->right = Rotateright(p->right);
		}

		return Rotateleft(p);
	}

	return p;
}

AVLNode* AVLTree::InternalInsert(AVLNode *p, size_t key, size_t &position) {
    if (p == NULL) {
		return new AVLNode(key);
    }

    ++(p->nodes);

    if (key < p->key) {
    	position += Nodes(p->right) + 1;
    	p->left = InternalInsert(p->left, key, position);
    } else {
        p->right = InternalInsert(p->right, key, position);
    }

    return Balance(p);
}

AVLNode* AVLTree::FindMin(AVLNode *p) {
    return (p->left == NULL) ? p : FindMin(p->left);
}

AVLNode* AVLTree::RemoveMin(AVLNode *p) {
    if (p->left == NULL) {
        return p->right;
    }

    p->left = RemoveMin(p->left);
    --p->nodes;

    return Balance(p);
}

AVLNode* AVLTree::InternalRemove(AVLNode *p, size_t position) {
    if (p == NULL) return NULL;
    if (position >= p->nodes) return p;

    int current = 0;
	std::stack<AVLNode *> nodes;

    while (true) {
		size_t nodes_right = Nodes(p->right);

		if (position - current > nodes_right) {
			nodes.push(p);
			p = p->left;
			current += nodes_right + 1;
		} else if (position - current < nodes_right) {
			if (p->right != NULL) {
				nodes.push(p);
				p = p->right;
			} else {
				break;
			}
		} else {
			AVLNode *left = p->left;
			AVLNode *right = p->right;
			size_t key = p->key;

			if (right == NULL) {
				if (left == NULL) {
					if (!nodes.empty()) {
						p = nodes.top();
						nodes.pop();

						if (p->key > key) {
							p->left = NULL;
						} else {
							p->right = NULL;
						}

						--p->nodes;
					} else {
						return NULL;
					}
				} else {
					p = left;
				}
			} else {
				AVLNode* min = FindMin(right);
				min->right = RemoveMin(right);
				min->left = left;
				FixNodes(min);
				p = Balance(min);
			}

			break;
		}
	}

	while (!nodes.empty()) {
		AVLNode *node = nodes.top();
		--node->nodes;

		if (node->key > p->key) {
			node->left = p;
		} else {
			node->right = p;
		}

		p = Balance(node);
		nodes.pop();
	}

    return p;
}

int main() {
	size_t n;

	std::cin >> n;

	AVLTree avlTree;
	std::vector<int> result;

	size_t type, value, position;

	for (int i = 0; i < n; ++i) {
		std::cin >> type;

		if (type == 1) {
			position = 0;

			std::cin >> value;

			avlTree.Insert(value, position);
			result.push_back(position);
		} else if (type == 2) {
			std::cin >> value;
			avlTree.Remove(value);
		}
	}

	for (size_t i = 0; i < result.size(); ++i) {
		std::cout << result[i] << std::endl;
	}

	return 0;
}
