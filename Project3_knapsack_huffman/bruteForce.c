#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]){
	int number = 0;
	double capacity = 0;
	int profitCounter = 0, weightCounter = 0;
	double profit[10] = {-1};
	double weight[10] = {-1};

	//input parameters
    FILE *fp;
    char c;
    int line = 0;
    int num = 0;
    char charNum[10];
   	fp = fopen(*(argv+1),"r");
   	//store the data from csv file to matrix[][]
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
      			capacity = (double)atoi(charNum);
      		else if(line == 2){
      			profit[profitCounter] = (double)atoi(charNum);
				profitCounter++;
      		}else if(line == 3){
      			weight[weightCounter] = (double)atoi(charNum);
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
   	//calculate every case, total loopCounter times
	int loopCounter = 1;
	for(int i = 1; i<=number; i++){
		loopCounter = loopCounter * 2;
	}
	loopCounter = loopCounter - 1;

	int bits = 1;
	int mask = 1;
	int firstBit = 0;
	double bufferProfit = 0;
	double bufferWeight = 0;
	double maxProfit = 0;
	double maxWeight = 0;
	int counter = 0;
	double selectItemProfit[10];
	double selectItemWeight[10];
	double bufferItemProfit[10];
	double bufferItemWeight[10];
	
	while(counter <= loopCounter){
		bufferWeight = 0;
		bufferProfit = 0;
		for(int i = 0; i< number; i++){
			bufferItemProfit[i] = -1;
			bufferItemWeight[i] = -1;
		}
		for(int i = 0; i<number; i++){
			//count bit, to calculate every case in 0~loopCounter
			firstBit = (counter >> i) & mask;
			if(firstBit == 1){
				bufferProfit = bufferProfit + profit[i];
				bufferWeight = bufferWeight + weight[i];
				bufferItemProfit[i] = profit[i];
				bufferItemWeight[i] = weight[i];
			}
		}
		if(bufferWeight <= capacity && bufferProfit >= maxProfit){
			maxProfit = bufferProfit;
			maxWeight = bufferWeight;
			for(int i = 0; i< number; i++){
				selectItemProfit[i] = bufferItemProfit[i];
				selectItemWeight[i] = bufferItemWeight[i];
			}
		}
		counter++;
	}
	printf("--brute force--\n");
	printf("select item:\n");
	for(int i = 0; i < number; i++){
		if(selectItemProfit[i] != -1){
			printf("weight >> %f\n", selectItemWeight[i]);
			printf("profit >> %f\n", selectItemProfit[i]);
		}
	}
	printf("\n");
	printf("total weight >> %f\n", maxWeight);
	printf("total profit >> %f\n", maxProfit);
}