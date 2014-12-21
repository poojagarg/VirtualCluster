#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
//write output of init in configLocation.txt
//keeps all the parameter location to be changed
int find(char* str, FILE* fp){
	
	int len=strlen(str);
	int start=0;
	while(!feof(fp)){
		char c=fgetc(fp);
		
		if(c==str[start]){
			start++;
		
			if(start==len){
				while(c!='>'){
					c=fgetc(fp);
				}
				return ftell(fp);//place to start writing after >, <str>
			}
		}
		else
			start=0;
		
		
	}//end of while
return -1;
}//end of find
int findExact(char* str, FILE* fp){
	
	int len=strlen(str);
	int start=0;
	while(!feof(fp)){
		char c=fgetc(fp);
		
		if(c==str[start]){
			start++;
		
			if(start==len){
				return ftell(fp);//place to start writing after >, <str>
			}
		}
		else
			start=0;
		
		
	}//end of while
return -1;
}//end of find
//save output in configLocation.txt
void init(){
	FILE* fp=fopen("newXML.xml","r");//via Image
	/*order is important, because old value of fp is taken*/
	char buf[200];
	strcpy(buf,"name");
	cout<<find(buf,fp)<<endl;
	strcpy(buf,"uuid");
	cout<<find(buf,fp)<<endl;
	strcpy(buf,"currentMemory");
	cout<<find(buf,fp)<<endl;
	strcpy(buf,"poojaAkankshaCloud/r");//start writing after this
	cout<<findExact(buf,fp)-1<<endl;
	strcpy(buf,"<mac address='");
	cout<<findExact(buf,fp)<<endl;
	fclose(fp);
}
int main(){
	init();
}
