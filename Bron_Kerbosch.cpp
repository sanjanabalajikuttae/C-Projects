/*This program takes an adjacency matrix on the standard input and outputs
all maximal cliques on the standard output. The Bron-Kerbosch
algorithm was implemented to detect the maximal cliques.*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <map>

using namespace std;

map<string, int>final_cliques;

//Square matrix validation
void square_matrix(vector<vector<int>>matrix){
    for(int i = 0; i < matrix.size(); i++){
        if(matrix.size() != matrix[i].size()){
            cerr<<"Not a square matrix"<<endl;
            exit(0);
        }
    }

}
//funtion to find the union values between the sets
vector<int> union_set(vector<int> R, int node){
    R.push_back(node);
    return R;
}

//funtion to find the intersection values
vector<int> intersection_set(vector<vector<int>> undirected_graph, vector<int> intersect_val, int node) {
    std::vector<int> updated_set;
    for (size_t i = 0; i < intersect_val.size(); ++i) {
        for (size_t j = 0; j < undirected_graph[node].size(); ++j)
            if (intersect_val[i] == undirected_graph[node][j]) {
                updated_set.push_back(intersect_val[i]);
            }
    }
    return updated_set;
}

//funtion to print the output in the given format
void print_output(vector<int> &R){
    sort(R.begin(), R.end());
    stringstream out;

    ostream_iterator<int >clique (out, ", ");

    if(!R.empty()) {
        copy(R.begin(), R.end() - 1, clique);
        out << R.back();

    }

    final_cliques[out.str()];
}



//bron kerbosch algorithm
void bronKerbosch(vector<vector<int>> &undirected_graph, vector<int>R, vector<int> P, vector<int> X)
{
    vector<int> r;
    vector<int> intersection_p;                     //the values of R, and X updated here in these vectors
    vector<int> intersection_x;
    vector<int>max_cliques;



    if(P.empty() && X.empty())                              //according to algorithm if P and X is empty then R is the maximal clique
    {

        for (auto it=R.begin(); it != R.end(); ++it)
        {
            max_cliques.push_back(*it);
        }
        print_output(max_cliques);

    }

    else{
        for(auto node : P) {
            r = union_set(R,node);                      //union of R and the node
            intersection_p = intersection_set(undirected_graph, P, node);      //intersection between  P and node
            intersection_x = intersection_set(undirected_graph, X, node);      //intersection between  X and node


            bronKerbosch(undirected_graph,r,intersection_p,intersection_x); //calling the bron kerbosch algorithm
            X.push_back(node);
        }
    }


}


int main(int /*argc*/, const char* /*argv*/[]) {
    vector<int> R;
    vector<int> P;
    vector<int> X;

    string input_lines;
    vector<vector<int>> matrix;//input matrix
    vector<vector<int>> undirected_graph;

    while(getline(cin, input_lines) && !input_lines.empty())          //get the input matrix
    {
        vector<int> row_vec;
        istringstream iss(input_lines);

        int input;
        while (iss >> input) {
            row_vec.push_back(input);
        }
        matrix.push_back(row_vec);
    }
    square_matrix(matrix);

//graph formation
        size_t size = matrix.size();
        undirected_graph.resize(size);

        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                if (matrix[i][j] != 0) {
                    {
                        undirected_graph[i].push_back(j);
                        undirected_graph[j].push_back(i);
                    }
                }
            }
        }

        for (size_t i = 0; i < undirected_graph.size(); i++)
            P.push_back(i);
//    }
//calling bron kerbosch algorith

    bronKerbosch(undirected_graph, R, P, X);


    for(auto a : final_cliques)
        cout <<"{"+ a.first +"}"<<endl;
    return 0;
}
