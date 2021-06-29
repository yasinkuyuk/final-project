/* * * * * * * * * * * * * * * * * * * * * * * * * *
    name: yasin küyük
    id: 150170059
 * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

//structure to keep square matrix's dimension
struct Matrix{
    int** matrix;
    int size;
};

Matrix createAdjacencyMatrix(vector<vector<int>>&); //function to create adjacency matrix of given graph's one side directed form

class Solution {
public:
    bool isBipartite(vector<vector<int> >& graph) {
        Matrix m = createAdjacencyMatrix(graph);
        int** adj = m.matrix;
        //two set initilization to keep partites of the graph
        vector<int> firstSet; 
        vector<int> secondSet;

        for(int i=0; i<m.size; i++){
            for(int j=0; j< m.size; j++){
                if(adj[i][j] != 0){
                    if(count(firstSet.begin(), firstSet.end(), i)){
                        if(count(firstSet.begin(), firstSet.end(), j)){
                            return false;
                        }
                    }
                    else if(count(secondSet.begin(), secondSet.end(), i)){
                        if(count(secondSet.begin(), secondSet.end(), j)){
                            return false;
                        }
                    }
                    if(count(firstSet.begin(), firstSet.end(), i)){
                        secondSet.push_back(j);
                    }
                    else if(count(secondSet.begin(), secondSet.end(), i)){
                        firstSet.push_back(j);
                    }
                    else if(count(firstSet.begin(), firstSet.end(), j)){
                        secondSet.push_back(i);
                    }
                    else if(count(secondSet.begin(), secondSet.end(), j)){
                        firstSet.push_back(i);
                    }
                    else{
                        firstSet.push_back(i);
                        secondSet.push_back(j);
                    }
                }
            }
        }
        return true;
    }
};

void printv(vector <vector <int> > v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++)
            cout << v[i][j] << " ";
        cout << endl;
    }
}

Matrix createAdjacencyMatrix(vector<vector<int>>& graph){
    Matrix result;
    int nodeCount = graph.size();
    int** matrix = new int*[nodeCount];
    for(int m=0; m<nodeCount; m++){
        matrix[m] = new int[nodeCount];
    }

    int i,j;
    for(i=0; i<nodeCount; i++){
        for(j=0; j<nodeCount; j++){
            matrix[i][j] = 0;
        }
    }

    i =0;
    for(auto node:graph){
        for(auto adj: node){
            matrix[i][adj] = 1;
        }
        i += 1;
    }

    for(i =0; i<nodeCount; i++){
        for(j = 0; j<nodeCount;j++){
            if(matrix[i][j] != 0){
                matrix[j][i] = 0;
            }
        }
    }

    result.matrix = matrix;
    result.size = nodeCount;

    return result;
}

int main()
{
    // Solution class for bipartite-ness problem
    Solution s;

    string fname;
    cin >> fname;
    ifstream graphFileHandler(fname);

    // An array of integers to store neighbours of a vertex
    vector <int> adj;
    // A 2D array of integers to store neighbours of each vertex in a graph
    vector<vector <int> > graph;

    string line;
    while (graphFileHandler >> line) {
        stringstream ss(line);
        string substr;

        while (ss.good()) {
            getline(ss, substr, ',');
            // Push the substring in adjacency list, we got a neighbour here
            adj.push_back(stoi(substr));
        }

        graph.push_back(adj);

        // Clear the array, before the next iteration begins
        adj.clear();
    }

    //printv(graph);


    bool answer = s.isBipartite(graph);

    if (answer == 1){
        cout << "True" <<endl;
    }
    else{
        cout << "False" << endl;
    }

    return 0;
}

