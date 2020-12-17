#include <iostream>

#define XOR_PTR(T, x, y) ((XorNode<T>*)((uintptr_t)x ^ (uintptr_t)y))


template<typename T>
class XorList;

template<typename T>
class XorNode {
private:
    T data;
    XorNode *link;

public:
    XorNode(T data, XorNode *link) : data(data), link(link) {}

    XorNode *xorLink(XorNode *other) const {
        auto ptr = XOR_PTR(T, link, other);
        return (XorNode*)ptr;
    }

    friend std::ostream &operator<<(std::ostream &os, const XorNode &list) {
        os << "Node(data: " << list.data << ", link: " << list.link << ")";
        return os;
    }

    friend class XorList<T>;
};

template<typename T>
class XorList {
private:
    XorNode<T> *head;
    XorNode<T> *tail;

public:
    XorList() : head(nullptr), tail(nullptr) {}

    void prepend(T data) {
        auto node = new XorNode<T>(data, head);
        if (!head) {
            head = node;
            tail = node;
        } else {
            head->link = XOR_PTR(T, head->link, node);
            head = node;
        }
    }

    void append(T data) {
        auto node = new XorNode(data, tail);
        if (!tail) {
            tail = node;
            head = node;
        } else {
            tail->link = XOR_PTR(T, tail->link, node);
            tail = node;
        }
    }

    void iter(void (*fn)(XorNode<T>*)) const {
        iterate(head, fn);
    }

    void iter_rev(void (*fn)(XorNode<T>*)) const {
        iterate(tail, fn);
    }

private:
    static void iterate(XorNode<T> *start, void (*fn)(XorNode<T>*)) {
        XorNode<T> *prev = nullptr;
        XorNode<T> *curr = start;

        fn(curr);
        while (curr->link != prev) {
            XorNode<T> *temp = curr;
            curr = curr->xorLink(prev);
            prev = temp;
            fn(curr);
        }
    }
};

int main() {
    XorList<int> list;
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);
    list.prepend(1);
    list.iter([](auto node){ std::cout << *node << std::endl; });
    std::cout << std::endl;
    list.iter_rev([](auto node){ std::cout << *node << std::endl; });

    std::cout << std::endl;

    XorList<std::string> list_str;
    list_str.append("two");
    list_str.append("three");
    list_str.append("four");
    list_str.append("five");
    list_str.prepend("one");
    list_str.iter([](auto node){ std::cout << *node << std::endl; });
    std::cout << std::endl;
    list_str.iter_rev([](auto node){ std::cout << *node << std::endl; });

    return 0;
}
