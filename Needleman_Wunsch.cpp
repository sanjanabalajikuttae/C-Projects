/*This program takes two strings as arguments and outputs the alignment score and alignments for the strings
 using Needleman-wunsch algorithm*/


#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>


using namespace std;
//sequence comparison
int seq_comparison(char seq1, char seq2){
    int val = -1;
    if(seq1 == seq2){
        val = 1;
        return val;
    }
    return val;
}


//function to check diagonal path
bool diagonalCheck (vector<vector<int>> matrix, string seq1, string seq2, int &a_size, int &b_size){

    bool a = false;
    if(a_size > 0 && b_size > 0 && matrix[a_size][b_size] == matrix[a_size-1][b_size-1]+ seq_comparison(seq1[a_size-1], seq2[b_size - 1])){
        a=true;
    }
    return a;

}
//function to check top path
bool topCheck (vector<vector<int>> matrix, string seq1, string seq2, int gap, int& a_size, int& b_size){
//    int a_size = seq1.size();
//    int b_size = seq2.size();
    bool a = false;
    if (a_size > 0 && (matrix[a_size][b_size] == matrix[a_size-1][b_size]+gap)){
        a=true;
    }
    return a;

}
//function to check left path
bool leftCheck (vector<vector<int>> matrix, string seq1, string seq2, int gap, int &a_size, int &b_size){
//    int a_size = seq1.size();
//    int b_size = seq2.size();
    bool a = false;
    if (a_size > 0 && (matrix[a_size][b_size] == matrix[a_size][b_size-1]+gap)){
        a=true;
    }
    return a;
}

int main(int argc,  char *argv[])
{
    if(argc != 3){
        cerr << "Invalid no of arguments" << endl;      //Validation to check for invalid no of arguments
        exit(0);
    }

    char *ag1 = argv[1];
    char *ag2 = argv[2];

    if (isdigit(*ag1) or isdigit(*ag2)) {             //validation to check if the arguments are integers
        cerr << "Invalid arguments: Input arguments can only be strings" << endl;
        exit(0);
    }



    string seq1 = argv[1];
    string seq2 = argv[2];
    int arg_size = seq1.size();
    int gap_penalty = -1;

    string alignment_a = "";
    string alignment_b = "";

    int a_size = seq1.size();
    int b_size = seq2.size();




    vector<int> v(arg_size + 1, 0);
    vector <vector<int>> matrix;
    for (int i = 0; i <= arg_size; i++) {
        matrix.push_back(v);
    }

//Needleman-Wunsch Algorithm
//filling left and top border elements
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[0].size(); j++){
            matrix[i][0] = gap_penalty * i;
            matrix[0][j] = gap_penalty * j;
        }
    }

//filling rest of the matrix elements
    for(int i = 1; i < matrix.size(); i++){
        for(int j = 1; j < matrix[0].size(); j++){
            int diagonal = matrix[i-1][j-1] + seq_comparison(seq1[i-1], seq2[j-1]);
            int left = matrix[i-1][j] + gap_penalty;
            int top = matrix[i][j - 1] + gap_penalty;
            matrix[i][j] = max(left, max(diagonal, top));

        }
    }


//traceback
    while(a_size > 0 || b_size > 0){

        if(diagonalCheck(matrix,seq1,seq2, a_size, b_size)){
            alignment_a = seq1[a_size-1] + alignment_a;
            alignment_b = seq2[b_size-1] + alignment_b;
            a_size = a_size - 1;
            b_size = b_size - 1;


        }

        else if(topCheck(matrix,seq1,seq2,gap_penalty, a_size, b_size)){
            alignment_a = seq1[a_size-1]+alignment_a;
            alignment_b = "-" + alignment_b;
            a_size = a_size-1;


        }

        else {
            alignment_a = "-" + alignment_a;
            alignment_b = seq2[b_size-1]+alignment_b;
            b_size = b_size - 1;

        }
    }

    vector<int>score;
    for(int i = 0; i<alignment_a.size(); i++){
        if(alignment_a[i] == alignment_b[i]){
            score.push_back(1);
        }
        else{
            score.push_back(-1);
        }
    }




    cout<<accumulate(score.begin(), score.end(), 0)<<endl;
    cout<<alignment_a<<endl;
    cout<<alignment_b<<endl;



    return 0;
}
