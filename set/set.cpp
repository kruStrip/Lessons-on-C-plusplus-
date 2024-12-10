#include <iostream>
#include <queue>


struct SetElement {
    int value;
    SetElement* left;
    SetElement* right;
    SetElement(int v) {
        value = v;
        left = nullptr;
        right = nullptr;
    }
};
struct IntSet {
    SetElement* root;
    IntSet() {
        root = nullptr;
    }
    ~IntSet() {
        std::queue<SetElement*> q;
        q.push(root);
        while (!q.empty()) {
            SetElement* cur = q.front();
            q.pop();
            if (cur != nullptr) {
                q.push(cur->left);
                q.push(cur->right);
                delete cur;
            }
        }
        root = nullptr;
    }
    void add(int key) {
        if (root == nullptr) {
            root = new SetElement(key);
        }
        else {
            SetElement* cur = root;
            while (cur != nullptr) {
                if (key < cur->value) {
                    if (cur->left == nullptr) {
                        cur->left = new SetElement(key);
                        break;
                    }
                    else {
                        cur = cur->left;
                    }
                }
                else if (key > cur->value) {
                    if (cur->right == nullptr) {
                        cur->right = new SetElement(key);
                        break;
                    }
                    else {
                        cur = cur->right;
                    }
                }
                else {
                    break;
                }
            }
        }
    }
    void print() {
        std::queue<SetElement*> q;
        q.push(root);
        while (!q.empty()) {
            SetElement* cur = q.front();
            q.pop();
            if (cur != nullptr) {
                q.push(cur->left);
                q.push(cur->right);
                std::cout << cur->value << " ";
            }
        }
    }
    void remove(int n) {
        std::queue<SetElement*> q;
        q.push(root);
        while (!q.empty()) {
            SetElement* cur = q.front();
            SetElement* vrem = cur;
            q.pop();
            if (cur != nullptr) {
                q.push(cur->left);
                q.push(cur->right);
                if (cur->value == n) {
                    if ((cur->right != nullptr) && (cur->left != nullptr)) {
                        vrem = cur->left;
                        while (true) {
                         vrem = vrem->right;
                         if (vrem->right == nullptr) {
                               cur->value = vrem->value;
                               cur = vrem;
                               cur = nullptr;
                                    }
                                }
                            }
                        }
                    }
                    else if(cur->right != nullptr){
                        cur->right = vrem->right->right;
                        delete cur->right->right;
                    }
                    else if(cur->left != nullptr){
                        cur->left = vrem->left->left;
                        delete cur->left->left;
                    }
                    else {
                        delete cur;
                    }
                }
            }
        }
        }
};

int main()
{
    setlocale(LC_ALL, "");
    IntSet a;
    a.add(1);
    a.add(5);
    a.add(0);
    a.add(7);
    a.add(1);
    a.add(8);
    a.add(-2);
    a.add(3);
    a.add(-1);
    a.print();
    int n;
    std::cout << "\nЧто удалить?\n";
    std::cin >> n;
    a.remove(n);
    a.print();
}
