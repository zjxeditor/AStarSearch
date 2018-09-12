/* //////////////////////////////////////////////////////////////////////// */
/* File: Asearch.c */
/* Description: the definition of functions in Asearch.h */
/* //////////////////////////////////////////////////////////////////////// */

#include "Asearch.h"

/* //////////////////////////////////////////////////////////////////////// */
/* function prototype: void InitializeSearch(struct CAsearch* s, struct Cnode* org, struct Cnode* des, struct Cboard* bor); */
/* parameters: a search struct, start position, destination and the board */
/* return value: NULL */
/* description: initialize a search struct for searching */
/* //////////////////////////////////////////////////////////////////////// */
void InitializeSearch(struct CAsearch* s, struct Cnode* org, struct Cnode* des, struct Cboard* bor)
{
	s->m_origin = org;
	s->m_destination = des;
	s->m_board = bor;

	/* initialize the two heap */
	s->OPEN = InitializeQueue(1000);
	s->CLOSE = InitializeQueue(1000);
}

/* //////////////////////////////////////////////////////////////////////// */
/* function prototype: bool ASearch(struct CAsearch* s); */
/* parameters: a search struct pointer */
/* return value: if the search is successful then return true, else return false */
/* description: the main search algorithm */
/* //////////////////////////////////////////////////////////////////////// */
bool ASearch(struct CAsearch* s)
{
	struct Cnode* currentnode = NULL;
	struct Cnode* next = NULL;
	int time_count = 0;
	int i, xo, yo;
	struct Cpoint off;
	struct Cnode* pnode = NULL;
	struct Cnode* child = NULL;
	/* verify if the start position or the destination position is invalid, just return false */
	if (!s->m_origin || !s->m_destination || !s->m_board)
		return false;
	if (s->m_origin->m_x<0 || s->m_origin->m_x>s->m_board->m_xdis - 1 || s->m_origin->m_y<0 || s->m_origin->m_y>s->m_board->m_ydis - 1
		|| s->m_destination->m_x<0 || s->m_destination->m_x>s->m_board->m_xdis - 1 || s->m_destination->m_y<0 || s->m_destination->m_y>s->m_board->m_ydis - 1)
		return false;
	if (orgdata[s->m_destination->m_x][s->m_destination->m_y] == 1 || orgdata[s->m_origin->m_x][s->m_origin->m_y] == 1)
		return false;

	currentnode = s->m_origin;
	calcurrentnode(s, currentnode);

	while (true)
	{
		currentnode->m_closeflag = true;
		currentnode->m_openflag = false;
		InsertQueue(currentnode, s->CLOSE);	/* insert the accessed node to the CLOSE heap */
		xo = currentnode->m_x;
		yo = currentnode->m_y;
		/* push the 4 node around current node into the OPEN table and push the current into the CLOSE table */
		for (i = 0; i < 4; i++)
		{
			off.x = offset[i][0];
			off.y = offset[i][1];
			if ((xo + off.x) < 0 || (xo + off.x) > s->m_board->m_xdis - 1
				|| (yo + off.y) < 0 || (yo + off.y) > s->m_board->m_ydis - 1)
				continue;
			else
			{
				pnode = (s->m_board->data)[xo + off.x][yo + off.y];
				if (orgdata[xo + off.x][yo + off.y] == 1 || pnode->m_closeflag || pnode->m_openflag)
					continue;
				/* it is a new node and we don't need to update the distant because we can just move in four directions */
				else
				{
					time_count++;
					pnode->m_timepro = time_count;
					pnode->m_openflag = true;
					pnode->m_closeflag = false;
					pnode->m_pParent = currentnode;
					calcurrentnode(s, pnode);
					InsertQueue(pnode, s->OPEN);	/* insert the new node to the OPEN heap */
				}
			}
		}
		/* check if we find the destination or we can not find it */
		if (s->m_destination->m_openflag || s->OPEN->Size == 0)
			break;
		/* choose the node with smallest F value */
		next = FindMinQueue(s->OPEN);
		DeleteMinQueue(s->OPEN);
		currentnode = next;

	}
	/* can not reach there */
	if (s->OPEN->Size == 0)
	{
		return false;
	}

	/* populate the result chain */
	currentnode = s->m_destination;
	
	while (true)
	{
		child = currentnode;
		currentnode = currentnode->m_pParent;
		if (!currentnode)
			break;;
		currentnode->m_next = child;
	}
	child = NULL;
	return true;
}

/* //////////////////////////////////////////////////////////////////////// */
/* function prototype: void calcurrentnode(struct CAsearch* s, struct Cnode* currentnode); */
/* parameters: a search struct pointer and a node pointer */
/* return value: NULL */
/* description: calculate the "F" value of a node which will be used for calculating the final distance */
/* //////////////////////////////////////////////////////////////////////// */
void calcurrentnode(struct CAsearch* s, struct Cnode* currentnode)
{
	int h;

	if (currentnode->m_pParent == NULL)
		currentnode->m_G = 0;
	else
		currentnode->m_G = currentnode->m_pParent->m_G + 10;

	h = Hdistance(s, currentnode);
	currentnode->m_F = h + currentnode->m_G;
}

/* //////////////////////////////////////////////////////////////////////// */
/* function prototype: int Hdistance(struct CAsearch* s, struct Cnode* currentnode); */
/* parameters: a search struct pointer and a node pointer */
/* return value: NULL */
/* description: calculate the "H" value of a node which will be used for calculating the final distance */
/* //////////////////////////////////////////////////////////////////////// */
int Hdistance(struct CAsearch* s, struct Cnode* currentnode)
{
	int delta_x, delta_y;

	delta_x = abs(currentnode->m_x - s->m_destination->m_x);
	delta_y = abs(currentnode->m_y - s->m_destination->m_y);
	return (delta_x + delta_y) * 10;
}

/* //////////////////////////////////////////////////////////////////////// */
/* End of Asearch.c */
/* //////////////////////////////////////////////////////////////////////// */

