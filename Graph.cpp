#include "Graph.h"
#include <random>
#include <algorithm>
#include <fstream>

Graph::Graph(int vertices_number, int range){
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

Graph::Graph(const char* filename){
    std::ifstream inputFile(filename);
    if(inputFile.is_open()){
        inputFile >> vertices_number;
        int edge_number, v1, v2;
        
    }else{
        std::cout << "Error. Couldn't open file: " << filename << std::endl;
    }
}

Graph::~Graph(){}