//
//  LinearAlgebra.cpp
//  OCR
//
//  Created by Pan, Zimeng on 12/6/16.
//  Copyright © 2016 Pan, Zimeng. All rights reserved.
//

#include <vector>
#include <iostream>

using namespace std;

class LinearAlgebra{
public:
    static vector <vector <double> > cross(vector <vector <double> > & x, vector <vector <double> > & y){
        // Dot product
        unsigned long dim = y.size(), r = x.size(), c = y.at(0).size();
        vector <vector <double> > res(r, vector <double> (c,0));

        if(x.at(0).size() != y.size()){
            printf("1:Dimension Does not match!\n");
            cout << dim << " " << r << " " << c << endl;
        } else {
            for(int i = 0; i < r; i++){
                for(int j = 0; j < c; j++){
                    double sum = 0;
                    for(int k = 0; k < dim; k++){
                        //cout << k << endl;
                        //cout << x.at(r).at(dim) << endl;
                        sum = sum + x.at(i).at(k) * y.at(k).at(j);
                        //cout << sum << endl;
                    }
                    res.at(i).at(j) = sum;
                    //cout << sum << endl;
                }
            }
        }
        return res;
    }

    static vector <vector <double> > sum(vector <vector <double> > & x, vector <vector <double> > & y){
        // Element-wise summation
        unsigned long rx = x.size(), ry = y.size(), cx = x.at(0).size(), cy = y.at(0).size();
        vector <vector <double> > res(rx, vector <double> (cx,0));

        if(rx != ry || cx != cy){
            printf("2: Dimension Does not match!\n");
        } else {
            for(int i = 0; i < rx; i++){
                for(int j = 0; j < cx; j++){
                    res.at(i).at(j) = x.at(i).at(j) + y.at(i).at(j);
                }
            }
        }
        return res;
    }

    static vector <vector <double> > hdot(vector <vector <double> > & x, vector <vector <double> > & y){
        // Element-wise multiplication
        unsigned long rx = x.size(), ry = y.size(), cx = x.at(0).size(), cy = y.at(0).size();
        vector <vector <double> > res(rx, vector <double> (cx,0));

        if(rx != ry || cx != cy){
            printf("2: Dimension Does not match!\n");
        } else {
            for(int i = 0; i < rx; i++){
                for(int j = 0; j < cx; j++){
                    res.at(i).at(j) = x.at(i).at(j) * y.at(i).at(j);
                }
            }
        }
        return res;
    }
};
