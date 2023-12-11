#include <iostream>
#include <random>

// Function to generate a random number with a fixed byte length
template <typename T>
T generateRandomNumber(int byteLength) {
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<T> distr(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

    T randomValue = 0;

    for (int i = 0; i < byteLength; ++i) {
        randomValue = (randomValue << 8) | distr(eng);
    }

    return randomValue;
}

int main() {
    // Specify the byte length you want (e.g., 4 bytes for a 32-bit integer)
    int byteLength = 6;
    
    // Generate a random number with the specified byte length
    uint32_t randomNumber = generateRandomNumber<uint32_t>(byteLength);

    // Display the generated random number
    std::cout << "Random Number: " << randomNumber << std::endl;

    return 0;
}