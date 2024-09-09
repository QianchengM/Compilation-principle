#include <iostream>
#include <stdlib.h>
#include <stdio.h>
 
using namespace std;
string KEYWORD[5]={"if","else","while","then","do"};      //�ؼ���

char SEPARATER[8]={';',',','{','}','[',']','(',')'};    //�ָ���
char OPERATOR[8]={'+','-','*','/','>','<','=','|'};     //�����
char FILTER[4]={' ','\t','\r','\n'};                    //���˷�
const int IDENTIFIER=100;         //��ʶ��ֵ
const int CONSTANT=101;           //����ֵ
const int FILTER_VALUE=102;       //�����ַ�ֵ
const int INT8=103;
const int INT10=104;
const int INT16=105;
const int EQU=200;
const int MORE=201;
const int LESS=202;
const int ADD=203;
const int MINUS=204;
const int MUL=205;
const int DIC=206;
const int LBRAC=207;
const int RBRAC=208;
const string None=" "; 

int ProcedureE(FILE*fpin);
int ProcedureC(FILE*fpin);
int ProcedureT(FILE*fpin);
int ProcedureS(FILE*fpin);
int ProcedureF(FILE*fpin);
int ProcedureL(FILE*fpin);
int ProcedureP(FILE*fpin);
int ProcedureSn(FILE *fpin);
 
class Token{
	public :
		int type;
		string value;            
		string name;
	Token(){
		type=0;
		value=" ";
		
	}
	Token(int type,string value,string name):type(type),value(value),name(name){
	}
	~Token(){}
}; 
 
 
 
/**�ж��Ƿ�Ϊ�ؼ���**/
bool IsKeyword(string word){
    for(int i=0;i<5;i++){
        if(KEYWORD[i]==word){
            return true;
        }
    }
    return false;
}
/**�ж��Ƿ�Ϊ�ָ���**/
bool IsSeparater(char ch){
    for(int i=0;i<8;i++){
        if(SEPARATER[i]==ch){
            return true;
        }
    }
    return false;
}
 
