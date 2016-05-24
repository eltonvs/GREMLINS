/*!
 *  @file StoragePool.hpp
 *  @brief StoragePool Class Prototype
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with the StoragePool Class prototype
 */

#ifndef _StoragePool_hpp_
#define _StoragePool_hpp_

#include <cstddef>

class StoragePool {
 public:
    /**
     * @brief StoragePool destructos
     */
    virtual ~StoragePool();

    /**
     * @brief Allocate memory
     * @param _b Number of bytes to be allocated
     */
    virtual void *Allocate(std::size_t _b) = 0;

    /**
     * @brief Free memory
     * @param _p A pointer to element to be freed
     */
    virtual void Free(void *_p) = 0;
};

#endif
