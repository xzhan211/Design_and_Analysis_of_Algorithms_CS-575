#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define nameLength 30
#define teleLength 30
#define backupLenth 200
#define amplifier 2
char buffer[nameLength];
char recover[nameLength];
int total_length;
int total_left;
int total_right;
int positive;
int negative;
char insertName[nameLength];
char insertTele[teleLength];
int arraylength;
char (*name)[nameLength];
char (*tele)[teleLength];




void create(char filePath[] ){
	FILE *fp;
    int c;
    fp = fopen(filePath,"r");
    int num_row = 0;
    int name_col = 0;
    int tele_col = 0;
    int lock = 0;
    int filter = 0;
    int countComma = 0;
	int c_buffer;

	while(1){
		c_buffer = fgetc(fp);
      	if(feof(fp)){ 
         	break;
      	}
      	if(c_buffer==44)
      		countComma++;
    }
    fclose(fp);
    
    name = (char (*)[nameLength])malloc(sizeof(char) * (nameLength * countComma * amplifier + backupLenth));
    tele = (char (*)[teleLength])malloc(sizeof(char) * (teleLength * countComma * amplifier + backupLenth));
    /* //reference
    printf(" : %-30s\n", *name);
    printf(" : %-30s\n", *(name+1));
   	printf(" : %c\n", (*name)[6]);
    printf(" : %c\n", (*(name+1))[6]);
	*/
   	FILE *fp1;
   	fp1 = fopen(filePath,"r");
    while(1)
    {
       	c = fgetc(fp1);
       	if(feof(fp1))
       	{ 
        	break;
      	}
      	if((filter==1)||((c != 32)&&(c != 48)&&(c != 49)&&(c != 50)&&(c != 51)&&(c != 52)&&(c != 53)&&(c != 54)&&(c != 55)&&(c != 56)&&(c != 57))){ // 0~9
	      	if(c == 44) // 44: ascII ","
	        	lock = 1;

	      	if(c == 10){ // return sign
	        	name_col = 0;
	         	tele_col = 0;
	         	num_row = num_row + 1;
	         	lock = 0;
	         	filter = 0;

	      	}
	      	if((lock == 0)&&(c != 10)){ // avoid to save return sign
	        	(*(name+num_row))[name_col] = (char)c;
	        	name_col = name_col + 1;
	        	filter = 1;
	      	}

	      	if((lock == 1)&&(c != 44)&&(c != 32)&&(c != 13)){ // 44: ","; 32:" "; 13: CR
	        	(*(tele+num_row))[tele_col] = (char)c;
	         	tele_col = tele_col + 1;
	         	filter = 1;
	      	}
	    }
   	}
   	fclose(fp1);
}

/*---------------------------------------------------------------*/
//QS combine

void quickSortCombine(char l_name_list[][nameLength], char r_name_list[][nameLength], char o_name_list[][nameLength], char l_tele_list[][teleLength], char r_tele_list[][teleLength], char o_tele_list[][teleLength], int l_len, int r_len, int start_po, int o_length, char name_pivot_value[nameLength], char tele_pivot_value[teleLength]){
	
	char tele_buffer[teleLength];
	char name_buffer[nameLength];
	strcpy(tele_buffer,tele_pivot_value);
	strcpy(name_buffer,name_pivot_value);


	for( int i = start_po; i < (o_length + start_po); i++){
		if( (i - start_po) < l_len){
			strcpy(o_tele_list[i], l_tele_list[i-start_po]);
			strcpy(o_name_list[i], l_name_list[i-start_po]);
		}else if ((i - start_po) == l_len){
			strcpy(o_tele_list[i], tele_buffer); //note!!!
			strcpy(o_name_list[i], name_buffer); //note!!!
		}else {
			strcpy(o_tele_list[i], r_tele_list[i-start_po-l_len-1]);
			strcpy(o_name_list[i], r_name_list[i-start_po-l_len-1]);
		}
	}
}

/*---------------------------------------------------------------*/
//QS

