#include <iostream>
#include <cstdint>
#include <random>

struct CustomNumber {
    // 6-byte number represented using an array of uint8_t
    uint8_t value[6];

    // Constructor to initialize the 6-byte number
    CustomNumber() {
        generateRandomNumber();
    }

private:
    // Function to generate a random 6-byte number with the first 2 bits set to 0
    void generateRandomNumber() {
        std::random_device rd;
        std::mt19937_64 eng(rd());
        std::uniform_int_distribution<uint8_t> distr(0, std::numeric_limits<uint8_t>::max());

        // Set the first 2 bits to 0
        value[0] &= 0b00111111;

        // Fill the rest with random values
        for (int i = 1; i < 6; ++i) {
            value[i] = distr(eng);
        }
    }
};

int main() {
    // Create an instance of the CustomNumber struct
    CustomNumber myNumber;

    // Display the generated 6-byte number
    std::cout << "Generated 6-byte Number: ";
    for (int i = 0; i < 6; ++i) {
        std::cout << std::hex << static_cast<int>(myNumber.value[i]) << " ";
    }
    std::cout << std::dec << std::endl;

    return 0;
}