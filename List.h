#pragma once

#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class Node
{
private:
    Node<T>* next, * prev;

public:
    T data;

    Node() : next(nullptr), prev(nullptr) {};

    Node(T data)
    {
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }

    ~Node()
    {
        next = nullptr;
        prev = nullptr;
    }

    void set_data(T data)
    {
        this->data = data;
    }

    T& get_data()
    {
        return &data;
    }

    Node<T>* get_next()
    {
        return next;
    }

    Node<T>* get_prev()
    {
        return prev;
    }

    void set_next(Node<T>* pointer)
    {
        next = pointer;
    }

    void set_prev(Node<T>* pointer)
    {
        prev = pointer;
    }
};

template<typename T>
class List
{
private:
    Node<T>* head, * tail;

public:
    List() : head(nullptr), tail(nullptr)
    {

    }

    List(const List<T>& list)
    {
        clear();
        Node<T>* temp = list.head;
        while (temp)
        {
            push_back(temp->get_data());
            temp = temp->get_next();
        }
    }

    ~List()
    {
        while (head)
        {
            tail = head->get_next();
            delete head;
            head = tail;
        }
        head = nullptr;
    }

    Node<T>* get_pointer(size_t index)
    {
        if (isEmpty() || (index > get_size() - 1))
        {
            throw out_of_range("Invalid argument");
        }
        else if (index == get_size() - 1)
        {
            return tail;
        }
        else if (index == 0)
        {
            return head;
        }
        else
        {
            Node<T>* temp = head;
            while ((temp) && (index--))
            {
                temp = temp->get_next();
            }
            return temp;
        }
    }

    void push_back(T data)
    {
        Node<T>* temp = new Node<T>;
        temp->set_data(data);
        if (head)
        {
            temp->set_prev(tail);
            tail->set_next(temp);
            tail = temp;
        }
        else
        {
            head = temp;
            tail = head;
        }
    }

    void push_front(T data)
    {
        Node<T>* temp = new Node<T>;
        temp->set_data(data);
        if (head)
        {
            temp->set_next(head);
            head->set_prev(temp);
            head = temp;
        }
        else
        {
            head = temp;
            tail = head;
        }
    }

    void push_front(List& list)
    {
        Node<T>* temp = list.tail;
        size_t n = list.get_size();
        while ((temp) && (n--))
        {
            push_front(temp->get_data());
            temp = temp->get_prev();
        }
    }

    void pop_back()
    {
        if (head != tail)
        {
            Node<T>* temp = tail;
            tail = tail->get_prev();
            tail->set_next(nullptr);
            delete temp;
        }
        else if (!isEmpty())
        {
            Node<T>* temp = tail;
            tail = head = nullptr;
            delete temp;
        }
        else
        {
            throw out_of_range("The list is empty");
        }
    }

    void pop_front()
    {
        if (head != tail)
        {
            Node<T>* temp = head;
            head = head->get_next();
            head->set_prev(nullptr);
            delete temp;
        }
        else if (!isEmpty())
        {
            Node<T>* temp = head;
            head = tail = nullptr;
            delete temp;
        }
        else
        {
            throw out_of_range("The list is empty");
        }
    }

    void insert(size_t index, T data)
    {
        Node<T>* temp;
        temp = get_pointer(index);
        if (temp == head)
        {
            push_front(data);
        }
        else
        {
            Node<T>* newElement = new Node<T>;
            newElement->set_data(data);
            temp->get_prev()->set_next(newElement);
            newElement->set_prev(temp->get_prev());
            newElement->set_next(temp);
            temp->set_prev(newElement);
        }
    }

    T at(size_t index)
    {
        Node<T>* temp;
        temp = get_pointer(index);
        return temp->get_data();
    }

    void remove(size_t index)
    {
        Node<T>* temp;
        temp = get_pointer(index);
        if (temp == head)
        {
            pop_front();
        }
        else if (temp == tail)
        {
            pop_back();
        }
        else
        {
            temp->get_prev()->set_next(temp->get_next());
            temp->get_next()->set_prev(temp->get_prev());
            delete temp;
        }
    }

    void remove(T data)
    {
        Node<T>* temp = head;
        while (temp && temp->get_data() != data)
        {
            temp = temp->get_next();
        }
        if (!temp)
        {
            throw out_of_range("Invalid argument");
        }
        if (temp == head)
        {
            pop_front();
        }
        else if (temp == tail)
        {
            pop_back();
        }
        else
        {
            temp->get_prev()->set_next(temp->get_next());
            temp->get_next()->set_prev(temp->get_prev());
            delete temp;
        }
    }

    size_t get_size()
    {
        Node<T>* temp = head;
        size_t length = 0;
        while (temp)
        {
            length++;
            temp = temp->get_next();
        }
        return length;
    }

    void print_to_console()
    {
        Node<T>* temp = head;
        while (temp)
        {
            cout << temp->get_data() << ' ';
            temp = temp->get_next();
        }
        cout << endl;
    }

    void clear()
    {
        while (head)
        {
            tail = head->get_next();
            delete head;
            head = tail;
        }
    }

    void set(size_t index, T data)
    {
        Node<T>* temp;
        temp = get_pointer(index);
        temp->set_data(data);
    }

    bool isEmpty()
    {
        if (!head)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
