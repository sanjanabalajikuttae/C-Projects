#include "munkres_algorithm.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Global variables declaration
vector<int> row;
vector<int> col;
int step;
vector< pair <int,int> >S;
pair<int, int>z;


//square matrix validation
void square_matrix(Matrix<int>&m){
    if(m.nrows() == m.ncols()){
        step = 0;
    }
    else{
        exit(0);
    }
}

//function to find minimum element in each row
vector<int> find_row_minimum(Matrix<int>&c){
    vector<int>row_min;
    for (int i = 0; i < c.nrows(); i++) {
        int min_row = c(i,0);
        for (int j = 1; j < c.ncols(); j++) {

            if (c(i,j) < min_row)
                min_row = c(i,j);
        }
        row_min.push_back(min_row);
    }
    return row_min;

}

//subtract its minimum with every element in row
Matrix<int> subtract_row_minimum(Matrix<int>&c, vector<int>a){
    for (size_t i = 0; i < c.nrows(); i++){
        for (size_t j = 0; j < c.ncols(); j++) {
            c(i, j) = c(i, j) - a[i];
        }
    }
    return c;
}

//function to find minimum element in each column
vector<int> find_col_minimum(Matrix<int>&c){
    vector<int>col_min;
    for (int i = 0; i < c.nrows(); i++) {
        int min_col = c(0,i);
        for (int j = 1; j < c.ncols(); j++) {

            if (c(j,i) < min_col)
                min_col = c(j,i);
        }
        col_min.push_back(min_col);
    }
    return col_min;
}
//subtract its minimum with every element in column
Matrix<int> subtract_col_minimum(Matrix<int>&c, vector<int>b){
    for (size_t i = 0; i < c.ncols(); i++){
        for (size_t j = 0; j < c.nrows(); j++) {
            c(i, j) = c(i, j) - b[j];
        }
    }
    return c;

}

//step2
//if C contains an uncovered zero then
//Find an arbitrary uncovered zero Z 0 and prime it
//if There is no starred zero in the row of Z 0 then
//GOTO STEP 3
//else
//Cover this row, and uncover the column containing the
//starred zero GOTO STEP 2
void uncovered_zeroes(Matrix<int>&c, Matrix<int>&temp){
    int k =0;
    for (int i = 0; i < c.nrows(); i++) {
        for (int j = 0; j < c.ncols(); j++) {

            if (c(i, j) == 0 && !col[j]) {
                temp(i, j) = 2;


                k = i;
                z = (make_pair(i,j));

                for(int a = 0; a < temp.ncols(); a++) {
                    if (temp(z.first, a) == 1) {
                        col[a] = 0;
                        row[k] = 1;
                        step = 2;
                    }
                    else {
                        step = 3;

                    }
                }
            }

        }
    }


}

//For all zeros z i in C, mark z i with a star if there is no starred
//zero in its row or column
void starred_zeroes(Matrix<int>&c, Matrix<int>&temp) {
    row.resize(c.nrows());
    col.resize(c.ncols());
    int counter = 0;

    for (int i = 0; i < c.nrows(); ++i) {
        for (int j = 0; j < c.ncols(); ++j) {
            if (c(i, j) == 0) {
                if (row[i] == 0 && col[j] == 0) {
                    temp(i, j) = 1;
                    row[i] = 1;
                    col[j] = 1;
                    counter += 1;
                    break;
                }
            }

        }
    }
    step = 1;

}

//step1
//Each for Each column containing a starred zero do
//cover this column
//if n columns are covered then GOTO DONE else GOTO STEP 2
//end if
void step_1(Matrix<int>&temp){
    int counter = 0;

    for (int i = 0; i < temp.nrows(); i++) {
        for (int j = 0; j < temp.ncols(); j++) {
            if (temp(i, j) == 1) {
                counter += 1;
            }
        }
    }
    if(counter >= temp.ncols()){
        step = 5;
    }
    else{
        step = 2;
    }
}

//Erase all other primes
void erase_extra_primes(Matrix<int>&temp){
    for (int i = 0; i < temp.nrows(); i++) {
        for (int j = 0; j < temp.ncols(); j++) {
            if(temp(i,j) == 2){
                temp(i,j) = 0;
            }
        }
    }
}

//step 3
//Construct a series S of alternating primed and starred
//zeros as follows:
//Insert Z 0 into S
//while In the column of Z 0 exists a starred zero Z 1 do
//Insert Z 1 into S
//Replace Z 0 with the primed zero in the row of Z 1 . Insert Z 0
//into S
//end while
//Unstar each starred zero in S and replace all primes with
//stars. Erase all other primes and uncover every line in C GOTO
//STEP 1
void series(Matrix<int>&c, Matrix<int>&temp) {
    S.push_back(z);
    int count =0;
    for (int i = 0; i < c.nrows(); i++) {
        if (temp(i, z.second) == 1) {

            S.push_back(make_pair(i, z.second));
            temp(z.first, z.second) = 1;


            for (int j = 0; j < c.ncols(); j++) {
                if (temp(S[1].first, j) == 2) {
                    S[count] = make_pair(S[1].first, j);

                }
            }

        }
    }


    for (int i = 0; i < temp.nrows(); i++) {
        for (int j = 0; j < temp.ncols(); j++) {
            pair<int, int>t;
            t = make_pair(i, j);
            while (count < 2) {
                if (temp(i, j) == 1 && t == S[count]) {
                    temp(i, j) = 0;

                }
                if (temp(i, j) == 2) {
                    temp(i, j) = 1;

                }
                count+=1;
            }
            count=0;
        }
    }


    erase_extra_primes(temp);
    row.clear();
    col.clear();

    step = 1;

}


//Add e min to every element in covered rows and
//subtract it from every element in uncovered columns. GOTO
//STEP 2
void e_min(Matrix<int>&c){

    int min_value = 2147483647;
    for (int i = 0; i < c.nrows(); i++) {
        for (int j = 0; j < c.ncols(); j++) {
            if(row[i] == 0 && col[j] == 0){
                if(min_value > c(i,j)){
                    min_value = c(i,j);
                }
            }
        }
    }
    for (int i = 0; i < c.nrows(); i++) {
        for (int j = 0; j < c.ncols(); j++) {
            if(row[i] == 1){
                c(i,j) += min_value;

            }
            if(col[j] == 0){
                c(i,j) -= min_value;
            }
        }
    }
    step = 2;
}


Matrix<int> run_munkres_algorithm(Matrix<int>c) {
    square_matrix(c);
    Matrix<int>temp(c.nrows(), c.ncols(), 0);
    bool done = false;
    while (!done) {
        switch (step)
        {
            case 0:
                subtract_row_minimum(c,find_row_minimum(c));
                subtract_col_minimum(c, find_col_minimum(c));
                starred_zeroes(c,temp);
                break;
            case 1:
                step_1(temp);
                break;
            case 2:
                uncovered_zeroes(c,temp);
                break;
            case 3:
                series(c, temp);
                break;
            case 4:
                e_min(c);
                break;
            case 5:
                done = true;
                break;
            default:
                done = true;
                break;

        }

    }
    return temp;

}
