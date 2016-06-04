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

#include <iostream>  // std::cout
#include <cstdlib>   // rand()
#include <queue>     // std::priority_queue
#include <ctime>     // time
#include <chrono>    // std::chrono
#include "mempool_common.hpp"
#include "SLPool.hpp"
#include "Event.hpp"

void StoragePoolTest(StoragePool *_pool, std::time_t _timeLimit) {
    // [1] Setup random numbers generator for memory size, say [100,2000] bytes.
    auto ms_max = 2000u, ms_min = 100u;
    // [2] Setup random numbers generator for time intervals, say [1,100] units.
    auto ti_max = 100u, ti_min = 1u;
    // [3] Create the pirority queue std::priority_queue 'pq' and
    //     insert some events comprising the simulation.
    std::priority_queue<Event *> pq;
    // Assuming there is a class Event that creates a pair address / time - stamp.
    // Run simulation fot the time set by the client.

    for (std::time_t t(0); t < _timeLimit; t++) {
        // Run while we have events pending or time to run.
        while (!pq.empty()) {
            // Access the event with the smallest time - stamp.
            Event *ev = pq.top();
            // Still some time left....
            if (ev->getTimeStamp() > t) break;
            // When we got here, the top event has run out of time.
            // Remove event from priority queue.
            pq.pop();
            // Calling free operator.
            _pool->Free(ev->getMemoryPtr());
            delete ev;
        }
        srand(time(NULL));
        auto memSize = rand()%(ms_max - ms_min) + ms_min;
        void *const add = _pool->Allocate(memSize);
        auto elapsedTime = rand()%(ti_max - ti_min) + ti_min;
        // Set time stamp some time from now.
        std::time_t releaseTime = t + elapsedTime;
        // Creating a new simulation event.
        pq.push(new Event(add, releaseTime));
    }
}

int main(int argc, char const *argv[]) {
    std::chrono::time_point<std::chrono::system_clock> ini, end;

    StoragePool *pool = new SLPool(2000);

    ini = std::chrono::system_clock::now();
    StoragePoolTest(pool, 1);
    end = std::chrono::system_clock::now();

    delete pool;

    auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - ini).count();

    std::cout << ">>> Elapsed time: " << elapsed_time << "ns" << std::endl;

    std::cout << ">>> Exiting with success...\n";

    return EXIT_SUCCESS;
}
