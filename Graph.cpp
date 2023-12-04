#include "Graph.hpp"

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 g(seed);

Graph::Graph(){}

Graph::~Graph(){}

void Graph::initRandomGraph(int vert, int range){
    vertices_number = vert;
    std::cout << vertices_number << std::endl;
    std::vector<std::pair<int, int>> all_pairs_list;

    for (int i = 1; i <= range; i++){
        for (int j = 1; j <= range; j++){
            all_pairs_list.push_back(std::pair<int, int>(i,j));
        }
    }

    std::shuffle(all_pairs_list.begin(), all_pairs_list.end(), g);

    for (int i = 0; i < vertices_number; i++){
        vertices_list.push_back(all_pairs_list[i]);
    }
}

void Graph::saveGraphToFile(const char* filename){
    std::ofstream outputFile(filename);
    if (outputFile.is_open()){
        outputFile << vertices_number << std::endl;
        for (int i = 0; i < vertices_number; i++){
            outputFile << i+1 << " " << vertices_list[i].first << " " << vertices_list[i].second << std::endl;
        }
    } else {
        std::cout << "Error. Couldn't write to file " << std::endl;
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

std::vector<std::vector<float>> Graph::getAdjacencyMatrix(){
    return adjacency_matrix;
}

std::pair<float, std::vector<int>> Graph::antColonySystem(int a_n, int it, float alpha, float beta, float p, float Q, float c){

    std::uniform_int_distribution<int> rng(0, vertices_number-1);

    float min_distance = std::numeric_limits<float>::max();
    std::vector<int> route;

    iterations = it;
    ants_number = a_n;
    std::vector<std::vector<float>> trail_matrix (vertices_number, std::vector<float>(vertices_number, c));
    std::vector<std::vector<float>> tmp_trail_matrix (vertices_number, std::vector<float>(vertices_number,0));
    std::vector<std::vector<int>> ants_paths (ants_number, std::vector<int>());
    std::vector<std::vector<int>> ants_allowed (ants_number, std::vector<int>(vertices_number, 1));
    std::vector<std::vector<long double>> ants_probability (ants_number, std::vector<long double> (vertices_number, 0));

    for (int i = 0; i<iterations; i++){
        std::cout << "Iteration: " << i << "    ";
        for (int a = 0; a < ants_number; a++){
            ants_paths[a].push_back(rng(g));
            ants_allowed[a][ants_paths[a][0]] = 0;
        }
        for(int k = 0; k < vertices_number - 1; k++){
            for (int a = 0; a < ants_number; a++){
                int current_point = ants_paths[a].back();
                calculateProbability(current_point, ants_allowed[a], ants_probability[a], trail_matrix, alpha, beta);
                int point = pickNextPoint(ants_probability[a]);
                ants_paths[a].push_back(point);
                ants_allowed[a][point] = 0;
            }
        }
        for (int a = 0; a < ants_number; a++){
            ants_paths[a].push_back(ants_paths[a][0]);
            float distance = 0.0;
            for (int k = 0; k < vertices_number; k++){
                distance += adjacency_matrix[ants_paths[a][k]][ants_paths[a][k+1]];
            }
            for (int k = 0; k < vertices_number - 1; k++){
                tmp_trail_matrix[ants_paths[a][k]][ants_paths[a][k+1]] += Q/distance;
                tmp_trail_matrix[ants_paths[a][k+1]][ants_paths[a][k]] += Q/distance;
            }
            if (distance < min_distance){
                min_distance = distance;
                route = ants_paths[a];
            }
        }
        for (int k = 0; k < vertices_number; k++){
            for (int l = k+1; l < vertices_number; l++){
                trail_matrix[k][l] = (p*trail_matrix[k][l]) + tmp_trail_matrix[k][l];
                trail_matrix[l][k] = trail_matrix[k][l];
                tmp_trail_matrix[k][l] = 0.0;
                tmp_trail_matrix[l][k] = 0.0;
            }
        }
        for (int a = 0; a < ants_number; a++){
            ants_paths[a].clear();
            ants_allowed[a] = std::vector<int>(vertices_number, 1);
        }
        std::cout << "distance: " << min_distance << std::endl;
    }
    return std::pair<float, std::vector<int>>(min_distance, route);
}

void Graph::calculateProbability(int current_point, std::vector<int> &allowed, std::vector<long double> &probabilities, std::vector<std::vector<float>> &trail_matrix, float alpha, float beta){
    long double denominator = 0.0;
    for (int i = 0; i < vertices_number; i++){
        if(allowed[i] == 0){
            continue;
        }
        long double calc = pow(trail_matrix[current_point][i], alpha) * pow(1.0/adjacency_matrix[current_point][i], beta);
        if(calc < 0){
            denominator += std::numeric_limits<long double>::min();
        }
        else{
            denominator += calc;
        }
    }
    if(denominator <= 0) std::cout << "denominator <= 0 : " << denominator << std::endl;
    for (int i = 0; i < vertices_number; i++){
        if(i == current_point){
            allowed[i] = 0;
            probabilities[i] = 0;
        }
        else if (allowed[i] == 0){
            probabilities[i] = 0;
        }
        else{
            long double numerator = pow(trail_matrix[current_point][i], alpha)/pow(adjacency_matrix[current_point][i], beta);
            if(numerator <= 0){
                std::cout << "numerator <= 0" << " at i= " << i << "tau = " << trail_matrix[current_point][i] << "distance = " << adjacency_matrix[current_point][i] << std::endl;
                probabilities[i] = 0;
                continue;
            }
            else if(denominator == 0){
                std::cout << "denominator = 0" << " at i= " << i << "tau = " << trail_matrix[current_point][i] << "distance = " << adjacency_matrix[current_point][i] << std::endl;
                probabilities[i] = 1;
                continue;
            }
            else{
                probabilities[i] = numerator/denominator;
                continue;
            }
        }
    }
}


int Graph::pickNextPoint(std::vector<long double> &probabilities){
    
    std::uniform_real_distribution<long double> rng(0.0, 1.0);
    long double random_choice;
    while (true){
        random_choice = rng(g);
        for (int i = 0; i < vertices_number; i++){
            if (random_choice < probabilities[i]){
                return i;
            }
            random_choice -= probabilities[i];
        }
    }
}

float calculateDistance(std::pair<int, int> point1, std::pair<int, int> point2){
    return sqrt(pow(point2.first - point1.first, 2) + pow(point2.second - point1.second, 2) * 1.0); 
    
}