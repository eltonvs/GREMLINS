/**
 *  @file mempool_common.cpp
 *  @brief Common implementation of new and delete operators
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *  @authors Selan Rodrigues dos Santos, Elton de Souza Vieira
 *
 *  File with the SLPool Class prototype
 */

#ifndef _mempool_common_hpp_
#define _mempool_common_hpp_

#include <cstddef>
#include "StoragePool.hpp"

struct Tag {
    StoragePool *pool;
};

void *operator new (std::size_t bytes, StoragePool &p) {
    Tag * const tag = reinterpret_cast<Tag *>(p.Allocate(bytes + sizeof(Tag)));
    tag->pool = &p;
    // skip sizeof tag to get the raw data - block.
    return (reinterpret_cast<void *>(tag + 1U));
}

void *operator new (std::size_t bytes) {  // Regular new
    Tag *const tag = reinterpret_cast<Tag *>(std::malloc(bytes + sizeof(Tag)));
    tag->pool = nullptr;
    // skip sizeof tag to get the raw data - block.
    return (reinterpret_cast<void *>(tag + 1U));
}

void operator delete (void *arg) noexcept {
    // We need to subtract 1U (in fact, pointer arithmetics) because arg
    // points to the raw data (second block of information).
    // The pool id (tag) is located "sizeof (Tag)" bytes before.
    Tag * const tag = reinterpret_cast<Tag *>(arg) - 1U;
    if (nullptr != tag->pool)  // Memory block belongs to a particular GM.
        tag->pool->Free(tag);
    else
        std::free(tag);  // Memory block belongs to the operational system.
}

#endif
