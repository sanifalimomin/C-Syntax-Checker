#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	int lineno;
	int linelen;
	char linetext[100];
}fileline;

void print(fileline str[],int len);
int search(char arr[],int len);
void bracket(fileline arr[],int len);
void keyword(fileline arr[],int length);
void function_and_prototype_count(fileline arr[],int len);
//void protocheck(fileline arr[],int len);
//void functioncheck(fileline arr[],int len);
void checkkeyword(fileline arr[],int len);
void builtinfunction(fileline arr[],int len);
//void count(fileline arr[],int len);
void printscan(fileline arr[],int size);
int printcheck(char arr[],int size);
int scancheck(char arr[],int size);
void varcount(fileline arr[],int len);
int getscheck(char arr[],int size);
int putscheck(char arr[],int size);
int fprintf(char arr[],int size);
int fscanf(char arr[],int size);
void fcheck(fileline arr[],int len);
int forcheck(char arr[],int size);
int whilecheck(char arr[],int size);

int main(){
	FILE *input;
	fileline str[100]; 
	char str1[100];
	int totallen,j,i=0,len,found;
	input=fopen("input.txt","r");
	while(fgets(str1,100,input)!=NULL){
		len=strlen(str1); //length of a line
		found=search(str1,len); //position of comment if exists
		if (str1[0]!='\n'&&found==-1){
			str[i].lineno=i+1;
		    str[i].linelen=len;
		    strcpy(str[i].linetext,str1);
		    i++;
		}
		else if (str1[0]!='\n'&&found!=-1){
			str[i].lineno=i+1;
			for( j=0;j<found;j++) str[i].linetext[j]=str1[j];
			str[i].linetext[found]='\n';
			str[i].linelen=strlen(str[i].linetext);
			i++;
		}
	}
	totallen=i;
	printf("******************THE C- PROGRAM***********************\n\n\n\n");
	printf("\t\tOUTPUT PRINTED ON TEXT FILE NAME OUTPUT\n\n\n");
	print(str,totallen);
	
	printf("-----------BRACKET ,PARANTHESIS Check-----------\n\n\n\n");
	bracket(str,totallen);
	
	printf("\n\n\n\t\t\tKEYWORDS with LINE NUMBER\n\n\n");
	keyword(str,totallen);
	//protocheck(str,totallen);
	printf("\n\n\n\t\t\tTOTAL NUMBER OF BUILTIN FUNCTIONS USED\n\n\n");
	builtinfunction(str,totallen);
	printf("\n\n\n\t\t\tTOTAL FUNCTIONS USED INCLUDING MAIN\n\n\n");
	function_and_prototype_count(str,totallen);
	printf("\n\n\n\t\t\tVARIABLES WITH COUNTS\n\n\n");
	varcount(str,totallen);
	
	
	printf("\n\n\n\t\t\tSYNTAX CHECK\n\n");
	//printscan(str,totallen);
	fcheck(str,totallen);
	printf("\n\n\n\t\t\tTOTAL LINES IN PROGRAM\n\n\n");
	printf("Total line in Program are: %d",totallen);
	return 0;
}


void print(fileline str[],int len){
	FILE * fout; 
	int i;
	fout=fopen("output.txt","w");
	for(i=0;i<len;i++){
		fprintf(fout,"line %d [%d]: %s",str[i].lineno,str[i].linelen,str[i].linetext);
	}
	
}


int search(char arr[],int len){
	int found=0,i;
	for(i=0;!found&&i<len;i++){
		if(arr[i]=='/'&&arr[i+1]=='/'){
			return i;
			found=1;
		}
	}
	if (!found) return -1;
}

