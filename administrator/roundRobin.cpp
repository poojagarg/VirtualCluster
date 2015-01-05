#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
string clusterName;
int quantum=1;
char ip[20][20];
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
//cout<<"CS"<<counterString<<endl;
}
void create(int start,int end,int RAM,int nod){
	for(int j=start;j<=end;j++){
		char cRAM[10],cNod[4];
		itoa(RAM,cRAM);
		itoa(nod,cNod);
		string sRAM(cRAM);
		string sNod(cNod);
		string str(ip[j]);
		system(("ssh csisadmin@"+str+" <<'ENDSSH'\ncd /mnt/kvmshared/poojaCloud\n./createVM "+sNod+" "+sRAM +" "+ clusterName).c_str());//do passwordless ssh
			}
}
int main(){
	
	//max # of VM: 3 digits, max # of digits in RAM- 7
	
	cin>>clusterName;
	int numberOfNodes, RAM;
	cin>>numberOfNodes>>RAM;
	FILE* fp=fopen("physicalInfrastructure","r");
	int nodePhy;
	fscanf(fp,"%d",&nodePhy);
	
	for(int i=0;i<nodePhy;i++){
		fscanf(fp,"%s",ip[i]);
	}
	//numberOfNodes=(nodePhy*i+l)*(quantum)+x, 
	int x=numberOfNodes%quantum;
	int b1=numberOfNodes/quantum;
	int l=b1%nodePhy;
	int i=b1/nodePhy;
	// each node gets i*quantum, first l nodes get quantum each, and l+1 node get x.
	//for first l: (i+1)*quantum), l+1th node: i*quantum+x,remaining get: i*quantum
	int nod=(i+1)*quantum;
	create(0,l-1,RAM,nod);
	nod=i*quantum+x;
	create(l,l,RAM,nod);
	nod=i*quantum;
	create(l+1,nodePhy-1,RAM,nod);
}

	
	
	
