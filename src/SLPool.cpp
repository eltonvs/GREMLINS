/*!
 *  @file SLPool.cpp
 *  @brief SLPool Class Implementations
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with the SLPool Class implementations
 */

#include <iostream>
#include <cstddef>  // To std::size_t
#include <string>   // To std::string
#include <cmath>    // To std::ceil
#include <new>      // To std::bad_alloc
#include "SLPool.hpp"

// Constructor
SLPool::SLPool(size_t _b) :
    mui_NumberOfBlocks(std::ceil(static_cast<float>(_b)/Block::BlockSize) + 1),
    mp_Pool(new Block[mui_NumberOfBlocks]),
    mr_Sentinel(mp_Pool[mui_NumberOfBlocks - 1]) {
    // Sets the first mp_Pool element values
    mp_Pool[0].mui_Length = mui_NumberOfBlocks - 1;
    mp_Pool[0].mp_Next = nullptr;

    // Makes mr_Sentinel points to the first mp_Pool element
    mr_Sentinel.mp_Next = mp_Pool;
}

// Destructor
SLPool::~SLPool() {
    delete[] mp_Pool;
}

// Allocate function
void *SLPool::Allocate(std::size_t _b) {
    unsigned n_blocks = std::ceil(static_cast<float>(_b)/Block::BlockSize);
    Block *pos        = mr_Sentinel.mp_Next;
    Block *prev_pos   = &mr_Sentinel;

    while (pos != nullptr) {
        if (pos->mui_Length >= n_blocks) {
            if (pos->mui_Length == n_blocks) {
                prev_pos->mp_Next = pos->mp_Next;
            } else {
                prev_pos->mp_Next             = pos + n_blocks;
                prev_pos->mp_Next->mp_Next    = pos->mp_Next;
                prev_pos->mp_Next->mui_Length = pos->mui_Length - n_blocks;
                pos->mui_Length               = n_blocks;
            }
            return reinterpret_cast<void *>(reinterpret_cast<int *>(pos)+1U);
        }
        prev_pos = pos, pos = pos->mp_Next;
    }

    throw(std::bad_alloc());
}

// Free memory
void SLPool::Free(void *_p) {}

// Debugging (just for tests)
void SLPool::debug() {
    auto *temp = mr_Sentinel.mp_Next;
    auto i     = 0u;
    while (i < mui_NumberOfBlocks - 1) {
        auto j = (mp_Pool + i)->mui_Length;
        i += j;
        if (mp_Pool + i - j == temp)
            while (j-- > 0)
                std::cout << "[] ";
        else
            std::cout << "[" << std::string(j, '#') << "] ";
    }
    std::cout << "\n";
}
