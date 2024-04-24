/**
 * \file __base.hpp
 * \brief Defines all constants used by objects.
 * \author Fedyna K.
 * \version 0.1.0
 * \date 24/04/2024
 * 
 * Should not be included.
 */

#ifndef __OPTIMISED_SPARSED_MATRIX_BASE__
#define __OPTIMISED_SPARSED_MATRIX_BASE__


namespace OSM {
    /** \brief Chain type flag for column chain. */
    const int COLUMN = 0b01;
    /** \brief Chain type flag for row chain. */
    const int ROW    = 0b10;

    /** \brief The default type for signed integers. */
    typedef int ZCoefficient;
}

#endif