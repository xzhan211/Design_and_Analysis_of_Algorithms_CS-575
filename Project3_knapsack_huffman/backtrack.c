#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


double maxprofit = 0;
int numItem = 0;
int number = 0;
double capacity = 0;
int profitCounter = 1, weightCounter = 1;
double profit[11] = {-1};
double weight[11] = {-1};
double include[11] = {-1};
double bestset[11] = {-1};
// note 0 is nothing.
struct binary_tree {
    double v_profit;
    double v_weight;
} node[11]; 
//use array to build tree, no linked list.

void sortItem(int n, double w[11], double p[11]){
  double unitProfit[n+1];
  for(int i = 1; i<= n; i++){
    unitProfit[i] = p[i] / w[i];
  }
  
  double maxBuffer = 0;
  int ptrBuffer = 0;
  double wBuffer = 0;
  double pBuffer = 0;
  for(int i = 1; i<n; i++){
    maxBuffer = unitProfit[i];
    ptrBuffer = i;
    for(int j = i+1; j <= n; j++){
      if(unitProfit[j] > maxBuffer){
        maxBuffer = unitProfit[j];
        ptrBuffer = j;
      }
    }

    if(i != ptrBuffer){
      unitProfit[ptrBuffer] = unitProfit[i];
      unitProfit[i] = maxBuffer;
      wBuffer = w[i];
      pBuffer = p[i];
      w[i] = w[ptrBuffer];
      p[i] = p[ptrBuffer];
      w[ptrBuffer] = wBuffer;
      p[ptrBuffer] = pBuffer;
    }  
  }
}

double KWF4(int i, double wt, double pt){
  double bound = pt;
  double bt = 0;
  while((wt < capacity) &&  i <= number){
    if((wt + node[i].v_weight)<=capacity){
      wt = wt + node[i].v_weight;
      bound = bound + node[i].v_profit;
    }else{
      bt = (double)(capacity - wt)/(double)node[i].v_weight;
      wt = capacity;
      bound = bound + node[i].v_profit * bt;
    }
    i++;
  }
  return bound;
}

int promising(int i, double wt, double pt){
  if(wt >= capacity){
    return 0;
  }
  double bound = KWF4(i+1, wt, pt);
  return (bound > maxprofit);
  
}

void knapsack(int i, double pt, double wt){
  //save better solution
  if((wt <= capacity) && (pt > maxprofit)){
    maxprofit = pt;
    numItem = i;
    for(int j = 0; j<=10; j++){
      bestset[j] = include[j];
    }
  }
  // recursion stop, if(0)
  if(promising(i, wt, pt)){
    include[i+1] = 1;
    knapsack(i+1, pt+profit[i+1], wt+weight[i+1]);
    include[i+1] = 0;
    knapsack(i+1, pt, wt);
  }
}


void Knapsack(void){
  numItem = 0;
  maxprofit = 0;
  knapsack(0,0,0);

}


int main(int argc, char *argv[]){


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

  sortItem(number, weight, profit);
  
  for(int i = 1; i<= number; i++){
    node[i].v_profit = profit[i];
    node[i].v_weight = weight[i];
  }
  
  Knapsack();  
  double totalWeight = 0;
  printf("--backtrack--\n");
  printf("select items:\n");

  for(int i = 0; i<=10; i++){
    if(bestset[i] == 1){
      printf("weight >> %f\n", weight[i]);
      printf("profit >> %f\n", profit[i]);
      totalWeight = totalWeight + weight[i];
    }
  }
  printf("\n");
  printf("total weight > %f\n",totalWeight);
  printf("total profit > %f\n",maxprofit);




}
