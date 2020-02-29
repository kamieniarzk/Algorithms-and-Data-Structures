#pragma once
#include <iostream>

using namespace std;

template <typename Key, typename Info>
class Dictionary
{
    struct Node
    {
        Key ID;
        Info data;
        int height;
        int bf;
        Node *left;
        Node *right;
    };
    Node *root;

public:
    class iterator;

    //CONSTRUCTORS AND DESTRUCTOR
    Dictionary(): root(nullptr) {};
    ~Dictionary();
    Dictionary(const Dictionary& d);

    //OPERATOR
    Dictionary& operator=(const Dictionary& d);
    Dictionary& operator=(Dictionary&& d);

    //ACCESS
    int height() const;
    bool isEmpty() const;
    bool belongs(const Key& key) const;
    Key& getMax();
    Key& getMin();
    Info& getID(const Key& key);

    //OPERATIONS
    void insert(const Key& key, const Info& info);
    void clear();
    void erase(const Key& key);

    //DISPLAY
    void display2D() const;
    void displayInOrder() const;
    void node(iterator i); // for testing iterator

    //ITERATOR
    iterator iter() const
    {
        if(root)
            return iterator(root);
        else
            return iterator(nullptr);
    }


private:
    //ACCESS
    Key& getMax(Node *start) const;
    Key& getMin(Node *start) const;
    Node* getNode(const Key& key, Node *start) const;
    Node* minValue(Node* n);


    //OPERATIONS
    Node* insert(const Key& key, const Info& info, Node *n);
    Node* copy(Node *n);
    Node* erase(Node* n, const Key& key);
    Node* balance(Node *n);
    void clear(Node *n);
    void updateHeight(Node *n);
    bool belongs(const Key& key, Node *n) const;

    //ROTATIONS
    Node* leftRotation(Node *n);
    Node* rightRotation(Node *n);
    Node* leftRightRotation(Node *n);
    Node* rightLeftRotation(Node *n);

    //DISPLAY
    void print2D(Node *n, int space) const;
    void printInOrder(Node *n) const;


};


template <typename Key, typename Info>
Dictionary<Key, Info>::Dictionary(const Dictionary& d)
{
    root = copy(d.root);
}

template <typename Key, typename Info>
Dictionary<Key, Info>::~Dictionary()
{
    clear(root);
}

template <typename Key, typename Info>
Dictionary<Key, Info>& Dictionary<Key, Info>::operator=(const Dictionary<Key, Info>& d)
{
    clear();
    root = copy(d.root);
    return *this;
}

