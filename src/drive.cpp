/*!
 *  @mainpage GREMLINS
 *  @author Elton de Souza Vieira
 *  @date May, 2016
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *  @version 1.0
 *
 *  @file drive.cpp
 *  @brief Driver File
 *
 *  File with the Memory Manager tests
 */

#include <iostream>  // I/O
#include <cstdlib>   // rand_r()
#include <cassert>   // assert
#include <queue>     // std::priority_queue
#include <chrono>    // std::chrono
#include <cmath>     // std::ceil
#include <string>    // std::string

#include "mempool_common.hpp"
#include "SLPool.hpp"
#include "Event.hpp"

/**
 * @brief Function to test the Pool allocation in a time limit
 * @param _pool A pointer to the pool to be used
 * @param _timeLimit The time limit
 */
void StoragePoolTest(StoragePool *_pool, std::time_t _timeLimit) {
    // [1] Setup random numbers generator for memory size, say [100,2000] bytes.
    auto ms_max = 2000u, ms_min = 100u;
    // [2] Setup random numbers generator for time intervals, say [1,100] units.
    auto ti_max = 100u, ti_min = 1u;
    // [3] Create the pirority queue std::priority_queue 'pq' and
    //     insert some events comprising the simulation.
    std::priority_queue<Event> pq;
    // Assuming there is a class Event that creates a pair address / time stamp.
    // Run simulation fot the time set by the client.

    for (std::time_t t(0); t < _timeLimit; t++) {
        // Run while we have events pending or time to run.
        while (!pq.empty()) {
            // Access the event with the smallest time - stamp.
            Event ev = pq.top();
            // Still some time left....
            if (ev.getTimeStamp() > t) break;
            // When we got here, the top event has run out of time.
            // Remove event from priority queue.
            pq.pop();
            // Calling free operator.
            _pool->Free(ev.getMemoryPtr());
        }
        unsigned seed = static_cast<unsigned>(time(NULL));
        auto memSize = rand_r(&seed)%(ms_max - ms_min) + ms_min;
        void *const add = _pool->Allocate(memSize);
        auto elapsedTime = rand_r(&seed)%(ti_max - ti_min) + ti_min;
        // Set time stamp some time from now.
        std::time_t releaseTime = t + elapsedTime;
        // Creating a new simulation event.
        pq.push(Event(add, releaseTime));
        // Show Memory Map on Screen.
        _pool->view();
    }
}

/**
 * @brief The unit and visual tests to ensure the Pool is working as well
 * @param _pool The Pool to be tested
 */
