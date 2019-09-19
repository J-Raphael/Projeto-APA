#ifndef PJ_FINAL_CUP_MATRIX_H
#define PJ_FINAL_CUP_MATRIX_H

#include <climits>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <climits>
#include <algorithm>
#include <random>
#include <ctime>


using namespace std;

vector<vector<float>> Transpose(vector<vector<int>>& matrix, int dimension){

    int b = 0, a = 0, k = 0, o = 0;

    vector<vector<float>> transposed_matrix;
    for(k = 0; k < dimension; k++){
        vector<float> p;
        for (o = 0; o < dimension; o++){
            p.push_back(0.0);
        }
        transposed_matrix.push_back(p);
    }

    //---------------------------------------------------------
    transposed_matrix.at(0).at(0) = 0;
    cout << " " << transposed_matrix.at(a).at(b) << " ";
    while (a < dimension) {
        if(a == 0){
            b = 1;
        }
        while (b < dimension){
            transposed_matrix.at(a).at(b) = sqrt(pow(matrix[a][1] - matrix[b][1], 2) + pow(matrix[a][2] - matrix[b][2], 2));
            transposed_matrix[b][a] = transposed_matrix[a][b];
            cout << " " << transposed_matrix.at(a).at(b) << " ";
            if (a == b)
                transposed_matrix[a][b] = 0;
            b += 1;
        }
        cout << endl;
        a += 1;
        b = 0;
    }
    //---------------------------------------------------------

    for(k = 0; k < dimension; k++){
        for (o = 0; o < dimension; o++){
            cout << " " << transposed_matrix.at(k).at(o) << " ";
        }
        cout << "\n";
    }
    return transposed_matrix;
}

#endif //PJ_FINAL_CUP_MATRIX_H
