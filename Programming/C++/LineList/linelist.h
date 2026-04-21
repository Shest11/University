#pragma once
#include <iostream>
using namespace std;

template <class T>
class LineList {
    class LineListElem {
        T data;
        LineListElem* next;

    public:
        LineListElem(const T& adata, LineListElem* anext)
            : data(adata), next(anext) {}

        const T& getData() const {
            return data;
        }

        LineListElem* getNext() {
            return next;
        }

        template <class U> friend class LineList;
    };
    LineListElem* start;

public:
    LineList();

    ~LineList();

    LineListElem* getStart();

    void deleteFirst();

    void deleteAfter(LineListElem* ptr);

    void insertFirst(const T& data);

    void insertAfter(LineListElem* ptr, const T& data);

    template <class U>
    friend std::ostream& operator<<(std::ostream& out, LineList<U>& list);

    void makeCircular();

    void iosif(int N);
};

template<class T>
LineList<T>::LineList() {
    start = nullptr;
}

template<class T>
LineList<T>::~LineList() {
    while (start != nullptr)
        deleteFirst();
}

template<class T>
void LineList<T>::deleteFirst() {
    if (start == nullptr)
        throw "LineListException: empty list";
    LineListElem* temp = start->next;
    delete start;
    start = temp;
}

template<class T>
typename LineList<T>::LineListElem *LineList<T>::getStart() {return start;}

template<class T>
void LineList<T>::insertFirst(const T& data) {
    LineListElem* second = start;
    start = new LineListElem(data, second);
}

template<class T>
void LineList<T>::insertAfter(LineListElem *ptr, const T &data) {
    if (ptr == nullptr)
        throw "LineListException: cannot insert after null";
    LineListElem* temp = ptr->next;
    ptr->next = new LineListElem(data, temp);
}

template<class T>
void LineList<T>::deleteAfter(LineListElem* ptr) {
    if (ptr == nullptr or ptr->next == nullptr)
        throw "LineListException: nothing to delete after";
    LineListElem* temp = ptr->next;
    ptr->next = ptr->next->next;
    delete temp;
}

template <class T>
ostream& operator<<(ostream& out, LineList<T>& list) {
    typename LineList<T>::LineListElem* ptr = list.start;
    if (ptr == nullptr) {
        out << "EMPTY";
    } else {
        while (ptr != nullptr) {
            out << ptr->getData() << " ";
            ptr = ptr->getNext();
        }
    }
    return out;
}

template<class T>
void LineList<T>::makeCircular() {
    if (start == nullptr)
        return;
    LineListElem* node = start;
    while (node->next != nullptr)
        node = node->next;
    node->next = start;
}

template<class T>
void LineList<T>::iosif(int N) {
    for (int data = N; data > 0; data--)
        insertFirst(data);
    makeCircular();

    LineListElem* node = start;
    for (int i = 0; i < N - 1; i++) {
        deleteAfter(node);
        node = node->next;

    }

    start = node;
    start->next = nullptr;
}