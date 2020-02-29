#pragma once
#include <iostream>


using namespace std;

template<typename Key, typename Info>
class DLR{

    typedef struct node
    {
        Key key;
        Info info;
        node* prev;
        node* next;
    }node;
    node *any;
    size_t length;
    template<typename key, typename info>
    friend ostream& operator<<(ostream& os, const DLR<key, info>& seq);


public:

    class iterator;
    //CONSTRUCTORS
    DLR(): any(nullptr), length(0) {};
    DLR(const DLR<Key, Info>& copied)
    {
        any = nullptr;
        *this = copied;
    }

    //DESTRUCTOR
    ~DLR()
    {
        clear();
    }

    //ARITHMETIC OPERATORS
    DLR<Key, Info>& operator=(const DLR<Key, Info>& right);
    DLR<Key, Info> operator+(const DLR<Key, Info>& right);
    DLR<Key, Info>& operator+=(const DLR<Key, Info>& right);

    //BOOL OPERATORS
    bool operator==(const DLR<Key, Info>& right) const;
    bool operator!=(const DLR<Key, Info>& right) const;
    bool operator>(const DLR<Key, Info>& right) const;
    bool operator>=(const DLR<Key, Info>& right) const;
    bool operator<(const DLR<Key, Info>& right) const;
    bool operator<=(const DLR<Key, Info>& right) const;

    //DLR CONTENT
    bool isEmpty() const; //checks if the ring is empty
    bool contain(const Key& ID, const Info& data) const;
    bool exist(const Key& key) const;

    //MODIFIERS
    void push(const Key& ID, const Info& data);
    void pushAfterKey(const Key& search, const Key& key, const Info& info);
    void pushBeforeKey(const Key& search, const Key& key, const Info& info);
    void clear();
    int removeByKey(const Key& key);
    void inverse();

    //DISPLAY
    void displayByKey(const Key& ID) const;
    void displayRing() const;

    //ITERATOR
    iterator iter() const
    {
        return any ? iterator(any) : iterator(nullptr);
    }
    //ACCESS
    size_t size() const
    {
        return length;
    }

};


template<typename Key, typename Info>
bool DLR<Key, Info>::exist(const Key& key) const
{
    if(isEmpty())
        return false;
    node* curr = any;
    do
    {
        if(curr->key == key)
            return true;
        curr = curr->next;
    }
    while(curr != any);
    return false;
}



template<typename Key, typename Info>
bool DLR<Key, Info>::isEmpty() const
{
    return (any == nullptr);
}

template<typename Key, typename Info>
bool DLR<Key, Info>::contain(const Key& ID, const Info& data) const
{
    if(isEmpty())
        return false;

    node* curr = any;
    do
    {
        if(curr->key == ID && curr->info == data)
            return true;
        curr = curr->next;
    }
    while(curr != any);
    return false;
}

template<typename Key, typename Info>
void DLR<Key, Info>::push(const Key& ID, const Info& data)
{
    if(isEmpty())
    {
        any = new node{ID, data};
        any->next = any;
        any->prev = any;
        length++;
        return;
    }
    else
    {
        node* add = new node{ID, data, any->prev, any};
        any->prev->next = add;
        any->prev = add;
        length++;
        return;
    }


}

template<typename Key, typename Info>
void DLR<Key, Info>::pushAfterKey(const Key& search, const Key& key, const Info& info)
{
    if(!exist(search))
        return;
    node* curr = any;
    do
    {
        if(curr->key == search)
        {
            node* add = new node{key, info, curr, curr->next};
            curr->next->prev = add;
            curr->next = add;
            length++;
        }
        curr = curr->next;
    }
    while(curr != any);
    return;
}

template<typename Key, typename Info>
void DLR<Key, Info>::pushBeforeKey(const Key& search, const Key& key, const Info& info)
{
    if(!exist(search))
        return;
    node* curr = any;
    do
    {
        if(curr->key == search)
        {
            node* add = new node{key, info, curr->prev, curr};
            curr->prev->next = add;
            curr->prev = add;
            length++;
        }
        curr = curr->next;
    }
    while(curr != any);
    return;
}

template<typename Key, typename Info>
int DLR<Key, Info>::removeByKey(const Key& key)
{
    if(!exist(key))
        return 0;

    if(length == 1 && any->key == key)
    {
        delete any;
        any = nullptr;
        length--;
        return 1;
    }
    node* curr = any;
    int count = 0;
    do
    {
        if(curr->key == key)
        {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            any = curr->next;
            delete curr;
            length--;
            count++;
        }
        curr = curr->next;
    }
    while(curr != any);
    return count;
}

