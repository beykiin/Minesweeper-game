// Mayın Tarlası Oyunu.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

 
using namespace std;

const int BOARD_SIZE = 5;
const int MINE_COUNT = 5;

void printBoard(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

int countAdjacentMines(const vector<vector<char>>& board, int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newRow = row + i;
            int newCol = col + j;
            if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE) {
                if (board[newRow][newCol] == '*') {
                    count++;
                }
            }
        }
    }
    return count;
}

bool isMine(const vector<vector<char>>& board, int row, int col) {
    return board[row][col] == '*';
}

void revealCell(vector<vector<char>>& board, vector<vector<bool>>& visited, int row, int col) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return;
    }

    if (visited[row][col]) {
        return;
    }

    visited[row][col] = true;

    if (board[row][col] == '*') {
        int adjacentMines = countAdjacentMines(board, row, col);
        board[row][col] = '0' + adjacentMines;
        if (adjacentMines == 0) {
            revealCell(board, visited, row - 1, col - 1);
            revealCell(board, visited, row - 1, col);
            revealCell(board, visited, row - 1, col + 1);
            revealCell(board, visited, row, col - 1);
            revealCell(board, visited, row, col + 1);
            revealCell(board, visited, row + 1, col - 1);
            revealCell(board, visited, row + 1, col);
            revealCell(board, visited, row + 1, col + 1);
        }
    }
}

bool isBoardCleared(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell == ' ') {
                return false;
            }
        }
    }
    return true;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    vector<vector<char>> board(BOARD_SIZE, vector<char>(BOARD_SIZE, ' '));
    vector<vector<bool>> visited(BOARD_SIZE, vector<bool>(BOARD_SIZE, false));

    int mineCount = 0;
    while (mineCount < MINE_COUNT) {
        int row = rand() % BOARD_SIZE;
        int col = rand() % BOARD_SIZE;
        if (!isMine(board, row, col)) {
            board[row][col] = '*';
            mineCount++;
        }
    }

    cout << "Welcome to Minesweeper Game!" << endl;
    cout << "Enter 'M' to mark mines and 'A' to open cells." << endl;

    while (true) {
        printBoard(board);

        char choice;
        cout << "Make your selection (M/A): ";
        cin >> choice;

        int row, col;
        cout << "Enter the row and column number (ex: 1 2): ";
        cin >> row >> col;

        row--;

        if (choice == 'M' || choice == 'm') {
            if (!visited[row][col]) {
                board[row][col] = 'X';
            }
        }
        else if (choice == 'A' || choice == 'a') {
            if (isMine(board, row, col)) {
                cout << "You stepped on a mine! Game over." << endl;
                break;
            }
            else {
                revealCell(board, visited, row, col);
                if (isBoardCleared(board)) {
                    cout << "Congratulations! You have opened all the cells. You won the game!" << endl;
                    break;
                }
            }
        }
    }

    return 0;
}

// Programı çalıştır: Ctrl + F5 veya Hata Ayıkla > Hata Ayıklamadan Başlat menüsü
// Programda hata ayıkla: F5 veya Hata Ayıkla > Hata Ayıklamayı Başlat menüsü

// Kullanmaya Başlama İpuçları: 
//   1. Dosyaları eklemek/yönetmek için Çözüm Gezgini penceresini kullanın
//   2. Kaynak denetimine bağlanmak için Takım Gezgini penceresini kullanın
//   3. Derleme çıktısını ve diğer iletileri görmek için Çıktı penceresini kullanın
//   4. Hataları görüntülemek için Hata Listesi penceresini kullanın
//   5. Yeni kod dosyaları oluşturmak için Projeye Git > Yeni Öğe ekle veya varolan kod dosyalarını projeye eklemek için Proje > Var Olan Öğeyi Ekle adımlarını izleyin
//   6. Bu projeyi daha sonra yeniden açmak için Dosya > Aç > Proje'ye gidip .sln uzantılı dosyayı seçin
