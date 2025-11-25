# ColombiaAPI
api for api-colombia.com info about Colombia site
# main
```cpp
#include "ColombiaAPI.h"
#include <iostream>

int main() {
   ColombiaAPI api;
    auto country_info = api.get_country_info().then([](json::value result) {
        std::cout << result<< std::endl;
    });
    country_info.wait();
    
    return 0;
}

# Launch (your script)
```
g++ -std=c++11 -o main main.cpp -lcpprest -lssl -lcrypto -lpthread -lboost_system -lboost_chrono -lboost_thread
./main
```
