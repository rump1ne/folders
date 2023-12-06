#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

#define MAX_SIZE 20

using namespace std;

struct SymbolData {
    char symbol;
    int count;
};

int get_max_ind(const vector<SymbolData>& data) {
    int sum = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        sum += data[i].count;
    }
    return MAX_SIZE - sum;
}

void add_symbol(string& result, vector<SymbolData>& data) {
    int max_ind = get_max_ind(data);
    if (max_ind == 1) return;

    for (const auto& symbol : data) {
        if (symbol.count > max_ind) break;
        result.append(symbol.count, symbol.symbol);
    }
}

void add_ind(vector<SymbolData>& data) {
    int max_ind = get_max_ind(data);
    if (max_ind == 1) return;
    ++data.front().count;

    for (auto it = data.begin(); it != prev(data.end()); ++it) {
        if (it->count == max_ind) {
            it->count = 1;
            (++it)->count++;
            --it;
        }
    }
}

class Logger {
public:
    Logger(const string& filename) {
        logFile.open(filename, ios::app);
    }

    void Log(const string& message) {
        if (logFile.is_open()) {
            time_t currentTime = time(nullptr);
            tm* localTime = localtime(&currentTime);

            char timeStr[20];
            strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localTime);

            logFile << "[" << timeStr << "] " << message << endl;
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

private:
    ofstream logFile;
};

int main() {
    int quantity_folder;
    int quantity_file;
    string folder_symbols;
    string file_symbols;

    cout << "Введите символы для папок:\n>>"; cin >> folder_symbols;
    cout << "Введите количество папок:\n>>"; cin >> quantity_folder;
    cout << "Введите символы для файлов:\n>>"; cin >> file_symbols;
    cout << "Введите количество файлов:\n>>"; cin >> quantity_file;

    if (quantity_folder <= 0 || quantity_file <= 0) {
        cout << "Некорректное количество папок или файлов. Пожалуйста, введите положительное число." << endl;
        return 0;
    }

    vector<string> arr_folder(quantity_folder);
    vector<string> arr_file(quantity_file);

    vector<SymbolData> folder_data;
    for (char sym : folder_symbols) folder_data.push_back({ sym, 1 });

    vector<SymbolData> file_data;
    for (char sym : file_symbols) file_data.push_back({ sym, 1 });

    Logger folderLogger("folder_log.txt");

    for (int i = 0; i != quantity_folder; ++i) {
        string folder_result;
        add_symbol(folder_result, folder_data);
        add_ind(folder_data);
        arr_folder[i] = folder_result;

        folderLogger.Log("Создана папка: " + arr_folder[i]);
    }
    
    Logger fileLogger("file_log.txt");

    for (int i = 0; i != quantity_folder; ++i) {
        for (int j = 0; j != quantity_file; ++j) {
            string file_result;
            add_symbol(file_result, file_data);
            add_ind(file_data);
            arr_file[j] = file_result;

            fileLogger.Log("В папке " + arr_folder[i] + " создан файл: " + arr_file[j]);
        }
    }

    return 0;
}
