# Simple Diffie-Hellman Key Exchange Implementation
def is_prime(n):
    """Check if a number is prime."""
    if n < 2:
        return False
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
    return True

def get_prime():
    """Prompt user for a prime number and validate it."""
    while True:
        try:
            p = int(input("Enter a prime number (p): "))
            if is_prime(p):
                return p
            else:
                print("Error: Please enter a valid prime number.")
        except ValueError:
            print("Error: Please enter a valid integer.")

def get_generator(p):
    """Prompt user for a generator (1 <= g < p)."""
    while True:
        try:
            g = int(input(f"Enter a generator (g, 1 <= g < {p}): "))
            if 1 <= g < p:
                return g
            else:
                print(f"Error: Generator must be between 1 and {p-1}.")
        except ValueError:
            print("Error: Please enter a valid integer.")

def get_private_key(party, p):
    """Prompt user for a private key (1 <= key < p)."""
    while True:
        try:
            key = int(input(f"Enter {party}'s private key (1 <= key < {p}): "))
            if 1 <= key < p:
                return key
            else:
                print(f"Error: Private key must be between 1 and {p-1}.")
        except ValueError:
            print("Error: Please enter a valid integer.")

def modular_exponentiation(base, exponent, modulus):
    """Compute (base^exponent) mod modulus efficiently."""
    result = 1
    base = base % modulus
    while exponent > 0:
        if exponent & 1:  # If exponent is odd, multiply
            result = (result * base) % modulus
        base = (base * base) % modulus  # Square the base
        exponent >>= 1  # Divide exponent by 2
    return result

def diffie_hellman():
    """Perform Diffie-Hellman key exchange."""
    print("=== Diffie-Hellman Key Exchange ===")
    
    # Step 1: Get public parameters
    p = get_prime()
    g = get_generator(p)
    
    # Step 2: Get private keys
    print("\n--- Alice's Input ---")
    alice_private = get_private_key("Alice", p)
    print("\n--- Bob's Input ---")
    bob_private = get_private_key("Bob", p)
    
    # Step 3: Compute public keys
    alice_public = modular_exponentiation(g, alice_private, p)
    bob_public = modular_exponentiation(g, bob_private, p)
    
    # Step 4: Exchange public keys and compute shared secret
    alice_shared = modular_exponentiation(bob_public, alice_private, p)
    bob_shared = modular_exponentiation(alice_public, bob_private, p)
    
    # Step 5: Display results
    print("\n=== Results ===")
    print(f"Public Parameters: p = {p}, g = {g}")
    print(f"Alice's Public Key (A = g^a mod p): {alice_public}")
    print(f"Bob's Public Key (B = g^b mod p): {bob_public}")
    print(f"Alice's Shared Secret (B^a mod p): {alice_shared}")
    print(f"Bob's Shared Secret (A^b mod p): {bob_shared}")
    
    # Verify the shared secrets match
    if alice_shared == bob_shared:
        print("\nSuccess: Alice and Bob have the same shared secret key!")
    else:
        print("\nError: Shared secrets do not match!")

if __name__ == "__main__":
    diffie_hellman()