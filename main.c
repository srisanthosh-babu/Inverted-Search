#include "InvertedSearch.h"
int main(int argc, char*argv[]){
	if(argc<2){
		printf("\nERROR: Enter valid number of arguments\n");
		return 0;
	}
	flist*head=NULL;
	int op;
	if(read_and_validate(argc,argv,&head)==SUCCESS){
		printf("\nInputs are validated and %d  files added in database successfully\n",argc-1);
	}else{
		printf("\nERROR: Input files Validation Failed\n");
		return 0;
	}
	hash_t arr[27];
	for(int i=0;i<27;i++){
		arr[i].index=i;
		arr[i].link=NULL;
	}
	do{
		printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------");
		printf("\n1. Create Database\n2. Display Database\n3. Search Database\n4. Update Database\n5. Save Database\n6. Exit\n");
		printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		scanf("%d",&op);
		switch(op){
			case 1:
				printf("\nCreate Database selected\n");
				if(createDatabase(arr,27,head)==SUCCESS){
					printf("\nDatabase Created successfuullly\n");

				}else{
					printf("\nERROR: Database Creation failed\n");
				}
				break;
			case 2:
				printf("\nDisplay Database selected\n");
				displayDatabase(arr);
				break;
			case 3:
				printf("\nSearch Database selected\n");
				printf("\nEnter the word to search : ");
				char key[20];
				scanf(" %[^\n]",key);
				Status ret=searchDatabase(arr,key);
				if(ret==DATA_NOT_FOUND){
					printf("\nWord :'%s' not found in any file(s)\n",key);
				}
				if(ret==FAILURE){
					printf("\nERROR: Searching word operation is failed\n");
				}
				break;
			case 4:
				printf("\nUpdate Database selected\n");
				char new[20];
				printf("\nEnter new filename to add : ");
				scanf(" %[^\n]",new);
				if(updateDatabase(arr,&head,new)==SUCCESS){
					printf("\nFile update with %s  is successful..!\n",new);
				}else{
					printf("\nERROR: Failed to update '%s' in Database\n",new);
				}
				break;
			case 5:
				printf("\nSave Database selected\n");
				if(saveDatabase(arr)==SUCCESS){
					printf("\nDatabase saved successfully\n");
				}else{
					printf("\nERROR: Database save operation failed\n");
				}
				break;
			case 6:
				printf("\nExit selected\n");
				break;
			default :
				printf("\nInvalid selection..!\n");
				break;
		}
	}while(op!=6);
	return 0;
}
