#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <string>

namespace dllSpace {

    template <typename T>
        class List {
            private:
                // nested Node class
                struct Node {
                    T data;
                    Node *prev;
                    Node *next;

                    Node(const T & d = T{}, Node *p = nullptr, Node *n = nullptr)
                        : data{d}, prev{p}, next{n} {}
                    Node(T && d, Node *p = nullptr, Node *n = nullptr)
                        : data{std::move(d)}, prev{p}, next{n} {}
                };

            public:
                //nested const_iterator class
                class const_iterator {
                    public:
                        const_iterator(); // default zero parameter constructor
                        const T & operator*() const; // operator*() to return element

                        // increment/decrement operators
                        const_iterator & operator++();
                        const_iterator operator++(int);
                        const_iterator & operator--();
                        const_iterator operator--(int);

                        // comparison operators
                        bool operator==(const const_iterator &rhs) const;
                        bool operator!=(const const_iterator &rhs) const;

                    protected:
                        Node *current; // pointer to node in List
                        T & retrieve() const; // retrieve the element refers to
                        const_iterator(Node *p); // protected constructor

                        friend class List<T>;
                };

                // nested iterator class
                class iterator : public const_iterator {
                    public:
                        iterator();
                        T & operator*();
                        const T & operator*() const;

                        // increment/decrement operators
                        iterator & operator++();
                        iterator operator++(int);
                        iterator & operator--();
                        iterator operator--(int);

                    protected:
                        iterator(Node *p);
                        friend class List<T>;
                };

            public:
                // constructor, desctructor, copy constructor
                List(); // default zero parameter constructor
                List(const List &rhs); // copy constructor
                List(List && rhs); // move constructor
                // num elements with value of val
                explicit List(int num, const T& val = T{});
                // constructs with elements [start, end)
                List(const_iterator start, const_iterator end);

                ~List(); // destructor

                // copy assignment operator
                const List& operator=(const List &rhs);
                // move assignment operator
                List & operator=(List && rhs);

                // member functions
                int size() const; // number of elements
                bool empty() const; // check if list is empty
                void clear(); // delete all elements
                void reverse(); // reverse the order of the elements

                T &front(); // reference to the first element
                const T& front() const;
                T &back(); // reference to the last element
                const T & back() const;

                void push_front(const T & val); // insert to the beginning
                void push_front(T && val); // move version of insert
                void push_back(const T & val); // insert to the end
                void push_back(T && val); // move version of insert
                void pop_front(); // delete first element
                void pop_back(); // delete last element

                void remove(const T &val); // remove all elements with value = val

                // print out all elements. ofc is deliminitor
                void print(std::ostream& os, char ofc = ' ') const;

                iterator begin(); // iterator to first element
                const_iterator begin() const;
                iterator end(); // end marker iterator
                const_iterator end() const;
                iterator insert(iterator itr, const T& val); // insert val ahead of itr
                iterator insert(iterator itr, T && val); // move version of insert
                iterator erase(iterator itr); // erase one element
                iterator erase(iterator start, iterator end); // erase [start, end)


            private:
                int theSize; // number of elements
                Node *head; // head node
                Node *tail; // tail node

                void init(); // initialization
        };

    // overloading comparison operators
    template <typename T>
        bool operator==(const List<T> & lhs, const List<T> &rhs);

    template <typename T>
        bool operator!=(const List<T> & lhs, const List<T> &rhs);

    // overloading output operator
    template <typename T>
        std::ostream & operator<<(std::ostream &os, const List<T> &l);











    // include the implementation file here
#include "List.h"



        // default constructor w/ no parameters
        template<typename T>
        List<T>::const_iterator::const_iterator() : current{nullptr}
        {
        }
        // operator* returns the element (to be retrieve later)  (protected)
        template<typename T>
        const T & List<T>::const_iterator::operator*() const
        {
            return retrieve();
        }
        // operators various
        template<typename T>
        typename List<T>::const_iterator & List<T>::const_iterator::operator++()
        {  // increment operator, pointer to the next nodo
            current = current->next;    return *this;
            // basically returns the instance of this class, * = dereference, and "this" is the pointer to the instance
        }
        template<typename T>
        typename List<T>::const_iterator List<T>::const_iterator::operator++(int)  // ++(int) postfix increment
        { // return a copy of original object and then increment by 1
            auto cpy = *this;  //using dereferencing and member access.
            current = current->next; 	return cpy;
        }
        template<typename T>
        typename List<T>::const_iterator & List<T>::const_iterator::operator--() // decrement
        {
            current = current->prev; 	return *this;
        }
        template<typename T>
        typename List<T>::const_iterator List<T>::const_iterator::operator--(int) //--(int) posfix decrement
        {
            auto cpy = *this;
            current = current->prev;	return *this;
        }
        // comparisons
        template<typename T>
        bool List<T>::const_iterator::operator==(const typename List<T>::const_iterator & rhs) const
        {
            return current == rhs.current; // refer to the same element? ==
        }
        template<typename T>
        bool List<T>::const_iterator::operator!=(const typename List<T>::const_iterator & rhs) const
        {
            return current != rhs.current; // they do not refer to the same element? !=
        }
        // protected constructor
        template<typename T>
        List<T>::const_iterator::const_iterator(typename List<T>::Node* p) : current{p}
        {
        }
        //friend class List<T>;

