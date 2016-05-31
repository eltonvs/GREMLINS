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

#include <iostream>
#include "mempool_common.hpp"
#include "SLPool.hpp"

int main(int argc, char const *argv[]) {
    SLPool test(220);

    std::cout << "Empty Pool:" << std::endl;
    test.debug();

    for (int i = 0; i < 5; i++) {
        try {
            std::cout << "Returned value: " << test.Allocate(44) << std::endl;
        } catch (std::bad_alloc &e) {
            std::cerr << "Error" << std::endl;
        }
        test.debug();
    }

    std::cout << ">>> Exiting with success...\n";

    return EXIT_SUCCESS;
}