void quickSort(char name_list[][nameLength], char tele_list[][teleLength], int start, int length){
	if(length >= 2){
		int pivot;
		srand(time(0));
	    int r = rand(); 
	    pivot =r % (length-1) + start;
		int llen = 0;
	    int rlen = 0;
	    char tele_llist[length][teleLength];
	    char tele_rlist[length][teleLength];
	    char name_llist[length][nameLength];
	    char name_rlist[length][nameLength];
	    char *name_pivot = name_list[pivot];  //note!!!
	    char *tele_pivot = tele_list[pivot];  //note!!!

	    for(int i = start; i < start + length; i++){
	    	if(i != pivot){
	    		if(strcmp(*(tele_list+i), *(tele_list+pivot))<0){
	    			strcpy(tele_llist[llen], *(tele_list+i));
	    			strcpy(name_llist[llen], *(name_list+i));
	    			llen++;
	    		}else if(strcmp(*(tele_list+i), *(tele_list+pivot))>0){
	    			strcpy(tele_rlist[rlen], *(tele_list+i));
	    			strcpy(name_rlist[rlen], *(name_list+i));
	    			rlen++;
	    		}
	    	}
	    } 
	    quickSort(name_llist, tele_llist, 0, llen);
	    quickSort(name_rlist, tele_rlist, 0, rlen);
	    quickSortCombine(name_llist, name_rlist, name_list, tele_llist, tele_rlist, tele_list, llen, rlen, start, length,name_pivot,tele_pivot);
	}
}

/*---------------------------------------------------------------*/

void merge(char l_name_list[][nameLength], char r_name_list[][nameLength], char o_name_list[][nameLength], char l_tele_list[][teleLength], char r_tele_list[][teleLength], char o_tele_list[][teleLength], int o_length, int l_len, int r_len){

    int lp = 0;
    int rp = 0;

    for(int i = 0; i<o_length; i++){
        if((lp<l_len)&&(rp<r_len)){
            if(strcmp(l_name_list[lp], r_name_list[rp])<=0){
                strcpy(o_name_list[i], l_name_list[lp]);
                strcpy(o_tele_list[i], l_tele_list[lp]);
                lp++;
            }
            else{
                strcpy(o_name_list[i], r_name_list[rp]);
                strcpy(o_tele_list[i], r_tele_list[rp]);
                rp++;
            }  
        }else if((lp>=l_len)&&(rp<r_len)){
            strcpy(o_name_list[i], r_name_list[rp]);
            strcpy(o_tele_list[i], r_tele_list[rp]);
            rp++;
        }else if((rp>=r_len)&&(lp<l_len)){
            strcpy(o_name_list[i], l_name_list[lp]);
            strcpy(o_tele_list[i], l_tele_list[lp]);
            lp++;
        }
    }
}

/*---------------------------------------------------------------*/

void mergeSort(char name_list[][nameLength] , char tele_list[][teleLength]  , int length){
    if(length >= 2){  //termination condition
        int llen = length/2;
        int rlen = length - length/2;

        char llist_name[llen][nameLength];
        char llist_tele[llen][teleLength];
        char rlist_name[rlen][nameLength];
        char rlist_tele[rlen][teleLength];

        for(int i=0;i<llen;i++){
            strcpy(llist_name[i], *(name_list+i));
            strcpy(llist_tele[i], *(tele_list+i));
        }
    
        for(int i=0;i<rlen;i++){
            strcpy(rlist_name[i], *(name_list+i+llen));
            strcpy(rlist_tele[i], *(tele_list+i+llen));
        }

        mergeSort(llist_name, llist_tele, llen);
        mergeSort(rlist_name, rlist_tele, rlen);
        merge(llist_name, rlist_name, name_list, llist_tele, rlist_tele, tele_list, length, llen, rlen);
    	
    }
}



/*---------------------------------------------------------------*/

