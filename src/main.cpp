#include <iostream>
#include "order_service/order.pb.h"
#include "config/config.hpp"


int main() {

    try {
        Config config = Config::New();
    }
    catch {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
