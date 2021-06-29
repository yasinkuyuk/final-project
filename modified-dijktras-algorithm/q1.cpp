
/***********************************************************
 * name: yasin küyük
 * id: 150170059
**********************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

#define INT_MAX 1000

struct Edge{
	int src;
	int dest;
	int weight;
};

using namespace std;
class Graph{
public:
	int node_count;
	int edge_count;
	int** adjacency_matrix;

	Graph(){};
	void read_file(char* filename);
	void print_adjacency_matrix(); // in case you need
	int weight(int i, int j){return this->adjacency_matrix[i][j];}
	~Graph();
};

Graph::~Graph(){
	for(int i = 0; i < node_count; i++){
		delete [] adjacency_matrix[i];
	}
}

void Graph::print_adjacency_matrix(){	
	// Prints the adjacency matrix
	for(int i = 0; i < this->node_count; i++){
		for(int j = 0; j < this->node_count; j++){
			cout<<this->adjacency_matrix[i][j]<<", ";
		}
		cout<<endl;
	}
}

void Graph::read_file(char* filename){
	ifstream file;
	file.open(filename);
	string line;
	int flag = 0;

	while(!file.eof()){
		if(!flag){
			getline(file,line,'\n');
			this->node_count = stoi(line);
			this->adjacency_matrix = new int*[node_count];
			for(int i=0; i<node_count; i++){
				adjacency_matrix[i] = new int[node_count];
			}
			for(int m=0; m < this->node_count; m++){
				for(int n=0; n < this->node_count; n++){
					this->adjacency_matrix[m][n] =0;
				}
			}
		}
		else{
			int src,dest,width;
			getline(file,line,'\t');
			src = stoi(line);

			getline(file,line,'\t');
			dest = stoi(line);

			getline(file,line,'\n');
			width = stoi(line);

			this->adjacency_matrix[src][dest] = width;
			this->adjacency_matrix[dest][src] = width; //double connection of indirected graph
		}
		flag++;
	}
	this->edge_count = flag-1;;
}

vector<Edge> edgeFinder(Graph* graph,int sourceVertex){
	vector<Edge> edges;
	Edge temp;

	for(int j=0; j< graph->node_count; j++){
		if(graph->adjacency_matrix[sourceVertex][j] != 0){
			temp.src = sourceVertex;
			temp.dest = j;
			temp.weight = graph->adjacency_matrix[sourceVertex][j];
			edges.push_back(temp);
		}
	}
	return edges;
}

void Modified_Dijkstra(Graph* graph){
	vector<int> status(graph->node_count);
	int wt[graph->node_count];
	int dad[graph->node_count];

	int v;
	for(v=0; v<graph->node_count;v++){
		status.push_back(0);
		wt[v] = -1;
		dad[v] = -1;
	}

	status[0] = 2;
	wt[0] = INT_MAX;

	vector<Edge> edges = edgeFinder(graph,0); //function for finding edges with given vertex
	Edge temp;

	for(auto edge:edges){
		status[edge.dest] = 1;
		wt[edge.dest] = edge.weight;
		dad[edge.dest] = edge.src;
	}

	while(count(status.begin(), status.end(), 1 )){
		int max = 0;
		//finding the maximum wt-value of fringe vertices
		for(int index =0; index < graph->node_count; index++){
			if(status[index] == 1){
				if(wt[index] >= max){
					max = wt[index];
					v  = index;
				}
			}	
		}
		status[v] = 2;
		edges = edgeFinder(graph,v);

		for(auto edge: edges){
			if(status[edge.dest] == 0){
				status[edge.dest] = 1;
				wt[edge.dest] = min(wt[v],edge.weight);
				dad[edge.dest] = v;
			}
			else if(status[edge.dest] == 1 && wt[edge.dest] < min(wt[v],edge.weight)){
				wt[edge.dest] = min(wt[v],edge.weight);
				dad[edge.dest] = v;
			}
		}
	}

	cout<<"###########RESULTS###########"<<endl;
	cout<<endl;
	
	cout<<"1. WT ARRAY"<<endl;
	cout<<"------------------------"<<endl;
	cout<<"  ";
	for(int i = 0; i < graph->node_count - 1; i++){
		cout << wt[i] << ", ";
	}
	cout << wt[graph->node_count - 1] << endl;
	
	int iterator = graph->node_count - 1;
	vector<int> path_info;
	path_info.push_back(iterator);
	while(iterator != 0){
		path_info.push_back(dad[iterator]);
		iterator = dad[iterator];
	}
	cout<<endl;
	cout<<"2. MAXIMUM CAPACITY PATH"<<endl;
	cout<<"------------------------"<<endl;
	cout<<"  ";
	vector<int>::iterator it;
    for (it = path_info.end() - 1; it > path_info.begin(); it--)
        cout << *it << " -> ";
    cout<<*path_info.begin()<<endl;
    
    cout<<endl;
    cout<<"3. MAXIMUM CAPACITY"<<endl;
    cout<<"------------------------"<<endl;
    cout<<"  ";
    cout<<wt[graph->node_count - 1]<<endl;
    cout<<"#############################"<<endl;
    
    return;
}

int main(int argc, char **argv){
	Graph* graph = new Graph();
	graph->read_file(argv[1]);
	Modified_Dijkstra(graph);
	
	return 0;	
}
