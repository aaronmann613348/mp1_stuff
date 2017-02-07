#include <vector>
#include "node.h"
using namespace std;

class MinHeap
{
private:
    void BubbleDown(int index);
    void BubbleUp(int index);
    void Heapify();

public:
    vector <node> _vector;
    int large;

    //MinHeap(int* array, int length);
    MinHeap(const vector<node>& vector);
    MinHeap();

    void Insert(node newValue);
    node GetMin();
    void DeleteMin();
};