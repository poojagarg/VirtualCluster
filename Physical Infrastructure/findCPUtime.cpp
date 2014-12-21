#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<string>
#include <fstream>
#include<sstream>
#define numOfVM 10
int cpuTime[numOfVM][2];
using namespace std;

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

int extractTime(string l)
{
	
	int len=l.size();
	int i;

	for(i=0;i<len;i++){
		//cout<<i<<endl;
		if(l[i]==' '){
			while(l[i]==' '||l[i]=='\t')
				i++;		
			break;
		}
	}

	
	char fl[200];
	int index=0;
	//cout<<len;


	for(;i<len;i++){
		fl[index++]=l[i];
		if(l[i+1]=='.'){

			fl[index]='\0';
			break;
		}
	}
		int totalTime=0;
	index--;
	i=0;
	while(i<=index){
		totalTime=totalTime*10+(fl[i]-'0');
		i++;
	}
	
	return totalTime;
	
}

void sortCpuTime(int n)
{
	int i,p,j,temp1, temp2;
	//cout<<"inside sort\n";
	for(p=0;p<=n-1;p++)             // Loop for Pass
	{
		for(j=0;j<=n-2;j++)
		{
			if(cpuTime[j][1]>cpuTime[j+1][1])
			{
				temp1=cpuTime[j][0];                      // Interchange Values
				temp2=cpuTime[j][1];
				cpuTime[j][0]=cpuTime[j+1][0];
				cpuTime[j][1]=cpuTime[j+1][1];
				cpuTime[j+1][0]=temp1;
				cpuTime[j+1][1]=temp2;
			}
		}
	}
	for(int i=0;i<n;i++){
		cout<<cpuTime[i][0]<<":"<<cpuTime[i][1]<<endl;
	}
}

int main()
{
	string vmDomains[numOfVM],line, total="Total:";
	char *line1;
	
	FILE* fcpuStat=fopen("cpuStats.txt","w");
	fclose(fcpuStat);
	int i;
	size_t sz;
	system("wc -l domainID > numberOfDomain.txt");
	FILE* fNod=fopen("numberOfDomain.txt","r");
	int localnumOfVM=1;
	fscanf(fNod,"%d",&localnumOfVM);
	fclose(fNod);
	fNod=fopen("domainID","r");//name of domains
	for(i=0; i<localnumOfVM; i++)
	{
		char domainID[10];
		fscanf(fNod,"%s",domainID);
		vmDomains[i]= string(domainID);
		system(("virsh cpu-stats "+vmDomains[i]+" >> cpuStats.txt").c_str());
	}
//	system("cat cpuStats.txt");
//	i=0;
	ifstream stats("cpuStats.txt");
	if (stats.is_open())
	{
		i=0;
		while ( getline(stats,line) )
		{
			if(line.compare(total)==0)
			{
				getline(stats,line);
				//cout<<line<<"\n";
				stringstream ss(vmDomains[i]);
				int k;
				ss >> k;
				cpuTime[i][0]= k;// id of CPU
				cpuTime[i][1]=extractTime(line);
				//cout<<cpuTime[i][0]<<":"<<cpuTime[i][1]<<endl;
				i++;
			}
		}
		stats.close();
	}
	else
		 cout << "Unable to open file";


//cout <<" after closing file \n";
	sortCpuTime(localnumOfVM);
	FILE* fp=fopen("/home/csisadmin/destIp","r");
	char destIpArr[20];
	fscanf(fp,"%s",destIpArr);
	string destIp(destIpArr);
	char domainIDArr[10];
	itoa(cpuTime[localnumOfVM][0],domainIDArr);
	string domainID(domainIDArr);
	cout<<domainID;
	//system(("virsh domname "+domainID).c_str());	
	FILE* fp2=fopen("domainNameFile","r");
	char domainNameArr[10];
	fscanf(fp2,"%s",domainNameArr);
	string str(domainNameArr);
	system(("echo sudo virsh migrate --live --undefinesource"+ domainID +"qemu+ssh://csisadmin@"+destIp+"/system tcp://"+destIp).c_str());
}
