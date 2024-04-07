/**
 * \file SparseMatrix.hpp
 * \brief Namespace file for describing library.
 * \author Fedyna K.
 * \version 0.1.0
 * \date 02/04/2024
 * 
 * Define everything for the SparseMatrix class
 */

#ifndef __OSM_SPARSE_MATRIX__
#define __OSM_SPARSE_MATRIX__


#include "Chain.hpp"


/**
 * \class SparseMatrix
 * \brief Allow to create row/column sparse vectors.
 * 
 * The Chain class contains all algebraic functions that are related to vectors.
 * 
 * \tparam _CoefficientType The chain's coefficient types (default is OSM::ZCoefficient)
 * \tparam _ChainTypeFlag The type of vector the chain is representing (default is OSM::COLUMN)
 * 
 * \author Fedyna K.
 * \version 0.1.0
 * \date 07/04/2024
 */
template <typename _ChainType = OSM::Chain<OSM::ZCoefficient, OSM::COLUMN>>
class OSM::SparseMatrix {

private:
    std::vector<_ChainType> chains;
    // std::

public:



};


#endif