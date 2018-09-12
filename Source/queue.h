/* //////////////////////////////////////////////////////////////////////// */
/* File: queue.h */
/* Description: define a priority queue for the A8 search algorithm */
/* //////////////////////////////////////////////////////////////////////// */

#ifndef H_QUEUE
#define H_QUEUE

#include "base.h"
#include "board.h"

/* typedef */
struct heapStruct;
typedef struct heapStruct* PriorityQueue;
typedef struct heapStruct HeapStruct;
typedef struct Cnode* ElementType;

/* the heap struct. We will maintain an array of the element type */
struct heapStruct
{
	int Capacity;
	int Size;
	ElementType* Elements;
};

/* function declaration */
PriorityQueue InitializeQueue(int MaxElements);
void DestroyQueue(PriorityQueue H);
void InsertQueue(ElementType X, PriorityQueue H);
void DeleteMinQueue(PriorityQueue H);
ElementType FindMinQueue(PriorityQueue H);
bool IsEmptyQueue(PriorityQueue H);
bool IsFullQueue(PriorityQueue H);
bool IsLarger(ElementType X, ElementType Y);

#endif


/* //////////////////////////////////////////////////////////////////////// */
/* End of queue.h */
/* //////////////////////////////////////////////////////////////////////// */

