#include <iostream>
#include "Graph.hpp"

Graph graph;

int main(){

    int answer=-1;

    std::cout << "What input do you want to use?" << std::endl;
    std::cout << "File (0) or Your input (1)" << std::endl;
    std::cin >> answer;

    if(answer){
        int vert, range;
        std::cout << "Vertex number: ";
        std::cin >> vert;
        std::cout << "Range: ";
        std::cin >> range;
        
       graph.initRandomGraph(vert, range);
    }
    else{
        graph.initGraphFromFile("test.txt");
    }
    graph.generateAdjacencyMatrix();
    //graph.printGraph();

    std::pair<float, std::vector<int>> result = graph.greedyTSP();
    float min_distance = result.first;
    std::vector<int> min_route = result.second;

    std::cout << "Calculated distance: " << min_distance << std::endl;
    std::cout << "Calculated route: ";
    for (int i = 0; i < min_route.size(); i++){
        std::cout << min_route[i] + 1 << " ";
    }

    return 0;
}