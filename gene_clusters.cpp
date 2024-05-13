/*This program compute gene clusters in which each gene is at most at distance d of at least on one other
gene of the cluster and all being located on the same chromosome. The clusters are sorted in ascending coordinate order*/


#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;

//Validation for file checking
bool is_empty_file(ifstream& input_file)
{
    return input_file.peek() == ifstream::traits_type::eof();
}


bool calc_distance(vector<double>mid_vec, int prog_arg){
    double distance;
    bool check_dis = false;

    for (int i = 0; i < mid_vec.size()-1; i++) {
        cout << "midval vec" << mid_vec[i] <<" "<<mid_vec[i+1]<< endl;

        distance = abs(mid_vec[i] - mid_vec[i + 1]);
        if(distance <= prog_arg){
            cout<<distance<<" "<<prog_arg<<endl;
            check_dis = true;
//            return check_dis;
        }
    }
    return check_dis;

}

//Validation to check if the order of genes in the input file are in the coordinate order
bool coordinates(vector<double>start_vec, vector<double>end_vec){
    bool check = false;
    for(int i = 0; i < start_vec.size(); i++){
        if(start_vec[i] > end_vec [i]){
            cerr<<"Not in coordinate order"<<endl;
            exit(1);
        }
        else{
            check = true;
        }
    }
    return check;
}

int main(int argc, const char *argv[]) {

//    ifstream input_file("/home/sanjana/Documents/assignment2/assignment2/code/input.txt");
    ifstream input_file(argv[1]);
    int program_argument = std::atoi(argv[2]);
//    cout<<program_argument<<endl;
    ofstream output_file(argv[3]);

    if (input_file.is_open()) {                                     //validation to check if the file is open
        if (!is_empty_file(input_file)) {
            string input_lines;
            string chromosome;
            int start;
            int end;

            vector<string>chromosome_vec;
            vector<double>start_vec;
            vector<double>end_vec;
            vector<double>mid_vec;
            int cluster = 1;
            double distance;

//Read input file line by line and store it in the corresponding vector
            while (std::getline(input_file, input_lines) && input_lines != "") {
                istringstream is(input_lines);
                is >> chromosome >> start >> end;
                chromosome_vec.push_back(chromosome);
                start_vec.push_back(start);
                end_vec.push_back(end);
            }

            if(output_file.is_open()) {
                if(is_sorted(chromosome_vec.begin(), chromosome_vec.end())){
                    for (int i = 0; i < chromosome_vec.size(); i++) {
                        if (i == 0) {
                            if(coordinates(start_vec, end_vec)) {
                                double val = (start_vec[i] + end_vec[i]) / 2;
                                mid_vec.push_back(val);
                                output_file << chromosome_vec[0] << "\t" << start_vec[0] << "\t" << end_vec[0] << "\t"
                                            << "cluster=" << cluster << endl;
                            }
                            else{
                                cerr<<"wrong coordinates"<<endl;
                                exit(1);
                            }
                        }
                        else {
                                if(chromosome_vec[i] == chromosome_vec[i-1]){
                                    if(start_vec[i] > start_vec[i-1]){
                                        if(coordinates(start_vec, end_vec)) {
                                            double val = (start_vec[i] + end_vec[i]) / 2;
                                            mid_vec.push_back(val);
                                            double distance = abs(mid_vec[i] - mid_vec[i - 1]);
                                            if (distance <= program_argument) {
                                                output_file << chromosome_vec[i] << "\t" << start_vec[i] << "\t"
                                                            << end_vec[i] << "\t" << "cluster=" << cluster << endl;
                                            }

                                        else{
//                                            cout<<"else final distance"<<endl;
                                            cluster++;
                                            output_file << chromosome_vec[i]<<"\t"<<start_vec[i]<<"\t"<<end_vec[i]<<"\t"<<"cluster="<<cluster<<endl;
                                            }

                                        }
                                        else{
                                            cerr<<"wrong coordinates"<<endl;
                                            exit(1);
                                        }
                                    }
                                    else if(end_vec[i] > end_vec[i-1]){
                                        if(coordinates(start_vec, end_vec)) {
                                            double val = (start_vec[i] + end_vec[i]) / 2;
                                            mid_vec.push_back(val);
                                            double distance = abs(mid_vec[i] - mid_vec[i - 1]);
                                            if (distance <= program_argument) {
                                                output_file << chromosome_vec[i] << "\t" << start_vec[i] << "\t"
                                                            << end_vec[i] << "\t" << "cluster=" << cluster << endl;
                                            } else {
                                                cout << "else final distance" << endl;
                                                cluster++;
                                                output_file << chromosome_vec[i] << "\t" << start_vec[i] << "\t"
                                                            << end_vec[i] << "\t" << "cluster=" << cluster << endl;
                                            }
                                        }
                                        else{
                                            cerr<<"wrong coordinates"<<endl;
                                            exit(1);
                                        }
                                    }
                                    else{
                                        cerr<<"Invalid input: start not sorted in ascending order"<<endl;
                                        exit(1);
                                    }
                                }
                                else if(chromosome_vec[i] > chromosome_vec[i-1]){
                                    if(coordinates(start_vec, end_vec)) {
                                        double val = (start_vec[i] + end_vec[i]) / 2;
//                                        cout << "val for diff chr" << val << endl;
                                        mid_vec.push_back(val);
                                        cluster++;
                                        output_file << chromosome_vec[i] << "\t" << start_vec[i] << "\t" << end_vec[i]
                                                    << "\t" << "cluster=" << cluster << endl;
                                    }
                                    else{
                                        cerr<<"wrong coordinates"<<endl;
                                        exit(1);
                                    }
                                }
                                else{
                                    cerr<<"Invalid input: previous chromosome not sorted in ascending order"<<endl;
                                    exit(1);
                                }

                        }


                }
            }
                else{
                    cerr<<"chromosomes nor sorted in ascending order"<<endl;
                    exit(1);
                }

                output_file.close();
            }
            else{
                cerr<<"output file not open"<<endl;
                exit(1);
            }

        }
        input_file.close();

    }
    else{
        cerr<<"input file not open"<<endl;
        exit(1);
    }
//    output_file.close();
    return 0;
}