template <typename Key, typename Info>
void DLR<Key, Info>::inverse()
{
    if(isEmpty())
        return;

    node *curr = any;
    node *next = curr->next;
    node* prev;
    do{
        prev = curr->prev;
        curr->prev = curr->next;
        curr->next = prev;
        curr = next;
        next = curr->next;
    }
    while(curr != any);
}



template<typename Key, typename Info>
void DLR<Key, Info>::clear()
{
    if(isEmpty())
        return;
    node* curr = any;
    do
    {
        node* delPtr = curr;
        curr = curr->next;
        delete delPtr;
    }
    while(curr != any);

    length = 0;
    any = nullptr;
    delete any;
    return;
}

template<typename Key, typename Info>
DLR<Key, Info>& DLR<Key, Info>::operator=(const DLR<Key, Info>& right)
{
    if(this == &right)
        return *this;
    clear();
    if(right.isEmpty()) {
        return *this;
    }
    node* curr = right.any;
    do
    {
        this->push(curr->key, curr->info);
        curr = curr->next;
    }
    while(curr != right.any);

    return *this;

}

template<typename Key, typename Info>
DLR<Key, Info> DLR<Key, Info>::operator+(const DLR<Key, Info>& right)
{
    if(right.isEmpty())
        return *this;
    DLR<Key, Info> add(*this);
    node *temp = right.any;
    do
    {
        add.push(temp->key, temp->info);
        temp = temp->next;
    }
    while(temp != right.any);

    return add;
}

template<typename Key, typename Info>
DLR<Key, Info>& DLR<Key, Info>::operator+=(const DLR<Key, Info>& right)
{
    *this = *this + right;
    return *this;
}

template<typename Key, typename Info>
bool DLR<Key, Info>::operator==(const DLR<Key, Info>& right) const
{
    if(length != right.length)
        return false;
    node *lhs = any;
    node *rhs = right.any;
    do
    {
        if(lhs->key != rhs->key || lhs->info != rhs->info)
            return false;
        lhs = lhs->next;
        rhs = rhs->next;
    }
    while(lhs != any);

    return true;
}

template<typename Key, typename Info>
bool DLR<Key, Info>::operator!=(const DLR<Key, Info>& right) const
{
     return !(*this == right);
}

template<typename Key, typename Info>
bool DLR<Key, Info>::operator>(const DLR<Key, Info>& right) const
{
    return(length > right.length);
}

template<typename Key, typename Info>
bool DLR<Key, Info>::operator>=(const DLR<Key, Info>& right) const
{
    return(length >= right.length);
}

template<typename Key, typename Info>
bool DLR<Key, Info>::operator<(const DLR<Key, Info>& right) const
{
    return(length < right.length);
}

template<typename Key, typename Info>
bool DLR<Key, Info>::operator<=(const DLR<Key, Info>& right) const
{
    return(length <= right.length);
}



template<typename Key, typename Info>
void DLR<Key, Info>::displayByKey(const Key& ID) const
{
    if(isEmpty())
    {
        cout << "\nRING IS EMPTY!\n";
        return;
    }
    node* curr = any->next;
    while(curr->key != ID)
    {
        if(curr == any)
        {
            cout << "\nELEMENT WITH GIVEN ID DOES NOT EXIST\n";
            return;
        }
        curr = curr->next;
    }
    cout << "ID: " << curr->key << " Data: " << curr->info << endl;


    return;

}

template<typename Key, typename Info>
void DLR<Key, Info>::displayRing() const
{
    if(isEmpty())
    {
        cout << "\nRING IS EMPTY!\n";
        return;
    }

    node* curr = any;
    do
    {
        displayByKey(curr->key);
        curr = curr->next;
    }
    while(curr != any);
    cout << endl;
    return;
}

template<typename key, typename info>
ostream& operator<<(ostream& os, const DLR<key, info>& ring)
{
    typename DLR<key, info>::node *curr = ring.any;
    cout << '\n';
    do
    {
        os << "ID: " << curr->key << ' ' << "Data: " << curr->info << '\n';
        curr = curr->next;
    }
    while(curr != ring.any);
    cout << '\n';
    return os;
}


