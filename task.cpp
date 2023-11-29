#include <iostream>

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
