#include <stdio.h>
#define DEBUG
#define COLUM   8
#define ROW     8


int turn = 1;
int matrix[COLUM][ROW];
int temp1 = 0;
int temp2 = 0;
int mark1 = 0x4F;
int mark2 = 0x58;
int markt;
int i, j, k, l;       
int finish   = 0;
int numStar  = 0;    
int flag_f   = 0;
int flag_put = 0;
int score_a  = 0;
int score_b  = 0;

void display(void);
void reverse(int temp1, int temp2, int mode, int markt);
int  judgePut(int temp1, int temp2, int markt);
int  ifputtable(int markt);
void scoreing(void);
void finish_fase(void);

int main(void){
	
   //Initialize matrix.
	for(i=0; i<=COLUM-1; i++){
		for(j=0; j<=COLUM-1; j++){
			matrix[i][j] = 0x2A;
		}
	}
	matrix[3][3] = mark1;
	matrix[4][4] = mark1;	
	matrix[3][4] = mark2;
	matrix[4][3] = mark2;
	
	
   /* main routine */
	while(!finish){   
   		markt  = (turn) ? mark1 : mark2;      // judge whose turn
		scoreing();                          // calculate temporary socre

		/* reserch whether exist putable area or not */
		if(score_a == 0 || score_b == 0){
			finish_fase();
			finish = 1;
			continue;
		}

		numStar = 0;
		for(i=0; i<=ROW-1; i++){
			for(j=0; j<COLUM; j++){
				if(matrix[i][j] == 0x2A){
					numStar += 1;
				}
			}
		}
		if(numStar == 0){
			finish_fase();
			finish = 1;
			continue;
		}


		if(!ifputtable(markt)){
			printf("You cannot put any place! Pass this turn.\n");
			turn = (turn) ? 0 : 1;
			continue;
		}
		
		/* display the game board */
		display();
		
		/* input */
		if(turn){
			printf("Player A's Turn! Select marking place!\n");
		}else{
			printf("Player B's Turn! Select marking place!\n");
		}
		printf("ROW:");
		scanf("%d", &temp1);
		printf("\nCOLUM:");
		scanf("%d", &temp2);
		printf("\n");
		
        /* judge whether puttable or not and put character */
		if(temp1 > COLUM || temp2 > ROW){
			printf("You selected wrong coordinate!\n");
			continue;
		}
		flag_put = judgePut(temp1, temp2, markt);
		if(!flag_put){
			printf("You cannot mark that placeaaa!\n");
			continue;
		}
		if(matrix[temp1][temp2] == '*'){
			matrix[temp1][temp2] = markt;
		} else{
			printf("You cannot mark that place!\n");
			continue;
		}
		
		
	    /* reverse fase */
		for (i=0; i<8; i++){
			reverse(temp1, temp2, i, markt);
		}
		
        /* turn change */
		turn = (turn) ? 0 : 1;
		printf("change the turn!");
	}

	return 0;
}

void display(void){
    /* Display matrix */
	printf("  ");
	for(i=0; i<=COLUM-1; i++){
		if(i<10){
			printf(" %d", i);
		} else {
			printf("%d", i);
		}
	}
	printf("\n---");
	
	for(i=0; i<=COLUM-1; i++){
		printf("--", i);
	}
	printf("\n");
	
	for(i=0; i<=COLUM-1; i++){
		printf("   ");
		for(j=0; j<=COLUM-1; j++){
			putchar(matrix[i][j]);
			printf(" ");
		}
		printf("| %d\n", i);
	}
	putchar('\n');
}

