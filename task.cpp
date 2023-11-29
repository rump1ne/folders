#include <iostream>
#include <fstream>
#include <string>
#include <random>

class NameGenerator {
private:
    std::string chars;
    int count;

public:
    NameGenerator(const std::string& characters, int itemCount) : chars(characters), count(itemCount) {}

    void GenerateNames(std::ofstream& outputFile) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, chars.size() - 1);

        for (int i = 0; i < count; ++i) {
            std::string name;
            for (int j = 0; j < 5; ++j) { // Adjust the length of the generated name as needed
                name += chars[dis(gen)];
            }
            outputFile << name << std::endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "RUS");

    std::string folderChars, fileChars;
    int folderCount, fileCount;

    std::cout << "Введите уникальные символы для названия папок: ";
    std::cin >> folderChars;

    std::cout << "Введите количество папок: ";
    std::cin >> folderCount;

    std::cout << "Введите уникальные символы для названия файлов: ";
    std::cin >> fileChars;

    std::cout << "Введите количество файлов: ";
    std::cin >> fileCount;

    std::ofstream logFile("log.txt");
    if (!logFile.is_open()) {
        std::cerr << "Ошибка открытия файла лога." << std::endl;
        return 1;
    }

    NameGenerator folderNameGenerator(folderChars, folderCount);
    NameGenerator fileNameGenerator(fileChars, fileCount);

    folderNameGenerator.GenerateNames(logFile);
    fileNameGenerator.GenerateNames(logFile);

    logFile.close();

    return 0;
}