/**�ж��Ƿ�Ϊ�����**/
bool IsOperator(char ch){
    for(int i=0;i<8;i++){
        if(OPERATOR[i]==ch){
            return true;
        }
    }
    return false;
}
/**�ж��Ƿ�Ϊ���˷�**/
bool IsFilter(char ch){
    for(int i=0;i<4;i++){
        if(FILTER[i]==ch){
            return true;
        }
    }
    return false;
}
/**�ж��Ƿ�Ϊ��д��ĸ**/
bool IsUpLetter(char ch){
    if(ch>='A' && ch<='Z') return true;
    return false;
}
/**�ж��Ƿ�ΪСд��ĸ**/
bool IsLowLetter(char ch){
    if(ch>='a' && ch<='z') return true;
    return false;
}
/**�ж��Ƿ�Ϊ����**/
bool IsDigit(char ch){
    if(ch>='0' && ch<='9') return true;
    return false;
}
/**����ÿ���ֵ�ֵ**/
template <class T>
int value(T *a,int n,T str){
	for(int i=0;i<n;i++){
		if(a[i]==str) return i+1;
	}
	return -1;
}
/**�ʷ�����**/
Token* analyse(FILE * fpin){
    char ch=' ';
    string arr="";
    while((ch=fgetc(fpin))!=EOF){
        arr="";
        if(IsFilter(ch)){}              //�ж��Ƿ�Ϊ���˷�
        else if(IsLowLetter(ch)){       //�ж��Ƿ�Ϊ�ؼ���
            while(IsLowLetter(ch)||IsDigit(ch)||IsUpLetter(ch)){
				arr += ch;
				ch=fgetc(fpin);
            }
			//fseek(fpin,-1L,SEEK_CUR);
			if(IsKeyword(arr)){
               // printf("%3d    ",value(KEYWORD,5,arr));
			//	cout<<arr<<"  �ؼ���"<<endl;
				fseek(fpin,-1L,SEEK_CUR);
				return new Token((value(KEYWORD,5,arr)),None,arr); //None not define declared 
			}
			else
            {              
               // printf("%3d    ",IDENTIFIER);
              //  cout<<arr<<"  ��ʶ��"<<endl;
                fseek(fpin,-1L,SEEK_CUR);
                return new Token(IDENTIFIER,arr,arr);
            }
        }
        else if(IsDigit(ch)){           //�ж��Ƿ�Ϊ����
            if(ch=='0')
            {
            	arr += ch;
                ch=fgetc(fpin);
                if(ch>='0'&&ch<'8')
            	{
            		arr += ch;
                	ch=fgetc(fpin);
                	while(ch>='0'&&ch<'8'||ch=='.')
                	{
                		
                		arr += ch;	
						if(ch=='.') 
						{
							ch=fgetc(fpin);
							break;
						}
                		ch=fgetc(fpin);
                	
					}

					while(ch>='0'&&ch<'8')
                	{
                		arr += ch;
                		ch=fgetc(fpin);
					}
					fseek(fpin,-1L,SEEK_CUR);  //����  -1L ����һ�� SEEK_CUR ��ǰλ��      ����Ϊ���ٴλ��˻�û��ȫ�� 
            	//	printf("%3d    ",INT8);
                  //  cout<<arr<<endl;
                    return new Token(INT8,arr,arr);
				}
				else if(ch=='x'||ch=='X')
				{
					arr += ch;
                	ch=fgetc(fpin);
                	arr += ch;
                	ch=fgetc(fpin);
                	while(IsDigit(ch)||ch>='a'&&ch<'f'||ch=='.')
                	{
                		
                		arr += ch;	
						if(ch=='.') 
						{
							ch=fgetc(fpin);
							break;
						}
                		ch=fgetc(fpin);
                	
					}
						while(IsDigit(ch)||ch>='a'&&ch<'f')
                	{
                		arr += ch;
                		ch=fgetc(fpin);
					}
					fseek(fpin,-1L,SEEK_CUR);
				//	printf("%3d    ",INT16);
                  //  cout<<arr<<endl;
                    return new Token(INT16,arr,arr);
				}
				else if(ch=='.'){
					arr+=ch;
					ch=fgetc(fpin);
				while(IsDigit(ch))
                {
                	arr += ch;
                	ch=fgetc(fpin);
				}
            	fseek(fpin,-1L,SEEK_CUR);
            //	printf("%3d    ",CONSTANT);
        	//cout<<arr<<"  ������"<<endl;
				return new Token(INT10,arr,arr);	
				}
			}
            else
            {	
				while(IsDigit(ch)||ch=='.'/*||(ch=='.'&&IsDigit(fgetc(fpin)))*/){
                		arr += ch;	
						if(ch=='.') 
						{
							ch=fgetc(fpin);
							break;
						}
                		ch=fgetc(fpin);
            	}
            	while(IsDigit(ch))
                {
                	arr += ch;
                	ch=fgetc(fpin);
				}
            	fseek(fpin,-1L,SEEK_CUR);
            	//printf("%3d    ",CONSTANT);
            //	cout<<arr<<"  ������"<<endl;
            	return new Token(INT10,arr,arr);	
        	}
        }
        else if(IsUpLetter(ch)||IsLowLetter(ch)||ch=='_'){
            while(IsUpLetter(ch)||IsLowLetter(ch)||ch=='_'||IsDigit(ch)){
                arr += ch;
                ch=fgetc(fpin);
            }
            fseek(fpin,-1L,SEEK_CUR);
            
           // printf("%3d    ",IDENTIFIER);
           // cout<<arr<<"  ��ʶ��"<<endl;
            return new Token(IDENTIFIER,arr,arr);	
        }
        else switch(ch){
        case '+':
        case '-':
        case '*':
        case '/':
        case '>':
        case '<':
        case '=':
        case '!':
            {
                arr += ch;
               // printf("%3d    ",value(OPERATOR,8,*arr.data())+200);
               // cout<<arr<<"  �����"<<endl;
                return new Token(value(OPERATOR,8,*arr.data())+200,arr,arr);	
                break;
            }
        case ';':
        case ',':
        case '(':
        case ')':
        case '[':
        case ']':
        case '{':
        case '}':
            {
              arr += ch;
             // printf("%3d    ",value(SEPARATER,8,*arr.data())+300);
              //cout<<arr<<"  �ָ���"<<endl;
             return new Token(value(SEPARATER,8,*arr.data())+300,arr,arr);	
              break;
            }
        default :cout<<"\""<<ch<<"\":�޷�ʶ����ַ���"<<endl;
        }
    }
    return new Token(-1,"#","#");
 
}



