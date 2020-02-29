#pragma once
#include "dictionary.h"

template <typename Key, typename Info>
class Dictionary<Key, Info>::iterator
{
	Node* ptr;
	friend class Dictionary<Key, Info>;
    public:

	iterator() : ptr(nullptr) {};
	iterator(Node* p) : ptr(p){};
	iterator(const iterator& it) : ptr(it.ptr){};

	iterator& operator=(const iterator& it)
	{
	    ptr = it.ptr;
	    return *this;
	}

	bool operator==(const iterator& it) const
	{
	    return ptr == it.ptr;
	}

	bool operator!=(const iterator& it) const
	{
	    return ptr != it.ptr;
	}

	// pre-increment
	iterator& operator++()
	{
	    if (ptr->right)
        {
            ptr = ptr->right;
            while (ptr->left)
            {
                ptr = ptr->left;
            }
	    }
	    else
        {
            Node* before;
            do
            {
                before = ptr;
                ptr = findParent(ptr, ptr->ID);
            }
            while (ptr && before == ptr->right);
	    }
	    return *this;
    }

	// post-increment
	iterator operator++(int)
	{
	    iterator old(*this);
	    ++(*this);
	    return old;
	}

	// pre-decrement
	iterator& operator--()
	{
	    if (ptr->left != nullptr)
        {
            ptr = ptr->left;
            while (ptr->right)
            {
                ptr = ptr->right;
            }
	    }
	    else
        {
            Node* before;
            do
            {
                before = ptr;
                ptr = findParent(ptr, ptr->ID);
            }
            while (ptr && before == ptr->left);
	    }
	    return *this;
	}

	// post-decrement
	iterator operator--(int)
	{
	    iterator old(*this);
	    --(*this);
	    return old;
	}

	/*iterator operator*() const {
	    return ptr->data;
	}

	iterator operator->() const {
	    return &(ptr->data);
	}*/

	Key getID()
	{
	    return ptr->ID;
	}
	Info getData()
	{
	    return ptr->data;
	}

private:

    Node* findParent(Node *n, const Key& key)
    {
        if(key == n->ID)
        {
            return nullptr;
        }
        else if((n->left!=nullptr && key==n->left->ID ) || ( n->right!=nullptr && key==n->right->ID))
        {
            return n;
        }
        else if(key< n->ID)
        {
            return findParent(n->left,key);
        }
        else if(key>n->ID)
        {
            return findParent(n->right,key);
        }
    }
};
