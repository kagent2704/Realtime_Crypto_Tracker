#include <iostream>
#include <cpr/cpr.h>
#include <json/json.h>
#include <chrono>
#include <thread>

void fetchCryptoPrice(const std::string& symbol, const std::string& apiKey) {
    const std::string apiUrl = "https://pro-api.coinmarketcap.com/v1/cryptocurrency/quotes/latest?symbol=" + symbol;
    
    while (true) {
        cpr::Header headers = {
            {"Accepts", "application/json"},
            {"X-CMC_PRO_API_KEY", "9ed94f39-c49d-46d7-8763-cddda454c830"}
        };

        cpr::Response response = cpr::Get(cpr::Url{ apiUrl }, headers);

        if (response.status_code == 200) {
            Json::Value jsonData;
            Json::CharReaderBuilder reader;
            std::string errs;
            std::istringstream s(response.text);
            if (Json::parseFromStream(reader, s, &jsonData, &errs)) {
                double price = jsonData["data"][symbol]["quote"]["USD"]["price"].asDouble();
                std::cout << "Current price of " << symbol << " in USD: $" << price << std::endl;
            } else {
                std::cerr << "Error parsing JSON: " << errs << std::endl;
            }
        } else {
            std::cerr << "Error fetching data, HTTP Status Code: " << response.status_code << std::endl;
            std::cout << "Response text: " << response.text << std::endl;  // Print response text for debugging
        }
        std::this_thread::sleep_for(std::chrono::seconds(30)); // Update every 30 seconds
    }
}

int main() {
    std::string symbol;
    std::string apiKey = "9ed94f39-c49d-46d7-8763-cddda454c830";  // Replace with your API key
    std::cout << "Enter the cryptocurrency symbol (e.g., 'ETH'): ";
    std::cin >> symbol;
    fetchCryptoPrice(symbol, apiKey);
    return 0;
}