void sortDirectory(){
	int length = 0;
	while(1){
		if((*(name+length))[0] == '\0'){
			break;
		}
		length++;
	}
	mergeSort(name,tele,length);
    int start_position;
    int same_length = 1; // means no two elements are same
    int same_flag = 0;

    for (int i = 0; i<(length-1); i++){
    	if (strcmp(*(name+i), *(name+i+1)) == 0){
    		if(same_length == 1){
    			start_position = i;
    		}
    		same_length++;
    		same_flag = 1;
    	}else{
    		if(same_length > 1){
			quickSort(name, tele, start_position, same_length);    			
    		}
    		same_flag = 0;
    		start_position = 0;
    		same_length = 1;
    	}
    }
}

/*---------------------------------------------------------------*/

void BS(int l_value, int r_value, int length, char keyword[nameLength]){
	int n;
	int p;
	int n_flag;
	int p_flag;
	if(length > 1){
		int len = length/2;
		if(strcmp(name[len+l_value], keyword) == 0){
			printf("Location >> %d\n", len+l_value);
			printf("Name >> %s     Phone >> %s\n", name[len+l_value],tele[len+l_value]);
			n = 1;
			p = 1;
			n_flag = 1;
			p_flag = 1;
			while((n_flag == 1) || (p_flag == 1)){
				if(((len+l_value+p) <= total_right+1) && (p_flag == 1)){
					if(strcmp(name[len+l_value], name[len+l_value+p]) == 0){
						printf("Location >> %d\n", len+l_value+p);
						printf("Name >> %s     Phone >> %s\n", name[len+l_value+p],tele[len+l_value+p]);
						p++;
					}else{
						p_flag = 0;
					}
				}
				if(((len+l_value-n) >= total_left-1) && (n_flag == 1)){
					if(strcmp(name[len+l_value], name[len+l_value-n]) == 0){
						printf("Location >> %d\n", len+l_value-n);
						printf("Name >> %s     Phone >> %s\n", name[len+l_value-n],tele[len+l_value-n]);
						n++;
					}else{
						n_flag = 0;
					}
				}
			}
		}else if(strcmp(name[len+l_value], keyword )> 0){
			r_value = r_value - (length - len); // a little bit confusion 
			BS(l_value, r_value, len, keyword);
		}else if(strcmp(name[len+l_value], keyword )< 0){
			l_value = l_value + len + 1; // a little bit confusion
			BS(l_value, r_value, length-len-1, keyword);
		}
	}else if((length == 1)||(length == 0)){
		if ((length == 1)&&(strcmp(name[l_value],keyword) == 0)){
			printf("Location >> %d\n", l_value);
			printf("Name >> %s     Phone >> %s\n", name[l_value], tele[l_value]);
			n = 1;
			p = 1;
			n_flag = 1;
			p_flag = 1;
			while((n_flag == 1) || (p_flag == 1)){
				if(((l_value+p) <= total_right+1) && (p_flag == 1)){
					if(strcmp(name[l_value], name[l_value+p]) == 0){
						printf("Location >> %d\n", l_value+p);
						printf("Name >> %s     Phone >> %s\n", name[l_value+p],tele[l_value+p]);
						p++;
					}else{
						p_flag = 0;
					}
				}
				if(((l_value-n) >= total_left-1) && (n_flag == 1)){
					if(strcmp(name[l_value], name[l_value-n]) == 0){
						printf("Location >> %d\n", l_value-n);
						printf("Name >> %s     Phone >> %s\n", name[l_value-n],tele[l_value-n]);
						n++;
					}else{
						n_flag = 0;
					}
				}
			}
		}else{
			printf("\n");
			printf(" >> Name not found.\n");
		}
	}
}


/*---------------------------------------------------------------*/

void searchDirectory(char name_buffer[nameLength]){
	int len = total_length;
	int left = 0;
	int right;
	if(len>0){
		right = len - 1;
	}else
		right = 0;
	
	BS(left, right, len, name_buffer);
} 

/*---------------------------------------------------------------*/

