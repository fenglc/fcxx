#ifndef _LAND_LIST_H
#define _LAND_LIST_H

#include <stddef.h>
#include <assert.h>
#include <stdio.h>

namespace land
{
    template <class T>
    struct __list_node
    {
        __list_node<T> *prev;
        __list_node<T> *next;
        T value;
    };

    template <class T>
    struct __list_iterator
    {
        using pointer = T *;
        using reference = T &;

        explicit __list_iterator(__list_node<T> *node)
            : _node(node)
        {
        }

        bool operator==(const __list_iterator &o)
        {
            return _node == o._node;
        }
        bool operator!=(const __list_iterator &o)
        {
            return !(*this == o);
        }
        __list_iterator &operator++()
        {
            assert(_node);
            _node = _node->next;
            return *this;
        }
        reference operator*() const
        {
            assert(_node);
            return _node->value;
        }
        pointer operator->()
        {
            assert(_node);
            return &_node->value;
        }

        __list_node<T> *_node;
    };

    template <class T>
    class list
    {
    public:
        using value_type = T;
        using reference = value_type &;
        using const_reference = const value_type &;
        using size_type = size_t;
        using iterator = __list_iterator<value_type>;

        list()
            : _node_header(),
              _size(0)
        {
            _node_header.next = &_node_header;
        }

        ~list()
        {
            clear();
        }

        list(const list &o)
            : _node_header(),
              _size(0)
        {
            _node_header.next = &_node_header;
            auto node = o._node_header.next;
            while (node != &o._node_header)
            {
                push_back(node->value);
                node = node->next;
            }
        }

        list &operator=(const list &o)
        {
            if (this == &o)
                return *this;

            _node_header.next = &_node_header;
            auto node = o._node_header.next;
            while (node != &o._node_header)
            {
                push_back(node->value);
                node = node->next;
            }

            return *this;
        }

        void clear()
        {
            auto node = _node_header.next;
            while (node != &_node_header)
            {
                auto tmp = node;
                node = node->next;
                delete tmp;
            }

            _size = 0;
            _node_header.next = &_node_header;
        }

        bool empty() const { return _node_header.next == (&_node_header); }

        size_type size() const { return _size; }

        void push_back(const_reference value)
        {
            insert(end(), value);
        }

        iterator begin()
        {
            return iterator(_node_header.next);
        }

        iterator end()
        {
            return iterator(&_node_header);
        }

        iterator erase(iterator pos)
        {
            auto it = end();
            if (it == pos)
                return it;

            auto node = _node_header.next;
            while (node)
            {
                if (node != pos._node)
                {
                    node = node->next;
                    continue;
                }

                auto prev = node->prev;
                auto next = node->next;
                delete node;

                if (!next)
                    next = &_node_header;
                prev->next = next;
                --_size;
                return iterator(next);
            }
            return end();
        }

        iterator insert(iterator pos, const_reference value)
        {
            ++_size;
            auto new_node = new __list_node<value_type>;
            new_node->value = value;

            auto node = _node_header.next;
            assert(node);
            while (node != &_node_header)
            {
                if (node != pos._node)
                {
                    if (node->next == &_node_header)
                    {
                        node->next = new_node;
                        new_node->prev = node;
                        new_node->next = &_node_header;
                        return iterator(new_node);
                    }
                    node = node->next;
                    continue;
                }

                auto prev = node->prev;
                auto next = node->next;

                prev->next = new_node;
                new_node->prev = prev;
                new_node->next = next;
                if (next)
                    next->prev = new_node;
                return iterator(new_node);
            }

            _node_header.next = new_node;
            new_node->prev = &_node_header;
            new_node->next = &_node_header;
            return iterator(new_node);
        }

    private:
        __list_node<value_type> _node_header;
        size_type _size;
    };
}

#endif
