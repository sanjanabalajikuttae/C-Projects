/* This program takes a FASTA file as a first argument, verify whether the sequences are DNA or RNA,
 and converts any RNA sequences into DNA */

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>


using namespace std;

//function to check whether the sequence is dna
bool is_dna(string sequence){
    bool counter = true;
    for (char& c : sequence) {

        if(c == 'A' || c == 'T' || c == 'G' || c == 'C'){
            continue;
        }
        else{
            counter = false;
            break;
        }
    }

    return counter;

}

//Function to check whether the sequence in rna
bool is_rna(string sequence){
    bool counter = true;
    for (char& c : sequence) {
        if(c == 'A' || c == 'U' || c == 'G' || c == 'C'){
            continue;
        }
        else{
            counter = false;
            break;
        }
    }
    return counter;
}

//Funtion to check if the input file is empty
bool is_empty_file(std::ifstream& input_file)
{
    return input_file.peek() == std::ifstream::traits_type::eof();
}

//Funtion to sort the sequence according to the length
bool compare_length(const string& s1, const string& s2) {
    return s1.length() < s2.length();
}



//Function to compute next largest word by permutation
string next_largest_permutation(string sequence){
    bool val = next_permutation(sequence.begin(), sequence.end());
    if(val == true){
        return sequence;
    }
}


int main(int argc, const char *argv[]) {
    if(argc != 2){
        cerr << "Invalid no of arguments" << endl;      //Validation to check for invalid no of arguments
        exit(0);
    }

    ifstream input_file(argv[1]);


    vector<string> result;
    string temp_line;
    if (input_file.is_open()) {                                     //validation to check if the file is open

        if(!is_empty_file(input_file)){
            string input_lines;


            while (getline(input_file, input_lines) && (!input_lines.empty()))  {    //read the file line by line

                if (input_lines[0] == '>') {                                                    //Store the header of each sequence in temp_line
                    temp_line = input_lines;

                }
                else {
                    if (!is_dna(input_lines) && !is_rna(input_lines)) {      //if not DNA or RNA then ignore the line for calculation
                        continue;
                    }
                    else{
                        for (auto i = 0; i < input_lines.size(); i++) {

                            if (input_lines[i] == '>') {
                                break;
                            }
                            else {
                                if (input_lines[i] == 'U'){
                                                                              //if RNA sequence found change it into DNA
                                    input_lines[i] = 'T';
                                }
                                else {
                                    continue;
                                }

                            }

                        }
                        result.push_back(next_largest_permutation(input_lines));

                    }

                }


            }


            int empty_count = 0;                                //If next larger word cannot be computed by permutation the empty string is stored in  vector
            for(int i = 0; i < result.size(); i++){            //which is later removed
                if(result[i] == ""){
                    empty_count += 1;
                }
                else{
                    continue;
                }

            }

            if(empty_count > 0){
                result.erase(remove(result.begin(), result.end(), ""));
            }

            sort(result.begin(), result.end());                   //sort the sequences lexicographically
            sort(result.begin(), result.end(), compare_length);


            for(int i = 0; i < result.size(); i++) {            //printing the output in the desired format
                cout<<result[i]<<endl;
            }

            input_file.close();
        }
    }


    else{                                                      //Error message is the file cannot be opened
        cerr<<"file not open"<<endl;
        exit(0);
    }

    return 0;

}

