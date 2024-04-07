#include "SparseMatrix.hpp"

int main() {
    OSM::Chain test;
    OSM::Chain<OSM::ZCoefficient, OSM::ROW> test2;
    int index[] = {1, 2, 3};

    auto boom = 3 * test / index;

    return 0;
}