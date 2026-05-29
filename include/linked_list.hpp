#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <stdexcept>
#include <ostream> 

template <class T>
struct Node {
    T data;
    Node<T>* next; // T replaces the type of data stored in the node 
};

template <class T>
class LinkedList {
public:
    LinkedList(): head(nullptr), tail(nullptr), m_size(0)  {} //create and initialize head, tail and size using initializer list
    //new object
    LinkedList(const LinkedList& other){//copy constructor, deep copy every node
        head = nullptr;
        tail = nullptr;
        m_size = 0;
        Node<T>* current = other.head;
        while (current != nullptr){
            push_back(current->data);
            current = current->next;
        }
    } 
    //assign to an already existing object
    LinkedList& operator=(const LinkedList& other){//deep copy, handle self-assignment
        if (this == &other) return *this; 
        clear();                            
        Node<T>* current = other.head;
        while (current != nullptr) {
        push_back(current->data);
        current = current->next;
    }
    return *this;
}
    //create a new object by stealing from exisiting oject
    LinkedList(LinkedList&& other){ //steal the pointer, null out the source
        head=other.head;
        tail=other.tail;
        m_size=other.m_size;
        other.head=nullptr;
        other.tail=nullptr;
        other.m_size=0;
    }
    //steal into an existing object
    LinkedList& operator =(LinkedList&& other){ //steal the pointer, free existing nodes, set source to null
        if(this == &other) return *this;
        clear();
        head = other.head;
        tail=other.tail;
        m_size = other.m_size;
        other.head = nullptr;
        other.tail = nullptr;
        other.m_size = 0;
        return *this;
    } 
    void push_front(T val) {// insert at head, O(1)
        Node<T>* newNode = new Node<T>;
        newNode->data = val;
        newNode->next = head;
        head = newNode;
        if(m_size==0){
        tail = newNode;
        }
        m_size++;

        
    }
    void push_back(T val){ //insert at tail, O(1) with tail pointer
        Node<T>* newNode = new Node<T>;
        newNode->data = val;
        newNode->next = nullptr;
        if(m_size==0){
            head = newNode;
            tail = newNode;
        }else{
            tail->next = newNode;
            tail = newNode;
        }
        m_size++;
    }
    T pop_front(){ //remove head, free memory, O(1)
        if(empty()) {
            return T{};
        }else{
            T savedData = head->data;
            Node<T>* temp = head;
            head= head->next;
            delete temp;
            m_size--;
        if(m_size==0){
            tail = nullptr;
        }
        return savedData;
    }    
    } 
    T pop_back(){//remove tail, free memory, O(n)
    if(empty()) {
            return T{};
    }else{
        T savedData = tail->data;
        if(m_size==1){
            delete tail;
            head = nullptr;
            tail = nullptr;
        }else{
            Node<T>* prev = head;
            while(prev->next!=tail){
                prev= prev->next;
            }
            delete tail; //frees memory that tail points to but variable pointer still exists
            tail = prev;
            tail->next = nullptr;
        }
        m_size--;
        return savedData;
    }    
    }    
    void insert(int index, T val) {//insert at arbitrary position, O(n)
        if (index<0||index>m_size){
            return;
        }
        if (index == 0){
            push_front(val);
            return;
        }
        if (index==m_size){
            push_back(val);
            return;
        }
        Node<T>* prev = head;
        int i = 0;
        while(i<index-1){
            prev =prev->next;
            i++;
        }
        Node<T>* newNode = new Node<T>;
        newNode->data=val;
        newNode->next = prev->next;
        prev->next = newNode;
        m_size++;
    }
    bool remove(T val){ //remove first node matching value, O(n)
        if(empty()){
            return false;
        }
        if (head->data == val){
            Node<T>* temp = head; // save node to return later
            head = head->next;
            delete temp;
            m_size--;
            if(m_size == 0){
                tail = nullptr;
            }
            return true;
        }
        Node<T>* prev = head;
        while(prev->next!=nullptr){
            if(prev->next->data == val){
            Node<T>* temp = prev->next;
            prev->next=temp->next;
            if(temp == tail){
                tail = prev;
            }
            delete temp;
            m_size--;
            return true;
        }
        prev = prev->next;      
    }
    return false;
    }
    bool contains(T val){ //linear search, O(n)
        Node <T>* current = head;
        while(current !=nullptr){
            if(current->data == val){
            return true;
        }   
        current = current->next;  
    }
    return false;
    }
    T at(int index){ //index access; throw std::out_of_range if index is invalid
        if( index <0 || index >= m_size){
            throw std::out_of_range("index out of range");
        }
        int count = 0;
        Node<T>* current = head;
        while ( count < m_size){
            if (count == index){
                return current->data;
            }
            current = current -> next;
            count ++;
            
        }
        throw std::out_of_range("index out of range");
    }
    int size(){
        return m_size;
    }
    bool empty(){ //O(1) using the cached counter
        return m_size == 0;
    }
    void clear(){ //delete all nodes and reset the list
        if (m_size == 0) return; 
        Node<T>* current= head;
        
        while(current!=nullptr){
            Node<T>* temp = current->next;
            delete current;
            current = temp;
        }
        head = nullptr;
        tail = nullptr;
        m_size = 0;
    }
    ~LinkedList() { 
    Node<T>* current = head;    
    while(current!= nullptr){
        Node<T>* temp=current->next; //initalize next and set current to next
        delete current;
        current = temp; // increment

    }
}

class Iterator {
public:
    Iterator(Node<T>* ptr) : current(ptr){} //constructor
    
    T& operator*(){ //return data
    return current->data;
    }
    Iterator& operator++(){ //advance
    current = current->next;
    return *this;
    }
    bool operator!=(const Iterator& other){
    return current!= other.current;
    }
private:
    Node<T>* current; 

};

Iterator begin() { //return Iterator Pointing to head node
    return Iterator(head);
}
Iterator end() { // return iterator pointing to nullptr
    return Iterator(nullptr);
}
void reverse() { 
    Node<T>* prev = nullptr;
    Node<T>* current = head;
    tail = head;
    while(current!=nullptr){
        Node<T>* temp = current->next;
        current->next= prev;
        prev=current;
        current=temp;
    }
    head = prev;
    }
friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list){
Node<T>* current = list.head;
    os<<"[ ";
while(current!=nullptr){
    os<<current->data;
    if(current->next != nullptr){
        os<< " -> ";
    }
    current=current->next;
}
os<< " -> null ]";
return os;
}

private:
    Node<T>* head;
    Node<T>* tail;
    int m_size;
};

#endif 