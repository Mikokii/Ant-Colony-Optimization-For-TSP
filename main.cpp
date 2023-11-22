#include <iostream>
#include <string>
#include "Graph.hpp"

Graph graph;

int main(int argc, char *argv[]){

    int answer=-1;
    std::string filename;

    if(argc < 1){
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

            graph.saveGraphToFile("out.txt");
        }
            else graph.initGraphFromFile("test.txt");
            filename = "test";
    }
    else {
        graph.initGraphFromFile(argv[1]);
        std::string filename(argv[1]);
        filename =  filename.substr(0, filename.find("."));
        std::cout << filename << std::endl;
    }

    filename += "_wynik.txt";

    graph.generateAdjacencyMatrix();
    // graph.printGraph();

    std::pair<float, std::vector<int>> result = graph.greedyTSP();
    float min_distance = result.first;
    std::vector<int> min_route = result.second;

    //std::ofstream outFile; - trzeba tu zrobić wpisywanie wyników do filename pliku, nie dziala mi deklaracje idk why
    std::cout << "Calculated distance: " << min_distance << std::endl;
    std::cout << "Calculated route: ";
    for (int i = 0; i < min_route.size(); i++){
        std::cout << min_route[i] + 1 << " ";
    }

    return 0;
}