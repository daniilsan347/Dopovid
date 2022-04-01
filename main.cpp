#include <iostream>
#include <vector>

// У цьому прикладі відсутній захист від помилок

// Низькорівнева реалізація
double** MatrixSumLow (double **A, double **B, int sizeX, int sizeY) {
    // Сума двох матриць
    // Ініціалізація результатної матриці С
    auto **C = new double *[sizeX];
    for (int i = 0; i < sizeX; ++i) {
        C[i] = new double [sizeY];
    }

    // Додавання відповідних елементів
    for (int i = 0; i < sizeX; ++i) {
        for (int j = 0; j < sizeY; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

double ScalarProductLow (const double *A, const double *B, int size) {
    // Скалярний добуток
    double result = 0;
    for (int i = 0; i < size; ++i) {
        result += A[i] * B[i];
    }
    return result;
}

double** MatrixTranspositionLow (double **A, int sizeX, int sizeY) {
    // Ініціалізація нового масиву
    auto **C = new double *[sizeY];
    for (int i = 0; i < sizeY; ++i) {
        C[i] = new double [sizeX];
    }

    // Транспозиція матриці
    for (int i = 0; i < sizeX; ++i) {
        for (int j = 0; j < sizeY; ++j) {
            C[j][i] = A[i][j];
        }
    }
    return C;
}

double** MatrixMultiplicationLow (double **A, double **B, int sizeAX, int sizeAY, int sizeBX) {
    // Добуток двох матриць. Не гарантую що мій алгоритм найефективніша
    // Ініціалізація результатної матриці С
    auto **C = new double *[sizeBX];
    for (int i = 0; i < sizeBX; ++i) {
        C[i] = new double [sizeAY];
    }

    // Транспозиція матриці А для спрощення обчислення
    auto transA = MatrixTranspositionLow(A, sizeAX, sizeAY);

    // Заповнення скалярними добутками вектор-рядків матриці A і вектор-стовпців матриці B
    for (int i = 0; i < sizeBX; ++i) {
        for (int j = 0; j < sizeAY; ++j) {
            C[i][j] = ScalarProductLow(B[i], transA[j], sizeAX);
        }
    }
    return C;
}

void DisplayLow (double **A, int sizeX, int sizeY) {
    // Вивід матриці у термінал
    auto B = MatrixTranspositionLow(A, sizeX, sizeY);
    for (int i = 0; i < sizeY; ++i) {
        for (int j = 0; j < sizeX; ++j) {
            std::cout << B[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

// Високорівнева реалізація
auto MatrixSumHigh (const std::vector<std::vector<double>>& A,
                    const std::vector<std::vector<double>>& B) {
    // Сума двох матриць
    // Ініціалізація результатної матриці С
    std::vector<std::vector<double>> C;

    // Додавання відповідних елементів
    for (int i = 0; i < A.size(); ++i) {
        C.emplace_back();
        for (int j = 0; j < A[i].size(); ++j) {
            C[i].push_back(A[i][j] + B[i][j]);
        }
    }
    return C;
}

double ScalarProductHigh (const std::vector<double>& A, const std::vector<double>& B) {
    // Скалярний добуток
    double result = 0;
    for (int i = 0; i < A.size(); ++i) {
        result += A[i] * B[i];
    }
    return result;
}

auto MatrixTranspositionHigh (const std::vector<std::vector<double>>& A) {
    // Транспозиція матриці. Найбільша різниця між способами
    // Ініціалізація нового масиву
    std::vector<std::vector<double>> C;

    // Транспозиція матриці
    for (int i = 0; i < A[0].size(); ++i) {
        C.emplace_back();
        for (const auto & j : A) {
            C[i].push_back(j[i]);
        }
    }
    return C;
}

auto MatrixMultiplicationHigh (const std::vector<std::vector<double>>& A,
                               const std::vector<std::vector<double>>& B) {
    // Добуток двох матриць. Не гарантую що мій алгоритм найефективніший.
    // Ініціалізація результатної матриці С
    std::vector<std::vector<double>> C;

    // Транспозиція матриці А для спрощення обчислення
    auto transA = MatrixTranspositionHigh(A);

    // Заповнення скалярними добутками вектор-рядків матриці A і вектор-стовпців матриці B
    for (int i = 0; i < B.size(); ++i) {
        C.emplace_back();
        for (int j = 0; j < A[0].size(); ++j) {
            C[i].push_back(ScalarProductHigh(B[i], transA[j]));
        }
    }
    return C;
}

void DisplayHigh (const std::vector<std::vector<double>>& A) {
    // Вивід матриці у термінал
    for (const auto& row:MatrixTranspositionHigh(A)) {
        for (const auto& col:row) {
            std::cout << col << "\t";
        }
        std::cout << "\n";
    }
}

int main() {
    std::cout << "Демонстрація функцій\n"
                 "Ініціалізація матриць A і B для суми\n";
    int sizeX, sizeY;
    std::cout << "Кількість стовпчиків: "; std::cin >> sizeX;
    std::cout << "Кількість рядків: "; std::cin >> sizeY;

    auto **ASLow = new double *[sizeX];
    std::vector<std::vector<double>> ASHigh;
    double buffer;
    for (int i = 0; i < sizeX; ++i) {
        ASHigh.emplace_back();
        ASLow[i] = new double [sizeY];
        for (int j = 0; j < sizeY; ++j) {
            std::cout << "A[" << i << "][" << j << "]: "; std::cin >> buffer;
            ASLow[i][j] = buffer;
            ASHigh[i].push_back(buffer);
        }
    }

    auto **BSLow = new double *[sizeX];
    std::vector<std::vector<double>> BSHigh;
    for (int i = 0; i < sizeX; ++i) {
        BSHigh.emplace_back();
        BSLow[i] = new double [sizeY];
        for (int j = 0; j < sizeY; ++j) {
            std::cout << "B[" << i << "][" << j << "]: "; std::cin >> buffer;
            BSLow[i][j] = buffer;
            BSHigh[i].push_back(buffer);
        }
    }

    // Вивід початкових матриць та їх суми
    std::cout << "A:\n";
    DisplayHigh(ASHigh);
    std::cout << "B:\n";
    DisplayHigh(BSHigh);
    std::cout << "Sum Low:\n";
    DisplayLow(MatrixSumLow(ASLow, BSLow, sizeX, sizeY), sizeX, sizeY);
    std::cout << "Sum High:\n";
    DisplayHigh(MatrixSumHigh(ASHigh, BSHigh));

    std::cout << "Ініціалізація матриць A і B для добутку:\n";
    int sizeAX, sizeAY;
    std::cout << "Кількість стовпчиків A: "; std::cin >> sizeAX;
    std::cout << "Кількість рядків A: "; std::cin >> sizeAY;
    int sizeBX, sizeBY;
    std::cout << "Кількість стовпчиків B: "; std::cin >> sizeBX;
    std::cout << "Кількість рядків B: "; std::cin >> sizeBY;

    auto **APLow = new double *[sizeX];
    std::vector<std::vector<double>> APHigh;
    for (int i = 0; i < sizeAX; ++i) {
        APHigh.emplace_back();
        APLow[i] = new double [sizeAY];
        for (int j = 0; j < sizeAY; ++j) {
            std::cout << "A[" << i << "][" << j << "]: "; std::cin >> buffer;
            APLow[i][j] = buffer;
            APHigh[i].push_back(buffer);
        }
    }

    auto **BPLow = new double *[sizeBX];
    std::vector<std::vector<double>> BPHigh;
    for (int i = 0; i < sizeBX; ++i) {
        BPHigh.emplace_back();
        BPLow[i] = new double [sizeBY];
        for (int j = 0; j < sizeBY; ++j) {
            std::cout << "B[" << i << "][" << j << "]: "; std::cin >> buffer;
            BPLow[i][j] = buffer;
            BPHigh[i].push_back(buffer);
        }
    }

    // Вивід початкових матриць та їх добуток
    std::cout << "A:\n";
    DisplayHigh(APHigh);
    std::cout << "B:\n";
    DisplayHigh(BPHigh);
    std::cout << "Sum Low:\n";
    DisplayLow(MatrixMultiplicationLow(APLow, BPLow, sizeAX, sizeAY, sizeBX), sizeBX, sizeAY);
    std::cout << "Sum High:\n";
    DisplayHigh(MatrixMultiplicationHigh(APHigh,BPHigh));
    return 0;
}
