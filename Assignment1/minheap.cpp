//#include "stdafx.h"
#include "minheap.h"

/*MinHeap::MinHeap(int* array, int length) : _vector(length)
{
    for(int i = 0; i < length; ++i)
    {
        _vector[i] = array[i];
    }

    Heapify();
}*/

MinHeap::MinHeap(const vector<node>& vector) : _vector(vector)
{
    Heapify();
}

MinHeap::MinHeap() 
{
            //cout<<"ugh2"<<endl; 

}

void MinHeap::Heapify()
{
    int length = _vector.size();
    for(int i=length-1; i>=0; --i)
    {
        BubbleDown(i);
    }
}

void MinHeap::BubbleDown(int index)
{
    int length = _vector.size();
    int leftChildIndex = 2*index + 1;
    int rightChildIndex = 2*index + 2;

    if(leftChildIndex >= length)
        return; //index is a leaf

    int minIndex = index;

    if(_vector[index].hfunc > _vector[leftChildIndex].hfunc)
    {
        minIndex = leftChildIndex;
    }
    
    if((rightChildIndex < length) && (_vector[minIndex].hfunc > _vector[rightChildIndex].hfunc))
    {
        minIndex = rightChildIndex;
    }

    if(minIndex != index)
    {
        //need to swap
        node temp = _vector[index];
        _vector[index] = _vector[minIndex];
        _vector[minIndex] = temp;
        BubbleDown(minIndex);
    }
}

void MinHeap::BubbleUp(int index)
{
    if(index == 0)
        return;

    int parentIndex = (index-1)/2;

    if(_vector[parentIndex].hfunc > _vector[index].hfunc)
    {
        node temp = _vector[parentIndex];
        _vector[parentIndex] = _vector[index];
        _vector[index] = temp;
        BubbleUp(parentIndex);
    }
}

void MinHeap::Insert(node newValue)
{

    int length = _vector.size();
    _vector.push_back(newValue);
    BubbleUp(length);
}

node MinHeap::GetMin()
{
    return _vector[0];
}
    
void MinHeap::DeleteMin()
{
    int length = _vector.size();

    if(length == 0)
    {
        return;
    }
    
    _vector[0] = _vector[length-1];
    _vector.pop_back();

    BubbleDown(0);

}



