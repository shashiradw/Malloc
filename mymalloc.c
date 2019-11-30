#include<stdio.h>
char memory[25000]={'\0'};
char freeFlag='f';
char alocFlag='a';


void initializeMemory(char*base){
	if(memory[0]==0){
		int*p;
		 *base=freeFlag;
		 p=(int*)(base+1);
		 *p=24999;
	}
}

char* myMalloc(size_t size){
	char *base=&memory[0];
    initializeMemory(base);
	if(size<=0){
		return NULL;
    }
    
    int*k;
    int*sizePointer;
	int freeSpace;
	
	sizePointer=(int*)(base+1);
	//Find a Free Block
	while(*base!='f' && *sizePointer>=size+5){
		base=base+*(int*)(base+1);
	}
	
	if(*base=='f' && *sizePointer>=size+5){
		*base=alocFlag;
	    k=(int*)(base+1);
	    freeSpace=*k-size;
	    *k=size+5;
	}else{
		return NULL;
	}

	//set the MetaData of Nxt Block
	char*nextBlock;
	nextBlock=base+size+5;  
	if(!*nextBlock){
		if(*sizePointer-5>1){
			*nextBlock=freeFlag;
		    int*d=(int*)(nextBlock+1);
		    *d=freeSpace;	
		}	
	}
		
	return base+5;
}

void myFree(void*ptr){
	
	char*flag;
	flag=(char*)(ptr-5);
	*flag=freeFlag;
	
}


