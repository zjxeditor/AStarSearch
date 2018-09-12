/* //////////////////////////////////////////////////////////////////////// */
/* File: board.h */
/* Description: define basic element for the game board include: Cpoint, Cnode, Cboard */
/* //////////////////////////////////////////////////////////////////////// */

#ifndef H_BOARD
#define H_BOARD

#include "base.h"

#define MAPX 30
#define MAPY 28

/* point struct */
struct Cpoint
{
	int x;
	int y;
};

/* cell for A* search */
struct Cnode
{
	struct Cnode* m_pParent;
	struct Cnode* m_next;
	int m_G;
	int m_F;
	int m_x;
	int m_y;
	bool m_openflag;
	bool m_closeflag;
	int m_timepro;
};

/* main board */
struct Cboard
{
	int m_xdis;	/* dimension */
	int m_ydis;
	struct Cnode* data[MAPX][MAPY];	/* used for A* search */
};

/* global variants */
extern int offset[4][2];		/* array for looking for around element */
extern int orgdata[MAPX][MAPY];
extern int recoverdata[MAPX][MAPY];

/* function declaration */
void setNode(struct Cnode* node, int x, int y);
void initializeBoardData(struct Cboard* board);
void resetBoardData(struct Cboard* board);
void boardPointClear(int x, int y);
void recoverOrgData();
void clearBoard(struct Cboard* board);
bool VerifyPos(struct Cboard* board, struct Cpoint pos);
bool Verify(struct Cboard* board, int x, int y);

#endif


/* //////////////////////////////////////////////////////////////////////// */
/* End of board.h */
/* //////////////////////////////////////////////////////////////////////// */