void keyword(fileline arr[],int len){
	char str[100],a[100];
	char sync[32][10]={"auto","double","int","struct","break","else","long","switch","case","enum","register","typedef","char","extern","return","union","const","float","short","unsigned","continue","for","signed","void","default","goto","sizeof","volatile","do","if","static","while"};		
		int i,j,l;
	
	for (i=0;i<len;i++){
		int pos=0,k=0;
		strcpy(str,arr[i].linetext);
		for(j=0;j<arr[i].linelen;j++){
			if (str[j]==' '||str[j]=='('|| str[j]=='\0'||str[j]=='\t'){
				a[k]='\0';
				for(l=0;l<32;l++){
					if (strcmp(a,sync[l])==0) printf("Line %d: %s\n",arr[i].lineno,a);
				}
				k=0;
				pos=j+1;
			}
			else {a[k]=str[j]; k++;}
		}
	}
}	
void bracket(fileline arr[],int len){
	int *p;
	int i,j;
	p=(int*)calloc(3,sizeof(int));
	int linea1[20],linea2[20],lineb1[20],lineb2[20],linec1[20],linec2[20],a=0,a2=0,b=0,b2=0,c=0,c2=0;
	for(i=0;i<len;i++){
		for(j=0;j<arr[i].linelen;j++){
		if (arr[i].linetext[j]=='{')        {*p=*p+1;           linea1[a++]=arr[i].lineno;}
		else if (arr[i].linetext[j]=='}')   {*p=*p-1;           linea2[a2++]=arr[i].lineno;}
		else if (arr[i].linetext[j]=='(')   {*(p+1)=*(p+1)+1;   lineb1[b++]=arr[i].lineno;}
		else if (arr[i].linetext[j]==')')   {*(p+1)=*(p+1)-1;   lineb2[b2++]=arr[i].lineno;}
		else if (arr[i].linetext[j]=='[')   {*(p+2)=*(p+2)+1;   linec1[c++]=arr[i].lineno;}
		else if (arr[i].linetext[j]==']')   {*(p+2)=*(p+2)-1;   linec2[c2++]=arr[i].lineno;}
		}
	}
	while(*p>0)  {   printf("line %d: { is greater\n",linea1[--a]) ; *p-=1;     }
	while(*p<0)  {   printf("line %d: } is greater\n",linea2[--a2]);*p+=1;      }
	while(*(p+1)>0){ printf("line %d: ( is greater\n",lineb1[--b]);*(p+1)-=1;   } 
	while(*(p+1)<0){ printf("line %d: ) is greater\n",lineb2[--b2]);*(p+1)+=1;  }
	while(*(p+2)>0){ printf("line %d: [ is greater\n",linec1[--c]); *(p+2)-=1;  }
	while(*(p+2)<0){ printf("line %d: ] is greater\n",linec2[--c2]);*(p+2)+=1;  }
}

void builtinfunction(fileline arr[],int len){ 
	char str[100],a[100];
	char sync[30][10]={"printf","scanf","gets","puts","fsanf","fprintf","fgets","fputs","fputc","fgetc","fopen","fclose","feof","fflush","malloc","calloc","rand","strcmp","strlen","strcpy","strncpy","strncmp","tolower","toupper","strrev","getch","strcat","strncat","sqrt","pow"};		
	int i,j,l,total=0;
	
	for (i=0;i<len;i++){
		int pos=0,k=0;
		strcpy(str,arr[i].linetext);
		for(j=0;j<arr[i].linelen;j++){
			if (str[j]==' '||str[j]=='('|| str[j]=='\0'||str[j]=='\t'){
				a[k]='\0';
				for(l=0;l<30;l++){
					if (strcmp(a,sync[l])==0) total+=1;
				}
				k=0;
				pos=j+1;
			}
			else {a[k]=str[j]; k++;}
		}
	}
	printf("Total Builtin Functions: %d\n",total);
}

void printscan(fileline arr[],int size){
	int i,j,k,l,x;
	char str[100];
	
	for(i=0;i<size;i++){
		for(x=0;(arr[i].linetext[x]==' '||arr[i].linetext[x]=='\t');x++);
		printf("%d",x);
		//strcpy(str,arr[i].linetext);
		for(int a=0;a<arr[i].linelen-x;a++){
			str[a]=arr[i].linetext[x+a];
		}
	
		if (strncmp(arr[i].linetext,"printf",6)==0) {
		printcheck(str,arr[i].linelen);
		printf("exist\n");	
		}
		if(strncmp(arr[i].linetext,"scanf",5)==0)	{
			scancheck(str,arr[i].linelen);
			printf("scanf exist\n");
			
		}
	}
}


int printcheck(char arr[],int size){
		int pcount=0,ccount=0,icount=0,f=0;
	for(int i=0;i<size;i++){
		if(arr[i]=='%')pcount++;
		if(arr[i]==',')ccount++;
		if(arr[i]=='\"')icount++;
	}
	if(pcount!=ccount)f=1;
	if(icount%2!=0)f=1;
	
	return f;
	
}

