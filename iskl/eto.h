#pragma once
#include <iterator>
#include <queue>
#include <iostream>
#include <exception>
#include <stack>

template <typename T>

class Tree {
	class TreeElement {
	public:
		T value;
		TreeElement* right;
		TreeElement* left;

		TreeElement(T const& a) : value(a), right(nullptr), left(nullptr){}
		~TreeElement() = default;
	};
	
	class DFSIterator : std::iterator<std::forward_iterator_tag, T>
	{
        std::stack<TreeElement*> st;
    public:
        DFSIterator(TreeElement* first) : st() {
            st.push(first);
        };
        DFSIterator(DFSIterator const& other) : st(other.st) {}
        ~DFSIterator() = default;
        bool operator==(DFSIterator const& other) {
            return st.top() == other.st.top();
        }
        bool operator!=(DFSIterator const& other) {
            return !(*this == other);
        }
        DFSIterator& operator++() {
            TreeElement* i = st.top();
            st.pop();
            if (st.empty() && i->left == nullptr && i->right == nullptr) {
                st.push(nullptr);
            }
            else if (i->left != nullptr && i->right != nullptr) {
                st.push(i->left);
                st.push(i->right);
            }
            else if(i->left != nullptr){
                st.push(i->left);
            }
            else if (i->right != nullptr) {
                st.push(i->right);
            }

            return *this;
        }
        T const & operator*() const {
            return st.top()->value;
        }
        T const * operator->() const {
            return &st.top()->value;
        }
	};

	TreeElement* root;
public:
	using iterator = DFSIterator;
	Tree() : root(nullptr){}
	~Tree()
	{

	}

    void add(T key) {
        if (root == nullptr) {
            root = new TreeElement(key);
        }
        else {
            TreeElement* cur = root;
            while (cur != nullptr) {
                if (key < cur->value) {
                    if (cur->left == nullptr) {
                        cur->left = new TreeElement(key);
                        break;
                    }
                    else {
                        cur = cur->left;
                    }
                }
                else if (key > cur->value) {
                    if (cur->right == nullptr) {
                        cur->right = new TreeElement(key);
                        break;
                    }
                    else {
                        cur = cur->right;
                    }
                }
                else {
                    throw std::logic_error("”же есть такое");
                }
            }
        }
    };
    void print() {
        std::queue<TreeElement*> q;
        q.push(root);
        while (!q.empty()) {
            TreeElement* cur = q.front();
            q.pop();
            if (cur != nullptr) {
                q.push(cur->left);
                q.push(cur->right);
                std::cout << cur->value << "\n";
            }
        }
    };

    iterator begin() const {
        return iterator(root);
    }
    iterator end() const {
        return iterator(nullptr);
    }
};