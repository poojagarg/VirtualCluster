//Input- no input
//Output- migrates highest CPU using Virtual machines of the processors whose CPU usage is more than a user defined threshold
//files required- physicalInfrastructure
//utility required- rsysinfo
/*Algorithm-
compute usage statistic of all the CPUs
sort the CPU in descending order of their CPU usage
Repeat-
	migrate highest CPU using VM of CPU[start] to CPU[end] 
	until CPU usage of CPU[start]<threshold 
*/
//Things to note- For migration, image of VM to be migrated has to be in shared directory.
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
	system(("ssh csisadmin@"+sourceIP+" <<'ENDSSH'\ncd /mnt/kvmshared/poojaCloud\n./domainID.sh\n./findEachVMTime > vmTime").c_str());
	// file name: VMTime is created in sorted form
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
		//above statement over-writes usage statistic of ith node
		system("./usageStat.sh");	
		//appends the usage statistic of ith node in the file finalUsageStat
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
