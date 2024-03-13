#include <bits/stdc++.h>
#include <fstream>
using namespace std;






// interface for using encryption algorithms

class EncryptionAlgorithm {
public:
    virtual string encrypt(const string& input, int key) const = 0;
    virtual string decrypt(const string& input, int key) const = 0;
    virtual ~EncryptionAlgorithm() = default;
};






// CaesarCipher Algorithms
class CaesarCipher : public EncryptionAlgorithm {
public:
    string encrypt(const string& input, int key) const override {
        return applyCaesarCipher(input, key);
    }

    string decrypt(const string& input, int key) const override {
        return applyCaesarCipher(input, -key);
    }

private:
    string applyCaesarCipher(const string& input, int key) const {
        string result = input;
        for (char& ch : result) {
            if (isalpha(ch)) {
                char base = isupper(ch) ? 'A' : 'a';
                ch = static_cast<char>((ch - base + key + 26) % 26 + base);
            }
        }
        return result;
    }
};










//******************* AtbashCipher algorithm *********//
class AtbashCipher : public EncryptionAlgorithm {
public:
    string encrypt(const string& input, int key) const override {
        return applyAtbashCipher(input);
    }

    string decrypt(const string& input, int key) const override {
         
        return applyAtbashCipher(input);
    }

private:
    string applyAtbashCipher(const string& input) const {
        string result = input;
        for (char& ch : result) {
            if (isalpha(ch)) {
                char base = isupper(ch) ? 'A' : 'a';
                ch = static_cast<char>(25 - (ch - base) + base);
            }
        }
        return result;
    }
};








class FileEncryptor {


    string fileName;

    string readFile(const string& specificFileName = "") const {
        ifstream file(specificFileName.empty() ? fileName : specificFileName);
        string content;

        if (file.is_open()) {
            char ch;
            while (file.get(ch)) {
                content.push_back(ch);
            }
            file.close();
        } else {
            cerr << "Error: Unable to open file " << fileName << endl;
        }

        return content;
    }

    void writeFile(const string& content, const string& specificFileName) const {
        ofstream file(specificFileName);
        if (file.is_open()) {
            file << content;
            file.close();
        } else {
            cerr << "Error: Unable to create file " << specificFileName << endl;
        }
    }

    string getOutputFileName(const string& operation) const {
        size_t dotPos = fileName.find_last_of('.');
        if (dotPos != string::npos) {
            return fileName.substr(0, dotPos) + "_" + operation + fileName.substr(dotPos);
        } else {
            return fileName + "_" + operation;
        }
    }





public:
    FileEncryptor(const string& fileName) : fileName(fileName) {}

    void encrypt(int key, const EncryptionAlgorithm& algorithm) {
        string content = readFile();
        string encryptedContent = algorithm.encrypt(content, key);
        writeFile(encryptedContent, getOutputFileName("encrypted"));
        cout << "Encryption complete. Encrypted file: " << getOutputFileName("encrypted") << endl;
    }

    void decrypt(int key, const EncryptionAlgorithm& algorithm) {
        string content = readFile(getOutputFileName("encrypted"));
        string decryptedContent = algorithm.decrypt(content, key);
        writeFile(decryptedContent, getOutputFileName("decrypted"));
        cout << "Decryption complete. Decrypted file: " << getOutputFileName("decrypted") << endl;
    }

 
};








int main() {
    string fileName;
    int key;
    int algorithmChoice;

    cout << "Enter the name of the file to encrypt/decrypt: ";
    cin >> fileName;

    cout << "Enter the key for encryption/decryption: ";
    cin >> key;

    cout << "Select encryption algorithm:\n";
    cout << "1. Caesar Cipher\n";
    cout << "2. Atbash Cipher\n";
    cout << "Enter your choice: ";
    cin >> algorithmChoice;
    
    
    
    

    EncryptionAlgorithm* selectedAlgorithm;
    switch (algorithmChoice) {
        case 1:
            selectedAlgorithm = new CaesarCipher();
            break;
        case 2:
            selectedAlgorithm = new AtbashCipher();
            break;
        default:
            cerr << "Invalid choice. Exiting program.\n";
            return 1;
    }


    FileEncryptor encryptor(fileName);
    encryptor.encrypt(key, *selectedAlgorithm);
    encryptor.decrypt(key, *selectedAlgorithm);

    delete selectedAlgorithm; 

    return 0;
}
