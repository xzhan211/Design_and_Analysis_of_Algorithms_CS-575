#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct heap_node{
	char letter;
	int freq;
	int path;
	struct heap_node *left;
	struct heap_node *right;
	struct heap_node *selfAddr;

};

typedef struct heap_node node;
node nodes[31];
//build heap Q
void insertHeap(char l, int f, node *addr, int po){
	if(nodes[po].freq == 0){
		nodes[po].letter = l; 
		nodes[po].freq = f;
		nodes[po].selfAddr = addr;
	}else
		printf("insertHeap error\n");
}
//build heap Q
void insertHeapify(int po){
	int parentPo = po/2;
	if(parentPo == 0){
		parentPo = 1;
	}
	char letterTemp;
	int freqTemp;
	node *selfAddrTemp;
	if(nodes[po].freq < nodes[parentPo].freq){
		letterTemp = nodes[po].letter;
		freqTemp = nodes[po].freq;
		selfAddrTemp = nodes[po].selfAddr;

		nodes[po].letter = nodes[parentPo].letter;
		nodes[po].freq = nodes[parentPo].freq;
		nodes[po].selfAddr = nodes[parentPo].selfAddr;
		
		nodes[parentPo].letter = letterTemp;
		nodes[parentPo].freq = freqTemp;
		nodes[parentPo].selfAddr = selfAddrTemp;
		insertHeapify(parentPo);
		return;
	}
}
//build heap Q
void buildHeap(char *ls, int *fs){
	for(int i = 1; i<31; i++){
		if(*(fs+i) != 0){
			insertHeap(*(ls+i), *(fs+i), 0, i);
			insertHeapify(i);
		}
	}
}


void deleteMin(void){
	int n = 1;
	while(nodes[n].freq != 0){
		n++;
	}
	n--;
	nodes[1].letter = nodes[n].letter;
	nodes[1].freq = nodes[n].freq;
	nodes[1].selfAddr = nodes[n].selfAddr;
	nodes[n].letter = '\0';
	nodes[n].freq= 0;
	nodes[n].selfAddr= 0;
	n--;
	for(int i = 1; i<=n; i++){
		insertHeapify(i);	
	}	
}

node minBuffer;
void findMin(void){
	minBuffer.letter = nodes[1].letter; 
	minBuffer.freq = nodes[1].freq;
	minBuffer.selfAddr = nodes[1].selfAddr;
	deleteMin();
	return;
}

//traverse the tree, only for debug.
/*
void preorder(node *tree){
	if(tree) {
		printf("%c\n",tree->letter);
		preorder(tree->left);
		preorder(tree->right);
	}
}
*/

int main(int argc, char *argv[]){
	int charCounter = 1, numCounter = 1;
	char letters[31] = {'\0'};
	int freqs[31] = {0};

	//input parameters
    FILE *fp;
    char c;
    int line = 0;
    int num = 0;
    char charNum[10];
   	fp = fopen(*(argv+1),"r");
    while(1){
   		c = fgetc(fp);
       	if(feof(fp)){ 
        	break;
      	}
      	// 44 , / 13 return / 10 \n / 32 space
      	if(c == 44 || c == 10 || c == 13){
      		if(line == 1){
      			freqs[numCounter] = atoi(charNum);
	    		numCounter++;
      		}		
		
	      	for(int x = 0; x<10; x++){
	      		charNum[x] = 'a';
	      		num = 0;
	   		}
	   	}else if(c != 32){
	   		if(line == 0){
      		letters[charCounter] = c;
			charCounter++;
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
   	int inputCounter = 0;
	for(int i = 1; i < 31; i++){
		if(freqs[i] != 0){
			inputCounter++;
		}
	}

	buildHeap(letters, freqs);
	
	//only for debug
	/*
	printf("Heap node data: \n");
	for(int i = 1; i < 21; i++){
		if(nodes[i].freq != 0){
			printf("node letters[%d] >> %c\n", i, nodes[i].letter);
			printf("node freqs[%d] >> %d\n", i, nodes[i].freq);
		}
	}
	*/
	//build binary tree
	node *x, *y, *z;
	int counter = 1;
	for(int i = 1; i <= 30; i++){
		//read x
		findMin();
		if(minBuffer.letter != '\0' && minBuffer.freq != 0){
			x = (node *)malloc(sizeof(node));
			x->letter = minBuffer.letter;
			x->freq = minBuffer.freq;
			x->path = 0;
			x->left = 0;
			x->right = 0;
		}else if(minBuffer.letter == '\0' && minBuffer.freq != 0){
			x = minBuffer.selfAddr;
			x->path = 0;
		}
		//read y	
		findMin();
		if(minBuffer.letter != '\0' && minBuffer.freq != 0){
			y = (node *)malloc(sizeof(node));
			y->letter = minBuffer.letter;
			y->freq = minBuffer.freq;
			y->path = 1;
			y->left = 0;
			y->right = 0;
		}else if(minBuffer.letter == '\0' && minBuffer.freq != 0){
			y = minBuffer.selfAddr;
			y->path = 1;

		}else if(minBuffer.letter == '\0' && minBuffer.freq == 0){
			x->path = -1;
			break;
		}


		z = (node *)malloc(sizeof(node));
		z->letter = '\0';
		z->freq = x->freq + y->freq;
		z->left = x;
		z->right = y;
		z->selfAddr = z;
		z->path = -1;

		counter = 1;
		while(nodes[counter].freq != 0){
			counter++;
		}
		insertHeap(z->letter, z->freq, z->selfAddr, counter);
		insertHeapify(counter);
	}
	//debug
	//preorder(z);
	int k = 1;
	node *cur;
	printf("--huffman--\n");
	printf("letter  code\n");
	
	int outBuffer[31] = {-1};
	int outCounter = 0;

	while(k <= 35){
		if(z->right == 0 && z->left == 0)
			break;
		cur = z;
		outCounter = 0;
		for(int i = 0; i< 31; i++){
			outBuffer[i] = -1;
		}
		while(cur->right != 0 || cur->left != 0){
			if(cur->left !=0){
				if(((cur->left)->left == 0) && ((cur->left)->right == 0) 
					&& ((cur->left)->letter == '\0')){
					cur->left = 0;
					continue;
				}
				if(cur->left != 0){
					outBuffer[outCounter] = (cur->left)->path;
					outCounter++;
				}
				if((cur->left)->letter != '\0'){
					printf("%c       ", (cur->left)->letter);
					for(int i = 0; i< 31; i++){
						if(outBuffer[i] == -1){
							break;
						}
						printf("%d",outBuffer[i]);
					}
					printf("\n");
					cur->left = 0;
					break;
				}
				cur = cur->left;
			}else if(cur->right !=0){
				if(((cur->right)->left == 0) && ((cur->right)->right == 0) 
					&& ((cur->right)->letter == '\0')){
					cur->right = 0;
					continue;
				}
				if(cur->right != 0){
					outBuffer[outCounter] = (cur->right)->path;
					outCounter++;
				}
				if((cur->right)->letter != '\0'){
					printf("%c       ", (cur->right)->letter);
					for(int i = 0; i< 31; i++){
						if(outBuffer[i] == -1){
							break;
						}
						printf("%d",outBuffer[i]);
					}
					printf("\n");
					cur->right = 0;
					break;
				}
				cur = cur->right;
			}
		}
		k++;
	}
}






