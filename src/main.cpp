#include <iostream>
#include "order_service/order.pb.h"

int main() {

    order_service::v1::Order order;
    order.set_id("1");

    std::cout << order.id() << std::endl;
    return 0;
}