int scancheck(char arr[],int size){
		int pcount=0,ccount=0,icount=0,f=0,acount=0,scount=0;
	for(int i=0;i<size;i++){
		if(arr[i]=='%')pcount++;
		if(arr[i]==',')ccount++;
		if(arr[i]=='\"')icount++;
		if(arr[i]=='&')acount++;
		if(arr[i]=='%'&&arr[i+1]=='s')scount++;
		
	}
	
	
	
	
	
	if(pcount!=ccount)f=1;
	if(icount%2!=0)f=1;
	if((pcount-scount)!=acount)f=1;
	
	return f;
	
}
int fprintfcheck(char arr[],int size){
		int pcount=0,ccount=0,icount=0,f=0;
	for(int i=0;i<size;i++){
		if(arr[i]=='%')pcount++;
		if(arr[i]==',')ccount++;
		if(arr[i]=='\"')icount++;
	}
	if(pcount!=ccount-1)f=1;
	if(icount%2!=0)f=1;
	
	return f;
	
}
int getscheck(char arr[],int size){
		int f=0;
	for(int i=0;i<size;i++){
		if(arr[i]=='%')f=1;
		if(arr[i]==',')f=1;
		if(arr[i]=='\"')f=1;
		if(arr[i]=='&')f=1;
		if(arr[i]=='\'')f=1;
		
	}

	return f;
	
}
int putscheck(char arr[],int size){
		int f=0;
	for(int i=0;i<size;i++){
		if(arr[i]=='%')f=1;
		if(arr[i]==',')f=1;
		if(arr[i]=='\"')f=1;
		if(arr[i]=='&')f=1;
		if(arr[i]=='\'')f=1;
		
	}

	return f;
	
}

void function_and_prototype_count(fileline arr[],int len){
	char str[100],a[100];
	char sync[7][10]={"int","char","void","double","float","long","short"};		
	int i,j,l,total=0;
	
	for (i=0;i<len;i++){
		int pos=0,k=0;
		strcpy(str,arr[i].linetext);
		int strlength;
		strlength=arr[i].linelen;
	//	printf("---> %c\n",str[strlength-2]);
		for(j=0;j<arr[i].linelen;j++){
			if (str[j]==' '||str[j]=='('|| str[j]=='\0'||str[j]=='\t'){
				a[k]='\0';
				for(l=0;l<7;l++){
					if ((strcmp(a,sync[l])==0)&&str[strlength-2]==')')total++;
						
					
				}
				k=0;
				pos=j+1;
			}
			else {a[k]=str[j]; k++;}
		}
	}
	printf("Total Functions used including main function: %d\n",total);
		int fun=0,found=0,m,pos=0;
//	char a[100],str[100];
	for (i=0;i<len&&!found;i++){
		int k=0;
		strcpy(str,arr[i].linetext);
		for(j=0;j<arr[i].linelen;j++){
			if (str[j]==' '||str[j]=='('|| str[j]=='\0'||str[j]=='\t'){
				a[k]='\0';
					
				k=0;
				
			}
			else {a[k]=str[j]; k++;}
			if (strcmp(a,"main")==0) {
						found=1;
						pos=i;
						break;
					}
		}
	}
	 fun=0;
	for(i=0;i<pos;i++){
		int k=0;
		strcpy(str,arr[i].linetext);
		int strlength;
		strlength=arr[i].linelen;
	
		for(j=0;j<arr[i].linelen;j++){
			if (str[j]==' '||str[j]=='('|| str[j]=='\0'||str[j]=='\t'){
				a[k]='\0';
				for(l=0;l<7;l++){
					if ((strcmp(a,sync[l])==0)&&str[strlength-3]==')'&&str[strlength-2]==';')fun++;
						
					
				}
				k=0;
				pos=j+1;
			}
			else {a[k]=str[j]; k++;}
		}
	}
	printf("\n\n\n\t\t\tPROTOTYPE CHECK\n\n\n");
	
	printf("Total prototypes: %d\n",fun);
	
	if(fun<total-1)printf("Some prototypes are not defined\n");
	else printf("Prototypes are defined\n");
}
void varcount(fileline arr[],int len){
	char str[100],a[100];
	char sync[6][10]={"int","char","long","double","float","short"};		
	int i,j,l,total[6]={0},memory[6]={0};
	
	for(i=0;i<len;i++){
		int pos=0,k=0;
		strcpy(str,arr[i].linetext);
		int strlength;
		strlength=arr[i].linelen;
		
		for(j=0;j<arr[i].linelen;j++){
			if (str[j]==' '||str[j]=='('|| str[j]=='\0'||str[j]=='\t'){
				a[k]='\0';
					for(int l=0;l<6;l++){
						
						
						if (strcmp(a,sync[l])==0){
							pos=j;
							if((str[strlength-3]!=')')&&(str[strlength-2]!=')')){
								for(int x=pos;x<strlength;x++){
									if(str[x]==','||str[x]==';')total[l]++;
								}	
							}
						}
					}		
					
				
				k=0;
				
			}
			else {a[k]=str[j]; k++;}
		}
	}

	printf("Total int: %d\nTotal Char: %d\nTotal long integer: %d\nTotal Double: %d\nTotal float: %d\nTotal short integer: %d\n",total[0],total[1],total[2],total[3],total[4],total[5],total[6]);
	memory[0]=total[0]*sizeof(int);
	memory[1]=total[1]*sizeof(char);
	memory[2]=total[2]*sizeof(long);
	memory[3]=total[3]*sizeof(double);
	memory[4]=total[4]*sizeof(float);
	memory[5]=total[5]*sizeof(short);
	printf("\n\n\n\t\t\tMEMORY CONSUMED BY VARIABLES\n\n\n");
	printf("Memory int: %d BYTES\nMemory Char: %d BYTES\nMemory long integer: %d BYTES\nMemory Double: %d BYTES\nMemory float: %d BYTES\nMemory short integer: %d BYTES\n",memory[0],memory[1],memory[2],memory[3],memory[4],memory[5],memory[6]);
	
}
int fscanfcheck(char arr[],int size){
		int pcount=0,ccount=0,icount=0,f=0,acount=0,scount=0;
	for(int i=0;i<size;i++){
		if(arr[i]=='%')pcount++;
		if(arr[i]==',')ccount++;
		if(arr[i]=='\"')icount++;
		if(arr[i]=='&')acount++;
		if(arr[i]=='%'&&arr[i]=='s')scount++;
		
	}
	
	
	
	
	
	if(pcount!=ccount-1)f=1;
	if(icount%2!=0)f=1;
	if((pcount-scount)!=acount)f=1;
	
	return f;
	
	
}
int forcheck(char arr[],int size){
		int pcount=0,qcount=0,f=0;
	for(int i=0;i<size;i++){
		if(arr[i]==';')pcount++;
		
		if(arr[i]=='\'')qcount++;
	
		}
	if(pcount!=2)f=1;
	if(qcount%2!=0)f=1;
	
	
	return f;
	
}
int whilecheck(char arr[],int size){
		int pcount=0,qcount=0,f=0,icount=0;
	for(int i=0;i<size;i++){
		if(arr[i]==';')f=1;
		
		if(arr[i]=='\'')qcount++;
		if(arr[i]=='\"')icount++;
		}
		
		
	if(qcount%2!=0)f=1;
	if(icount%2!=0)f=1;
	
	
	return f;
	
}

