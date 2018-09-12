/* //////////////////////////////////////////////////////////////////////// */
/* File: queue.c */
/* Description: the definition of functions in queue.h */
/* //////////////////////////////////////////////////////////////////////// */

#include "queue.h"

/* //////////////////////////////////////////////////////////////////////// */
/* function prototype: PriorityQueue InitializeQueue(int MaxElements); */
/* parameters: the max number of elements the heap will contain */
/* return value: a pointer to a heap */
/* description: initialize a heap and return a pointer to it */
/* //////////////////////////////////////////////////////////////////////// */
PriorityQueue InitializeQueue(int MaxElements)
{
	PriorityQueue H;
	ElementType mindata;

	if (MaxElements < 10)	/* max elements must larger than 10 */
		exit(0);

	H = (PriorityQueue)malloc(sizeof(HeapStruct));
	if (H == NULL)
		exit(0);

	H->Elements = (ElementType*)malloc((MaxElements + 1)*sizeof(ElementType));
	if (H->Elements == NULL)
		exit(0);

	H->Capacity = MaxElements;
	H->Size = 0;

	mindata = (ElementType)malloc(sizeof(struct Cnode));	/* insert a node as a sentinel */
	setNode(mindata, -1, -1);
	mindata->m_F = -1;
	mindata->m_timepro = 100000;
	H->Elements[0] = mindata;

	return H;
}

/* //////////////////////////////////////////////////////////////////////// */
/* function prototype: bool IsFullQueue(PriorityQueue H); */
/* parameters: a heap pointer */
/* return value: if the heap is full return true, else return false */
/* description: judge whether a heap is full */
/* //////////////////////////////////////////////////////////////////////// */
bool IsFullQueue(PriorityQueue H)
{
	if (H->Size >= H->Capacity)
		return true;
	else
		return false;
}

/* //////////////////////////////////////////////////////////////////////// */
/* function prototype: void InsertQueue(ElementType X, PriorityQueue H); */
/* parameters: a heap pointer and a element pointer */
/* return value: NULL */
/* description: insert a element to the heap */
/* //////////////////////////////////////////////////////////////////////// */
void InsertQueue(ElementType X, PriorityQueue H)
{
	int i;

	if (IsFullQueue(H))
		return;
	for (i = ++H->Size; IsLarger(H->Elements[i / 2], X); i /= 2)
		H->Elements[i] = H->Elements[i / 2];
	H->Elements[i] = X;
}

/* //////////////////////////////////////////////////////////////////////// */
/* function prototype: bool IsLarger(ElementType X, ElementType Y); */
/* parameters: two element pointer */
/* return value: if element one is larger than the two return true, else return false */
/* description: overload the ">" operator */
/* //////////////////////////////////////////////////////////////////////// */
bool IsLarger(ElementType X, ElementType Y)
{
	if (X->m_F > Y->m_F) return true;	/* if X's distance is larger than Y return true */
	if (X->m_F == Y->m_F)
	{
		return X->m_timepro < Y->m_timepro;		/* if their distance is the same then judge the time priority */
	}											/* we will first access the newest element we have accessed to make the algorithm accelerated */
	return false;
}

/* //////////////////////////////////////////////////////////////////////// */
/* function prototype: void DeleteMinQueue(PriorityQueue H); */
/* parameters: a heap pointer */
/* return value: NULL */
/* description: pop the min element and just */
/* //////////////////////////////////////////////////////////////////////// */
void DeleteMinQueue(PriorityQueue H)
{
	int i, child;
	ElementType LastElement;
	if (IsEmptyQueue(H))
		return;
	LastElement = H->Elements[H->Size--];

	for (i = 1; i * 2 <= H->Size; i = child)
	{
		child = i * 2;
		if (child != H->Size && !IsLarger(H->Elements[child + 1], H->Elements[child]))
			child++;

		if (IsLarger(LastElement, H->Elements[child]))
			H->Elements[i] = H->Elements[child];
		else
			break;
	}
	H->Elements[i] = LastElement;
}

/* //////////////////////////////////////////////////////////////////////// */
/* function prototype: bool IsEmptyQueue(PriorityQueue H); */
/* parameters: a heap pointer */
/* return value: if the heap is empty return true, else return false */
/* description: judge whether the heap is empty */
/* //////////////////////////////////////////////////////////////////////// */
bool IsEmptyQueue(PriorityQueue H)
{
	if (H->Size <= 0)
		return true;
	else
		return false;
}

/* //////////////////////////////////////////////////////////////////////// */
/* function prototype: ElementType FindMinQueue(PriorityQueue H); */
/* parameters: a heap pointer */
/* return value: a Cnode pointer */
/* description: return the top element in the heap */
/* //////////////////////////////////////////////////////////////////////// */
ElementType FindMinQueue(PriorityQueue H)
{
	return H->Elements[1];
}

/* //////////////////////////////////////////////////////////////////////// */
/* function prototype: void DestroyQueue(PriorityQueue H); */
/* parameters: a heap pointer */
/* return value: NULL */
/* description: free the space and destroy the heap */
/* //////////////////////////////////////////////////////////////////////// */
void DestroyQueue(PriorityQueue H)
{
	free(H->Elements[0]);
	free(H->Elements);
	free(H);
	H = NULL;
}

/* //////////////////////////////////////////////////////////////////////// */
/* End of queue.c */
/* //////////////////////////////////////////////////////////////////////// */

