#include <iostream>
#include <exception>

#include <radiorandom/core/executor/core.hpp>

int main(int argc, char ** argv) {
    try {
        core::executor core(argc,argv);
        core.run();
    } catch (std::exception const& e) {
        std::cout << e.what() << std::endl;
    }
}
