#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//tree node
struct binary_tree {
    int data;
    struct binary_tree * left;
    struct binary_tree * right;
};  

typedef struct binary_tree node;
//root node
node * origin_node;
//bulid tree
void insert(node ** tree, int val) {
    node * temp = NULL;
    if(!(*tree)) {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = val;
        *tree = temp;
        return ;
    }
    
    if (val < (*tree)->data) {
        insert(&(*tree)->left,val);
    }else if (val > (*tree)->data) {
        insert(&(*tree)->right,val);
    }
}
//delete tree, free() memory
void deltree(node * tree) {
    if(tree) {
        deltree(tree->left);
        deltree(tree->right);
        free(tree);
    }
}


//pick out the node from weight matrix
void printTree (int root, int first, int last, int length, int matrix[][length]){
	int rootL, rootR;
	int firstL, lastL;
	int firstR, lastR;
	//printf("node = %d\n", root);
	insert(&origin_node, root);


	firstL = first;
	lastL = root - 1;
	rootL = matrix[firstL][lastL];
	if(firstL <= lastL && rootL != 0){
		printTree(rootL, firstL, lastL, length, matrix);
	}
	
	firstR = root + 1;
	lastR = last;
	rootR = matrix[firstR][lastR];
	if(firstR <= lastR && rootR != 0){
		printTree(rootR, firstR, lastR, length, matrix);

	}
}
//just for debug, traverse tree nodes by pre-order.
/*
void print_preorder(node * tree) {
    if(tree) {
        printf("%d\n",tree->data);
        print_preorder(tree->left);
        print_preorder(tree->right);
    }
}
*/
//set FIFO size
node *queue[1000];
//traverse tree nodes by level.
void printTreeByLevel(node * tree, int num){
	int head = 0;
	int tail = 1;
	int nextline = 0;
	int count = 0;
	int depth = 1;
	queue[head] = tree;
	if(tree != NULL)
		printf("depth 0: ");
	if(tree == NULL)
		return;
	while(head != tail && num != count){
		if(queue[head] != NULL){
			queue[tail] = queue[head]->left;
		}else{
			queue[tail] = NULL;
		}
		if(queue[head] != NULL){
			queue[tail+1] = queue[head]->right;
		}else{
			queue[tail+1] = NULL;
		}
		tail = tail + 2;
		if(queue[head] != NULL){
			printf("%d, ",queue[head]->data);
			count = count + 1;
		}else{
			printf("0, ");
		}

		if(head == nextline){
			printf("depth %d: ", depth);
			depth =  depth + 1;
			nextline = tail - 1;
		}
		head = head + 1;
	}
	printf("\n");	
} 



int main (int argc, char * argv[]){

	//read input
    int n = atoi(argv[1]);
    float p[n+1];
    p[0] = 0;
    for(int i = 0; i<n; i++){
    	p[i+1] = atof(argv[i+2]);
    }

    //p[0] is not probablity, just use for sitting in p0 position.
    int i = 0;
    int j = 0;
    int k = 0;
    int diagonal = 0;
    float A[n+2][n+1];
    int R[n+2][n+1];

    for(int x = 0; x<n+2; x++){
    	for(int y = 0; y<n+1; y++){
    		A[x][y] = 0;
    		R[x][y] = 0;
    	}
    }

    for(int x = 1; x <= n; x++){
    	A[x][x-1]=0;
    	R[x][x-1]=0;
    	A[x][x] = p[x];
    	R[x][x] = x;
    }
    
    float buffer;
    float min = 1000;
    float pSum = 0;
    for(diagonal=1; diagonal<=n-1;diagonal++){
    	for(i = 1; i<= n - diagonal; i++){
    		j = i + diagonal;
    		for(k = i; k<=j; k++){
    			buffer = A[i][k-1] + A[k+1][j];
    			if(buffer < min){
    				min = buffer;
    				R[i][j] = k;
    			}
    		}
    		for(int x = i; x<=j; x++){
    			pSum = pSum + p[x];
    		}
    		A[i][j] = min + pSum;
    		pSum = 0; 
    		min = 1000;

    	}
    }
    //for debugging, output the weight & R[][]
    /*
	printf("The min avg is : %f\n", A[1][n]); 
	for(int x = 0; x < n+2; x++){
		for(int y = 0; y<n+1; y++){
			printf("%d ",R[x][y]);
		}
		printf("\n");
	}
	*/
	printTree (R[1][n], 1, n, n+1,R);
	printTreeByLevel(origin_node,n);
	deltree(origin_node);

}
	
	
   	
   	