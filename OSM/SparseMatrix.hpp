/**
 * \file SparseMatrix.hpp
 * \brief Namespace file for describing library.
 * \author Fedyna K.
 * \version 0.1.0
 * \date 08/04/2024
 * 
 * Define everything for the SparseMatrix class
 */

#ifndef __OSM_SPARSE_MATRIX__
#define __OSM_SPARSE_MATRIX__


#include "Chain.hpp"
#include <stdint.h>


/**
 * \class SparseMatrix
 * \brief Vector<Map> implementation of sparse matrices.
 * 
 * The SparseMatrix class contains all algebraic functions that are related to matrix.
 * 
 * \tparam _ChainType The matrix chains types (default is default OSM::Chain)
 * 
 * \author Fedyna K.
 * \version 0.1.0
 * \date 08/04/2024
 */
template <typename _ChainType = OSM::Chain<OSM::ZCoefficient, OSM::COLUMN>>
class OSM::SparseMatrix {

private:
    /** \brief The inner chain storage. */
    std::vector<_ChainType> chains;

    /** \brief A vector of int containing state of each columns. */
    std::vector<uint64_t> chainsStates;

    /** \brief Stores all non empty chain indexes in order to implement iterators. */
    std::vector<int> nonEmptyChainsIndexes;

public:
    /**
     * \brief Create new SparseMatrix object.
     * 
     * Default constructor, initialize an empty Matrix as Z integers column chains.
     * 
     * \tparam _ChainType The matrix chains types (default is default OSM::Chain)
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    SparseMatrix();

    /**
     * \brief Create new SparseMatrix object.
     * 
     * Constructor with size, initialize an empty Matrix as Z integers column chains.
     * 
     * \tparam _ChainType The matrix chains types (default is default OSM::Chain)
     * \param[in] _chainCount The number of chains to preallocate.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    SparseMatrix(const int _chainCount);

    /**
     * \brief Create new Chain for SparseMatrix object.
     * 
     * Copy constructor, initialize a SparseMatrix based on the same type of matrix.
     * The resulting matrix will be a copy of the passed matrix.
     * 
     * \pre The matrices are the same type.
     * 
     * \warning Will raise an error if the other matrix is not the same chain type.
     * 
     * \tparam _ChainType The matrix chains types (default is default OSM::Chain)
     * \param[in] _otherToCopy The matrix we want to copy.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    SparseMatrix(const SparseMatrix &_otherToCopy);

    /**
     * \brief Assign to other matrix.
     * 
     * Assign to other matrix coefficient-wise, equivalent to copying it.
     * 
     * \pre The matrixs have the same chain type.
     * 
     * \warning Will raise an error if the other matrix is not the same chain type.
     * 
     * \param[in] _otherToCopy The matrix we want to copy.
     * 
     * \return The reference to the modified matrix.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    SparseMatrix& operator=(const SparseMatrix &_otherToCopy);

    /**
     * \brief Adds two matrices together.
     * 
     * Adds each coefficient of the matrix together.
     * 
     * \pre The matrixs have the same chain type.
     * 
     * \warning Will raise an error if the other matrix is not the same chain type.
     * 
     * \param[in] _first The first matrix.
     * \param[in] _second The second matrix.
     * 
     * \return A new matrix representing the result.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    template <typename _CT>
    friend SparseMatrix operator+(const SparseMatrix<_CT> &_first, const SparseMatrix<_CT> &_second);

    /**
     * \brief Substracts two matrices together.
     * 
     * Substracts each coefficient of the matrix together.
     * 
     * \pre The matrixs have the same chain type.
     * 
     * \warning Will raise an error if the other matrix is not the same chain type.
     * 
     * \param[in] _first The first matrix.
     * \param[in] _second The second matrix.
     * 
     * \return A new matrix representing the result.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    template <typename _CT>
    friend SparseMatrix operator-(const SparseMatrix<_CT> &_first, const SparseMatrix<_CT> &_second);

    /**
     * \brief Apply factor on each coefficients.
     * 
     * \warning Will raise an error if _lambda is 0.
     * 
     * \param[in] _lambda The factor to apply.
     * \param[in] _matrix The matrix.
     * 
     * \return A new matrix representing the result.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    template <typename _CT>
    friend SparseMatrix operator*(const int _lambda, const SparseMatrix<_CT> &_matrix);

    /**
     * \brief Apply factor on each coefficients.
     * 
     * \warning Will raise an error if _lambda is 0.
     * 
     * \param[in] _matrix The matrix.
     * \param[in] _lambda The factor to apply.
     * 
     * \return A new matrix representing the result.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    template <typename _CT>
    friend SparseMatrix operator*(const SparseMatrix<_CT> &_matrix, const int _lambda);

    /**
     * \brief Perform matrix multiplication between two chains.
     * 
     * Generate a column-based matrix from the matrix multiplication and return it.
     * 
     * \pre The matrix have the same coefficent type.
     * 
     * \warning Will raise an error if the two chains are not the same coefficient type.
     * 
     * \param[in] _first The first matrix.
     * \param[in] _second The second matrix.
     * 
     * \return The result of the matrix multiplication, column-based.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    template <typename _CT, int _CTF>
    friend SparseMatrix<Chain<_CT, COLUMN>> operator*(const SparseMatrix<Chain<_CT, _CTF>> &_first, const SparseMatrix<Chain<_CT, _CTF>> &_second);

    /**
     * \brief Perform matrix multiplication between two chains.
     * 
     * Generate a line-based matrix from the matrix multiplication and return it.
     * 
     * \pre The matrix have the same coefficent type.
     * 
     * \warning Will raise an error if the two chains are not the same coefficient type.
     * 
     * \param[in] _first The first matrix.
     * \param[in] _second The second matrix.
     * 
     * \return The result of the matrix multiplication, line-based.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    template <typename _CT, int _CTF>
    friend SparseMatrix<Chain<_CT, ROW>> operator%(const SparseMatrix<Chain<_CT, _CTF>> &_first, const SparseMatrix<Chain<_CT, _CTF>> &_second);

    /**
     * \brief Add a matrix and assign.
     * 
     * Adds each coefficient of the matrix together.
     * 
     * \pre The matrix have the same coefficent type.
     * 
     * \warning Will raise an error if the two chains are not the same coefficient type.
     * 
     * \param[in] _other The other matrix.
     * 
     * \return The modified matrix representing the result.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    SparseMatrix& operator+=(const SparseMatrix &_other);

    /**
     * \brief Substract a matrix and assign.
     * 
     * Substracts each coefficient of the matrix together.
     * 
     * \pre The matrix have the same coefficent type.
     * 
     * \warning Will raise an error if the two chains are not the same coefficient type.
     * 
     * \param[in] _other The other matrix.
     * 
     * \return The modified matrix representing the result.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    SparseMatrix& operator-=(const SparseMatrix &_other);

    /**
     * \brief Apply factor on each coefficients and assign.
     * 
     * \warning Will raise an error if _lambda is 0.
     * 
     * \param[in] _lambda The factor to apply.
     * 
     * \return The modified matrix representing the result.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    SparseMatrix& operator*=(const int _lambda);

    /**
     * \brief Apply factor on each coefficients and assign.
     * 
     * \warning Will raise an error if _lambda is 0.
     * 
     * \param[in] _lambda The factor to apply.
     * 
     * \return The modified matrix representing the result.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    template <typename _CT, int _CTF>
    SparseMatrix& operator*=(const SparseMatrix<Chain<_CT, _CTF>> &_other);

    /**
     * \brief Get a chain from the matrix.
     * 
     * \warning The matrix will perform boundary check.
     * 
     * \param[in] _index The coefficient index.
     * 
     * \return The chain stored at given index.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    _ChainType operator[](const int _index) const;

    /**
     * \brief Set a chain from the matrix.
     * 
     * \warning The matrix will perform boundary check.
     * 
     * \param[in] _index The coefficient index.
     * 
     * \return The reference to the chain stored at given index.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    _ChainType& operator[](const int _index);

    /**
     * \brief Get a column from the matrix, even if matrix is a row-chain matrix.
     * 
     * \note For column-chain matrixes, it is equivalent to operator[]. 
     * 
     * \warning The matrix will perform boundary check.
     * 
     * \param[in] _index The coefficient index.
     * 
     * \return The column stored at given index.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 17/04/2024
     */
    template <typename _CT>
    Chain<_CT, COLUMN> getColumn(const int _index) const;