void deleteBS(int l_value, int r_value, int length, char keyword[nameLength]){
	int p;
	int p_flag;
	if(length > 1){
		int len = length/2;
		if(strcmp(name[len+l_value], keyword) == 0){
			p = 1;
			p_flag = 1;
			while(p_flag == 1){
				if(((len+l_value+p) <= total_right+1) && (p_flag == 1)){
					if(strcmp(name[len+l_value], name[len+l_value+p]) == 0){
						p++;
					}else{
						p_flag = 0;
						int move_count1 = len+l_value+p-1;
						for(int i = move_count1; i < total_length ; i++){
							strcpy(name[i],name[i+1]);
							strcpy(tele[i],tele[i+1]);
						}
						total_length--;
						if(total_length > 0){
							total_right--;
						}else if(total_length == 0){
							total_right = 0;
						}
					}
				}
			}
		}else if(strcmp(name[len+l_value], keyword )> 0){
			r_value = r_value - (length - len); 
			deleteBS(l_value, r_value, len, keyword);
		}else if(strcmp(name[len+l_value], keyword )< 0){
			l_value = l_value + len + 1;
			deleteBS(l_value, r_value, length-len-1, keyword);
		}
	}else if((length == 1)||(length == 0)){
		if ((length == 1)&&(strcmp(name[l_value],keyword) == 0)){	
			p = 1;
			p_flag = 1;
			while(p_flag == 1){
				if(((l_value+p) <= total_right+1) && (p_flag == 1)){
					if(strcmp(name[l_value], name[l_value+p]) == 0){
						p++;
					}else{
						p_flag = 0;
						int move_count2 = l_value+p-1;
						for(int i = move_count2; i < total_length ; i++){
							strcpy(name[i],name[i+1]);
							strcpy(tele[i],tele[i+1]);
						}
					total_length--;
					if(total_length > 0){
							total_right--;
						}else if(total_length == 0){
							total_right = 0;
						}
					}
				}
			}
		}else
			printf(">> unable to delete as entry not found.\n");
	}
}





/*---------------------------------------------------------------*/

void deleteEntry(char name_buffer[nameLength]){
	int len = total_length;
	int left = 0;
	int right;
	if(len > 0){
		right = len - 1;	
	}else if(len == 0){
		right = 0;
	}
	
	deleteBS(left, right, len, name_buffer);
}

/*---------------------------------------------------------------*/

void insertBS(int l_value, int r_value, int length, char keyword[nameLength], char phone[teleLength]){
	if(length > 1){
		int len = length/2;
		if((strcmp(name[len+l_value], keyword) == 0)&&(strcmp(tele[len+l_value], phone) == 0)){
			printf("entry already exist in the directory\n");
		}else if(strcmp(name[len+l_value], keyword )>= 0){  // keyword less than middle value
			r_value = r_value - (length - len); // finally, r_value will equal l_value. So in final insertBS, length = 0, no need compared anymore.
			insertBS(l_value, r_value, len, keyword, phone);
		}else if(strcmp(name[len+l_value], keyword )< 0){ // keyword large than middle value
			l_value = l_value + len + 1; // finally, l_value will larger than r_value. So final insertBS, length = 0, no need compared anymore.
			insertBS(l_value, r_value, length-len-1, keyword, phone);
		}
	}else if((length == 1)||(length == 0)){
		if ((length == 1)&&(strcmp(name[l_value],keyword) == 0)&&(strcmp(tele[l_value],phone) == 0)){
			printf("entry already exist in the directory\n");
		}else{
			strcpy(name[total_length],insertName);
			strcpy(tele[total_length],insertTele);
			total_length++;
			total_right++;
			sortDirectory();
		}
	}
}

/*---------------------------------------------------------------*/

void insertEntry(char name_buffer[nameLength], char phone_number[teleLength]){
	int len = total_length;
	int left = 0;
	int right;
	if(len>0){
		right = len - 1;
	}else if(len == 0){
		right = 0;
	}
	insertBS(left, right, len, name_buffer, phone_number);
}




