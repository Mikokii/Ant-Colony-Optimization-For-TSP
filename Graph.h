#pragma once

#include <vector>
#include <iostream>

class Graph{
public:
    int vertices_number;
    std::vector<std::pair<int,int>> vertices_list;
    std::vector<std::vector<int>> adjacency_matrix;

    //Graph(){};
    Graph(int vertices_number, int range);
    Graph(const char* filename);
    void generateAdjacencyMatrix();
    ~Graph();
};