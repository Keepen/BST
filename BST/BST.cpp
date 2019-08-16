#include <iostream>
using namespace std;

//����������������<���ڵ�<�Һ���

//�������
template <class T>
struct BSNode {
	T _data;
	BSNode<T>* _left;
	BSNode<T>* _right;
	//���캯��
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
	 
	//���캯��
	BSTree(): _root(nullptr)
	{}

	//��������
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

	//��ֵ���������
	BSTree<T>& operator=(const BSTree& bst) {
		//���ж��Ƿ����Լ��������Լ�
		if (this == &bst) {
			return *this;
		}
		//�����Լ������Լ����ж�ԭ����bst���Ƿ�Ϊ��
		//��Ϊ�գ�������ͷ�
		if (bst._root != nullptr) {
			//�ͷſռ�
			destroy(bst._root);
		}
		//�ͷ���ռ���߱������ǿյģ����п���
		_root = Copy(bst._root);
		return *this;
	}


	//������
	bool Insert(const T& data) {
		//���ж��Ƿ��ǿ���
		if (_root == nullptr) {
			_root = new Node(data);
			return true;
		}
		//�ǿգ��ҵ����ʵ�λ��
		pNode cur = _root;
		pNode parent = nullptr;
		while (cur) {
			//�����ǰ������Ŀ���㣬������ѭ���������������в������ظ��Ľ��
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
		//��ʱ���ҵ����ʵ�λ��
		if (parent->_data > data) {
			parent->_left = new Node(data);
			return true;
		}
		else {
			parent->_right = new Node(data);
			return true;
		}
	}

	//ɾ�����
	bool Erase(const T& data) {
		//���ж����Ƿ�Ϊ��
		if (_root == nullptr) {
			return false;
		}
		//��ʼ�����ҽڵ�,�����Ƿ���ڸýڵ�
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
		//curΪ�գ���ʾ�����в����ڸýڵ�
		if (cur == nullptr) {
			return false;
		}
		
		//�ýڵ����
		//1.Ҷ�ӽ��
		if (cur->_left == nullptr&&cur->_right == nullptr) {
			//���Ǹ��ڵ�
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
			//�Ǹ��ڵ�
			else {
				delete cur;
				cur = nullptr;
				_root = nullptr;
			}
		}
		//2.������û���Һ���
		else if (cur->_right == nullptr) {
			//���Ǹ��ڵ�
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
			//�Ǹ��ڵ�
			else {
				_root = cur->_left;
				delete cur;
				cur = nullptr;
			}
		}
		//3.���Һ���û������
		else if (cur->_right == nullptr) {
			//�Ǹ��ڵ�
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
			//Ϊ���ڵ�
			else {
				_root = cur->_right;
				delete cur;
				cur = nullptr;
			}
		}
		//4.���Һ��Ӿ���
		else {
			//�������ӵ����ҽ��,���������е������
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


	//�������
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
	
	//���պ������ͷ�
	void destroy(pNode root) {
		if (root == nullptr) {
			return;
		}
		destroy(root->_left);
		destroy(root->_right);
	}
	//��������
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
	cout << "��ֵ���������" << endl;
	bst2._InOrder();
}


int main() {
	test1();
	system("pause");
	return 0;
}