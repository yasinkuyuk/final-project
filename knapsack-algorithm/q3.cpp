/*
	name: yasin küyük
	id: 150170059
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <set>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

pair<int, set<int>> MaxProfit(int numOfCrystals, vector<int> entryCosts, vector<int> profit)
{
	int numOfCities = entryCosts.size();
	int matrix[numOfCities+1][numOfCrystals+1];
	int i,j; //loop iterators
	set<int> citiesToVisit;

	//initiliazing the matrix
	for(i = 0; i <= numOfCities; i++)
    {
        for(j = 0; j <= numOfCrystals; j++)
        {
            if (i == 0 || j == 0){
                matrix[i][j] = 0;
			}
            else if (entryCosts[i - 1] <= j){
                matrix[i][j] = max(profit[i - 1] + matrix[i - 1][j - entryCosts[i - 1]] , matrix[i - 1][j]);
			}
            else{
                matrix[i][j] = matrix[i - 1][j];
			}
        }
    }

	int maxProfit = matrix[numOfCities][numOfCrystals];
	i = numOfCities;
	j = numOfCrystals;

	while(i>0 && j>0){
		if(matrix[i][j] != matrix[i-1][j]){
			citiesToVisit.insert(i);
			j = j -entryCosts[i-1];
		}
		i = i-1;
	}


	cout << "Dynaming Programming Table" << endl;
	for (i = 0; i <= numOfCities; i++) {
		for (j = 0; j <= numOfCrystals; j++) {
			cout << std::right << std::setw(3) << matrix[i][j];
		}
		cout << endl;
	}

	return pair<int, set<int>>(maxProfit, citiesToVisit);
}

int main() {
	int numOfCrystals;
	vector<int> entryCosts;
	vector<int> profit;
	string inputFilename;
	cout << "Enter the name of the input file: ";
	cin >> inputFilename;

	ifstream input(inputFilename);

	if (!input.is_open()) {
		cerr << "File named \"" << inputFilename << "\" could not open!" << endl;
		return EXIT_FAILURE;
	}

	string line;
	if (getline(input, line)) {
		numOfCrystals = stoi(line);
	}
	while (getline(input, line, ' ')) {
		profit.push_back(stoi(line));
		getline(input, line);
		entryCosts.push_back(stoi(line));
	}

	pair<int, set<int>> result = MaxProfit(numOfCrystals, entryCosts, profit);

	cout << "Max profit is " << result.first << "." << endl;
	cout << "Cities visited:";
	for (int cityNumber : result.second) {
		cout << " " << cityNumber;
	}
	cout << endl;

	return EXIT_SUCCESS;
}

