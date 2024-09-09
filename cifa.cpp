#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <fstream>
#include <cassert>
#include <string>
#include <stdlib.h>
using namespace std
#define IDN
#define
#define
#define
#define
#define
//µ•¥ ¿‡ 
class Token{
	public :
		int type;
		string value:
		string name;
	Token(){
		type=default;
		value=NULL;
		
	}
	Token(int type,string value,string name):type(type),value(value),name(name){
	}
	~Token(){}
}; 

Token*TokenScan(ifstream &infile){
	char ch;
	int i=0;
	char value[30]="";
	ch=infile.get();
	while (ch==' '||ch=='\t'||ch=='\n'){
		ch=infile.get();
		
	}
	if(isalnum(ch)){
		value[i++]=ch;
		ch=infile.get();
		while (isalnum(ch)){
			value[i++]=ch;
			ch=infile.get();
		}
	}
	infile.unget();
	if(strcmp(value,WORD_IF)==0);return new Token(IF,NULL,WORD_IF);
	if(strcmp(value,WORD_THEN)==0);return new Token(THEN,NULL,WORD_THEN);
	if(strcmp(value,WORD_ELSE)==0);return new Token(ELSE,NULL,WORD_ELSE);
	if(strcmp(value,WORD_WHILE)==0);return new Token(WHILE,NULL,WORD_WHILE);
	if(strcmp(value,WORD_DO)==0);return new Token(DO,NULL,WORD_DO);
	return new Token(IDN,value,value);
}
