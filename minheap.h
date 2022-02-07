#include <vector>
#include <utility>
#include <exception>
#include <stdexcept>



template <class T>
  class MinHeap {
    public:
        MinHeap(int d);
        ~MinHeap ();
        void add(T item, int priority);
        const T & peek () const;
        void remove ();
        bool isEmpty ();

   private:
        int d_ary_heap;
        std::vector<std::pair<T, int> > heap;
      // whatever you need to naturally store things.
      // You may also add helper functions here.
        int parent(int i);
        int right_child(int p);
        void BubbleUp(int p);
        int size;
        void trickledown(int p);
        void swap(int a, int b);
  };
    //constructor - creates d ary heap and sets size variable
    template <class T>
    MinHeap<T>::MinHeap(int d){

        if(d >= 2){
            d_ary_heap = d;
        }
        size = 0;
        
    }  
       //adds and item and its associated priority to the heap
       template <class T>
       void MinHeap<T>::add(T item, int priority){

           //stl pair to store in vector of pairs
           //each pair has item and associated priority

           std::pair<T, int> pair1;
           pair1.first = item;
           pair1.second = priority;
           heap.push_back(pair1);

           BubbleUp(size);
           size++;
           
           
       }
         
        //returns item at the top of the heap
       template <class T>
        const T & MinHeap<T>::peek() const{

           if(heap.size() == 0){
               throw std::logic_error("Heap is Empty");
           }
           
           return heap[0].first; 

       }
    
        //removes an item at the top of the heap, and then adjusts the nodes of the tree accordingly
       template <class T>
       void MinHeap<T>::remove(){

        if(size == 0){
            throw std::logic_error("Heap is empty");
        }
        else{
           std::swap(heap[0], heap[(size)-1]);
           size--;
           heap.pop_back();
           trickledown(0);
        }


       }
         
        //checks to see if the heap is empty, if its empty it returns true, otherwise false 
       template <class T>
       bool MinHeap<T>::isEmpty(){

           if(size == 0){
               return true;
           }
           else{
               return false;
           }

       }
         
        //function to find parent node
       template <class T>
       int MinHeap<T>::parent(int i){

           return (i-1)/d_ary_heap;

       }

       //funtiom to find the right child
       template <class T>
       int MinHeap<T>::right_child(int p){

           return (d_ary_heap*p)+1;

       }
       //bubbleup function, makes sure the heap stays in order with minimum priority at the top
       //if the inserted item is greater than its parent node, swap
       template <class T>
       void MinHeap<T>::BubbleUp(int p){

           //if value of child is less than value of parent, swap them 
           //first create temp pair to get value of pair in vector, then access value of prio

           if(p > 0 && (heap[p].second < heap[parent(p)].second)){

               std::swap(heap[p], heap[parent(p)]);
               BubbleUp(parent(p));

           }

       }
       //trickledown function, makes sure the heap stays in order with minimum priority at the top
       template <class T>
       void MinHeap<T>::trickledown(int p){

           int child = right_child(p);
           int small = child;

           if(child < heap.size()){
           
            for(int i = 0; i < d_ary_heap; i++){

               if((child+i < heap.size()) && (heap[child+i].second < heap[small].second)){

                   small = child+i;

               }

            }
            if(heap[small].second < heap[p].second){

                std::swap(heap[small], heap[p]);
                trickledown(small);

            }

         }

       }
        //destructor
       template<class T> 
       MinHeap<T>::~MinHeap(){


       }