void fcheck(fileline arr[],int len){
	char str[100],a[100];
	//char sync[32][10]={"auto","double","int","struct","break","else","long","switch","case","enum","register","typedef","char","extern","return","union","const","float","short","unsigned","continue","for","signed","void","default","goto","sizeof","volatile","do","if","static","while"};		
	char sync[8][10]={"printf","scanf","gets","puts","fscanf","fprintf","for","while"};
	int i,j,l,f;
	
	for (i=0;i<len;i++){
		int pos=0,k=0;
		strcpy(str,arr[i].linetext);
		for(j=0;j<arr[i].linelen;j++){
			if (str[j]==' '||str[j]=='('|| str[j]=='\0'||str[j]=='\t'){
				a[k]='\0';
					if (strcmp(a,sync[0])==0){
						
						f=printcheck(str,arr[i].linelen);
						
						if(f)printf("Error in Statement; ---> line no: %d\n",arr[i].lineno);
					} 
					if (strcmp(a,sync[1])==0){
						
						f=scancheck(str,arr[i].linelen);
						if(f)printf("Error in Statement : ---> line no: %d\n",arr[i].lineno);
					} 
					if (strcmp(a,sync[2])==0){
						
						f=getscheck(str,arr[i].linelen);
						if(f)printf("Error in Statement : ---> line no: %d\n",arr[i].lineno);
					} 
			
			if (strcmp(a,sync[3])==0){
						
						f=putscheck(str,arr[i].linelen);
						if(f)printf("Error in Statement : ---> line no: %d\n",arr[i].lineno);
					} 
			if (strcmp(a,sync[4])==0){
						
						f=fscanfcheck(str,arr[i].linelen);
						if(f)printf("Error in Statement : ---> line no: %d\n",arr[i].lineno);
					} 
			if (strcmp(a,sync[5])==0){
						
						f=fprintfcheck(str,arr[i].linelen);
						if(f)printf("Error in Statement : ---> line no: %d\n",arr[i].lineno);
					} 
			if (strcmp(a,sync[6])==0){
						
						f=forcheck(str,arr[i].linelen);
						if(f)printf("Error in Statement : ---> line no: %d\n",arr[i].lineno);
					} 						
			if (strcmp(a,sync[7])==0){
						
						f=whilecheck(str,arr[i].linelen);
						if(f)printf("Error in Statement : ---> line no: %d\n",arr[i].lineno);
					} 	
				k=0;
				
			}
			else {a[k]=str[j]; k++;}
		}
	}
}




