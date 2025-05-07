#include <iostream>
#include <cmath>
using namespace std;

// Function to perform modular exponentiation: (base^exp) % mod
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 != 0)
            result = (result * base) % mod;
        exp = exp >> 1; // divide by 2
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    long long p, g; // Publicly known prime number and primitive root

    // Sample inputs for verification
    cout << "Enter prime number (p): ";
    cin >> p;

    cout << "Enter primitive root modulo p (g): ";
    cin >> g;

    long long a, b;
    cout << "Enter private key of Alice (a): ";
    cin >> a;

    cout << "Enter private key of Bob (b): ";
    cin >> b;

    // Compute public keys
    long long A = modExp(g, a, p); // Alice sends A
    long long B = modExp(g, b, p); // Bob sends B

    // Compute shared secret
    long long keyA = modExp(B, a, p); // Alice computes
    long long keyB = modExp(A, b, p); // Bob computes

    cout << "\nAlice's Public Key (A): " << A;
    cout << "\nBob's Public Key (B): " << B;

    cout << "\n\nShared Secret Key (Alice's computation): " << keyA;
    cout << "\nShared Secret Key (Bob's computation): " << keyB;

    if (keyA == keyB)
        cout << "\n\n✅ Shared keys match! Secure communication can proceed.";
    else
        cout << "\n\n❌ Shared keys DO NOT match. Check your inputs.";

    return 0;
}