/*---------------------------------------------------------------*/
int main (int argc, char * argv[]){
	
	int testlength = 0;
	int run = 1;
	int inputFlag = 1;
	char cmdNum = '\0';
	int filter = 1;
	total_length = 0;
   	
   	create(*(argv+1)); // need to change name
   	sortDirectory();
   	while(1){
		if(name[total_length][0] == '\0'){
			break;
		}
		total_length++;
	}
	total_left = 0;

	if(total_length > 0){
		total_right = total_length - 1;
	}else if(total_length == 0){
		total_right = 0;
	}
	
    while(run == 1){
    	inputFlag = 1;
    	strcpy(insertName,recover); // add name
    	strcpy(insertTele,recover); // add number
    	strcpy(buffer,recover); //delete name
    	printf(" \n");
    	printf(" \n");
    	printf(" Please provide options: \n");
    	printf(" Insert           (press 1)\n");
    	printf(" Search           (press 2)\n");
    	printf(" Delete           (press 3)\n");
    	printf(" Show Directory   (press 4)\n");
    	printf(" Exit             (press 5)\n");
    	printf(" \n");
    	while(inputFlag == 1){
    		cmdNum = '\0';
    		printf(" Please key in command >> ");
    		filter = 1;
    		while(filter){
    			cmdNum = '\0';
    			cmdNum = getchar();
    			if(cmdNum != '\0' && (int)cmdNum != 10){
    				filter = 0;
    			}
    		}
    		if((cmdNum == '5')||(cmdNum == '1')||(cmdNum == '2')||(cmdNum == '3')||(cmdNum == '4')){
    			inputFlag = 0;
    		}else{
    			printf(" \n");
    			printf(" >> Input command invalid. \n");
    		}
    	}

    	switch(cmdNum){
    		case '1':
    		
    			printf("\n");
    			printf("Insert item, input Name >> ");
    			fgets(insertName,nameLength,stdin); //clear
    			fgets(insertName,nameLength,stdin); // stdin means input from keyboard
 				for(int i = 0; i<nameLength; i++){ // wash data
 					if(insertName[i] == '\n'){
 						insertName[i] = '\0';
 					}
 				}
 				printf("\n");
    			printf("Insert item, input Phone# >> ");
    			//fgets(insertTele,teleLength,stdin); //clear
    			fgets(insertTele,teleLength,stdin); // stdin means input from keyboard
 				for(int i = 0; i<teleLength; i++){ // wash data
 					if(insertTele[i] == '\n'){
 						insertTele[i] = '\0';
 					}
 				}
 				insertEntry(insertName, insertTele);
       		break;

    		case '2':
    		
    			printf("\n");
    			printf(" Search directory, input name >> ");
    			fgets(buffer,nameLength,stdin); //clean
    			fgets(buffer,nameLength,stdin); // stdin means input from keyboard
 				for(int i = 0; i<nameLength; i++){ // wash data
 					if(buffer[i] == '\n'){
 						buffer[i] = '\0';
 					}
 				}

 				searchDirectory(buffer);
 				printf("\n");

       			
       		break;

       		case '3':
       		
       			printf("\n");
    			printf(" Delete item, input name >> ");
    			fgets(buffer,nameLength,stdin); //clean
    			fgets(buffer,nameLength,stdin); // stdin means input from keyboard
 				for(int i = 0; i<nameLength; i++){ // wash data
 					if(buffer[i] == '\n'){
 						buffer[i] = '\0';
 					}
 				}
 				deleteEntry(buffer);
 				printf("\n");
       			
       		break;

       		case '4':
       		
       			testlength = 0;
    			while(1){
					if(name[testlength][0] == '\0'){
					break;
					}
					testlength++;
				}
				printf(" \n");
				printf(" \n");
				printf(" Total Quantity : %d\n", testlength);
				for(int i = 0; i < testlength; i++){
					printf(" %-8d: %-30s , %-30s\n", i, *(name+i), *(tele+i));
				}
				//printf("total_length = %d\n",total_length);
				//printf("total_left = %d\n",total_left);
				//printf("total_right = %d\n",total_right);		
       		break;

       		case '5':
       			run = 0;
       		break;

    		default:
       			printf(" Just for test. \n");
		}		
    }
    printf(" --END-- \n");
    free(name);
    free(tele);
   	return(0);
}