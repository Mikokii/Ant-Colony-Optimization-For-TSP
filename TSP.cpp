#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

float calculateDistance(pair<int, int> point1, pair<int, int> point2);
vector<pair<int, int>> generateVerticesList(int vertices_number, int range);
vector<vector<float>> generateAdjacencyMatrix(int vertices_number, vector<pair<int, int>> vertices_list);

int main(){
    int vertices_number, range;
    vector<pair<int, int>> vertices_list, all_pairs_list;
    vector<vector<float>> adjacency_matrix;
    srand(time(nullptr));

    cout << "Vertex number: ";
    cin >> vertices_number;
    cout << "Range: ";
    cin >> range;

    vertices_list = generateVerticesList(vertices_number, range);

    for (int i = 0; i < vertices_number; i++){
        cout << vertices_list[i].first << " " << vertices_list[i].second << endl;
    }

    adjacency_matrix = generateAdjacencyMatrix(vertices_number, vertices_list);

    for (int i = 0; i < vertices_number; i++){
        for (int j = 0; j < vertices_number; j++){
            cout << adjacency_matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

vector<pair<int, int>> generateVerticesList(int vertices_number, int range){
    vector<pair<int, int>> vertices_list, all_pairs_list;
    for (int i = 0; i < vertices_number; i++){
        for (int j = 0; j < vertices_number; j++){
            all_pairs_list.push_back(pair<int, int>(i,j));
        }
    }

    random_shuffle(all_pairs_list.begin(), all_pairs_list.end());
    for (int i = 0; i < vertices_number; i++){
        vertices_list.push_back(all_pairs_list[i]);
    }

    return vertices_list;
}

vector<vector<float>> generateAdjacencyMatrix(int vertices_number, vector<pair<int, int>> vertices_list){
    vector<vector<float>> adjacency_matrix;
    for (int i = 0; i < vertices_number; i++){
        adjacency_matrix.push_back(vector<float>(vertices_number, -1));
        for (int j = 0; j < vertices_number; j++){
            if (i != j){
                adjacency_matrix[i][j] = calculateDistance(vertices_list[i], vertices_list[j]);
            }
        }
    }
    return adjacency_matrix;
}

float calculateDistance(pair<int, int> point1, pair<int, int> point2) 
{ 
    return sqrt(pow(point2.first - point1.first, 2) + pow(point2.second - point1.second, 2) * 1.0); 
}