int ProcedureSn(FILE *fpin){
	Token* token=analyse(fpin);
	if(token->name=="else"){
		cout<<token->name<<endl;
		cout<<"S_new"<<endl;
		ProcedureS(fpin);
	}
	else{
		
			for(int i=0;i<(int)token->name.length();i++){//*******************************
			//	cout<<"**************"<<endl;
				fseek(fpin,-1L,SEEK_CUR);
			}
		
		
		return 0;
	}
	
	
	return 0;
	
}

int ProcedureL(FILE *fpin){
	cout<<"L"<<endl;
	ProcedureS(fpin);
	Token* token=analyse(fpin);
	char ch;
	if(token->name==";"){
		cout<<token->name<<endl;
		cout<<"end of a sentence"<<endl;
		//cout<<token->name<<endl; 
		
	//	if((ch=fgetc(fpin))==EOF){
		//	cout<<"end of a project"<<endl;
		//		return 0;
	
	//	}
	} 
	else{
		cout<<"wrong!!"<<endl;
		exit(-1);
	}
	return 0;
}
int ProcedureP(FILE *fpin){
	
	char ch;
	Token* token=analyse(fpin);
	if(token->name=="#"){
		return 0;
	}
	else{

			fseek(fpin,-1L*(int)token->name.length(),SEEK_CUR);
		
	}

	ProcedureL(fpin); 
	
	Token* token1=analyse(fpin);

	if(token1->name!="#"){
	
		//if(ch==';'){
		//cout<<"end of a project2"<<endl;
		//	return 0;}
		cout<<"P"<<endl;
	fseek(fpin,-1L*(int)token1->name.length(),SEEK_CUR);
		ProcedureP(fpin);	
		}
	else{
		cout<<"bye"<<endl;
		return 0;
	}
	
}




int ProcedureS(FILE*fpin){
    cout<<"S"<<endl;
    Token* token=analyse(fpin);

    //string arr = "if";

 /*  if(token->name=="else"){
    	cout<<"Snew"<<endl;
    	ProcedureS(fpin);
	}*/
	
   if(token->name=="if"){//IF 
    	cout<<token->name<<endl;
    	ProcedureC(fpin);
    	token=analyse(fpin);

        if(token->name=="then"){//THEN
        	cout<<token->name<<endl;
        	ProcedureS(fpin);
       		ProcedureSn(fpin);
		}
		else{
			exit(-1);
		}
		
	}
	else if(token->name=="while"){//WHILE
		cout<<token->name<<endl;
		ProcedureC(fpin);
		token=analyse(fpin);
		if(token->name==";"){
			fseek(fpin,-1L,SEEK_CUR);
			return 0;
		}
		if(token->name=="do"){//DO
			cout<<token->name<<endl;
			ProcedureS(fpin);
		
		}else{
			exit(-1);
		}
		
	}else if(token->type==IDENTIFIER){
		cout<<"id: "<<token->name<<endl;
		token=analyse(fpin);
		if(token->name==";"){
			fseek(fpin,-1L,SEEK_CUR);
			return 0;
		}
		if(token->name=="="){
			cout<<token->name<<endl;
			ProcedureE(fpin);
		}else{
			exit(-1);
		}
		
	}
	else if(token->name=="{"){
		cout<<token->name<<endl;
		ProcedureP(fpin);
		Token* token=analyse(fpin);
		if(token->name=="}"){
		cout<<token->name<<endl;
		}
		else{
			cout<<"wrong {}"<<endl;
			exit(-1);
		}
		
			
		
	}
	return 0;	
} 

