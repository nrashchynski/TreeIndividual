#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Node {
public:
	int key;
	Node* left;
	Node* right;
	Node(int k) : key(k), left(nullptr), right(nullptr) {};
};

class Tree {
public:
	Tree() : root(nullptr) {};
	void insert(int key) {
		if (!root) {
			root = new Node(key);
		}
		else {
			insertNode(root, key);
		}
	}

	void TreeTraversal(std::vector<int>& result) {
		leftTraversal(root, result);
	}

	void TreeRightRemove(int key) {
		root = rightRemove(root, key);
	}
	void removeUnbalancedNodes(int key, std::vector<int>& unbalancedNodesKeys) {
		root = removeunbalancedNodes(root, unbalancedNodesKeys);
	}
	void inorderTraversal(std::vector<int>& keys) {
		inOrderLeftTraversal(root, keys);
	}

private:
	Node* root;
	void insertNode(Node* node, int key) {
		if (key < node->key) {
			if (node->left) {
				insertNode(node->left, key);
			}
			else {
				node->left = new Node(key);
			}
		}
		else if (key > node->key) {
			if (node->right) {
				insertNode(node->right, key);
			}
			else {
				node->right = new Node(key);
			}
		}
	}

	int Max(int a, int b) {
		return a > b ? a : b;
	}

	int getHeight(Node* node) {
		if (node == nullptr) {
			return -1;
		}
		int leftHeight = getHeight(node->left);
		int rightHeight = getHeight(node->right);
		return 1 + Max(leftHeight, rightHeight);
	}

	Node* removeunbalancedNodes(Node* node, std::vector<int>& unbalancedNodesKeys) {
		if (node == nullptr) {
			return nullptr;
		}
		int leftHeight = getHeight(node->left);
		int rightHeight = getHeight(node->right);
		if (leftHeight != rightHeight) {
			unbalancedNodesKeys.push_back(node->key);
		}
		node->left = removeunbalancedNodes(node->left, unbalancedNodesKeys);
		node->right = removeunbalancedNodes(node->right, unbalancedNodesKeys);

		return node;
	}

	// Прямой левый обход
	void leftTraversal(Node* node, std::vector<int>& result) {
		if (node) {
			result.push_back(node->key);
			leftTraversal(node->left, result);
			leftTraversal(node->right, result);
		}
	}

	// Внутренний левый обход
	void inOrderLeftTraversal(Node* node, std::vector<int>& keys) {
		if (node != nullptr) {
			inOrderLeftTraversal(node->left, keys);
			keys.push_back(node->key);
			inOrderLeftTraversal(node->right, keys);
		}
	}

	Node* rightRemove(Node* node, int key) {
		if (!node) {
			return nullptr;
		}
		else if (key < node->key) {
			node->left = rightRemove(node->left, key);
		}
		else if (key > node->key) {
			node->right = rightRemove(node->right, key);
		}
		else {
			if (!node->left) {
				Node* rightChild = node->right;
				delete node;
				return rightChild;
			}
			else if (!node->right) {
				Node* leftChild = node->left;
				delete node;
				return leftChild;
			}
			else {
				Node* minInRight = findMin(node->right);
				node->key = minInRight->key;
				node->right = rightRemove(node->right, minInRight->key);
			}
		}
		return node;
	}

	Node* findMin(Node* node) {
		while (node && node->left) {
			node = node->left;
		}
		return node;
	}
};

int main() {
	std::ifstream fin("in.txt");
	std::ofstream fout("out.txt");
	int key;
	int x;
	fin >> x;
	//std::cin >> x;
	Tree tree;
	std::vector<int>result;
	std::vector<Node*>unbalancedNodes;
	std::vector<int>unbalancedNodesKeys;
	tree.insert(x);

	while (fin >> key) {
		tree.insert(key);
	}
	/*for (int i = 0; i < 8; ++i) {
		std::cin >> key;
		tree.insert(key);
	}*/

	tree.removeUnbalancedNodes(x, unbalancedNodesKeys);
	std::sort(unbalancedNodesKeys.begin(), unbalancedNodesKeys.end());
	

	/*std::cout << std::endl << std::endl;
	for (int unk : unbalancedNodesKeys) {
		std::cout << unk << " ";
	}*/
	
	int n = unbalancedNodesKeys.size();

	/*for (int i = 0; i < n; ++i) {
		std::cout << unbalancedNodesKeys[i] << " ";
	}
	std::cout << std::endl;*/


	if (n % 2 == 0) {
		tree.TreeTraversal(result);
	}
	else {
		tree.TreeRightRemove(unbalancedNodesKeys[n / 2]);
		tree.TreeTraversal(result);	
	}


    std::cout << std::endl << std::endl << std::endl;
	for (int r : result) {
		fout << r << std::endl;
		//std::cout << r << std::endl;
	}
}