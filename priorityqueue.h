#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <iostream>
using namespace std;

template<class Type>
class priorityQ {
public:
    priorityQ (int c=10);
    priorityQ (const priorityQ < Type >&);
    ~priorityQ ();
    const priorityQ<Type>& operator =(const priorityQ <Type>&);
    void insert (const Type &);
    void deleteHighestPriority ();
    Type getHighestPriority () const;
    bool isEmpty () const;
    void bubbleUp (int);
    void bubbleDown (int);
    int getSize () const ;
    void printArr();
    // void printLANDER(); // to help debug
private:
    int capacity;
    int items;
    Type * heapArray;
};


//sets this->capacity with capacity, allocates a dynamic
//array to heapArray, and sets items to 1 or 0 
template <class Type> priorityQ<Type>::priorityQ(int c){
    capacity = c;
    items = 0;
    heapArray = new Type[capacity+1]; // adjust to plus one
}


// copy constructor, performs a deep copy
// of the copy object to the *this object 
template<class Type> priorityQ<Type>::priorityQ(const priorityQ& copy){
    this->capacity = copy.capacity; // sets this capacity to copy capacity
    this->items = copy.getSize();
    this->heapArray = new Type[capacity+1]; // dynamically allocated new heapArray
    for(int i=1; i<=items; i++){
        this->heapArray[i] = copy.heapArray[i]; // perform the deep copy
    }
}


// destructor
template<class Type> priorityQ<Type>::~priorityQ(){
    for(int i=1; i<=capacity; i++){
        heapArray[i] = 0;
        items--;
    }
    delete [] heapArray;
}


//assignment operator, performs a deep copy of rhs object into *this object, 
// remember to check for a self assignment and deallocate this->heapArray first 
// before performing the actual deep copy
template<class Type> 
const priorityQ<Type>& priorityQ<Type>::
    operator=(const priorityQ<Type>& rhs){
        // check for self assignment
        if(this == &rhs){
            return *this;
        }else{
            //otherwise, deallocate this->heapArray
            this->~priorityQ();
            this->capacity = rhs.capacity;
            this->heapArray = new Type[capacity+1];
            this->items = rhs.getSize();
            for(int i=1; i<=items; i++){
                this->heapArray[i] = rhs.heapArray[i]; // perform the deep copy
            }
        }
    return *this;
}


// inserts element to the end of the heap
// and bubbles the element up
template<class Type> void priorityQ<Type>::insert(const Type& element){
    if(items==capacity){
        //resize
        Type *temp = new Type[capacity+1];
        for(int i=1; i<=capacity; i++){
            temp[i] = heapArray[i];
        }
        delete [] heapArray;
        heapArray = temp;
        capacity++;
    }
    items++;
    heapArray[items] = element;
    bubbleUp(items);
}


// removes the root element by assigning the
// root with the end element in the heap and bubbles the element down, 
// also decrements items by 1 (does nothing if the heap is empty) 
template<class Type> void priorityQ<Type>::deleteHighestPriority(){
    if(items==0){return;}
    heapArray[1] = heapArray[items];
    items--;
    bubbleDown(1);
}


// returns the highest priority item, the item
// at index 1 of the heapArray
template<class Type> Type priorityQ<Type>::getHighestPriority() const{
    return heapArray[1];
}

// returns true if there are no items in the heap and
// false otherwise 
template<class Type> bool priorityQ<Type>::isEmpty() const{
    return (this->items>0)? false : true;
}


// bubbles up an element in heapArray at index ”index”, 
// and keeps bubbling up as needed
template<class Type> void priorityQ<Type>::bubbleUp(int index){
    // if index = top, no bubbling up
    if(index==1 || index==0){return;}

    int parent = index / 2;
    
    //compare index and parent
    //swap if index > parent
    if(heapArray[index] > heapArray[parent]){
        swap(heapArray[parent], heapArray[index]);
        bubbleUp(parent); // call again using new index
    }
}


// bubbles down an element from index ”index”, and keeps bubbling
// down as needed, remember the left child and right child of element 
template<class Type> void priorityQ<Type>::bubbleDown(int index){
    int left = 2 * index ;
    int right = 2 * index + 1;
    
    //if left child > items, then no children nodes exist
    if(left > this->items){return;}

    //bubble down left if left > right
    if(heapArray[left] > heapArray[right]){
        if(heapArray[left] > heapArray[index]){
            swap(heapArray[left], heapArray[index]);
            bubbleDown(left);
        }
    }else{ //right > left
        if(heapArray[right] > heapArray[index]){
            swap(heapArray[right], heapArray[index]);
            bubbleDown(right);
        }
    }
}

// returns the amount of elements stored in the heap
template<class Type> int priorityQ<Type>::getSize() const{
    return this->items;
}

template<class Type> void priorityQ<Type>::printArr(){
    for(int i=1; i<=items; i++){
        cout << heapArray[i] << " ";
    }
    cout << endl;
    cout << "capacity: " << this->capacity << "\titems: " 
        << this->items << endl;
}


#endif