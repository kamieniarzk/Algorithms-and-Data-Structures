#pragma once
#include "DLR.h"

template<typename Key, typename Info>
class DLR<Key, Info>::iterator
{
    node* current;
public:
    //CONSTRUCTORS

    iterator(): current(nullptr){};

    iterator(node *ptr): current(ptr){};


    iterator(const iterator& source)
    {
        this->current = source.current;
    }

    ~iterator() = default;

    //OPERATORS

    iterator& operator=(const iterator& right)
    {
        this->current = right.current;
        return *this;
    }

    bool operator==(const iterator& right) const
    {
        if(this->current == right.current) return true;
        else return false;
    }

    bool operator !=(const iterator& right) const
    {
        return !(*this == right);
    }


    iterator operator++()
    {
        if(current)
            current = current->next;
        return *this;
    }

    iterator operator++(int)
    {
        iterator curr(current);
        if(current)
            current = current->next;
        return curr;
    }

    iterator operator+(int right)
    {
            for(int i = 0; i < right; i++)
            {
                if(current->next)
                    current = current->next;
            }
            return *this;
    }

    iterator operator--()
    {
        if(current)
            current = current->prev;
        return *this;
    }

    iterator operator--(int)
    {
        iterator curr(current);
        if(current)
            current = current->prev;
        return curr;
    }

    iterator operator-(int right)
    {
            for(int i = 0; i < right; i++)
            {
                if(current->prev)
                    current = current->prev;
            }
            return *this;
    }

    isEmpty()
    {
        if(current == nullptr)
            return true;
    }

    //ACCESS

    Key& getKey() const
    {
        if(current)
            return current->key;
        else throw exception();
    }

    Info& getInfo() const
    {
        if(current)
            return current->info;
        else throw exception();
    }
};
