//clusterName: contains IP address of all the VMs in this cluster

#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<utility>

#define threshold 0.5

using namespace std;

typedef pair<string, int> psi;
typedef vector<psi> vpsi;
vpsi cpuV;//ip, cpu usage
bool compare2(psi a, psi b){
	return a.second<b.second;
}

void migrate(string sourceIP,string destIP){
	system(("echo "+destIP+" >destIp").c_str());
	system(("scp destIp csisadmin@"+sourceIP+":.").c_str());
	system(("ssh csisadmin@"+sourceIP+" <<'ENDSSH'\ncd /mnt/kvmshared/poojaAkankshaCloud\n./domainID.sh\n./findEachVMTime > vmTime").c_str());// file name: VMTime is created in sorted form
	}

int main(){
	
	FILE* phyFile=fopen("physicalInfrastructure","r");
	int nodePhy;
	
	fscanf(phyFile,"%d",&nodePhy);
	cpuV.resize(nodePhy);
	FILE* fCPUstat=fopen("usageStat","w");//create a new file, shared folder
	char ip[20];
	for(int i=0;i<nodePhy;i++){
		
		fscanf(phyFile,"%s",ip);
		cpuV[i].first=string(ip);
		//cout<<cpuV[i].first;
		system(("rsysinfo "+cpuV[i].first+"|grep load>> usageStat").c_str());
		system("./usageStat.sh");	
}
	
	fclose(phyFile);
		
	FILE* fp=fopen("finalUsageStat","r");
	if(!fp)
		return 0;
	for(int i=0;i<nodePhy;i++){
		int d;
		fscanf(fp,"%d",&d);
		cpuV[i].second=d;
		}
	sort(cpuV.begin(),cpuV.end(),compare2);
	int start=0,end=nodePhy-1;
	while(cpuV[end].second>threshold){
		migrate(cpuV[end].first,cpuV[start].first);
		end--;
		start++;
		if(start>=end)//everything is overloaded it seems!
			break;
	}
	
}
