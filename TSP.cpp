#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <random>
#include <fstream>
using namespace std;

float calculateDistance(pair<int, int> point1, pair<int, int> point2);
vector<pair<int, int>> generateVerticesList(int vertices_number, int range);
bool getVerticesFromFile(const char* filename, vector<pair<int, int>>* vertices_list);
vector<vector<float>> generateAdjacencyMatrix(int vertices_number, vector<pair<int, int>> vertices_list);
pair<float, vector<int>> greedyTSP(vector<vector<float>> adjacency_matrix, int vertices_number);

int main(){
    int vertices_number, range;
    vector<pair<int, int>> vertices_list;
    vector<vector<float>> adjacency_matrix;
    pair<float, vector<int>> result;
    float min_distance;
    vector<int> min_route;

    int answer;
    cout << "What input do you want to use?" << endl;
    cout << "File (0) or Your input (1)" << endl;
    cin >> answer;
    
    if(answer){
        cout << "Vertex number: ";
        cin >> vertices_number;
        cout << "Range: ";
        cin >> range;
        
        vertices_list = generateVerticesList(vertices_number, range);
    }
    else{

    }

    cout << "Point coordinates: " << endl;
    for (int i = 0; i < vertices_number; i++){
        cout << vertices_list[i].first << " " << vertices_list[i].second << endl;
    }
    cout << "-----------------------------------------------------------" << endl;

    adjacency_matrix = generateAdjacencyMatrix(vertices_number, vertices_list);

    cout << "Adjacency matrix: " << endl;
    for (int i = 0; i < vertices_number; i++){
        for (int j = 0; j < vertices_number; j++){
            printf("%.4f ", adjacency_matrix[i][j]);
            //cout << adjacency_matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-----------------------------------------------------------" << endl;

    result = greedyTSP(adjacency_matrix, vertices_number);
    min_distance = result.first;
    min_route = result.second;

    cout << "Calculated distance: " << min_distance << endl;
    cout << "Calculated route: ";
    for (int i = 0; i < min_route.size(); i++){
        cout << min_route[i] << " ";
    }
    return 0;
}

vector<pair<int, int>> generateVerticesList(int vertices_number, int range){
    vector<pair<int, int>> vertices_list, all_pairs_list;
    random_device rd;
    mt19937 g(rd());

    for (int i = 0; i < vertices_number; i++){
        for (int j = 0; j < vertices_number; j++){
            all_pairs_list.push_back(pair<int, int>(i,j));
        }
    }

    shuffle(all_pairs_list.begin(), all_pairs_list.end(), g);
    for (int i = 0; i < vertices_number; i++){
        vertices_list.push_back(all_pairs_list[i]);
    }

    return vertices_list;
}

bool getVerticesFromFile(const char* filename, vector<pair<int, int>>* vertices_list){
    ifstream inputFile(filename);
    if(inputFile.is_open()){
        return 1;
    }else{
        cout << "Error. Couldn't open file: " << filename << endl;
        return 0;
    }
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

float calculateDistance(pair<int, int> point1, pair<int, int> point2) { 
    return sqrt(pow(point2.first - point1.first, 2) + pow(point2.second - point1.second, 2) * 1.0); 
}

pair<float, vector<int>> greedyTSP(vector<vector<float>> adjacency_matrix, int vertices_number){
    vector<int> visited(vertices_number, 0), route;
    int current_vertex, destination_vertex;
    float min_distance, full_distance = 0.0;

    route.push_back(0);
    visited[0] = 1;
    while (route.size() < vertices_number){
        min_distance = numeric_limits<float>::max();
        current_vertex = route.back();
        for (int i = 0; i < vertices_number; i++) {
            if (current_vertex != i && !visited[i] && adjacency_matrix[current_vertex][i] < min_distance) {
                min_distance = adjacency_matrix[current_vertex][i];
                destination_vertex = i;
            }
        }
        route.push_back(destination_vertex);
        visited[destination_vertex] = 1;
        full_distance += min_distance;
    }
    route.push_back(0);
    full_distance += adjacency_matrix[0][destination_vertex];
    
    return pair<float, vector<int>>(full_distance, route);
}