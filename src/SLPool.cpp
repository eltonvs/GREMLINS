/*!
 *  @file SLPool.cpp
 *  @brief SLPool Class Implementations
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with the SLPool Class implementations
 */

#include <iostream>
#include <cstddef>  // To std::size_t
#include <cmath>    // To std::ceil
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
    return 0;
}

// Free memory
void SLPool::Free(void *_p) {}

// Debugging (just for tests)
void SLPool::debug() {
    std::cout << "Number of Blocks: " << mui_NumberOfBlocks << "\n\n";

    std::cout << "mr_Sentinel content:\n  ";
    std::cout << "memPos: " << &mr_Sentinel << ", ";
    std::cout << "mui_Lenght: " << mr_Sentinel.mui_Length << ", ";
    std::cout << "mp_Next: " << mr_Sentinel.mp_Next << "\n\n";

    std::cout << "mp_Pool content:\n";
    for (auto i(0u); i < mui_NumberOfBlocks; i++) {
        std::cout << "  [" << i << "], memPos: " << (mp_Pool+i) << ", ";
        std::cout << "mui_Lenght: " << mp_Pool[i].mui_Length << ", ";
        if (mp_Pool[i].mp_Next) {
            std::cout << "mp_Next: " << mp_Pool[i].mp_Next << "\n";
        } else {
            std::cout << "mc_RawArea: " << mp_Pool[i].mc_RawArea << "\n";
        }
    }
    std::cout << "\n";
}
