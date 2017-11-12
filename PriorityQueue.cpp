#include "PriorityQueue.h"

template < typename DataType, typename KeyType, typename Comparator >
PriorityQueue<DataType, KeyType, Comparator>::PriorityQueue ( int maxNumber ) : Heap<DataType>( maxNumber ) {
}

template < typename DataType, typename KeyType, typename Comparator>
void PriorityQueue<DataType, KeyType, Comparator>::enqueue ( const DataType &newDataItem ) {

	Heap<DataType>::insert(newDataItem);
}

template < typename DataType, typename KeyType, typename Comparator>
DataType PriorityQueue<DataType, KeyType, Comparator>::dequeue () {

	return Heap<DataType>::remove();
}