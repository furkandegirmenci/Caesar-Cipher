#include <iostream>
#include <fstream>
#include <memory>
#include <deque>
#include <algorithm>


std::string encryptMessage(std::deque<char> alphabet, std::string line, const int moveAmount) {
    bool flag{false};
    std::string encryptedLine;
    for (std::size_t i = 0; i < line.size(); i++) {
        int j{0};
        while (j < alphabet.size()) { // Checking if given sentence's letter is in the alphabet
            if (line.at(i) == alphabet.at(j)) { // While decrypting, we might have moveAmount higher than j, which will cause deque to go out of range
                if (j < -moveAmount && moveAmount < 0) {
                    j++;
                    continue;
                }
                encryptedLine += alphabet.at(j + moveAmount);
                flag = true;
                break;
            }
            j++;
        }
        if (flag == false) { // If its not in alphabet, add to encrypted line.
            encryptedLine += line.at(i);

        }
        flag = false;
    }
    return encryptedLine;
}


std::string decryptMessage(std::deque<char> alphabet, std::string line, const int moveAmount) {
    return encryptMessage(alphabet, line, -moveAmount);
}

int main() {

    std::fstream encryptor{"../Alphabet.txt", std::ios::in}; // You can change the alphabet by editing Alphabet.txt file
    try {
        if (!encryptor.is_open()) {
            throw 0;
        }

        std::string encryptedLine, line;
        std::deque<char> alphabet;
        const int moveAmount{3}; // Change this number to how many letters you want to move it

        char letter;


        // Saving the Alphabet decided in file to an object
        while (encryptor.get(letter)) {
            alphabet.push_back(letter);
        }
        auto it = std::find(alphabet.begin(), alphabet.end(), '\n');
        std::copy(alphabet.begin(), alphabet.begin() + moveAmount, std::inserter(alphabet, it));
        it = std::find(alphabet.begin(), alphabet.end(), '\n');
        it++;
        std::copy(it, it + moveAmount, std::inserter(alphabet, alphabet.end()));


        encryptor.close();

        std::cout << "Şifrelemek için 'E' Yazınız\n"
                  << "Deşifrelemek İçin 'D' Yazınız\n";
        std::cin >> letter;
        letter = toupper(letter);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // To fix enter bug when using cin

        if (letter == 'E') {
            std::cout << "Şifrelenecek metni giriniz : ";
            std::getline(std::cin, line);
            encryptedLine = encryptMessage(alphabet, line, moveAmount);
            std::cout << "Şifrelenmiş mesaj : " << encryptedLine;

        } else if (letter == 'D') {
            std::cout << "Deşifrelenecek metni giriniz : ";
            std::getline(std::cin, encryptedLine);
            encryptedLine = decryptMessage(alphabet, encryptedLine, moveAmount);
            std::cout << "Deşifrelenmiş mesaj : " << encryptedLine;
        } else {
            std::cout << "Invalid character";
        }


    }
    catch (int &ex) {
        std::cerr << "Unable to open file";
    }

    return 0;
}
