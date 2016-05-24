/*!
 *  @file SLPool.cpp
 *  @brief SLPool Class Prototype
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with the SLPool Class prototype
 */

#ifndef _SLPool_hpp_
#define _SLPool_hpp_

#include <cstddef>
#include "StoragePool.hpp"

class SLPool : public StoragePool {
 public:
    explicit SLPool(std::size_t _b);
    ~SLPool();
    void *Allocate(std::size_t _b);
    void Free(void *_p);

    struct Header {
        unsigned int mui_Length;
        Header() : mui_Length(0u) {}
    };

    struct Block : public Header {
        enum {
            BlockSize = 16  // Each block has 16 bytes.
        };
        union {
            Block *mp_Next;
            char mc_RawArea[BlockSize - sizeof(Header)];
        };
        Block() : Header(), mp_Next(nullptr) {}
    };

 private:
    unsigned int mui_NumberOfBlocks;
    Block *mp_Pool;      //!< Head of list.
    Block &mr_Sentinel;  //!< End of the list.
};

#endif
