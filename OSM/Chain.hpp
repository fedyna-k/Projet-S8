/**
 * \file Chain.hpp
 * \brief Namespace file for describing library.
 * \author Fedyna K.
 * \version 0.1.0
 * \date 02/04/2024
 * 
 * Define everything for the Chain class
 */

#ifndef __OSM_CHAIN__
#define __OSM_CHAIN__


#include "OSM.hpp"
#include <unordered_map>


template <typename _CoefficientType = OSM::ZCoefficient, int _ChainTypeFlag = OSM::COLUMN>
class OSM::Chain {

private:
    std::unordered_map<int, _CoefficientType> chainData;

public:
    Chain();
    Chain(const Chain<_CoefficientType, _ChainTypeFlag> &_otherToCopy);

};


#endif