void reverse(int temp1, int temp2, int mode, int markt)
{
	/* reverse enemy's mark */
	int symbol1;
	int symbol2;
	int y = 1;
	int row;
	int colum; 
	
	switch(mode){
		case 0: // direction "6"
		symbol1 = 1;
		symbol2 = 0;
		break;
		case 1: // direction "9"
		symbol1 = 1;
		symbol2 = 1;
		break;
		case 2: // direction "8"
		symbol1 = 0;
		symbol2 = 1;
		break;
		case 3: // direction "7"
		symbol1 = -1;
		symbol2 = 1;
		break;
		case 4: // direction "4"
		symbol1 = -1;
		symbol2 = 0;
		break;
		case 5: // direction "1"
		symbol1 = -1;
		symbol2 = -1;
		break;
		case 6: // direction "2"
		symbol1 = 0;
		symbol2 = -1;
		break;
		case 7: // direction "3"
		symbol1 = 1;
		symbol2 = -1;
		break;
		default:
		symbol1 = 0;
		symbol2 = 0;
		break;
	}	
	
	row   = temp1 + symbol1 * y;
	colum = temp2 + symbol2 * y;
	
	while(row >= 0 && colum >= 0 && row < ROW && colum < COLUM) {
		if(matrix[row][colum] == 0x2A || matrix[row][colum] == markt){
			break;
		}
		
		if(matrix[row][colum] != 0x2A && matrix[row][colum] != markt){
			y += 1;
			row   = temp1 + symbol1 * y;
			colum = temp2 + symbol2 * y;
			if(matrix[row][colum] == markt){
				for(; y>=1; y--){
					row   = temp1 + symbol1 * y;
					colum = temp2 + symbol2 * y;
					matrix[row][colum] = markt;
				}
				break;
			}
			continue;
		}

	}
}

int judgePut(int temp1, int temp2, int markt)
{
	/* Judge selected place puttable or not. 
	   This function is nealy equal to 'reverse', 
	   There is still room for improvement.  */
	
	int symbol1;
	int symbol2;
	int mode;
	int y;
	int row;
	int colum; 
	int flag = 0;
	
	for(mode=0; mode<8; mode++){
		y = 1;
		
		switch(mode){
			case 0: // direction "6"
			symbol1 = 1;
			symbol2 = 0;
			break;
			case 1: // direction "9"
			symbol1 = 1;
			symbol2 = 1;
			break;
			case 2: // direction "8"
			symbol1 = 0;
			symbol2 = 1;
			break;
			case 3: // direction "7"
			symbol1 = -1;
			symbol2 = 1;
			break;
			case 4: // direction "4"
			symbol1 = -1;
			symbol2 = 0;
			break;
			case 5: // direction "1"
			symbol1 = -1;
			symbol2 = -1;
			break;
			case 6: // direction "2"
			symbol1 = 0;
			symbol2 = -1;
			break;
			case 7: // direction "3"
			symbol1 = 1;
			symbol2 = -1;
			break;
		}	

		if(matrix[temp1][temp2] != 0x2A ){
				break;
		}
		
		row   = temp1 + symbol1 * y;
		colum = temp2 + symbol2 * y;
		
		while(row >= 0 && colum >= 0 && row < ROW && colum < COLUM) {
			if(matrix[row][colum] == 0x2A || matrix[row][colum] == markt){
				break;
			}
			
			if(matrix[row][colum] != 0x2A && matrix[row][colum] != markt){
				y += 1;
				row   = temp1 + symbol1 * y;
				colum = temp2 + symbol2 * y;
				if(matrix[row][colum] == markt){
#ifdef DEBUG
					printf("markable place: \n");
					printf("(%d, %d)\n", temp1, temp2);
#endif
					flag = 1;
					break;
				}
				continue;
			}
		}
	}
	return flag;
}

int ifputtable(int markt){
	/* reseach are there puttable area. */
	int i, j;
	int rtn = 0;
	for(i=0; i<ROW; i++){
		for(j=0; j<COLUM; j++){
			if (judgePut(i, j, markt)){
				rtn = 1;
			}
		}
	}
	return rtn;

}

void scoreing(void){
	/* calculate temporaly score. 
	   score is "total number of get place from start to finish".
	*/

	for(i=0; i<ROW; i++){
		for(j=0; j<COLUM; j++){
			if(matrix[i][j] == mark1){
				score_a += 1;
			} else if( matrix[i][j] == mark2){
				score_b += 1;
			}
		}
	}
	
}

void finish_fase(void){
	/* finish fase */ 
	printf("game over.\n");
	printf("Player A's score : %d\n", score_a);
	printf("Player B's score : %d\n", score_b);
	
	if(score_a > score_b){
		printf("Player A won!\n");
	} else {
		printf("Player B won!\n");
	}
	finish = 1;
	display();
}
