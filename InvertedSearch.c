#include "InvertedSearch.h"

Status read_and_validate(int argc, char*argv[],flist**head){
	for(int i=1;i<argc;i++){
		if(strstr(argv[i],".txt") != NULL){
			FILE*fptr=fopen(argv[i],"r");
			if(fptr!=NULL){
				fseek(fptr,0,SEEK_END);
				if(ftell(fptr) != 0){
					fclose(fptr);
					if(insertLast(head,argv[i]) == SUCCESS){
						printf("\n%s added successfully\n",argv[i]);
					}else{
						printf("\nERROR: %s insertion failed\n",argv[i]);
						return FAILURE;
					}
				
				}else{
					printf("\nERROR: %s is empty\n",argv[i]);
					fclose(fptr);
					return FAILURE;
				}
			
			}else{
				printf("\nERROR: %s does not exist Enter a valid file\n",argv[i]);
				return FAILURE;
			}
		}else{
			printf("\nERROR: %s is not a .txt file\n",argv[i]);
			return FAILURE;
		}
	}
	return SUCCESS;
}

Status insertLast(flist**head,char*filename){
	if(*head !=NULL){
		if(searchList(head,filename)==SUCCESS){
			flist*node=(flist*)malloc(sizeof(flist));
			if(node==NULL){
				printf("\nERROR: Memory allocation failed\n");
				return FAILURE;
			}
			strcpy(node->filename,filename);
			node->link=NULL;
			flist*temp=(*head);
			while(temp->link!=NULL){
				temp=temp->link;
			}
			temp->link=node;
			return SUCCESS;
		}else{
			printf ("\nERROR: %s file already exists in the database\n",filename);
			return FAILURE;
		}
	}
	flist*node=(flist*)malloc(sizeof(flist));
	if(node==NULL){
		printf("\nMemory allocation failed\n");
		return FAILURE;
	}
	strcpy(node->filename,filename);
	node->link=NULL;
	*head=node;
	return SUCCESS;
}
	
Status searchList(flist**head,char*filename){
	flist*temp=*head;
	while(temp!=NULL){
		if(strcmp(temp->filename,filename)==0){
			return FAILURE;
		}
		temp=temp->link;
	}
	return SUCCESS;
}
Status createDatabase(hash_t arr[],int size, flist*head){
	int index;
	char str[20];
	flist*temp=head;
	while(temp!=NULL){
		
		
		FILE*fptr=fopen(temp->filename,"r");
		if(fptr==NULL){
			printf("\nERROR: Could not open %s\n",temp->filename);
			return FAILURE;
		}
		while(fscanf(fptr,"%s",str)==1){
			if(isalpha((unsigned char)str[0])){
				index=tolower((unsigned char)str[0])-'a';	
			}else{
				index=26;
			}
			if(index<0 || index>26){
				index=26;
			}
			if(arr[index].link==NULL){
				mnode*mnew=(mnode*)malloc(sizeof(mnode));
				if(mnew==NULL){
					printf("\nERROR: Memory allocation for  main Node failed\n");
				        fclose(fptr);
					return FAILURE;
				}
				snode*snew=(snode*)malloc(sizeof(snode));
				if(snew==NULL){
					printf("\nERROR: Memory allocation for subnode failed\n");
					free(mnew);
					fclose(fptr);
					return FAILURE;
				}
				mnew->filecount=1;
				strcpy(mnew->word,str);
				mnew->slink=snew;
				mnew->mlink=NULL;

				snew->wordcount=1;
				strcpy(snew->fname,temp->filename);
				snew->sublink=NULL;

				arr[index].link=mnew;
			
			}else{
				mnode*mtemp=arr[index].link;
				mnode*mprev=NULL;
				int mflag=0;
				int sflag=0;

				while(mtemp!=NULL){
					if(strcmp(mtemp->word,str)==0){
						mflag=1;
						snode*stemp=mtemp->slink;
						snode*sprev=NULL;
						while(stemp!=NULL){
							if(strcmp(stemp->fname,temp->filename)==0){
								sflag=1;
								(stemp->wordcount)++;
								break;
							}else{
								sprev=stemp;
								stemp=stemp->sublink;
							}
						}
						if(sflag==0){
							snode*snew=(snode*)malloc(sizeof(snode));
							if(snew==NULL){
								printf("\nERROR: Memory allocation for subnode failed\n");
				       				fclose(fptr);
								return FAILURE;
							}

							snew->wordcount=1;
							strcpy(snew->fname,temp->filename);
							snew->sublink=NULL;
							if(sprev==NULL){
								mtemp->slink=snew;
							}else{
								sprev->sublink=snew;
							}
							(mtemp->filecount)++;
						}
						break;						
					}else{
						mprev=mtemp;
						mtemp=mtemp->mlink;
					}
				}
				if(mflag==0){
					mnode*mnew=(mnode*)malloc(sizeof(mnode));
					if(mnew==NULL){
						printf("\nERROR: Memory allocation for  main Node failed\n");
				       		fclose(fptr);
						return FAILURE;
					}
					snode*snew=(snode*)malloc(sizeof(snode));
					
if(snew==NULL){
						printf("\nERROR: Memory allocation for subnode failed\n");
				       		free(mnew);
						fclose(fptr);
						return FAILURE;
					}
					mnew->filecount=1;
					strcpy(mnew->word,str);
					mnew->slink=snew;
					mnew->mlink=NULL;

					snew->wordcount=1;
					strcpy(snew->fname,temp->filename);
					snew->sublink=NULL;

					mprev->mlink=mnew;
				}

			}
			
		}
		fclose(fptr);
		temp=temp->link;
	}
	return SUCCESS;
}

