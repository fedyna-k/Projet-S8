/**
 * \file Chain.hpp
 * \brief Namespace file for describing library.
 * \author Fedyna K.
 * \version 0.1.0
 * \date 08/04/2024
 * 
 * Define everything for the Chain class
 */

#ifndef __OSM_CHAIN__
#define __OSM_CHAIN__


#include "__base.hpp"
#include <unordered_map>
#include <vector>


namespace OSM {

/**
 * \class Chain
 * \brief Allow to create row/column sparse vectors.
 * 
 * The Chain class contains all algebraic functions that are related to vectors.
 * 
 * \tparam _CoefficientType The chain's coefficient types (default is OSM::ZCoefficient)
 * \tparam _ChainTypeFlag The type of vector the chain is representing (default is OSM::COLUMN)
 * 
 * \author Fedyna K.
 * \version 0.1.0
 * \date 08/04/2024
 */
template <typename _CoefficientType = OSM::ZCoefficient, int _ChainTypeFlag = OSM::COLUMN>
class Chain {

private:
    /** \brief The chain inner representation and storage of data. */
    std::unordered_map<int, _CoefficientType> chainData;

    /** \brief The chain coefficient type. */
    typedef _CoefficientType coefficientType;

    /** \brief The chain type flag. */
    int chainTypeFlag = _ChainTypeFlag;

