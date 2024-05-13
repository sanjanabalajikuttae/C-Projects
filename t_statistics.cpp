/*This program generates a vector V1 of n elements (as double) that are randomly drawn from a
negative binomial distribution (initialized with the probability of a trial generating true p and a number
of trial successes k and result type int). The random numbers should be generated with the Mersenne-Twister algorithm
by Matsumoto and Nishimura (2000) using 64-bit integers with default parameters and a fixed seed
s. A second vector V2 of m elements (as double) was generated in the same way as before, but
with a different seed s 2 = s · 2.

Then, given these two vectors V1 and V2 , a two-sample t-test was performed on the scaled and non-scaled
values and the t-statistic is given as a output*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <cmath>
#include <random>
#include <iomanip>

using namespace std;

//function to find mean
double find_mean(vector<double> &random_vec){
    double mean = accumulate(random_vec.begin(), random_vec.end(), 0.0) / random_vec.size();
    return mean;
}

//function to find variance
double find_variance(vector<double> &random_vec){
    double mean = find_mean(random_vec);
    double variance = 0;
    double sq_diff = 0;
    double vecsize = random_vec.size();
    for(size_t i = 0; i < random_vec.size(); i++) {
        variance += pow((random_vec[i] - mean), 2);
        sq_diff = variance / (vecsize - 1);
    }
    return sq_diff;
}

//function for standard deviation
double find_stddev(vector<double> &random_vec){
    double sq = find_variance(random_vec);
    return (sqrt(sq));
}

//function for log scale values
vector<double> log_scale(vector<double> &random_vec, vector<double> &scaled_vec){
    for(size_t i = 0; i < random_vec.size(); i++){
        double scaled = log2(abs(random_vec[i]) + 1);
        scaled_vec.push_back(scaled);
    }
    return scaled_vec;
}


//function to find largest elements
double largest_elements(vector<double> &scaled_vec) {
    sort(scaled_vec.begin(), scaled_vec.end(), greater<double>());
    if (scaled_vec.size() > 10) {
        for (size_t i = 0; i < 10; i++) {
            cout << setprecision(3) << scaled_vec[i] << ", ";
        }
    } else {
        string delim = "";
        for (auto it = scaled_vec.begin(); it < scaled_vec.end(); ++it) {

            cout << setprecision(3) <<delim<< *it;
            delim = ", ";
        }


    }
    cout  <<endl;

}

//function for t-test
double t_test(double mean1, double mean2, float n, float m, double std1, double std2) {
    double difference = mean1 - mean2;
    double den = n + m - 2;
    double sp = sqrt(((n-1)*std1*std1+(m-1)*std2*std2)/den);
    double t_den = sqrt((1/n)+(1/m)) ;
    double t_stats = difference/(sp*t_den);
    return t_stats;
}

//function to print the output
void print(vector<double> &random_vec1, vector<double> &scaled_vec1, vector<double> &random_vec2, vector<double> &scaled_vec2, float n, float m){
    cout<<"V1 Mean: "<<find_mean(random_vec1)<<endl;
    cout<<"V1 Sample standard deviation: "<<setprecision(3)<<find_stddev(random_vec1)<<endl;
    cout<<"V1 Top "<<scaled_vec1.size()<<" elements: ";
    largest_elements(scaled_vec1);
    cout<<"V2 Mean: "<<find_mean(random_vec2)<<endl;
    cout<<"V2 Sample standard deviation: "<<setprecision(3)<<find_stddev(random_vec2)<<endl;
    cout <<"V2 Top "<<scaled_vec2.size()<<" elements: ";
    largest_elements(scaled_vec2);
    cout<<endl;
    cout<<"Comparing V1 and V2..."<<endl;
    cout<<"Unscaled t-statistic: ";
    double a = t_test(find_mean(random_vec1), find_mean(random_vec2), n, m, find_stddev(random_vec1), find_stddev(random_vec2));
    cout<<a<<endl;
    cout<<"Comparing log2 scaled V1 and V2..."<<endl;
    cout<<"Scaled t-statistic: ";
    double b = t_test(find_mean(scaled_vec1), find_mean(scaled_vec2), n, m, find_stddev(scaled_vec1), find_stddev(scaled_vec2));
    cout<<b<<endl;
    int deg = n+m-2;
    cout<<"Total degrees of freedom: "<<deg<<endl;
    cout<<endl;
    cout<<"Sorted vector: ";
}

//function to sort the vector
vector<double> sorted_vec(vector<double> &final, vector<double> &even, vector<double> &odd){
    for(auto i:final){
        int a = round(i);
        if(a % 2 == 0){
            even.push_back(i);
        }
        else{
            odd.push_back(i);
        }
    }

    sort(even.begin(), even.end(), greater<double>());
    sort(odd.begin(), odd.end());

    even.insert(even.end(), odd.begin(), odd.end());

    string delim = "";
    for (auto it = even.begin(); it < even.end(); ++it) {

        cout << setprecision(3) <<delim<< *it;
        delim = ", ";
    }
    cout<<endl;
    return even;
}




int main(int argc, const char* argv[]) {

    if(argc != 6){									//valid arguments check
        cerr<<"Invaid no of arguments"<<endl;
        exit(1);
    }

    unsigned int n,m,s,k;
    double p;
    try {
        n = stoul(argv[1]);
        m = stoul(argv[2]);
        s = stoul(argv[3]);
        p = stod(argv[4]);
        k = stoul(argv[5]);
    }
    catch (invalid_argument& e) {
        cerr<<"Invalid arguments: "<<e.what()<<endl;
        exit(1);
    }
    


    if(n<=0 || m<=0 || s<=0|| p<=0|| k<=0){
        cerr<<"Invalid arguments"<<endl;
        exit(1);
    }
    


    vector<double>random_vec1;
    vector<double>scaled_vec1;

    mt19937_64 gen1(s);							 //Mersenne-Twister algorithm 64-bit integers with fixed seed s
    negative_binomial_distribution<int> distribution1(k,p);                     //negative binomial distribution
    for(size_t i = 0; i < n; i++){
        random_vec1.push_back(distribution1(gen1));
    }
    log_scale(random_vec1,scaled_vec1);

    vector<double>random_vec2;							//Mersenne-Twister algorithm 64-bit integers seed s * 2
    vector<double>scaled_vec2;
    mt19937_64 gen2(s * 2);
    negative_binomial_distribution<int> distribution2(k,p);                         //negative binomial distribution
    for(size_t i = 0; i < m; i++){
        random_vec2.push_back(distribution2(gen2));
    }
    log_scale(random_vec2, scaled_vec2);



    vector<double>random_vec3(n);
    iota(random_vec3.begin(), random_vec3.end(), 1);					//Mersenne-Twister algorithm 64-bit integers seed s*7
    mt19937_64 gen3(s*7);
    shuffle(random_vec3.begin(), random_vec3.end(), gen3);				//Shuffle them using random numbers

    vector<double>final;
    vector<double>odd;
    vector<double>even;

    for(size_t i = 0; i < random_vec3.size(); i++){
        double new_val = random_vec3[i]*scaled_vec1[i];
        final.push_back(new_val);
    }

    print(random_vec1, scaled_vec1, random_vec2, scaled_vec2, n, m);
    sorted_vec(final, even, odd);

    return 0;
}
