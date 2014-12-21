#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;

FILE* vmFiles;

void xmlWrite(FILE* fpModify,int loc,char *str){
	fseek(fpModify,loc,SEEK_SET);
	//cout<<str;
	
	fwrite(str,sizeof(char),strlen(str),fpModify);
}
int nodF(int counter){
	int digit=0;
	while(counter){
		counter=counter/10;
		digit++;
		}
	cout<<"digit"<<digit<<endl;
	return digit;
	}
void itoa(int counter,char* counterString){
	int nod=nodF(counter);
	counterString[nod]='\0';
	for(int i=nod-1;i>=0;i--){
		counterString[i]=(char)('0'+counter%10);
		counter=counter/10;
	}
}
string st;
void prepareName(char* sizeRAM,char* requireFileName,char* counterString,char* macID){
	char requireImg[10];
	char finalRequireXML[10];
	strcpy(requireImg, requireFileName);
	strcpy(finalRequireXML,"/home/csisadmin/");
	strcat(finalRequireXML, requireFileName);
	strcat(finalRequireXML,".xml");
	FILE* fpModify=fopen(finalRequireXML,"r+");//via Image
	FILE* fpConfig=fopen("configLocation.txt","r");
//for location of currentMemory, name, uuid,source img, mac address
	int locCurrentMemory,locName, locUuid,locImg, locAdd;// no need to change memory, but only currentMemory
	
	fscanf(fpConfig,"%d",&locName);
	fscanf(fpConfig,"%d",&locUuid);
	fscanf(fpConfig,"%d",&locCurrentMemory);
	fscanf(fpConfig,"%d",&locImg);
	fscanf(fpConfig,"%d",&locAdd);

	xmlWrite(fpModify,locCurrentMemory,sizeRAM);
	
	
	char vmName[7];
	vmName[0]='V';
	vmName[1]='M';
	vmName[2]='\0';
	strcat(vmName,counterString);
	
	xmlWrite(fpModify,locName,vmName);
	cout<<vmName;
	string vmNameStr(vmName);
	system(("echo "+vmNameStr+" >> "+st).c_str());
	//fprintf(vmFiles,"%s\n",vmName);
	xmlWrite(fpModify,locUuid,counterString);
	xmlWrite(fpModify,locImg,requireImg);
	xmlWrite(fpModify,locAdd,macID);
	fclose(fpModify);
	fclose(fpConfig);
}
void findMac(int line, char *mac){
	FILE* fp=fopen("mac.txt","r");
	int i=0;
	while(i<line){
		char c=fgetc(fp);
		while(c!='\n')
			c=fgetc(fp);
		i++;
	}
	fgets(mac,18,fp);
	fclose(fp);
}
void findRequireFileName(char* r, char* counterString,char *macID){
	FILE* fpCounter=fopen("/home/csisadmin/counter.txt","r");
	int counter;
	fscanf(fpCounter,"%d",&counter);
	counter++;
	fclose(fpCounter);
	fpCounter=fopen("/home/csisadmin/counter.txt","w"); 
	findMac(counter,macID);
	fprintf(fpCounter, "%d", counter);
	itoa(counter,counterString);
	strcat(r,counterString);
	fclose(fpCounter);

}
int main__(){
	return 0;
}

int main(int argc, char *argv[]){
	//vmFiles=fopen(argv[3],"r+");
	st=string(argv[3]);
	system(("ifconfig br0 | grep 'inet addr' | cut -d: -f2 | awk '{print $1}' >>"+st).c_str());
	//fprintf(vmFiles,"\n");
	cout<<argv[1]<<argv[2];
	//max # of VM: 3 digits, max # of digits in RAM- 7
	int numberOfNodes;
	//system("virsh -c qemu:///system list");
	char sizeRAM[10];
	char macID[100];
	//cin>>numberOfNodes>>sizeRAM;
	numberOfNodes=atoi(argv[1]);
	strcpy(sizeRAM,argv[2]);
		
	while(numberOfNodes){
		char requireFileName[200];
		requireFileName[0]='r';
		requireFileName[1]='\0';
		char counterString[4];
		findRequireFileName(requireFileName,counterString,macID);
	
	string str(requireFileName);
	string str2("VM");
	str+=".xml";
	system(("cp newXML.xml /home/csisadmin/"+ str).c_str());
	//string imgStr(requireFileName);
	//imgStr+=".img";
	//system(("cp new.img "+ imgStr).c_str()); //is already copied, so don't copy man!
	
	prepareName(sizeRAM,requireFileName, counterString,macID);
	str2+=counterString;
	int len=strlen(counterString);
	for(int i=len;i<3;i++){
		str2+="0";	
		
	}
	char requireXML[200];
	strcpy(requireXML,"/home/csisadmin/");
	strcat(requireXML, requireFileName);
	strcat(requireFileName,".xml");
	system(("virsh define /home/csisadmin/"+str).c_str());
	//system(("virsh start "+str2).c_str());
	numberOfNodes--;	
	//cout<<"I feel good";
	
	}
	//fclose(vmFiles);
	}

	
	
//to change folder of r.xml
//files on home folder- counter.txt, r_.xml, 
//poojaAkankshaCloud/r_.img	
