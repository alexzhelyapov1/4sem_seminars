#include <iostream>
#include "metrics.h"

// void test() {
//     std::string buffer;
//     MetricsManager main_manager = {};
//     auto main_min = std::shared_ptr<My_min>(new My_min());
//     auto main_max = std::shared_ptr<My_max>(new My_max());
//     auto average = std::shared_ptr<Average>(new Average());
//     auto unique = std::shared_ptr<Unique_values>(new Unique_values());

//     main_manager.register_metric("max", main_max);
//     main_manager.register_metric("min", main_min);
//     main_manager.register_metric("average", average);
//     main_manager.register_metric("unique", unique);

//     main_manager.handle(5);
//     main_manager.handle(7);
//     main_manager.handle(6);

//     main_manager.print_all();
//     // main_manager.print_current_metric("mox");
//     // main_manager.print_current_metric("max");

//     while (true) {
//         std::cin >> buffer;
//         if (buffer == "show") {
//             std::cin >> buffer;
//             if (buffer == "all") {
//                 main_manager.print_all();
//             }
//             else {
//                 std::cout << "I'll show u metric " << buffer << ":\n";
//                 main_manager.print_current_metric(buffer);
//             }
//         }
//         else if (buffer == "q" || buffer == "quit") {
//             return 0;
//         }
//         else {
//             if (atoi(buffer.c_str()) == 0 && !(buffer[0] == '0' && buffer.length() == 1)) {
//                 std::cout << "Wrong number = " << buffer << std::endl;
//             }
//             else {
//                 main_manager.handle(atoi(buffer.c_str()));
//                 std::cout << atoi(buffer.c_str()) << " " << !(buffer[0] == '0' && buffer.length() == 1) << std::endl;
//             }
//         }
//     }
// }

int main() {
    My_Max test_max = {};
    // test_max.update(5);
}