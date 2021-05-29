#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

void getpath(vector<vector<pair<int,int>>>adjac, vector<unordered_set<int>> demons, vector<int> &path)
{
	auto cmp=[&](  const int &i , const int &j)
	{
		return path[i]>path[j];
	};
	priority_queue< int, vector<int>, decltype(cmp)>q(cmp);
	q.push(1);
	while(!q.empty())
	{
		int current=q.top();
		q.pop();
		if(demons[current].find(path[current])!=demons[current].end())
		{
			path[current]++;
			q.push(current);
		}
		else
		{
			for(int j=0; j<adjac[current].size(); j++)
			{
				pair<int,int>next=adjac[current][j];
				
				if(path[next.first]==-1||path[next.first]>path[current]+next.second)
				{
					path[next.first]=path[current]+next.second;
					q.push(next.first);
				}
			}
			
		}
	}
}


int main() {
	int universe=0,portal=0;
	cin>>universe;
	cin>>portal;
	vector<vector<pair<int,int>>>adjac(portal+1);
	for(int i=0; i<portal; i++)
	{
		int a,b,c;
		cin>>a;
		cin>>b;
		cin>>c;
		adjac[a].push_back(make_pair(b,c));
	}
	vector<unordered_set<int>>demons(universe+1);
	for(int i=1; i<=universe; i++)
	{
		int a;
		cin>>a;
		for(int j=0; j<a; j++)
		{
			int b;
			cin>>b;
			demons[i].insert(b);
		}
	}
	vector<int>path(universe+1,-1);
	path[1]=0;
	/*for(int i=0; i<path.size(); i++)
	{
		cout<<path[i]<<"\t";
	}*/
	getpath(adjac,demons,path);

	cout<<path[universe];
	return 0;
}
