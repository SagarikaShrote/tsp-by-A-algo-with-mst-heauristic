#include<bits/stdc++.h>
using namespace std;
#define n 15
int numNodes=0;
// A utility function to find the vertex with 
// minimum key value, from the set of vertices 
// not yet included in MST 
int minKey(/*int n,*/ int key[], bool mstSet[],int visited[]) 
{ 
	// Initialize min value 
	int min = __INT_MAX__, min_index; 

	for (int v = 0; v < n; v++) 
		if (visited[v]==0 && mstSet[v] == false && key[v] < min) 
			min = key[v], min_index = v; 

	return min_index; 
} 
int CostOfMST(/*int n, */int parent[], int graph[][n],int visited[]) 
{ 
	int cost=0;
	cout<<"Edge \tWeight\n"; 
	for (int i = 0; i < n; i++) {
		if(parent[i]==-1 || visited[i]==1){cout<<"ignored "<<i<<endl;continue;}
		cout<<parent[i]<<" - "<<i<<" \t"<<graph[i][parent[i]]<<" \n"; 
		cost+=graph[i][parent[i]]; 
	}
	cout<<"cost="<<cost<<endl; 
	return cost;
} 

int primMST(int k, /*int n,*/ int graph[][n],int visited[]){
	
	int mstCost=0;
	// Array to store constructed MST 
	int parent[n]; 
	
	// Key values used to pick minimum weight edge in cut 
	int key[n]; 
	
	// To represent set of vertices included in MST 
	bool mstSet[n]; 

	// Initialize all keys as INFINITE 
	for (int i = 0; i < n; i++) 
		key[i] = __INT_MAX__, mstSet[i] = false; 

	 
	// Make key 0 so that this vertex is picked as first vertex. 
	key[k] = 0; 
	parent[k] = -1; //initialise parent of root as -1

	// The MST will have n vertices 
	for (int count = 0; count < n - 1; count++)
	{ 
		// Pick the minimum key vertex from the 
		// set of vertices not yet included in MST 
		int u = minKey(/*n,*/key, mstSet,visited); 

		// Add the picked vertex to the MST Set 
		mstSet[u] = true; 

		// Update key value and parent index of 
		// the adjacent vertices of the picked vertex. 
		// Consider only those vertices which are not 
		// yet included in MST 
		for (int v = 0; v < n; v++) 

			// graph[u][v] is non zero only for adjacent vertices of m 
			// mstSet[v] is false for vertices not yet included in MST 
			// Update the key only if graph[u][v] is smaller than key[v] 
			if (visited[v]==0 && graph[u][v]>0 && mstSet[v] == false && graph[u][v] < key[v]) 
				parent[v] = u, key[v] = graph[u][v]; 
	} 

	// print the constructed MST 
	mstCost= CostOfMST(/*n,*/parent, graph, visited); 
	return mstCost;
}

void TSPsolve(/*int n,*/ int dM[][n], queue<int>&q, int sc){
	int visited[n]={0};
	stack<int> connect;	//this stored the adjescent nodes to the current considered node
	visited[sc]=1;
	int actCost=0;		//actCost is the actual cost i.e, g(n)
	q.push(sc);
	int prev=sc;		//stores last seen node
	while(q.size()<n){
		for(int i=0;i<n;i++){
			if(visited[i]!=1 && dM[prev][i]>0){
				connect.push(i);
			}
		}
		cout<<"--------------------"<<endl;
		int minMSTcost=INT_MAX,mIndex=-1;		
			// minMSTcost will store the min heuristic cost seen 
			//mIndex will store the node that had min heauristic cost
		while(!connect.empty()){
			//cout<<"consider node "<<connect.top()<<endl;
			int tempMSTcost=primMST(connect.top(),/*n,*/dM,visited);
			if(minMSTcost>tempMSTcost+dM[prev][connect.top()]){
				minMSTcost=tempMSTcost+dM[prev][connect.top()];
				mIndex=connect.top();
			}
			connect.pop();
			numNodes++;
		}
		q.push(mIndex);
		visited[mIndex]=1;
		prev=mIndex;
		cout<<"-->adding "<<mIndex<<endl;
		cout<<"--------------------"<<endl;
	}

}

int CalcTotalCostOfPath(/*int n,*/int dM[n][n], queue<int>&q){
	int c=0;
	//returns the total cost of travel given by our algo.
	int parent=q.front();
	int origin=parent;
	q.pop();
	int t;
	while(!q.empty()){
		t=q.front();
		c+=dM[parent][t];
		q.pop();
		parent=t;
	}
	c+=dM[t][origin];
	return c;
}

int main(){
	//fully connected graph assumed
	int numCities=n,sCity;
	// cout<<"Enter no. of cities:";
	// cin>>numCities;
	int distMatrix[n/*umCities*/][n/*umCities*/];
	ifstream is("input.txt");
	cout<<"Enter adjescency matrix:\n";
	for(int i=0;i<numCities;i++){
		for(int j=0;j<numCities;j++){
			//cin>>distMatrix[i][j];
			is >>distMatrix[i][j];
		}
	}
	is.close();
	cout<<"\nEnter the start city:";
	cin>>sCity;
	queue<int>result,tempq;
	TSPsolve(/*numCities,*/distMatrix,result,sCity);	
	//numCities is no. of cities, distMatrix is the graph matrix containging distance, 
	//result is the resultant queue of cities and sCity is the index of the start city
	tempq=result;
	//printing result->
	cout<<"the order of traversal of salesman would be -"<<endl;
	while(!result.empty()){
		cout<<"node no.	\t"<<result.front()<<endl;
		result.pop();
	}
	cout<<"finally node no.	\t"<<sCity<<endl;
	cout<<"final cost of TSP path is "<<CalcTotalCostOfPath(distMatrix,tempq)<<endl;
	cout<<"no. of expanded nodes = "<<numNodes<<endl;
	return 0;
}