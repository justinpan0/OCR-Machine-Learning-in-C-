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
    
    void feedforward(Self & self, vector <vector <double> >& a){
        // Assume that the input a is an n-element vector
        
        // Some changes here!!
        for(int i = 0; i < self.num_layers; i++) {
            vector <vector <double> > weighted = LinearAlgebra::dot(self.weights.at(i), a);
            cout << weighted.size() << " " << weighted.at(0).size() << endl;
            sigmoid(weighted);
            for(int j = 0; j < weighted.size(); j++)
                
                a = LinearAlgebra::sum(weighted, self.biases.at(i));
        }
    };
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
