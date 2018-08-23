#include <stdio.h>
#include <string.h>
#include <stdlib.h>




int main(int argc, char *argv[]){
	//input parameters
	FILE *fp;
    int c;
    fp = fopen(*(argv+1),"r");
    int row = 0;
    int countComma = 0;
	int c_buffer;
	char charNum[3];
	int num = 0;
	int i,j;
	i = 0;
	j = 0;
	//check the size of the input matrix
	while(1){
		c_buffer = fgetc(fp);
      	if(c_buffer == 10){ 
         	break;
      	}
      	if(c_buffer==44)
      		countComma++;
    }
    fclose(fp);
   	//input matrix size is row
    row = countComma + 1;
    int matrix[row][row];

    FILE *fp1;
   	fp1 = fopen(*(argv+1),"r");
   	//store the data from csv file to matrix[][]
   	while(1){
   		c = fgetc(fp1);
       	if(feof(fp1)){ 
        	break;
      	}
      	//printf("c = %c\n", c);
      	if(c == 44 || c == 10){
      		matrix[i][j] = atoi(charNum);
      		for(int x = 0; x<3; x++){
      			charNum[x] = 'a';
      		}
      		num = 0;

      	}
  
      	if(num < 3 && c != 44 && c !=10){
      		charNum[num] = c;
      		num++;
      	}

	    if(c == 10){ //return sign
	    	if(i<row){
	    		i++;
	    		j = 0;
	    	}
	    }else if(c==44){
	    	if(j<row)
	    		j++;
	    }     	
   	}
   	fclose(fp1);
   	//for debug, check input data.
   	/*
   	for(int x = 0; x<row; x++){
   		for(int y = 0; y<row; y++){
   			printf(" %-3d ", matrix[x][y]);
   		}
   		printf("\n");
   	}
   	printf("\n");
   	printf("\n");
	*/
	
   	//Floyd's Algorithm

   	for(int k = 0; k < row; k++){
   		for(int i = 0; i < row; i++){
   			for(int j = 0; j<row; j++){
   				if(matrix[i][j]>matrix[i][k]+matrix[k][j]){
   					matrix[i][j] = matrix[i][k] + matrix[k][j];
   				}
   			}
   		}
   	}
   	// output the result: distance matrix
   	for(int x = 0; x<row; x++){
   		for(int y = 0; y<row; y++){
   			printf(" %-3d ", matrix[x][y]);
   		}
   		printf("\n");
   	}	
   	
}