int ProcedureC(FILE* fpin){
	cout<<"C"<<endl;
	Token*token;
	ProcedureE(fpin);
	token=analyse(fpin);

	if(token->name==";"){
		fseek(fpin,-1L,SEEK_CUR);
			return 0;
		}
	if(token->name==">"){
		cout<<token->name<<endl;
		ProcedureE(fpin);
	}
	else if(token->name=="<"){
		cout<<token->name<<endl;
		ProcedureE(fpin);
	}
	else if(token->name=="="){
		cout<<token->name<<endl;
		ProcedureE(fpin);
	}
	else{
		exit(-1);
	}
	return 0;
}

int ProcedureE(FILE*fpin){
    cout<<"E"<<endl;
	Token*token;
	ProcedureT(fpin);
	while (true){
		token=analyse(fpin);
		//cout<<"proE:"<<token->name<<endl;
		if(token->name==";"){
			fseek(fpin,-1L,SEEK_CUR);
			return 0;
		}

		if(token->name=="+"){
		cout<<token->name<<endl;
		ProcedureT(fpin); 
		}else if(token->name=="-"){
			cout<<token->name<<endl;
			ProcedureT(fpin);
		}else{
		//	cout<<"huitui "<<token->name.length()<<":"<<token->name<<endl;
			for(int i=0;i<(int)token->name.length();i++){//*******************************
			//	cout<<"**************"<<endl;
				fseek(fpin,-1L,SEEK_CUR);
			}
			return 0;
		}
	}
	return 0;
}


int ProcedureT(FILE*fpin){
	cout<<"T"<<endl;
	Token*token;
	ProcedureF(fpin);
	while(true){
		token=analyse(fpin);
		if(token->name==";"){
			fseek(fpin,-1L,SEEK_CUR);
			return 0;
		}
		if(token->name=="*"){
			cout<<token->name<<endl;
			ProcedureF(fpin);
		}
		else if(token->name=="/"){
		    cout<<token->name<<endl;
			ProcedureF(fpin);
		}else{
		//	cout<<"huitui "<<token->name.length()<<":"<<token->name<<endl;
			for(int i=0;i<(int)token->name.length();i++){//*******************************
			
		//	cout<<"$$$$$$$$$$"<<endl;
			fseek(fpin,-1L,SEEK_CUR);
			}
		return 0;
		}
	}
	return 0;
}

int ProcedureF(FILE*fpin){
	cout<<"F"<<endl;
	Token*token;
	token=analyse(fpin);
	if(token->name==";"){
			return 0;
			fseek(fpin,-1L,SEEK_CUR);
		}

	if(token->name=="("){
		cout<<token->name<<endl;
		ProcedureE(fpin);
		token=analyse(fpin);
		if(token->name==";"){
			fseek(fpin,-1L,SEEK_CUR);
			return 0;
		}
		else if(token->name!=")"){
			cout<<"wrong"<<endl;
			exit(-1);
		}
	
		cout<<token->name<<endl;
	}

	if(token->type==IDENTIFIER){
	//	cout<<"??"<<endl;
		cout<<"id: "<<token->name<<endl;
	}
	if(token->type==INT8){
		cout<<"int8: "<<token->name<<endl;
	}
	if(token->type==INT10){
		cout<<"int10: "<<token->name<<endl;
	}
	if(token->type==INT16){
		cout<<"int16: "<<token->name<<endl;
	}
	return 0;
}


int main()
{
    char inFile[40];
    FILE *fpin;
   // cout<<"������Դ�ļ���������·���ͺ�׺��:";
    while(true){
        //cin>>inFile;
        if((fpin=fopen("C:\\Users\\lenovo\\Desktop\\jzl1.txt","r"))!=NULL)
            break;
        else{
            cout<<"�ļ�������"<<endl;
            cout<<"������Դ�ļ���������·���ͺ�׺��:";
        }
 
    }
    cout<<"------�ʷ���������------"<<endl;
	cout<<"P"<<endl; 
    ProcedureP(fpin);
	//while(1){
	//	analyse(fpin);
	//}
	return 0;
}
