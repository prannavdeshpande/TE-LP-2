#include <iostream>
#include <cmath>

// Function to check if a number is prime
bool isPrime(long long n) {
    if (n <= 1) return false;
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

// Function to compute GCD using Euclidean algorithm
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find modular multiplicative inverse using Extended Euclidean Algorithm
long long modInverse(long long e, long long phi) {
    long long t = 0, newT = 1;
    long long r = phi, newR = e;
    
    while (newR != 0) {
        long long quotient = r / newR;
        long long tempT = newT;
        newT = t - quotient * newT;
        t = tempT;
        
        long long tempR = newR;
        newR = r - quotient * newR;
        r = tempR;
    }
    
    // If GCD is not 1, inverse doesn't exist
    if (r > 1) {
        std::cerr << "Inverse does not exist!" << std::endl;
        return -1;
    }
    
    // Make sure t is positive
    if (t < 0) {
        t += phi;
    }
    
    return t;
}

// Function for modular exponentiation (base^exp % mod)
long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    long long p, q, e, m;
    
    // Input two prime numbers
    std::cout << "Enter first prime number (p): ";
    std::cin >> p;
    while (!isPrime(p)) {
        std::cout << "Please enter a prime number for p: ";
        std::cin >> p;
    }
    
    std::cout << "Enter second prime number (q): ";
    std::cin >> q;
    while (!isPrime(q)) {
        std::cout << "Please enter a prime number for q: ";
        std::cin >> q;
    }
    
    // Compute n and phi
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    std::cout << "Modulus n = " << n << ", Totient phi = " << phi << std::endl;
    
    // Choose public exponent e
    std::cout << "Enter public exponent e (must be coprime with " << phi << "): ";
    std::cin >> e;
    while (gcd(e, phi) != 1 || e <= 1 || e >= phi) {
        std::cout << "Invalid e. Choose e such that 1 < e < " << phi << " and gcd(e, " << phi << ") = 1: ";
        std::cin >> e;
    }
    
    // Compute private exponent d
    long long d = modInverse(e, phi);
    if (d == -1) {
        std::cerr << "Error computing private key!" << std::endl;
        return 1;
    }
    std::cout << "Public key (e, n) = (" << e << ", " << n << ")" << std::endl;
    std::cout << "Private key (d, n) = (" << d << ", " << n << ")" << std::endl;
    
    // Input message
    std::cout << "Enter a message (number less than " << n << "): ";
    std::cin >> m;
    while (m < 0 || m >= n) {
        std::cout << "Message must be between 0 and " << n - 1 << ": ";
        std::cin >> m;
    }
    
    // Encryption: c = m^e % n
    long long c = modPow(m, e, n);
    std::cout << "Encrypted message (ciphertext) = " << c << std::endl;
    
    // Decryption: m' = c^d % n
    long long decrypted = modPow(c, d, n);
    std::cout << "Decrypted message = " << decrypted << std::endl;
    
    return 0;
}