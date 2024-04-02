/**
 * \file OSM.hpp
 * \brief Namespace file for describing library.
 * \author Fedyna K.
 * \version 0.1.0
 * \date 02/04/2024
 * 
 * Define all classes and types for the Optimised Sparsed Matrix (OSM) library.
 * Should not be included directly.
 */

#ifndef __OPTIMISED_SPARSED_MATRIX__
#define __OPTIMISED_SPARSED_MATRIX__


namespace OSM {
    /** \brief Chain type flag for column chain. */
    const int COLUMN = 0b01;
    /** \brief Chain type flag for row chain. */
    const int ROW    = 0b10;

    /** \brief The default type for signed integers. */
    typedef int ZCoefficient;

    template <typename _CoefficientType = ZCoefficient, int _ChainTypeFlag = COLUMN>
    class Chain;

    template <typename _ChainType>
    class SparseMatrix;

    class BinaryMatrix;
    
}


#endif