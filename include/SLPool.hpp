/*!
 *  @file SLPool.cpp
 *  @brief SLPool Class Prototype
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with the SLPool Class prototype
 */

#ifndef _SLPool_hpp_
#define _SLPool_hpp_

#include <cstddef>  // To std::size_t
#include "StoragePool.hpp"

class SLPool : public StoragePool {
 public:
    /**
     * @brief SLPool constructor
     */
    explicit SLPool(std::size_t _b);

    /**
     * @brief SLPool destructor
     */
    ~SLPool();

    /**
     * @brief Allocate memory
     * @param _b Number of bytes to be allocated
     * @return A pointer to the beggining of the allocated area
     */
    void *Allocate(std::size_t _b);

    /**
     * @brief Allocate memory using the Best Fit algorithm
     * @param _b Number of bytes to be allocated
     * @return A pointer to the beggining of the allocated area
     */
    void *AllocateBF(std::size_t _b);

    /**
     * @brief Free Memory
     * @param _p A pointer to element to be freed
     */
    void Free(void *_p);

    /**
     * @brief Function to show a visual representation from memory Blocks
     */
    void view();

    /**
     * @brief The header of the memory block
     */
    struct Header {
        unsigned int mui_Length;  //!< The block's size
        //! Header Constructor
        Header() : mui_Length(0u) {}
    };

    /**
     * @brief The reserved memory (or a pointer to another block)
     */
    struct Block : public Header {
        //! A enum with the memory block size
        enum {
            BlockSize = 16  // Each block has 16 bytes.
        };

        //! A union with a pointer to the next block or the allocated memory
        union {
            Block *mp_Next;  //!< A pointer to the next block
            //! The allocated memory
            char mc_RawArea[BlockSize - sizeof(Header)];
        };

        //! The Block constructor
        Block() : Header(), mp_Next(nullptr) {}
    };

 private:
    unsigned int mui_NumberOfBlocks;  //!< The number of blocks
    Block *mp_Pool;                   //!< Head of list.
    Block &mr_Sentinel;               //!< End of the list.
};

#endif