        // nested iterator class begin, it will return a modifiable reference of current Node
        template<typename T>
        List<T>::iterator::iterator()  // constructor of derived iterator class
        {
        }
        template<typename T>
        T & List<T>::iterator::operator*() // this operator* is the one will return a modifiable
        //reference of the data in current Node
        {
            return this->current->data;
        }
        // retrieve the element refers to current node's data
        template<typename T>
        T & List<T>::const_iterator::retrieve() const
        {
            return current->data;
        }
        template<typename T>
        const T & List<T>::iterator::operator*() const
        {
            return this->retrieve();
        }
        // operators needed again
        template<typename T>
        typename List<T>::iterator & List<T>::iterator::operator++()
        {  //this->current to call base's protected data
            this->current = this->current->next; 	return *this;
        }
        template<typename T>
        typename List<T>::iterator List<T>::iterator::operator++(int)
        {
            auto cpy = *this;
            this->current = this->current->next; 	return cpy;
        }
        template<typename T>
        typename List<T>::iterator & List<T>::iterator::operator--()
        {
            this->current = this->current->prev;	return *this;
        }
        template<typename T>
        typename List<T>::iterator List<T>::iterator::operator--(int)
        {
            auto cpy = *this;
            this->current = this->current->prev;	return *this;
        }
        template<typename T>
        List<T>::iterator::iterator(typename List<T>::Node* p) : List<T>::const_iterator{p}
        {
        }
        template<typename T>
        List<T>::List()    // constructor, no parameter and will call member function
        {
            init(); // initialization private function
        }
        template<typename T>
        List<T>::~List() // destructor
        {
            clear(); // housekeeping job, // delete elements as needed
            delete head;  // head node
            delete tail;  // tail node
        }
        template<typename T>
        List<T>::List(const List<T> & rhs) // copy constructor
        {
            init();  // call function to do the copy need it
            for(auto itr = rhs.begin(); itr != rhs.end(); ++itr)
                push_back(*itr); // move
        }
        template<typename T> // move constructor
        List<T>::List( List<T> && rhs ) : theSize(rhs.theSize), head{rhs.head}, tail{rhs.tail}
        {
            rhs.theSize = 0;	rhs.head = nullptr;		rhs.tail = nullptr;
        }
        template<typename T> // copy assignment
        const List<T> & List<T>::operator=(const List<T> & rhs)
        {
            auto cpy = rhs;  // swap by reference
            std::swap(*this, cpy);  	return *this;
        }
        template<typename T>	// move assignment
        List<T> & List<T>::operator=(List<T> && rhs)
        {
            init();
            *this = std::move( rhs );	return *this;
        }
        template<typename T>
        List<T>::List(int num, const T & val)
        {
            init(); int index;
            for(index = 0; index < num; index++)
                push_back(val); // note  // insert val ahead of itr
        }
        template<typename T> // constructor w/ element [start, end)
        List<T>::List(typename List<T>::const_iterator start, typename List<T>::const_iterator end)
        {
            init();
            for(auto itr= start; itr != end; ++itr)
                push_back( *itr );
        }
        template<typename T>   // number of elements
        int List<T>::size() const
        {
            return theSize;
        }
        template<typename T>
        void List<T>::reverse() // to reverse the order of elements if not empty
        {
            if(!empty()) // check to be valid
            {
                auto current_ptr=head;
                while(current_ptr != nullptr)
                {
                    std::swap(current_ptr->next, current_ptr->prev);
                    current_ptr=current_ptr->prev;
                }
            }
            std::swap(head, tail); // awesome
        }
        template<typename T> // first element
        T & List<T>::front()
        {
            return *begin();  // ref. iterator to first element
        }
        template<typename T>
        const T & List<T>::front() const // now, w/ no permission to modify 1st elem.
        {
            return *begin();
        }
        template<typename T> //  last element
        T & List<T>::back()
        {
            return *(--end());
        }
        template<typename T> // now, w/ no permission to modify last elem.
        const T & List<T>::back() const
        {
            return *(--end());
        }
        template<typename T>
        void List<T>::push_front( T && val)
        {
            insert(begin(), std::move( val));
        }
        // insert to the beginning, alias, insert right after Node* head
        template<typename T>
        void List<T>::push_front(const T & val)
        {
            insert(begin(), val);  // insert after Node head
        }
        template<typename T>
        void List<T>::push_back(T && val) // move version insert_back
        {
            insert( end(), std::move( val));
        }
        template<typename T>
        void List<T>::pop_front() // delete first element
        {
            erase(begin());
        }
        template<typename T>
        void List<T>::clear()
        {
            while(!empty())
                pop_back(); // to delete all the elements
        }
        // insert to the end, alias, insert right before Node* tail
        template<typename T>
        void List<T>::push_back(const T & val)
        {
            insert(end(), val);
        }
        template<typename T>
        void List<T>::pop_back()
        {
            erase(--end()); // erase one element, the last one.
        }
        template<typename T>
        bool List<T>::empty() const
        {
            return size() == 0; // ==0  check if list is empty of nodes
        }
        template<typename T>
        void List<T>::remove(const T & val) // remove all elements with value val
        {
            for(auto itr = begin(); itr != end(); )
            {
                if(*itr == val)		itr = erase(itr);
                else {
                    itr++;
                }
            }
        }
        template<typename T>
        typename List<T>::iterator List<T>::begin()
        {
            if(!empty()) // check first
            {
                typename List<T>::iterator itr{head->next};
                return itr; // begining node (copy)
            }
        }
        template<typename T>
        typename List<T>::const_iterator List<T>::begin() const
        {
            if(!empty())
            {
                typename List<T>::const_iterator const_itr{head->next};
                return const_itr;
            }
        }
        template<typename T>
        typename List<T>::iterator List<T>::end()
        {
            typename List<T>::iterator itr{ tail };
            return itr; // return the end node (copy)
        }
        template<typename T>
        typename List<T>::const_iterator List<T>::end() const
        {
            typename List<T>::const_iterator const_itr{tail};
            return const_itr;
        }
        template<typename T>
        typename List<T>::iterator List<T>::insert(typename List<T>::iterator itr, const T & val)
        { // pointer "p" is copy of current node
            auto* p = itr.current;  theSize++;
            auto* nptr = new List<T>::Node{val, p->prev, p};
            p->prev->next = nptr;
            p->prev = nptr;
            typename List<T>::iterator iter{nptr};	return iter;
        }
        template<typename T>
        typename List<T>::iterator List<T>::insert(typename List<T>::iterator itr, T && val)
        {
            auto* p = itr.current;	theSize++;
            auto* nptr = new List<T>::Node{ std::move( val ), p->prev, p};
            p->prev->next = nptr;
            p->prev = nptr;
            typename List<T>::iterator iter{nptr};	return iter;
        }
        template<typename T>
        typename List<T>::iterator List<T>::erase(typename List<T>::iterator start, typename List<T>::iterator end)
        {
            for(auto itr = start; itr != end;) // erase from start to end
                itr = erase(itr); //  not including end. Alias, erase [start, end)

            return end;
        }
        template<typename T>
        void List<T>::init()  // init. private function
        {
            theSize = 0;
            head = new Node;	tail = new Node;
            head->next = tail;	tail->prev = head;
        }
        template<typename T>
        typename List<T>::iterator List<T>::erase(typename List<T>::iterator itr)
        {  // erase one element
            auto* p = itr.current;
            typename List<T>::iterator value{p->next};
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p;
            theSize--;
            return value;
        }
        // overloading comparison
        template<typename T>
        bool operator!=(const List<T> & lhs, const List<T> & rhs)
        {
            return !(lhs == rhs);
        }
        template<typename T>
        bool operator==(const List<T> & lhs, const List<T> & rhs)
        {
            bool flag = true;
            if( lhs.size() == rhs.size())
            {
                auto rhs_itr = rhs.begin();
                for(auto lhs_itr=lhs.begin(); lhs_itr !=lhs.end(); ++lhs_itr)
                {
                    if(*lhs_itr != *rhs_itr)
                       flag = false; break;
                    ++rhs_itr;
                }
                return flag;
            }
            else
                return false;
        }
        // overloading output
        template<typename T>
        std::ostream & operator<<(std::ostream & os, const List<T> & l)
        {
            l.print(os);	return os;
        }
        // print out all elements
        template<typename T>
        void List<T>::print(std::ostream & os, char ofc) const
        {
            for(auto itr = begin(); itr != end(); ++itr)
                os << *itr << ofc;  // ofc is the deliminitor
        }




} // end of dllSpace namespace

#endif
