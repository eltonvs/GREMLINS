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
            return reinterpret_cast<void *>(reinterpret_cast<Header *>(pos)+1U);
        }
        prev_pos = pos, pos = pos->mp_Next;
    }

    throw(std::bad_alloc());
}

// Allocate function using Best Fit
void *SLPool::AllocateBF(std::size_t _b) {
    unsigned n_blocks = std::ceil(static_cast<float>(_b)/Block::BlockSize);
    Block *pos        = mr_Sentinel.mp_Next;
    Block *prev_pos   = &mr_Sentinel;
    Block *prev_best  = nullptr;
    Block *best       = nullptr;

    while (pos != nullptr) {
        if (pos->mui_Length >= n_blocks) {
            // The current Block have the same size that the client needs
            if (pos->mui_Length == n_blocks) {
                prev_pos->mp_Next = pos->mp_Next;
                return reinterpret_cast<void *>(reinterpret_cast<Header *>(pos)+1U);
            } else if (best == nullptr || best->mui_Length > pos->mui_Length) {
                best = pos, prev_best = prev_pos;
            }
        }
        prev_pos = pos, pos = pos->mp_Next;
    }

    if (best != nullptr) {
        prev_best->mp_Next             = best + n_blocks;
        prev_best->mp_Next->mp_Next    = best->mp_Next;
        prev_best->mp_Next->mui_Length = best->mui_Length - n_blocks;
        best->mui_Length               = n_blocks;
        return reinterpret_cast<void *>(reinterpret_cast<Header *>(best)+1U);
    }

    throw(std::bad_alloc());
}

// Free memory
void SLPool::Free(void *_p) {
    auto *ini   = reinterpret_cast<Block *>(reinterpret_cast<Header *>(_p)-1U);
    auto *pos   = mr_Sentinel.mp_Next;
    auto *p_pos = &mr_Sentinel;

    while (pos != nullptr) {
        if (pos <= ini) {
            p_pos = pos, pos = pos->mp_Next;
            continue;
        }
        if (p_pos + p_pos->mui_Length == ini && ini + ini->mui_Length == pos) {
            p_pos->mui_Length += ini->mui_Length + pos->mui_Length;
            ini->mui_Length    = 0;
            pos->mui_Length    = 0;
            p_pos->mp_Next     = pos->mp_Next;
        } else if (p_pos + p_pos->mui_Length == ini) {
            p_pos->mui_Length += ini->mui_Length;
            ini->mui_Length    = 0;
        } else if (ini + ini->mui_Length == pos) {
            ini->mui_Length += pos->mui_Length;
            pos->mui_Length  = 0;
            ini->mp_Next     = pos->mp_Next;
            p_pos->mp_Next   = ini;
        } else {
            p_pos->mp_Next = ini;
            ini->mp_Next   = pos;
        }
        return;
    }
    if (pos == nullptr) {
        ini->mp_Next   = nullptr;
        p_pos->mp_Next = ini;
    }
}

// Method to show a visual representation from memory blocks
void SLPool::view() {
    auto *pt = mr_Sentinel.mp_Next;
    auto pos = 0u;
    while (pos < mui_NumberOfBlocks - 1) {
        auto j = (mp_Pool + pos)->mui_Length;
        pos   += j;
        if (mp_Pool + pos - j == pt) {
            while (j-- > 0) std::cout << "[] ";
            pt = pt->mp_Next;
        } else {
            std::cout << "[" << std::string(j, '#') << "] ";
        }
    }
    std::cout << "\n";
}
