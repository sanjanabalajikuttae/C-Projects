/*This program  takes a FASTA file as first argument, k-mer size as second argument the
and the skip size nas third argument and outputs the number of n-skip-
k-mers found in the sequences on the standard output.*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <fstream>
#include <unordered_map>
#include <map>

using namespace std;
//I tried hashfunction on unordered map but it seems to increase the run time of my program
class custom_hash
{
public:
    size_t operator() (string const& key) const
    {
        size_t hash = 0;
        int b;
        for (int i = 0; i < key.size(); i++) {
            switch (key[i]) {
                case 'A':
                    b = 0;
                    break;
                case 'T':
                    b = 1;
                    break;
                case 'G':
                    b = 2;
                    break;
                default:
                    b = 3;
                    break;
            }
            hash = b * pow(4, key.size() - i - 1);          //Given hash function

        }
        return hash;
    }
};


//Empty file validation
bool is_empty_file(ifstream& input_file)
{
    return input_file.peek() == ifstream::traits_type::eof();
}

//is Dna validation
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



int main(int argc, char* argv[]) {
    if(argc != 4){
        cerr << "Invalid no of arguments" << endl;      //Validation to check for invalid no of arguments
        exit(0);
    }


    ifstream input_file(argv[1]);
    int k = std::atoi(argv[2]);
    int n = std::atoi(argv[3]);


    if (input_file.is_open()) {                                     //validation to check if the file is open and not empty
        if (!is_empty_file(input_file)) {
            string input_lines;
            string header;

//Read input file line by line
            while (std::getline(input_file, input_lines) && input_lines != "") {
//                unordered_map<string , int>ump;
                map<string , int>mp;
                if (input_lines[0] =='>') {                                                         //extracting header name
                    header = input_lines.substr(1, input_lines.size());
                }
                else {
                    transform(input_lines.begin(), input_lines.end(),input_lines.begin(), ::toupper);  //converting inputs to upper case
                    if (!is_dna(input_lines)) {
                        cerr << header << endl;
                        continue;
                    }
                    else {
                        cout << header << endl;
                        int count = 0;
                        while (count < input_lines.size() - (k + n)) {
                            string a = "";
                            for (size_t i = count; i <= count + k + n; i = i + n + 1) {
                                a = a + input_lines[i];
                            }
                            mp[a]++;                    //updating the frequency of kmers
                            count++;
                        }
                    }
                    //sorting unordered map values if hash function was used
//                    std::map<string, int> omp(mp.begin(), mp.end());
//                    for(auto it = omp.begin(); it != omp.end(); ++it)
                    for(auto a : mp)
                        cout <<a.first<<" "<<a.second<<endl;
                    cout<<'\n';

                }
            }

        }
    }
    input_file.close();

  return 0;
}