    /** \brief The chain boundary. */
    int upperBound;

public:
    /**
     * \brief Create new Chain for SparseMatrix object.
     * 
     * Default constructor, initialize an empty Chain as a Z integers column chain.
     * 
     * \tparam _CoefficientType The chain's coefficient types (default is OSM::ZCoefficient)
     * \tparam _ChainTypeFlag The type of vector the chain is representing (default is OSM::COLUMN)
     * 
     * \see \link OSM::ZCoefficient \endlink
     * \see \link OSM::COLUMN \endlink
     * \see \link OSM::ROW \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    Chain();

    /**
     * \brief Create new Chain for SparseMatrix object.
     * 
     * Constructor with size, initialize an empty Chain as a Z integers column chain with boundary check.
     * 
     * \tparam _CoefficientType The chain's coefficient types (default is OSM::ZCoefficient)
     * \tparam _ChainTypeFlag The type of vector the chain is representing (default is OSM::COLUMN)
     * \param[in] _chainSize The upper bound of the Chain.
     * 
     * \see \link OSM::ZCoefficient \endlink
     * \see \link OSM::COLUMN \endlink
     * \see \link OSM::ROW \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    Chain(const int _chainSize);

    /**
     * \brief Create new Chain for SparseMatrix object.
     * 
     * Copy constructor, initialize a Chain based on the same type of chain.
     * The resulting chain will be a copy of the passed chain.
     * 
     * \pre The chains have the same coefficent type.
     * 
     * \warning Will raise an error if the other chain is not the same coefficient type.
     * 
     * \tparam _CoefficientType The chain's coefficient types (default is OSM::ZCoefficient)
     * \tparam _ChainTypeFlag The type of vector the chain is representing (default is OSM::COLUMN)
     * \param[in] _otherToCopy The chain we want to copy.
     * 
     * \see \link OSM::ZCoefficient \endlink
     * \see \link OSM::COLUMN \endlink
     * \see \link OSM::ROW \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    Chain(const Chain &_otherToCopy);

    /**
     * \brief Assign to other chain.
     * 
     * Assign to other chain coefficient-wise, equivalent to copying it.
     * 
     * \pre The chains have the same coefficent type.
     * 
     * \warning Will raise an error if the other chain is not the same coefficient type.
     * 
     * \param[in] _otherToCopy The chain we want to copy.
     * 
     * \return The reference to the modified chain.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    Chain& operator=(const Chain &_otherToCopy);

    /**
     * \brief Adds two chains together.
     * 
     * Adds each coefficient of the chain together.
     * 
     * \pre The chains have the same coefficent type and the same type flag.
     * 
     * \warning Will raise an error if the two chains are not the same coefficient type.
     * \warning Will raise an error if the two chains don't have the same type flag.
     * 
     * \param[in] _first The first chain.
     * \param[in] _second The second chain.
     * 
     * \return A new chain representing the result.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    template <typename _CT, int _CTF>
    friend Chain operator+(const Chain<_CT, _CTF> &_first, const Chain<_CT, _CTF> &_second);

    /**
     * \brief Substract two chains together.
     * 
     * Substract each coefficient of the chain together.
     * 
     * \pre The chains have the same coefficent type and the same type flag.
     * 
     * \warning Will raise an error if the two chains are not the same coefficient type.
     * \warning Will raise an error if the two chains don't have the same type flag.
     * 
     * \param[in] _first The first chain.
     * \param[in] _second The second chain.
     * 
     * \return A new chain representing the result.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    template <typename _CT, int _CTF>
    friend Chain operator-(const Chain<_CT, _CTF> &_first, const Chain<_CT, _CTF> &_second);

    /**
     * \brief Apply factor on each coefficients.
     * 
     * \warning Will raise an error if _lambda is 0.
     * 
     * \param[in] _lambda The factor to apply.
     * \param[in] _chain The second chain.
     * 
     * \return A new chain representing the result.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    template <typename _CT, int _CTF>
    friend Chain operator*(const int _lambda, const Chain<_CT, _CTF> &_chain);

    /**
     * \brief Apply factor on each coefficients.
     * 
     * \warning Will raise an error if _lambda is 0.
     * 
     * \param[in] _chain The second chain.
     * \param[in] _lambda The factor to apply.
     * 
     * \return A new chain representing the result.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    template <typename _CT, int _CTF>
    friend Chain operator*(const Chain<_CT, _CTF> &_chain, const _CT _lambda);

    /**
     * \brief Perform matrix multiplication between two chains.
     * 
     * Generate a column-based matrix from the matrix multiplication and return it.
     * 
     * \pre The chains have the same coefficent type.
     * 
     * \warning Will raise an error if the two chains are not the same coefficient type.
     * 
     * \param[in] _column The column chain.
     * \param[in] _row The row chain.
     * 
     * \return The result of the matrix multiplication, column-based.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    template <typename _CT>
    friend SparseMatrix<Chain<_CT, COLUMN>> operator*(const Chain<_CT, COLUMN> &_column, const Chain<_CT, ROW> &_row);

    /**
     * \brief Perform matrix multiplication between two chains.
     * 
     * Generate a row-based matrix from the matrix multiplication and return it.
     * 
     * \pre The chains have the same coefficent type.
     * 
     * \warning Will raise an error if the two chains are not the same coefficient type.
     * 
     * \param[in] _column The column chain.
     * \param[in] _row The row chain.
     * 
     * \return The result of the matrix multiplication, row-based.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    template <typename _CT>
    friend SparseMatrix<Chain<_CT, ROW>> operator%(const Chain<_CT, COLUMN> &_column, const Chain<_CT, ROW> &_row);

    /**
     * \brief Perform dot product between two chains.
     * 
     * \pre The chains have the same coefficent type.
     * 
     * \warning Will raise an error if the two chains are not the same coefficient type.
     * 
     * \param[in] _row The row chain.
     * \param[in] _column The column chain.
     * 
     * \return The result of type _CoefficientType.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    template <typename _CT>
    friend _CT operator*(const Chain<_CT, ROW> &_row, const Chain<_CT, COLUMN> &_column);

    /**
     * \brief Add a chain and assign.
     * 
     * Adds each coefficient of the chain together.
     * 
     * \pre The chains have the same coefficent type and the same type flag.
     * 
     * \warning Will raise an error if the two chains are not the same coefficient type.
     * \warning Will raise an error if the two chains don't have the same type flag.
     * 
     * \param[in] _other The other chain.
     * 
     * \return The modified chain representing the result.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    Chain& operator+=(const Chain &_other);

    /**
     * \brief Substract a chain and assign.
     * 
     * Substract each coefficient of the chain together.
     * 
     * \pre The chains have the same coefficent type and the same type flag.
     * 
     * \warning Will raise an error if the two chains are not the same coefficient type.
     * \warning Will raise an error if the two chains don't have the same type flag.
     * 
     * \param[in] _other The other chain.
     * 
     * \return The modified chain representing the result.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    Chain& operator-=(const Chain &_other);

    /**
     * \brief Apply factor on each coefficients and assign.
     * 
     * \warning Will raise an error if _lambda is 0.
     * 
     * \param[in] _lambda The factor to apply.
     * 
     * \return The modified chain representing the result.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    Chain& operator*=(const int _lambda);

    /**
     * \brief Get a coefficient from the chain.
     * 
     * \warning The chain will not perform boundary check if not specified in constructor and will return 0 if out of user-chosen bounds.
     * 
     * \param[in] _index The coefficient index.
     * 
     * \return The coefficient stored in the chain.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    _CoefficientType operator[](const int _index) const;

    /**
     * \brief Set a coefficient in the chain.
     * 
     * \warning The chain will not perform boundary check if not specified in constructor and will assign anyways.
     * 
     * \param[in] _index The coefficient index.
     * 
     * \return The reference to the assigned coefficient.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    _CoefficientType& operator[](const int _index);

    /**
     * \brief Get a subchain from the chain.
     * 
     * Removes all indexes provided in the vector from the chain and returns it.
     * 
     * \note Will return a copy of the chain if given vector is empty.
     * 
     * \param[in] _chain The chain to process.
     * \param[in] _indexes The indexes to remove.
     * 
     * \return A new chain representing the result.
     * 
     * \see \link OSM::Chain \endlink
     * \see \link std::vector \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    template <typename _CT, int _CTF>
    friend Chain<_CT, _CTF> operator/(const Chain<_CT, _CTF> &_chain, const std::vector<int> &_indexes);

    /**
     * \brief Get a subchain from the chain.
     * 
     * Removes all indexes provided in the vector from the chain and returns it.
     * 
     * \note Will return a copy of the chain if given vector is empty.
     * 
     * \param[in] _chain The chain to process.
     * \param[in] _indexes The indexes to remove.
     * 
     * \return A new chain representing the result.
     * 
     * \see \link OSM::Chain \endlink
     * \see \link std::vector \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    template <typename _CT, int _CTF>
    friend Chain<_CT, _CTF> operator/(const Chain<_CT, _CTF> &_chain, const int *_indexes);

    /**
     * \brief Get a subchain from the chain and assign.
     * 
     * Removes all indexes provided in the vector from the chain and returns it.
     * 
     * \note Will not alter the chain if given vector is empty.
     * 
     * \param[in] _indexes The indexes to remove.
     * 
     * \return The modified chain representing the result.
     * 
     * \see \link OSM::Chain \endlink
     * \see \link std::vector \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    Chain& operator/=(const std::vector<int> &_indexes);

    /**
     * \brief Get a subchain from the chain and assign.
     * 
     * Removes all indexes provided in the vector from the chain and returns it.
     * 
     * \note Will not alter the chain if given vector is empty.
     * 
     * \param[in] _indexes The indexes to remove.
     * 
     * \return The modified chain representing the result.
     * 
     * \see \link OSM::Chain \endlink
     * \see \link std::vector \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    Chain& operator/=(const int *_indexes);

    /**
     * \brief Iterator to the beginning of the chain.
     * 
     * \warning The chain is stored unordered for speed reason.
     * 
     * \return The iterator to the beginning of the chain.
     * 
     * \see \link OSM::Chain \endlink
     * \see \link std::unordered_map \endlink
     * \see \link std::unordered_map::iterator \endlink
     * \see \link std::unordered_map::begin \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    inline typename std::unordered_map<int, _CoefficientType>::iterator begin() noexcept;

    /**
     * \brief Constant iterator to the beginning of the chain.
     * 
     * \warning The chain is stored unordered for speed reason.
     * 
     * \return The constant iterator to the beginning of the chain.
     * 
     * \see \link OSM::Chain \endlink
     * \see \link std::unordered_map \endlink
     * \see \link std::unordered_map::const_iterator \endlink
     * \see \link std::unordered_map::begin \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    inline typename std::unordered_map<int, _CoefficientType>::const_iterator begin() const noexcept;

    /**
     * \brief Constant iterator to the beginning of the chain.
     * 
     * \warning The chain is stored unordered for speed reason.
     * 
     * \return The constant iterator to the beginning of the chain.
     * 
     * \see \link OSM::Chain \endlink
     * \see \link std::unordered_map \endlink
     * \see \link std::unordered_map::const_iterator \endlink
     * \see \link std::unordered_map::cbegin \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    inline typename std::unordered_map<int, _CoefficientType>::const_iterator cbegin() const noexcept;

    /**
     * \brief Iterator to the end of the chain.
     * 
     * \warning The chain is stored unordered for speed reason.
     * 
     * \return The iterator to the end of the chain.
     * 
     * \see \link OSM::Chain \endlink
     * \see \link std::unordered_map \endlink
     * \see \link std::unordered_map::iterator \endlink
     * \see \link std::unordered_map::end \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    inline typename std::unordered_map<int, _CoefficientType>::iterator end() noexcept;

    /**
     * \brief Constant iterator to the end of the chain.
     * 
     * \warning The chain is stored unordered for speed reason.
     * 
     * \return The constant iterator to the end of the chain.
     * 
     * \see \link OSM::Chain \endlink
     * \see \link std::unordered_map \endlink
     * \see \link std::unordered_map::const_iterator \endlink
     * \see \link std::unordered_map::end \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    inline typename std::unordered_map<int, _CoefficientType>::const_iterator end() const noexcept;

    /**
     * \brief Constant iterator to the end of the chain.
     * 
     * \warning The chain is stored unordered for speed reason.
     * 
     * \return The constant iterator to the end of the chain.
     * 
     * \see \link OSM::Chain \endlink
     * \see \link std::unordered_map \endlink
     * \see \link std::unordered_map::const_iterator \endlink
     * \see \link std::unordered_map::cend \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    inline typename std::unordered_map<int, _CoefficientType>::const_iterator cend() const noexcept;

    /**
     * \brief Transpose a Chain.
     * 
     * \return A new chain where the chain type flag is changed.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    inline Chain transpose();

    /**
     * \brief Checks if chain is a column.
     * 
     * \return true if chain is represented as a column, false otherwise.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 17/04/2024
     */
    bool isColumn() const;

    /**
     * \brief Checks if chain is a row.
     * 
     * \return true if chain is represented as a row, false otherwise.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 17/04/2024
     */
    bool isRow() const;
};

}

#endif