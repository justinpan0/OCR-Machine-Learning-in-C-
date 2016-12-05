#include <iostream>
#include <cmath>
#include <vector>
#include <random>
using namespace std;

struct Self{
    unsigned long num_layers;
    vector <int> sizes;
    vector <vector <vector <double> > > biases;
    vector <vector <vector <double> > > weights;
};


class Network{
    static vector <vector <double> > gaussian(int r, int c){
        vector <vector <double> > res(r, vector <double>(c,0));

        std::random_device device_random_;
        std::default_random_engine generator(device_random_());
        std::normal_distribution<> distribution(0, 1.0);

        for(int i = 0; i < r; i++) {
            //cout << i << endl;
            for (int j = 0; j < c; j++) {
                //cout << j << endl;
                double number = distribution(generator);
                //cout << number << endl;
                res[i][j] = number;
            }
        }
        return res;
    };

    double sigmoid(double z){
        return 1.0/(1.0 + exp(-z));
    }

    double feedforward(Self & self, vector <double> & a){
        // Assume that the input a is an n-element vector
        for(int i = 0; i < a.size(); i++) {
            for (int j = 0; j < self.weights.at(i).size(); j++){
                for (int k = 0; k < self.weights.at(i).at(j).size(); k++) {
                    a.at(i) = sigmoid(self.weights.at(i).at(j).at(k) + a.at(i)) + self.biases.at(i).at(1).at(k);
                }
            }
        }
    };

public:
    Self self;

    void _init_(Self & self, const vector <int> & sizes) {

        self.num_layers = sizes.size();
        self.sizes = sizes;

        for (int i = 0; i < self.num_layers - 1; i++) {
            self.biases.push_back(gaussian(1, self.sizes.at(i)));
            //cout << self.biases.at(i).at(0).at(0) << endl;
            for (int j = 1; j < self.num_layers; j++){
                self.weights.push_back(gaussian(self.sizes.at(j), self.sizes.at(i)));
            }
        }
    }
};


int main() {
    Self self;
    Network network;

    //cout << distribution(generator) << endl;
    vector <int> sizes = {2,3,1};
    network._init_(self, sizes);

    /*vector<vector<double> > g = Network::gaussian(3, 2);
    for (int i = 0; i < 3; i++) {
        //cout << i << endl;
        for (int j = 0; j < 1; j++) {
            for(int k = 0; k < sizes[i]; k++) {
                //cout << j << endl;
                cout << self.biases.at(i).at(j).at(k) << " ";
            }
        }
        cout << endl;
    }*/
}