    /**
     * \brief Get a row from the matrix, even if matrix is a row-chain matrix.
     * 
     * \note For row-chain matrixes, it is equivalent to operator[]. 
     * 
     * \warning The matrix will perform boundary check.
     * 
     * \param[in] _index The coefficient index.
     * 
     * \return The row stored at given index.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 17/04/2024
     */
    template <typename _CT>
    Chain<_CT, ROW> getRow(const int _index) const;

    /**
     * \brief Set a column from the matrix, even if matrix is a row-chain matrix.
     * 
     * \warning The matrix will perform boundary check.
     * 
     * \param[in] _index The coefficient index.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 17/04/2024
     */
    void setColumn(const int _index);

     /**
     * \brief Set a row from the matrix, even if matrix is a row-chain matrix.
     * 
     * \warning The matrix will perform boundary check.
     * 
     * \param[in] _index The coefficient index.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 17/04/2024
     */
    void setRow(const int _index);

    /**
     * \brief Get a submatrix from the matrix.
     * 
     * Removes all indexes provided in the vector from the matrix and returns it.
     * 
     * \note Will return a copy of the matrix if given vector is empty.
     * \note The submatrix will be rectangular.
     * 
     * \param[in] _matrix The matrix to process.
     * \param[in] _indexes The indexes to remove.
     * 
     * \return A new matrix representing the result.
     * 
     * \see \link OSM::SparseMatrix \endlink
     * \see \link std::vector \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    template <typename _CT>
    friend SparseMatrix<_CT> operator/(const SparseMatrix<_CT> &_matrix, const std::vector<int> &_indexes);

    /**
     * \brief Get a submatrix from the matrix.
     * 
     * Removes all indexes provided in the vector from the matrix and returns it.
     * 
     * \note Will return a copy of the matrix if given vector is empty.
     * \note The submatrix will be rectangular.
     * 
     * \param[in] _matrix The matrix to process.
     * \param[in] _indexes The indexes to remove.
     * 
     * \return A new matrix representing the result.
     * 
     * \see \link OSM::SparseMatrix \endlink
     * \see \link std::vector \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    template <typename _CT>
    friend SparseMatrix<_CT> operator/(const SparseMatrix<_CT> &_matrix, const int *_indexes);

    /**
     * \brief Get a submatrix from the matrix and assign.
     * 
     * Removes all indexes provided in the vector from the matrix and returns it.
     * 
     * \note Will not alter the matrix if given vector is empty.
     * 
     * \param[in] _indexes The indexes to remove.
     * 
     * \return The modified matrix representing the result.
     * 
     * \see \link OSM::SparseMatrix \endlink
     * \see \link std::vector \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    SparseMatrix& operator/=(const std::vector<int> &_indexes);

    /**
     * \brief Get a submatrix from the matrix and assign.
     * 
     * Removes all indexes provided in the vector from the matrix and returns it.
     * 
     * \note Will not alter the matrix if given vector is empty.
     * 
     * \param[in] _indexes The indexes to remove.
     * 
     * \return The modified matrix representing the result.
     * 
     * \see \link OSM::SparseMatrix \endlink
     * \see \link std::vector \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    SparseMatrix& operator/=(const int *_indexes);

    /**
     * \brief Iterator to the beginning of the chains.
     * 
     * \warning The chains are stored in a FIFO order for speed reason.
     * 
     * \return The iterator to the beginning of the chains.
     * 
     * \see \link OSM::SparseMatrix \endlink
     * \see \link OSM::Chain \endlink
     * \see \link std::vector \endlink
     * \see \link std::vector::iterator \endlink
     * \see \link std::vector::begin \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    inline typename std::vector<_ChainType>::iterator begin() noexcept;

    /**
     * \brief Constant iterator to the beginning of the chains.
     * 
     * \warning The chains are stored in a FIFO order for speed reason.
     * 
     * \return The constant iterator to the beginning of the chains.
     * 
     * \see \link OSM::SparseMatrix \endlink
     * \see \link OSM::Chain \endlink
     * \see \link std::vector \endlink
     * \see \link std::vector::const_iterator \endlink
     * \see \link std::vector::begin \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    inline typename std::vector<_ChainType>::const_iterator begin() const noexcept;

    /**
     * \brief Constant iterator to the beginning of the chains.
     * 
     * \warning The chains are stored in a FIFO order for speed reason.
     * 
     * \return The constant iterator to the beginning of the chains.
     * 
     * \see \link OSM::SparseMatrix \endlink
     * \see \link OSM::Chain \endlink
     * \see \link std::vector \endlink
     * \see \link std::vector::const_iterator \endlink
     * \see \link std::vector::begin \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    inline typename std::vector<_ChainType>::const_iterator cbegin() const noexcept;

    /**
     * \brief Reverse iterator to the beginning of the chains.
     * 
     * \warning The chains are stored in a FIFO order for speed reason.
     * 
     * \return The iterator to the beginning of the chains.
     * 
     * \see \link OSM::SparseMatrix \endlink
     * \see \link OSM::Chain \endlink
     * \see \link std::vector \endlink
     * \see \link std::vector::iterator \endlink
     * \see \link std::vector::begin \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    inline typename std::vector<_ChainType>::reverse_iterator rbegin() noexcept;

    /**
     * \brief Constant reverse iterator to the beginning of the chains.
     * 
     * \warning The chains are stored in a FIFO order for speed reason.
     * 
     * \return The constant iterator to the beginning of the chains.
     * 
     * \see \link OSM::SparseMatrix \endlink
     * \see \link OSM::Chain \endlink
     * \see \link std::vector \endlink
     * \see \link std::vector::const_iterator \endlink
     * \see \link std::vector::begin \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    inline typename std::vector<_ChainType>::const_reverse_iterator rbegin() const noexcept;

    /**
     * \brief Constant reverse iterator to the beginning of the chains.
     * 
     * \warning The chains are stored in a FIFO order for speed reason.
     * 
     * \return The constant iterator to the beginning of the chains.
     * 
     * \see \link OSM::SparseMatrix \endlink
     * \see \link OSM::Chain \endlink
     * \see \link std::vector \endlink
     * \see \link std::vector::const_iterator \endlink
     * \see \link std::vector::begin \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    inline typename std::vector<_ChainType>::const_reverse_iterator crbegin() const noexcept;

    /**
     * \brief Iterator to the endning of the chains.
     * 
     * \warning The chains are stored in a FIFO order for speed reason.
     * 
     * \return The iterator to the endning of the chains.
     * 
     * \see \link OSM::SparseMatrix \endlink
     * \see \link OSM::Chain \endlink
     * \see \link std::vector \endlink
     * \see \link std::vector::iterator \endlink
     * \see \link std::vector::end \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    inline typename std::vector<_ChainType>::iterator end() noexcept;

    /**
     * \brief Constant iterator to the endning of the chains.
     * 
     * \warning The chains are stored in a FIFO order for speed reason.
     * 
     * \return The constant iterator to the endning of the chains.
     * 
     * \see \link OSM::SparseMatrix \endlink
     * \see \link OSM::Chain \endlink
     * \see \link std::vector \endlink
     * \see \link std::vector::const_iterator \endlink
     * \see \link std::vector::end \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    inline typename std::vector<_ChainType>::const_iterator end() const noexcept;

    /**
     * \brief Constant iterator to the endning of the chains.
     * 
     * \warning The chains are stored in a FIFO order for speed reason.
     * 
     * \return The constant iterator to the endning of the chains.
     * 
     * \see \link OSM::SparseMatrix \endlink
     * \see \link OSM::Chain \endlink
     * \see \link std::vector \endlink
     * \see \link std::vector::const_iterator \endlink
     * \see \link std::vector::end \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    inline typename std::vector<_ChainType>::const_iterator cend() const noexcept;

    /**
     * \brief Reverse iterator to the endning of the chains.
     * 
     * \warning The chains are stored in a FIFO order for speed reason.
     * 
     * \return The iterator to the endning of the chains.
     * 
     * \see \link OSM::SparseMatrix \endlink
     * \see \link OSM::Chain \endlink
     * \see \link std::vector \endlink
     * \see \link std::vector::iterator \endlink
     * \see \link std::vector::end \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    inline typename std::vector<_ChainType>::reverse_iterator rend() noexcept;

    /**
     * \brief Constant reverse iterator to the endning of the chains.
     * 
     * \warning The chains are stored in a FIFO order for speed reason.
     * 
     * \return The constant iterator to the endning of the chains.
     * 
     * \see \link OSM::SparseMatrix \endlink
     * \see \link OSM::Chain \endlink
     * \see \link std::vector \endlink
     * \see \link std::vector::const_iterator \endlink
     * \see \link std::vector::end \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    inline typename std::vector<_ChainType>::const_reverse_iterator rend() const noexcept;

    /**
     * \brief Constant reverse iterator to the endning of the chains.
     * 
     * \warning The chains are stored in a FIFO order for speed reason.
     * 
     * \return The constant iterator to the endning of the chains.
     * 
     * \see \link OSM::SparseMatrix \endlink
     * \see \link OSM::Chain \endlink
     * \see \link std::vector \endlink
     * \see \link std::vector::const_iterator \endlink
     * \see \link std::vector::end \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    inline typename std::vector<_ChainType>::const_reverse_iterator crend() const noexcept;


    /**
     * \brief Transpose a matrix.
     * 
     * \return A new matrix where the chain type flag is changed.
     * 
     * \see \link OSM::Chain \endlink
     * 
     * \author Fedyna K.
     * \version 0.1.0
     * \date 08/04/2024
     */
    inline SparseMatrix transpose();
};


#endif