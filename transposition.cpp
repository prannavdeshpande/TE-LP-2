#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

void print_matrix(const std::vector<std::vector<char>>& matrix, const std::string& title) {
    std::cout << "\n" << title << ":\n";
    std::cout << "+";
    for (size_t i = 0; i < matrix[0].size(); ++i) std::cout << "---+";
    std::cout << "\n";
    for (const auto& row : matrix) {
        std::cout << "| ";
        for (char c : row) {
            std::cout << c << " | ";
        }
        std::cout << "\n+";
        for (size_t i = 0; i < matrix[0].size(); ++i) std::cout << "---+";
        std::cout << "\n";
    }
    std::cout << "\n";
}

std::string encrypt(const std::string& plaintext, const std::string& key, std::vector<std::vector<char>>& matrix) {
    if (key.empty()) throw std::runtime_error("Key cannot be empty");
    if (plaintext.empty()) throw std::runtime_error("Plaintext cannot be empty");

    int col = key.length();
    int row = (plaintext.length() + col - 1) / col;

    matrix.assign(row, std::vector<char>(col, '~'));

    for (size_t i = 0; i < plaintext.length(); ++i) {
        matrix[i / col][i % col] = plaintext[i];
    }

    std::vector<std::pair<char, int>> key_order;
    for (int i = 0; i < key.length(); ++i) {
        key_order.emplace_back(key[i], i);
    }
    std::sort(key_order.begin(), key_order.end());

    std::string cipher;
    for (const auto& pair : key_order) {
        int index = pair.second;
        for (int r = 0; r < row; ++r) {
            cipher += matrix[r][index];
        }
    }

    return cipher;
}

std::string decrypt(const std::string& cipher, const std::string& key) {
    if (key.empty()) throw std::runtime_error("Key cannot be empty");
    if (cipher.empty()) throw std::runtime_error("Ciphertext cannot be empty");
    int col = key.length();
    if (cipher.length() % col != 0) {
        throw std::runtime_error("Invalid ciphertext length");
    }
    int row = cipher.length() / col;

    std::vector<std::pair<char, int>> key_order;
    for (int i = 0; i < key.length(); ++i) {
        key_order.emplace_back(key[i], i);
    }
    std::sort(key_order.begin(), key_order.end());

    std::vector<int> index_order;
    for (const auto& pair : key_order) {
        index_order.push_back(pair.second);
    }

    std::vector<std::vector<char>> matrix(row, std::vector<char>(col, '~'));

    int idx = 0;
    for (int i : index_order) {
        for (int j = 0; j < row; ++j) {
            matrix[j][i] = cipher[idx++];
        }
    }

    std::string plaintext;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            plaintext += matrix[i][j];
        }
    }

    return plaintext;
}

std::string remove_trail_tilde(std::string plaintext) {
    while (!plaintext.empty() && plaintext.back() == '~') {
        plaintext.pop_back();
    }
    return plaintext;
}

int main() {
    std::string plaintext, key1, key2;

    std::cout << "====================================\n";
    std::cout << " Double Transposition Cipher\n";
    std::cout << "====================================\n";
    std::cout << "Enter plaintext: ";
    std::getline(std::cin, plaintext);

    std::cout << "Enter key for first encryption: ";
    std::getline(std::cin, key1);
    for (char& c : key1) c = std::toupper(c);

    std::vector<std::vector<char>> matrix1;
    std::string cipher_text;
    try {
        cipher_text = encrypt(plaintext, key1, matrix1);
        std::cout << "\nFirst Encryption: " << cipher_text << "\n";
        print_matrix(matrix1, "Matrix for First Encryption");
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    std::cout << "Enter key for second encryption: ";
    std::getline(std::cin, key2);
    for (char& c : key2) c = std::toupper(c);

    std::vector<std::vector<char>> matrix2;
    std::string double_cipher_text;
    try {
        double_cipher_text = encrypt(cipher_text, key2, matrix2);
        std::cout << "Double Encryption: " << double_cipher_text << "\n";
        print_matrix(matrix2, "Matrix for Second Encryption");
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    std::string single_decrypted_text, decrypted_text, final_decryption;
    try {
        single_decrypted_text = decrypt(double_cipher_text, key2);
        std::cout << "Single Decryption: " << single_decrypted_text << "\n";

        decrypted_text = decrypt(single_decrypted_text, key1);
        std::cout << "Decrypted Text: " << decrypted_text << "\n";

        final_decryption = remove_trail_tilde(decrypted_text);
        std::cout << "Final Plaintext: " << final_decryption << "\n";
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    std::cout << "====================================\n";
    return 0;
}