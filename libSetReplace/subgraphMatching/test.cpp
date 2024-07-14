#include <cstddef>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cassert>
#include "convert.h"
using namespace std;
using namespace STMatch;

int main() {
    vector<pair<int, int>> g = {
        {1, 2},
        {2, 99},
        {99, 100},
    };
    Graph ng = convert_to_arrays(g);
    cout << ng.nnodes << endl;
    cout << ng.nedges << endl;
    for (int i = 0; i < ng.nnodes + 1; ++i) {
        cout << ng.rowptr[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < ng.nedges; ++i) {
        cout << ng.colidx[i] << " ";
    }
    cout << endl;
    return 0;
}