void StoragePoolValidation(StoragePool &_pool) {
    int *allocs[7];

    // Shows the initial state from memory pool
    std::cout << "::: Initial State :::\n" << std::string(4, ' ');
    _pool.view();

    // Allocate 10 integers 3 times to test allocation on begining of pool
    for (int i = 0; i < 3; i++) {
        allocs[i] = new(_pool) int[10];
        std::cout << "[" << i << "] <<< Allocating 10 integers\n"
                  << std::string(8, ' ');
        _pool.view();
    }

    // Unit tests (testing assignment)
    for (int i = 0; i < 10; i++) {
        allocs[0][i] = i;
        allocs[1][i] = i;
        allocs[2][i] = i;
        assert(allocs[0][i] == i);
        assert(allocs[1][i] == i);
        assert(allocs[2][i] == i);
    }

    // Free the first allocation (no merge)
    delete allocs[0];
    std::cout << "[0] <<< Free allocation:\n" << std::string(8, ' ');
    _pool.view();

    // Free the third allocation (merge on right side)
    delete allocs[2];
    std::cout << "[2] <<< Free allocation:\n" << std::string(8, ' ');
    _pool.view();

    // Allocate 30 integers (allocation after another element and empty spaces)
    allocs[3] = new(_pool) int[30];
    std::cout << "[3] <<< Allocate 30 integers:\n" << std::string(8, ' ');
    _pool.view();

    // Unit tests (testing assignment)
    for (int i = 0; i < 30; i++) {
        allocs[3][i] = i;
        assert(allocs[3][i] == i);
    }

    // Free the second allocation (merge on left side)
    delete allocs[1];
    std::cout << "[1] <<< Free allocation:\n" << std::string(8, ' ');
    _pool.view();

    // Allocate 1 integer 2 times (at the beginning of the pool)
    for (int i = 4; i < 6; i++) {
        allocs[i] = new(_pool) int[1];
        std::cout << "[" << i << "] <<< Allocate 1 integer:\n"
                  << std::string(8, ' ');
        _pool.view();
    }

    // Unit tests (testing assignment)
    for (int i = 0; i < 1; i++) {
        allocs[4][i] = i;
        allocs[5][i] = i;
        assert(allocs[4][i] == i);
        assert(allocs[5][i] == i);
    }

    // Free allocs[4] (no merge)
    delete allocs[4];
    std::cout << "[4] <<< Free allocation:\n" << std::string(8, ' ');
    _pool.view();

    // Free allocs[3] (merge on both sides)
    delete allocs[3];
    std::cout << "[3] <<< Free allocation:\n" << std::string(8, ' ');
    _pool.view();

    // Allocate 65 integers (fitting all the right area on pool)
    allocs[6] = new(_pool) int[65];
    std::cout << "[6] <<< Allocate 65 integers:\n" << std::string(8, ' ');
    _pool.view();

    // Unit tests (testing assignment)
    for (int i = 0; i < 65; i++) {
        allocs[6][i] = i;
        assert(allocs[6][i] == i);
    }

    // Free allocs[6] (no merge)
    delete allocs[6];
    std::cout << "[6] <<< Free allocation:\n" << std::string(8, ' ');
    _pool.view();

    // Free allocs[5] (merge on both sides)
    delete allocs[5];
    std::cout << "[5] <<< Free allocation:\n" << std::string(8, ' ');
    _pool.view();
}

int main(int argc, char const *argv[]) {
#if (_TEST_TYPE_ == 1)
    StoragePool *pool = new SLPool(300);
    StoragePoolValidation(*pool);
    delete pool;

    std::cout << ">>> Exiting with success...\n";
#endif

#if (_TEST_TYPE_ == 2)
    // Creates the pool
    StoragePool *pool = new SLPool(2000);

    // The initial time
    auto s = std::chrono::steady_clock::now();
    // Run the function to tests
    StoragePoolTest(pool, 1);
    // The final time
    auto e = std::chrono::steady_clock::now();
    // Calculates the difference
    auto diff = std::chrono::duration<double, std::nano>(e - s).count();

    std::cout << ">>> Elapsed time: " << diff << "ns" << std::endl;

    // Deletes the pool
    delete pool;
#endif

#if (_TEST_TYPE_ == 3)
    std::chrono::steady_clock::time_point start, end;
    auto elapsed_time = 0.0l;
    int times = 100000, *al1 = nullptr, *al2 = nullptr;
    SLPool pool(100);

    // Average Time with the Memory Manager
    for (int i = 0; i < times; i++) {
        start = std::chrono::steady_clock::now();
        for (int j = 1; j <= 10; j += 2) {
            al1 = new(pool) int[j];
            al2 = new(pool) int[j+1];
            delete[] al1;
            delete[] al2;
        }
        // The final time
        end = std::chrono::steady_clock::now();
        // Calculates the difference
        auto diff = std::chrono::duration<double, std::nano>(end-start).count();
        // Calculates the average time using standard deviation
        elapsed_time += (diff - elapsed_time)/(i+1);
    }
    std::cout << ">>> MM time: " << elapsed_time << " ns\n";

    // Average Time with the Operational System
    elapsed_time = 0;
    for (int i = 0; i < times; i++) {
        start = std::chrono::steady_clock::now();
        for (int j = 1; j <= 10; j += 2) {
            al1 = new int[j];
            al2 = new int[j+1];
            delete[] al1;
            delete[] al2;
        }
        // The final time
        end = std::chrono::steady_clock::now();
        // Calculates the difference
        auto diff = std::chrono::duration<double, std::nano>(end-start).count();
        // Calculates the average time using standard deviation
        elapsed_time += (diff - elapsed_time)/(i+1);
    }
    std::cout << ">>> OS time: " << elapsed_time << " ns\n";
#endif

    return EXIT_SUCCESS;
}