template <typename Key, typename Info>
Dictionary<Key, Info>& Dictionary<Key, Info>::operator=(Dictionary<Key, Info>&& d)
{
    clear();
    root = std::move(d.root);
    d.root = nullptr;
    return *this;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::clear()
{
    clear(root);
    root = nullptr;
}

template <typename Key, typename Info>
bool Dictionary<Key, Info>::isEmpty() const
{
        return (root == nullptr);
}

template <typename Key, typename Info>
int Dictionary<Key, Info>::height() const
{
        if(root)
            return root->height;
        else
            return 0;
}

template <typename Key, typename Info>
Key& Dictionary<Key, Info>::getMax(Node *n) const
{
    if(n->right == nullptr)
        return n->ID;

    return getMax(n->right);
}

template <typename Key, typename Info>
Key& Dictionary<Key, Info>::getMin(Node *n) const
{
    if(n->left == nullptr)
        return n->ID;

    return getMin(n->left);
}


template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::getNode(const Key& key, Node *n) const
{
    if(n == nullptr)
    {
        cout << "Node with given key does not exist in the tree!" << endl;
        throw exception();
    }

    else
    {
        if(key > n->ID)
            return getNode(key, n->right);
        else if(key < n->ID)
            return getNode(key, n->left);
    }

    return n;
}

template <typename Key, typename Info>
Key& Dictionary<Key, Info>::getMax()
{
        return getMax(root);
}


template <typename Key, typename Info>
Key& Dictionary<Key, Info>::getMin()
{
        return getMin(root);
}


template <typename Key, typename Info>
Info& Dictionary<Key, Info>::getID(const Key& key)
{
        return getNode(key, root)->data;
}


template<typename Key, typename Info>
void Dictionary<Key, Info>::print2D(Node *n, int space) const
{
    if (n == NULL)
        return;
    space += 10;
    print2D(n->right, space);
        cout << endl;

    for (int i = 10; i < space; i++)
        cout << " ";

    cout << n->ID << " (" << n->data << ")" << endl;
    print2D(n->left, space);
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::printInOrder(Node* n) const
{
    if(n)
    {
        if(n->left)
            printInOrder(n->left);
        cout << n->ID << " (" << n->data << ") ";
        if(n->right)
            printInOrder(n->right);
    }
}



template<typename Key, typename Info>
void Dictionary<Key, Info>::displayInOrder() const
{
    if(root == nullptr)
    {
        cout << endl << "Tree is empty" << endl;
        return;
    }
    else
        printInOrder(root);
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::display2D() const
{
    if(root == nullptr)
    {
        cout << endl << "Tree is empty" << endl;
        return;
    }
    else
        print2D(root, 10);
}



template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::insert(const Key& key, const Info& info, Node *n)
{
    if(n == nullptr)
        return new Node{key, info, 0, 0, nullptr, nullptr};

    if(key > n->ID)
        n->right = insert(key, info, n->right);

    else if(key < n->ID)
        n->left = insert(key, info, n->left);

    updateHeight(n);
    return balance(n);
}


template <typename Key, typename Info>
void Dictionary<Key, Info>::insert(const Key& key, const Info& info)
{
    if(belongs(key, root))
    {
        cout << "Node with given key already belongs to the tree!" << endl;
        return;
    }

    else
        root = insert(key, info, root);
}


template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::erase(Node* n, const Key& key)
{
    if (n == nullptr)
        return nullptr;

    if (key < n->ID)
        n->left = erase(n->left, key);

    else if (key > n->ID)
        n->right = erase(n->right, key);

    else
    {
        if (n->left == nullptr)
        {
            Node *temp = n->right;
            delete n;
            return temp;
        }
        else if (n->right == nullptr)
        {
            Node *temp = n->left;
            delete n;
            return temp;
        }

        Node* temp = minValue(n->right);
        n->ID = temp->ID;
        n->data = temp->data;
        n->right = erase(n->right, temp->ID);
    }

    updateHeight(n);
    return balance(n);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::erase(const Key& key)
{
    if(root == nullptr)
    {
        cout << "Tree is empty" << endl;
        throw exception();
    }
    else
        root = erase(root, key);
}


template <typename Key, typename Info>
void Dictionary<Key, Info>::clear(Node *n)
{
    if(n == nullptr)
        return;
    clear(n->left);
    clear(n->right);
    delete n;
}




template <typename Key, typename Info>
bool Dictionary<Key, Info>::belongs(const Key& key) const
{
    return belongs(key, root);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::updateHeight(Node *n)
{
    int leftHeight, rightHeight;

    if(n->left != nullptr)
        leftHeight = n->left->height;
    else
        leftHeight = -1;

    if(n->right != nullptr)
        rightHeight = n->right->height;
    else
        rightHeight = -1;

    if(leftHeight > rightHeight)
        n->height = leftHeight + 1;

    else
        n->height = rightHeight + 1;

    n->bf = rightHeight - leftHeight;

}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::balance(Node *n)
{
    if(n->bf <= -1)
    {
        if(n->left->bf <= 0)
            return rightRotation(n);
        else
            return leftRightRotation(n);
    }
    else if(n->bf >= 1)
    {
        if(n->right->bf >= 0)
            return leftRotation(n);
        else
            return rightLeftRotation(n);
    }

    return n;
}



template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::leftRotation(Node *n)
{
    Node *temp = n->right;
    n->right = temp->left;
    temp->left = n;
    updateHeight(temp);
    updateHeight(n);

    return temp;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::rightRotation(Node *n)
{
    Node *temp = n->left;
    n->left = temp->right;
    temp->right = n;
    updateHeight(temp);
    updateHeight(n);

    return temp;
}


template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::leftRightRotation(Node *n)
{
    n->left = leftRotation(n->left);
    return rightRotation(n);
}


template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::rightLeftRotation(Node *n)
{
    n->right = rightRotation(n->right);
    return leftRotation(n);
}





template <typename Key, typename Info>
bool Dictionary<Key, Info>::belongs(const Key& key, Node *n) const
{
    if(n == nullptr)
        return false;

    if(key > n->ID)
        return belongs(key, n->right);

    else if(key < n->ID)
        return belongs(key, n->left);

    else
        return true;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::copy(Node *n)
{
    Node *temp = nullptr;

    if(n != nullptr)
    {
        temp = new Node{n->ID, n->data, n->bf, n->height, nullptr, nullptr};
        temp->left = copy(n->left);
        temp->right = copy(n->right);
    }

    return temp;
}



template <typename Key, typename Info>
 void Dictionary<Key, Info>::node(iterator i)
{
    cout << endl <<"ID: " << i.getID() << " Data: " << i.getData() << endl;
}


template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::minValue(Node* n)
{
    Node* current = n;

    /* loop down to find the leftmost leaf */
    while (current->left != nullptr)
        current = current->left;

    return current;
}

