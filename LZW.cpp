#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

// Function to perform LZW compression
std::vector<int> lzw_compress(const std::string& input) {
    // Initialize the dictionary with single character entries
    std::unordered_map<std::string, int> dictionary;
    int dictSize = 256; // ASCII characters
    for (int i = 0; i < dictSize; ++i) {
        dictionary[std::string(1, i)] = i;
    }

    std::string currentPrefix;
    std::vector<int> compressedOutput;

    for (char c : input) {
        std::string combined = currentPrefix + c;

        if (dictionary.count(combined)) {
            // Update the current prefix if combined is in the dictionary
            currentPrefix = combined;
        } else {
            // Add the current prefix's dictionary code to the output
            compressedOutput.push_back(dictionary[currentPrefix]);

            // Add the new combination to the dictionary
            dictionary[combined] = dictSize++;

            // Start with the new character
            currentPrefix = std::string(1, c);
        }
    }

    // Output the code for the last prefix
    if (!currentPrefix.empty()) {
        compressedOutput.push_back(dictionary[currentPrefix]);
    }

    return compressedOutput;
}

// Function to print the compressed output as a sequence of integers
void print_compressed_output(const std::vector<int>& compressedOutput) {
    std::cout << "Compressed output: ";
    for (int code : compressedOutput) {
        std::cout << code << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::string input;
    
    std::cout << "Enter the string to compress using LZW: ";
    std::getline(std::cin, input);

    std::vector<int> compressedOutput = lzw_compress(input);

    print_compressed_output(compressedOutput);

    return 0;
}
