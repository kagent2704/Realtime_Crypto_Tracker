#include <iostream>
#include <cpr/cpr.h>
#include <json/json.h>
#include <chrono>
#include <thread>

void fetchCryptoPrice(const std::string& symbol) {
    const std::string apiUrl = "https://api.coingecko.com/api/v3/simple/price?ids=" + symbol + "&vs_currencies=usd";
    while (true) {
        cpr::Response response = cpr::Get(cpr::Url{ apiUrl });
        if (response.status_code == 200) {
            Json::Value jsonData;
            Json::CharReaderBuilder reader;
            std::string errs;
            std::istringstream s(response.text);
            if (Json::parseFromStream(reader, s, &jsonData, &errs)) {
                double price = jsonData[symbol]["usd"].asDouble();
                std::cout << "Current price of " << symbol << " in USD: $" << price << std::endl;
            }
            else {
                std::cerr << "Error parsing JSON: " << errs << std::endl;
            }
        }
        else {
            std::cerr << "Error fetching data, HTTP Status Code: " << response.status_code << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(10)); // Update every 10 seconds
    }
}

int main() {
    std::string symbol;
    std::cout << "Enter the cryptocurrency symbol (e.g., 'bitcoin'): ";
    std::cin >> symbol;
    fetchCryptoPrice(symbol);
    return 0;
}
