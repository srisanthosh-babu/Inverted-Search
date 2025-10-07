#ifndef INVERTEDSEARCH_H
#define INVERTEDSEARCH_H
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

typedef enum{
	SUCCESS,FAILURE,DATA_NOT_FOUND
}Status;

typedef struct node{
	char filename[20];
	struct node*link;
}flist;

typedef struct subnode{
	int wordcount;
	char fname[20];
	struct subnode*sublink;
}snode;


typedef struct mainode{
	int filecount;
	char word[20];
	snode*slink;
	struct mainode*mlink;
}mnode;

typedef struct hash{
	int index;
	struct mainode*link;
}hash_t;


Status read_and_validate(int,char**,flist**);
Status createDatabase(hash_t [],int,flist*);
Status insertLast(flist**,char*);
Status searchList(flist**,char*);
Status searchDatabase(hash_t[],char*);
Status updateDatabase(hash_t[],flist**,char*);
Status saveDatabase(hash_t[]);
void displayDatabase(hash_t[]);

#endif
