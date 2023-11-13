#include "Graph.hpp"

#include <random>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <limits>

Graph::Graph(){}

Graph::~Graph(){}

void Graph::initRandomGraph(int vert, int range){
    vertices_number = vert;
    std::cout << vertices_number << std::endl;
    std::vector<std::pair<int, int>> all_pairs_list;

    std::random_device rd;
    std::mt19937 g(rd());

    for (int i = 0; i < vertices_number; i++){
        for (int j = 0; j < vertices_number; j++){
            all_pairs_list.push_back(std::pair<int, int>(i,j));
        }
    }

    std::shuffle(all_pairs_list.begin(), all_pairs_list.end(), g);

    for (int i = 0; i < vertices_number; i++){
        vertices_list.push_back(all_pairs_list[i]);
    }
}

void Graph::initGraphFromFile(const char* filename){
    std::ifstream inputFile(filename);
    if(inputFile.is_open()){
        inputFile >> vertices_number;
        int edge_number, v1, v2;
        while (inputFile >> edge_number >> v1 >> v2){
            vertices_list.push_back(std::pair<int, int>(v1, v2));   
        }
        
    }else{
        std::cout << "Error. Couldn't open file: " << filename << std::endl;
    }
}

void Graph::printGraph(){
    std::cout << "Point coordinates: " << std::endl;
    for (int i = 0; i < vertices_number; i++){
        std::cout << vertices_list[i].first << " " << vertices_list[i].second << std::endl;
    }
        std::cout << "-----------------------------------------------------------" << std::endl;

    std::cout << "Adjacency matrix: " << std::endl;
    for (int i = 0; i < vertices_number; i++){
        for (int j = 0; j < vertices_number; j++){
            printf("%.4f ", adjacency_matrix[i][j]);
            //cout << adjacency_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------------------------------------------------" << std::endl;
}

void Graph::generateAdjacencyMatrix(){
    for (int i = 0; i < vertices_number; i++){
        adjacency_matrix.push_back(std::vector<float>(vertices_number, -1));
        for (int j = 0; j < vertices_number; j++){
            if (i != j){
                adjacency_matrix[i][j] = calculateDistance(vertices_list[i], vertices_list[j]);
            }
        }
    }
}

std::pair<float, std::vector<int>> Graph::greedyTSP(){
    std::vector<int> visited(vertices_number, 0), route;
    int current_vertex, destination_vertex;
    float min_distance, full_distance = 0.0;

    route.push_back(0);
    visited[0] = 1;
    while (route.size() < vertices_number){
        min_distance = std::numeric_limits<float>::max();
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
    
    return std::pair<float, std::vector<int>>(full_distance, route);
}

float calculateDistance(std::pair<int, int> point1, std::pair<int, int> point2){
    return sqrt(pow(point2.first - point1.first, 2) + pow(point2.second - point1.second, 2) * 1.0); 
}