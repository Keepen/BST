#include <iostream>
using namespace std;

//二叉搜索树：左孩子<根节点<右孩子

//创建结点
template <class T>
struct BSNode {
	T _data;
	BSNode<T>* _left;
	BSNode<T>* _right;
	//构造函数
	BSNode(const T& data)
		:_data(data),
		_left(nullptr),
		_right(nullptr)
	{}
};


template <class T>
class BSTree {
public:
	typedef BSNode<T> Node;
	typedef BSNode<T>* pNode;
	 
	//构造函数
	BSTree(): _root(nullptr)
	{}

	//拷贝构造
	BSTree(const BSTree& bst) {
		_root = Copy(bst._root);
	}
	pNode Copy(pNode root) {
		if (root == nullptr) {
			return nullptr;
		}
		pNode newRoot = new Node(root->_data);
		newRoot->_left = Copy(root->_left);
		newRoot->_right = Copy(root->_right);
		return newRoot;
	}

	//赋值运算符重载
	BSTree<T>& operator=(const BSTree& bst) {
		//先判断是否是自己拷贝给自己
		if (this == &bst) {
			return *this;
		}
		//不是自己拷贝自己，判断原来的bst中是否为空
		//不为空，则进行释放
		if (bst._root != nullptr) {
			//释放空间
			destroy(bst._root);
		}
		//释放完空间或者本来就是空的，进行拷贝
		_root = Copy(bst._root);
		return *this;
	}


	//插入结点
	bool Insert(const T& data) {
		//先判断是否是空树
		if (_root == nullptr) {
			_root = new Node(data);
			return true;
		}
		//非空，找到合适的位置
		pNode cur = _root;
		pNode parent = nullptr;
		while (cur) {
			//如果当前结点就是目标结点，则跳出循环，二叉搜索树中补存在重复的结点
			if (cur->_data == data) {
				break;
				return false;
			}
			parent = cur;
			if (cur->_data > data) {
				cur = cur->_left;
			}
			else {
				cur = cur->_right;
			}
		}
		//此时已找到合适的位置
		if (parent->_data > data) {
			parent->_left = new Node(data);
			return true;
		}
		else {
			parent->_right = new Node(data);
			return true;
		}
	}

	//删除结点
	bool Erase(const T& data) {
		//先判断树是否为空
		if (_root == nullptr) {
			return false;
		}
		//开始遍历找节点,树中是否存在该节点
		pNode cur = _root;
		pNode parent = nullptr;
		while (cur) {		
			if (cur->_data == data) {
				break;
			}
			parent = cur;
			if (cur->_data > data) {
				cur = cur->_left;
			}
			else {
				cur = cur->_right;
			}
		}
		//cur为空，表示该树中不存在该节点
		if (cur == nullptr) {
			return false;
		}
		
		//该节点存在
		//1.叶子结点
		if (cur->_left == nullptr&&cur->_right == nullptr) {
			//不是根节点
			if (cur != _root) {
				if (parent->_left == cur) {
					parent->_left = nullptr;
				}
				else {
					parent->_right = nullptr;
				}
				delete cur;
				cur = nullptr;
			}
			//是根节点
			else {
				delete cur;
				cur = nullptr;
				_root = nullptr;
			}
		}
		//2.有左孩子没有右孩子
		else if (cur->_right == nullptr) {
			//不是根节点
			if (cur != _root) {
				if (parent->_left == cur) {
					parent->_left = cur->_left;
				}
				else {
					parent->_right = cur->_left;
				}
				delete cur;
				cur = nullptr;
			}
			//是根节点
			else {
				_root = cur->_left;
				delete cur;
				cur = nullptr;
			}
		}
		//3.有右孩子没有左孩子
		else if (cur->_right == nullptr) {
			//非根节点
			if (cur != _root) {
				if (parent->_left = cur) {
					parent->_left = cur->_right;
				}
				else {
					parent->_right = cur->_right;
				}
				delete cur;
				cur = nullptr;
			}
			//为根节点
			else {
				_root = cur->_right;
				delete cur;
				cur = nullptr;
			}
		}
		//4.左右孩子均有
		else {
			//找其左孩子的最右结点,即左子树中的最大数
			parent = cur;
			pNode next = cur->_left;
			while (next->_right) {
				parent = next;
				next = next->_right;
			}
			cur->_data = next->_data;
			if (parent->_left = next) {
				parent->_left = next->_left;
			}
			else {
				parent->_right = next->_left;
			}
			delete next;
			next = nullptr;
		}
		return true;
	}


	//中序遍历
	void InOrder(pNode root) {
		if (root == nullptr) {
			return;
		}
		InOrder(root->_left);
		cout << root->_data << " ";
		InOrder(root->_right);
	}
	void _InOrder() {
		InOrder(_root);
		cout << endl;
	}
	
	//按照后序来释放
	void destroy(pNode root) {
		if (root == nullptr) {
			return;
		}
		destroy(root->_left);
		destroy(root->_right);
	}
	//析构函数
	~BSTree(){
		destroy(_root);	
	}
private:
	pNode _root;
};

void test1() {
	BSTree<int> bst;
	bst.Insert(10);
	bst.Insert(0);
	bst.Insert(15);
	bst.Insert(13);
	bst._InOrder();
	//bst.Erase(0);
	//bst._InOrder();
	bst.Erase(13); 
	bst._InOrder();

	BSTree<int> bst2 = bst;
	bst2._InOrder();
	//bst.~BSTree();
	bst._InOrder();

	bst2 = bst;
	cout << "赋值运算符重载" << endl;
	bst2._InOrder();
}


int main() {
	test1();
	system("pause");
	return 0;
}