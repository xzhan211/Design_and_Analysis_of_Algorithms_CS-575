#include<stdio.h>
#include <stdlib.h> // atof atoi

int count = 1;
/*
row, col: hole
por 1~4,poc 1~4: center square, 4 items. (each tile has 3 items)
k: 2^k * 2^k
size: 2^k, fix in first time
matrix[][]: original matrix
*/
void trominoTile(int row, int col, int por1, int poc1, int por2, int poc2, int por3, int poc3, int por4, int poc4, int k, int size, int matrix[][size]){
	int move = 1;
	int bufferK;
	if(k == 1){
		if(matrix[por1][poc1] != 0){
			matrix[por2][poc2] = count;
			matrix[por3][poc3] = count;
			matrix[por4][poc4] = count;
		}else if(matrix[por2][poc2] != 0){
			matrix[por1][poc1] = count;
			matrix[por3][poc3] = count;
			matrix[por4][poc4] = count;
		}else if(matrix[por3][poc3] != 0){
			matrix[por1][poc1] = count;
			matrix[por2][poc2] = count;
			matrix[por4][poc4] = count;
		}else if(matrix[por4][poc4] != 0){
			matrix[por1][poc1] = count;
			matrix[por2][poc2] = count;
			matrix[por3][poc3] = count;
		}
			count++;
			return;

	}else if(k>1){

		bufferK = k;
		bufferK = bufferK - 2;
			for(int i = 1; i <= bufferK; i++){
				move = move * 2;
			}
		
		if(row <= por1 && row <= por2 && row <= por3 && row <= por4 && col <= poc1 && col <= poc2 && col <= poc3 && col <= poc4){ //1
			
			matrix[por2][poc2] = count;
			matrix[por3][poc3] = count;
			matrix[por4][poc4] = count;
			count++;
			trominoTile(row, col, por1-move, poc1-move, por2-move, poc2-move, por3-move, poc3-move, por4-move, poc4-move, k-1, size,matrix);
			trominoTile(por2, poc2, por1-move, poc1+move, por2-move, poc2+move, por3-move, poc3+move, por4-move, poc4+move, k-1, size,matrix);
			trominoTile(por3, poc3, por1+move, poc1+move, por2+move, poc2+move, por3+move, poc3+move, por4+move, poc4+move, k-1, size,matrix);
			trominoTile(por4, poc4, por1+move, poc1-move, por2+move, poc2-move, por3+move, poc3-move, por4+move, poc4-move, k-1, size,matrix);
	

		}else if(row <= por1 && row <= por2 && row <= por3 && row <= por4 && col >= poc1 && col >= poc2 && col >= poc3 && col >= poc4){ //2
			
			matrix[por1][poc1] = count;
			matrix[por3][poc3] = count;
			matrix[por4][poc4] = count;
			count++;
			trominoTile(por1, poc1, por1-move, poc1-move, por2-move, poc2-move, por3-move, poc3-move, por4-move, poc4-move, k-1, size,matrix);
			trominoTile(row, col, por1-move, poc1+move, por2-move, poc2+move, por3-move, poc3+move, por4-move, poc4+move, k-1, size,matrix);
			trominoTile(por3, poc3, por1+move, poc1+move, por2+move, poc2+move, por3+move, poc3+move, por4+move, poc4+move, k-1, size,matrix);
			trominoTile(por4, poc4, por1+move, poc1-move, por2+move, poc2-move, por3+move, poc3-move, por4+move, poc4-move, k-1, size,matrix);
	

		}else if(row >= por1 && row >= por2 && row >= por3 && row >= por4 && col >= poc1 && col >= poc2 && col >= poc3 && col >= poc4){//3
			
			matrix[por1][poc1] = count;
			matrix[por2][poc2] = count;
			matrix[por4][poc4] = count;
			count++;
			trominoTile(por1, poc1, por1-move, poc1-move, por2-move, poc2-move, por3-move, poc3-move, por4-move, poc4-move, k-1, size,matrix);
			trominoTile(por2, poc2, por1-move, poc1+move, por2-move, poc2+move, por3-move, poc3+move, por4-move, poc4+move, k-1, size,matrix);
			trominoTile(row, col, por1+move, poc1+move, por2+move, poc2+move, por3+move, poc3+move, por4+move, poc4+move, k-1, size,matrix);
			trominoTile(por4, poc4, por1+move, poc1-move, por2+move, poc2-move, por3+move, poc3-move, por4+move, poc4-move, k-1, size,matrix);
	
			
		}else if(row >= por1 && row >= por2 && row >= por3 && row >= por4 && col <= poc1 && col <= poc2 && col <= poc3 && col <= poc4){//4
			
			matrix[por1][poc1] = count;
			matrix[por2][poc2] = count;
			matrix[por3][poc3] = count;
			count++;
			trominoTile(por1, poc1, por1-move, poc1-move, por2-move, poc2-move, por3-move, poc3-move, por4-move, poc4-move, k-1, size,matrix);
			trominoTile(por2, poc2, por1-move, poc1+move, por2-move, poc2+move, por3-move, poc3+move, por4-move, poc4+move, k-1, size,matrix);
			trominoTile(por3, poc3, por1+move, poc1+move, por2+move, poc2+move, por3+move, poc3+move, por4+move, poc4+move, k-1, size,matrix);
			trominoTile(row, col, por1+move, poc1-move, por2+move, poc2-move, por3+move, poc3-move, por4+move, poc4-move, k-1, size,matrix);
		}
	}
}
//Display result.
void showBoard_num(int len, int matrix[][len]){
	for(int i = 0; i< len; i++){
    	for(int j = 0; j< len; j++){
    		if(matrix[i][j] != -1)
    			printf("%3d ",matrix[i][j]);
    		else
    			printf("  X ");
    	}
    	printf("\n");
    	printf("\n");
    }
}

int main(int argc, char *argv[]){
	//input parameters
	int k = atoi(argv[1]);
    int row =  atoi(argv[2]);
    int col =  atoi(argv[3]);
    int size = 1;
    for(int i = 1; i <= k; i++){
    	size = size * 2;
    }
    int board[size][size];
    for(int i = 0; i<size; i++){
    	for(int j = 0; j<size; j++){
    		board[i][j] = 0;
    	}
    }
    //init board, -1 means hole. later will change to X.
    board[row][col] = -1;

    int por1,por2,por3,por4;
    int poc1,poc2,poc3,poc4;
    //initialization
    por1 = size/2 - 1;
    poc1 = size/2 - 1;

    por2 = size/2 - 1;
    poc2 = size/2;

    por3 = size/2;
    poc3 = size/2;

    por4 = size/2;
    poc4 = size/2 - 1;
    
	trominoTile(row, col, por1, poc1, por2, poc2, por3, poc3, por4, poc4, k ,size, board);
	
    showBoard_num(size, board);
    
}