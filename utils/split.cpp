#include <sstream>
#include <vector>
#include <string>

std::vector<std::string> split(const std::string& input, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

std::vector<std::string> splitByString(const std::string& input, const std::string& delimiter) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end;

    while ((end = input.find(delimiter, start)) != std::string::npos) {
        result.push_back(input.substr(start, end - start));
        start = end + delimiter.length();
    }

    result.push_back(input.substr(start));
    return result;
}