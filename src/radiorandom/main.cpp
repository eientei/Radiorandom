#include <iostream>
#include <string>

#include <radiorandom/executor/core.hpp>
#include <radiorandom/controller/generic/superclass.hpp>

int main(int argc, char ** argv) {
    try {
        executor::core core(argc,argv);
        core.run();
    } catch (std::exception const& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
