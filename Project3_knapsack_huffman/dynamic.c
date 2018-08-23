#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]){
	int number = 0;
	int capacity = 0;
	int profitCounter = 0, weightCounter = 0;
	int profit[15] = {-1};
	int weight[15] = {-1};

	//input parameters
  FILE *fp;
  char c;
  int line = 0;
  int num = 0;
  char charNum[10];
 	fp = fopen(*(argv+1),"r");
 	//store the data from csv file
  while(1){
 		c = fgetc(fp);
     	if(feof(fp)){ 
      	break;
    	}
    	// 44 , / 13 return / 10 \n / 32 space
    	if(c == 44 || c == 10 || c == 13){

    		if(line == 0)
    			number = atoi(charNum);
    		else if(line == 1)
    			capacity = atoi(charNum);
    		else if(line == 2){
    			profit[profitCounter] = atoi(charNum);
			    profitCounter++;
    		}else if(line == 3){
    			weight[weightCounter] = atoi(charNum);
    		  weightCounter++;
    		}		
	
      	for(int x = 0; x<10; x++){
      		charNum[x] = 'a';
      		num = 0;
   		}
   	}  
    	if(num < 10 && c != 44 && c !=10 && c != 32 && c != 13){
    		charNum[num] = c;
    		num++;
    	}
    	if(c == 10 || c == 13){ //return sign
    	line++;
    }    		    
 	}
 	fclose(fp);


 	int B[number+1][capacity+1];
 	for(int i = 0; i <= number; i++){
 		for(int j = 0; j<= capacity; j++){
 			B[i][j] = 0;
 		}
 	}

 	int totalWeight = 0;
 	int totalProfit = 0;
 	for(int k = 1; k <= number; k++){
 		for(int w = 1; w <= capacity; w++){
 			if((weight[k-1] <= w) && ((B[k-1][w-weight[k-1]] + profit[k-1]) > B[k-1][w])){
 				B[k][w] = B[k-1][w-weight[k-1]] + profit[k-1];
 				if(totalProfit != B[k][w]){
 					totalProfit = B[k][w];
 					totalWeight = w;
 				}
 			}else{
 				B[k][w] = B[k-1][w];
 			}
 		}
 	}
	printf("--dynamic--\n");
  printf("select item:\n");
	int n = number;
  int m = capacity;
	while(B[n][m] != 0){
		if(B[n][m] == B[n-1][m]){
			n = n - 1;
		}else if((m-weight[n-1]>=0) && (B[n][m] == (B[n-1][m-weight[n-1]] + profit[n-1]))){
			printf("weight >> %d\n", weight[n-1]);
			printf("profit >> %d\n", profit[n-1]);
			m = m - weight[n-1];
			n = n - 1;
		}
	}
  printf("\n");
  printf("total weight >> %d\n", totalWeight);
  printf("total profit >> %d\n", B[number][capacity]);
}



