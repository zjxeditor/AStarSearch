/* //////////////////////////////////////////////////////////////////////// */
/* File: Asearch.h */
/* Description: realize the A* search algorithm */
/* //////////////////////////////////////////////////////////////////////// */

#ifndef H_SEEARCH
#define H_SEEARCH

#include "base.h"
#include "queue.h"

/* basic search struct */
struct CAsearch
{
	/* maintain two heap for searching */
	PriorityQueue OPEN;
	PriorityQueue CLOSE;

	struct Cnode* m_origin;			/* start position */
	struct Cnode* m_destination;	/* destination */
	struct Cboard* m_board;			/* the board */
};

/* function declaration */
void InitializeSearch(struct CAsearch* s, struct Cnode* org, struct Cnode* des, struct Cboard* bor);
bool ASearch(struct CAsearch* s);
void calcurrentnode(struct CAsearch* s, struct Cnode* currentnode);
int Hdistance(struct CAsearch* s, struct Cnode* currentnode);

#endif

/* //////////////////////////////////////////////////////////////////////// */
/* End of Asearch.h */
/* //////////////////////////////////////////////////////////////////////// */