void displayDatabase(hash_t arr[]){
	for(int i=0;i<27;i++){
		if(arr[i].link!=NULL){
			printf("[ %d ]\t",i);
			mnode*mtemp=arr[i].link;
			while(mtemp!=NULL){
				printf("[ %s ]\t%d file(s)\t:",mtemp->word,mtemp->filecount);
				snode*stemp=mtemp->slink;
				while(stemp!=NULL){
					printf("file : %s\t%d time(s)",stemp->fname,stemp->wordcount);
					stemp=stemp->sublink;
				}
				printf("\n-->");
				mtemp=mtemp->mlink;
			}
			printf("\n");
		}
	}
}

Status searchDatabase(hash_t arr[],char*word){
	int index;
	if(isalpha(word[0])){
		index=tolower((unsigned char)word[0])-'a';
	}else{
		index=26;
	}
	mnode*mtemp=arr[index].link;
	while(mtemp!=NULL){
		if(strcmp(mtemp->word,word)==0){
			printf("\nWord found : '%s'\n",word);
			printf("\nAppears in %d file(s):\n",mtemp->filecount);
			snode*stemp=mtemp->slink;
			while(stemp!=NULL){
				printf(" ->%s : %d time(s)\n",stemp->fname,stemp->wordcount);
				stemp=stemp->sublink;
			}
			return SUCCESS;
		}
		mtemp=mtemp->mlink;
	}
	printf("\nWord '%s' not found in any file.\n",word);
	return DATA_NOT_FOUND;
}
Status updateDatabase(hash_t arr[],flist**head,char*newfile){
	if(strstr(newfile,".txt")==NULL){
		printf("\nERROR: %s is not a .txt file\n",newfile);
		return FAILURE;
	}
	FILE*fptr=fopen(newfile,"r");
	if(fptr==NULL){
		printf("\nERROR: Unable to open %s\n",newfile);
		return FAILURE;
	}
	fseek(fptr,0,SEEK_END);
	if(ftell(fptr)==0){
		printf("\nERROR: %s is empty\n",newfile);
		fclose(fptr);
		return FAILURE;
	}
	rewind(fptr);
	if(insertLast(head,newfile)==FAILURE){
		printf("\nERROR: Could not insert %s\n",newfile);
		fclose(fptr);
		return FAILURE;
	}
	printf("\nFile '%s' added successfully. Updating Database...\n",newfile);
	flist*temp=*head;
	while(temp->link!=NULL){
		temp=temp->link;
	}
	Status ret=createDatabase(arr,27,temp);
	fclose(fptr);
	return ret;
}

Status saveDatabase(hash_t arr[]){
	FILE*fptr=fopen("InvertedSearchDB.txt","w");
	if(fptr==NULL){
		printf("\nERROR: Could not open file\n");
		return FAILURE;
	}
	for(int i=0;i<27;i++){
		if(arr[i].link!=NULL){
			mnode*mtemp=arr[i].link;
			while(mtemp!=NULL){
				fprintf(fptr,"Word: %s | File(s): %d\n",mtemp->word,mtemp->filecount);
			       snode*stemp=mtemp->slink;
			       while(stemp!=NULL){
			fprintf(fptr," -> %s : %d time(s)\n",stemp->fname,stemp->wordcount);
			stemp=stemp->sublink;
			       }
			       fprintf(fptr,"\n");
			       mtemp=mtemp->mlink;
			}
		}
	}
	fclose(fptr);
	return SUCCESS;
}


			

