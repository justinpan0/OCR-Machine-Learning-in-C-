//
//  main.cpp
//  OCR
//
//  Created by Pan, Zimeng on 12/6/16.
//  Copyright © 2016 Pan, Zimeng. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include "LinearAlgebra.cpp"
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

        random_device device_random_;
        default_random_engine generator(device_random_());
        normal_distribution<> distribution(0, 1.0);

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

    void sigmoid(vector <vector <double> > & z){
        for(int i = 0; i < z.size(); i++)
            for(int j = 0; j < z.at(0).size(); j++)
                z.at(i).at(j) = 1.0/(1.0 + exp(-z.at(i).at(j)));
    }

    vector <vector <double> > dsigmoid(vector <vector <double> > & z){
        unsigned long r = z.size(), c = z.at(0).size();
        vector <vector <double> > res(r, vector <double> (c, 0));
        for(int i = 0; i < z.size(); i++)
            for(int j = 0; j < z.at(0).size(); j++)
                res.at(i).at(j) = z.at(i).at(j)*(1-z.at(i).at(j));
    }

public:
    Self self;

    void _init_(Self & self, const vector <int> & sizes) {

        self.num_layers = sizes.size();
        self.sizes = sizes;

        for (int i = 0; i < self.num_layers-1; i++) {
            self.biases.push_back(gaussian(self.sizes.at(i+1),1));
            //cout << self.biases.at(i).at(0).at(0) << endl;
            for (int j = 1; j < self.num_layers; j++){
                self.weights.push_back(gaussian(self.sizes.at(j), self.sizes.at(i)));
            }
        }
    };

    vector < vector <double> > feedforward(Self & self, vector <vector <double> >& a){
        // Feedforward
        // Pass results to a and Return last weighted input
        vector < vector <double> > weighted;
        for(int i = 0; i < self.num_layers-1; i++) {
            // Compute z^{l} = w^{l}a^{l-1} + b^{l}
            a = LinearAlgebra::cross(self.weights.at(i), a);
            a = LinearAlgebra::sum(weighted, self.biases.at(i)); // Weighted input
            // Compute a^{l} = sigma(z^{l})
            sigmoid(a);
        }
        a = LinearAlgebra::cross(self.weights.at(self.num_layers-1), a);
        weighted = LinearAlgebra::sum(weighted, self.biases.at(self.num_layers-1)); // Weighted input
        // Compute a^{l} = sigma(z^{l})
        a = weighted;
        sigmoid(a);
        return weighted;
    };

    vector < vector <double> > grad(vector <vector <double> >& y, vector <vector <double> >& a){
        // Compute gradiant for cost function
        unsigned long r = a.size(), c = a.at(0).size();
        vector < vector <double> > gradiant (r, vector <double> (c, 0));
        for(int i = 0; i < a.size(); i++)
            for(int j = 0; j < a.at(0).size(); j++){
                gradiant.at(i).at(j) = (y.at(i).at(j) - a.at(i).at(j))/(r*c);
            }
        return gradiant;
    }

    vector < vector <double> > error(vector <vector <double> >& y, vector <vector <double> >& a){
        // Compute output error
        vector < vector <double> > error (a.size(), vector <double> (a.at(0).size(), 0));
        vector < vector <double> > gradiant = grad(y, a);
        vector < vector <double> > derivative = dsigmoid(a);
        return error = LinearAlgebra::hdot(gradiant, derivative);
    }
};


int main() {
    Self self;
    Network network;

    //cout << distribution(generator) << endl;
    vector <int> sizes = {2,3,1};
    network._init_(self, sizes);

    /*vector<vector<double> > g = Network::gaussian(3, 2);*/
    for (int i = 0; i < 2; i++) {
        //cout << i << endl;
        for(int j = 0; j < 1; j++) {
            for(int k = 0; k < sizes[i+1]; k++) {
                //cout << j << endl;
                //cout << self.biases.at(i).at(k).at(j) << " ";
            }
        }
        //cout << endl;
    }
    vector <vector <double> >a;
    a.push_back({1});
    a.push_back({1});
    network.feedforward(self, a);
    cout << a.at(0).at(0) << endl;
    /*vector <vector <double> > x,y,res;
    x.push_back({1,0});
    x.push_back({0,1});
    //cout << x.at(1).at(0) << endl;
    y.push_back({4,1});
    y.push_back({2,2});
    res = LinearAlgebra::dot(x,y);
    cout << res.at(0).at(0) << endl;*/
}
