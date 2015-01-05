#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<utility>
using namespace std;

string clusterName;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
vpii alloted;
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

bool compare(pii a, pii b){
	return a.first<b.first;
}
bool compare2(pii a, pii b){
	return a.second<b.second;
}

void create(int start,int end,int RAM,int nod){
	for(int j=start;j<=end;j++){
		
		char cRAM[10],cNod[4];
		itoa(RAM,cRAM);
		itoa(nod,cNod);
		string sRAM(cRAM);
		string sNod(cNod);
		string str(ip[alloted[j].second]);
		alloted[j].first+=nod;
		//system(("ssh csisadmin@"+str+" <<'ENDSSH'\ncd poojaCloud\n./createVM "+sNod+" "+sRAM+" "+ clusterName).c_str());//do passwordless ssh
system(("ssh csisadmin@"+str+" <<'ENDSSH'\ncd /mnt/kvmshared/poojaCloud\n./createVM "+sNod+" "+sRAM +" "+ clusterName).c_str());//do passwordless ssh
		}
}
void update(FILE* fp){
	fclose(fp);
	fp=fopen("VMsAllottedTillNow","w");
	int n=alloted.size();
	fprintf(fp,"%d\n",n);
	sort(alloted.begin(),alloted.end(),compare2);
	for(int i=0;i<n;i++){
		fprintf(fp,"%d\n",alloted[i].first);
	}
}
int main(){
	FILE* fp=fopen("physicalInfrastructure","r");
	int nodePhy;
	fscanf(fp,"%d",&nodePhy);
	
	for(int i=0;i<nodePhy;i++){
		fscanf(fp,"%s",ip[i]);
	}
	fclose(fp);
	fp=fopen("VMsAllottedTillNow","r");
	fscanf(fp,"%d",&nodePhy);
	alloted.resize(nodePhy);
	for(int i=0;i<nodePhy;i++){
		int a;
		fscanf(fp,"%d",&a);
		alloted[i].first=a;
		alloted[i].second=i;
	}
	sort(alloted.begin(), alloted.end(), compare);
	cin>>clusterName;
	int numberOfNodes, RAM;
	cin>>numberOfNodes>>RAM;
	int m=alloted[0].first;
	int M=alloted[nodePhy-1].first;
	int k;
	if(m!=M)
		k=(M-m)/numberOfNodes;
	else
		k=nodePhy;
	int nod=numberOfNodes/k;
	create(0,0,RAM,nod+numberOfNodes%k);
	create(1,k-1,RAM,nod);
	update(fp);
	fclose(fp);
}
