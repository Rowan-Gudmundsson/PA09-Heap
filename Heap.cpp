#include "Heap.h"

template < typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::Heap ( int maxNumber ) {

    dataItems = new DataType[maxNumber];
    maxSize = maxNumber;
    size = 0;
}

template < typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::Heap ( const Heap& other ) {

    (*this) = other;
}

template < typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>& Heap<DataType, KeyType, Comparator>::operator= ( const Heap& other ) {

    if(this == &other) return (*this);

    delete [] dataItems;

    dataItems = new DataType[other.maxSize];
    size = other.size;
    maxSize = other.maxSize;

    for(int i = 0; i < size; ++i) {

        dataItems[i] = other.dataItems[i];
    }

    return (*this);
}

template < typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::~Heap () {

    delete [] dataItems;
    size = 0; 
    maxSize = 0;
}

template < typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::insert ( const DataType &newDataItem ) throw ( logic_error ) {

    if(isFull()) throw(logic_error("insert() heap full."));
    dataItems[size] = newDataItem;
    topHeapify(size);
    ++size;
}

template < typename DataType, typename KeyType, typename Comparator>
DataType Heap<DataType, KeyType, Comparator>::remove () throw ( logic_error ) {

    if(isEmpty()) throw(logic_error("remove() heap empty."));
    DataType item = dataItems[0];
    dataItems[0] = dataItems[size - 1];
    bottomHeapify(0);
    --size;
    
    return item;
}

template < typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::clear () {

    size = 0;
}

template < typename DataType, typename KeyType, typename Comparator>
inline bool Heap<DataType, KeyType, Comparator>::isEmpty () const {

    if(size == 0) return true;
    else return false;
}

template < typename DataType, typename KeyType, typename Comparator>
inline bool Heap<DataType, KeyType, Comparator>::isFull () const {

    if(size == maxSize) return true;
    else return false;
}

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: showStructure () const

// Outputs the priorities of the data items in a heap in both array
// and tree form. If the heap is empty, outputs "Empty heap". This
// operation is intended for testing/debugging purposes only.

{
    int j;   // Loop counter

    cout << endl;
    if ( size == 0 )
       cout << "Empty heap" << endl;
    else
    {
       cout << "size = " << size << endl;       // Output array form
       for ( j = 0 ; j < maxSize ; j++ )
           cout << j << "\t";
       cout << endl;
       for ( j = 0 ; j < size ; j++ )
           cout << dataItems[j].getPriority() << "\t";
       cout << endl << endl;
       showSubtree(0,0);                        // Output tree form
    }
}

template < typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::writeLevels () const {


}

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: showSubtree ( int index, int level ) const

// Helper function for the showStructure() function. Outputs the
// subtree (subheap) whose root is stored in dataItems[index]. Argument
// level is the level of this dataItems within the tree.

{
     int j;   // Loop counter

     if ( index < size )
     {
        showSubtree(2*index+2,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )        // Tab over to level
            cout << "\t";
        cout << " " << dataItems[index].getPriority();   // Output dataItems's priority
        if ( 2*index+2 < size )                // Output "connector"
           cout << "<";
        else if ( 2*index+1 < size )
           cout << "\\";
        cout << endl;
        showSubtree(2*index+1,level+1);        // Output left subtree
    }
}

template < typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::topHeapify(int i) {

    bool sorted = false;

    while (!sorted) {

        if(parent(i) < 0)
            sorted = true;

        if(comparator(dataItems[i].getPriority(), dataItems[parent(i)].getPriority()) && !sorted) {

            DataType tmp = dataItems[i];
            dataItems[i] = dataItems[parent(i)];
            dataItems[parent(i)] = tmp;
            i = parent(i);
        }
        else 
            sorted = true;

    }
}

template < typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::bottomHeapify(int i) {

    bool sorted = false;

    while(!sorted) {

        if(leftChild(i) > size - 1 || rightChild(i) > size - 1)
            sorted = true;

        if((comparator(dataItems[leftChild(i)].getPriority(), dataItems[i].getPriority()) ||
            comparator(dataItems[rightChild(i)].getPriority(), dataItems[i].getPriority())) &&
            !sorted) {

            DataType tmp;

            if(comparator(dataItems[leftChild(i)].getPriority(), dataItems[rightChild(i)].getPriority())) {

                tmp = dataItems[i];
                dataItems[i] = dataItems[leftChild(i)];
                dataItems[leftChild(i)] = tmp;
                i = leftChild(i);
            }    
            else {

                tmp = dataItems[i];
                dataItems[i] = dataItems[rightChild(i)];
                dataItems[rightChild(i)] = tmp;
                i = rightChild(i);
            }
        }
        else 
            sorted = true;
    }
}

template < typename DataType, typename KeyType, typename Comparator>
inline int Heap<DataType, KeyType, Comparator>::leftChild(int i) const {

    return 2 * i + 1;
}

template < typename DataType, typename KeyType, typename Comparator>
inline int Heap<DataType, KeyType, Comparator>::rightChild(int i) const {

    return 2 * i + 2;
}

template < typename DataType, typename KeyType, typename Comparator>
inline int Heap<DataType, KeyType, Comparator>::parent(int i) const {

    return (i - 1) / 2;
}