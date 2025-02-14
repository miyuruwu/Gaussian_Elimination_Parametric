#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

// Hàm in ma trận
void printMatrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double value : row) {
            cout << setw(10) << value << " ";
        }
        cout << endl;
    }
}

// Hàm khử Gauss
void forwardElimination(vector<vector<double>>& augmentedMatrix) {
    int numEquations = augmentedMatrix.size();

    for (int i = 0; i < numEquations; ++i) {
        // Tìm phần tử pivot và hoán đổi hàng
        int pivotRow = i;
        for (int row = i + 1; row < numEquations; ++row) {
            if (fabs(augmentedMatrix[row][i]) > fabs(augmentedMatrix[pivotRow][i])) {
                pivotRow = row;
            }
        }
        swap(augmentedMatrix[i], augmentedMatrix[pivotRow]);

        // Loại bỏ các phần tử phía dưới phần tử pivot
        for (int row = i + 1; row < numEquations; ++row) {
            double factor = augmentedMatrix[row][i] / augmentedMatrix[i][i];
            for (int col = i; col <= numEquations; ++col) {
                augmentedMatrix[row][col] -= factor * augmentedMatrix[i][col];
            }
        }
    }
}

// Hàm thế ngược để tìm nghiệm
vector<double> backSubstitution(const vector<vector<double>>& augmentedMatrix) {
    int numEquations = augmentedMatrix.size();
    vector<double> solutions(numEquations);

    for (int i = numEquations - 1; i >= 0; --i) {
        solutions[i] = augmentedMatrix[i][numEquations] / augmentedMatrix[i][i];
        for (int row = i - 1; row >= 0; --row) {
            augmentedMatrix[row][numEquations] -= augmentedMatrix[row][i] * solutions[i];
        }
    }

    return solutions;
}

// Hàm giải hệ phương trình bằng phương pháp khử Gauss
vector<double> solveGaussianElimination(vector<vector<double>>& augmentedMatrix) {
    forwardElimination(augmentedMatrix);  // Thực hiện khử Gauss
    return backSubstitution(augmentedMatrix);  // Thực hiện thế ngược để tìm nghiệm
}

int main() {
    int numVariables;
    cout << "Nhập số lượng biến (số phương trình): ";
    cin >> numVariables;

    vector<vector<double>> augmentedMatrix(numVariables, vector<double>(numVariables + 1));

    cout << "Nhập hệ số của mỗi phương trình, sau đó là hằng số tự do:\n";
    for (int i = 0; i < numVariables; ++i) {
        cout << "Phương trình " << i + 1 << ": ";
        for (int j = 0; j <= numVariables; ++j) {
            cin >> augmentedMatrix[i][j];
        }
    }

    cout << "\nMa trận mở rộng sau khi khử Gauss:\n";
    printMatrix(augmentedMatrix);

    vector<double> solutions = solveGaussianElimination(augmentedMatrix);

    cout << "\nNghiệm của hệ phương trình:\n";
    for (int i = 0; i < numVariables; ++i) {
        cout << "x" << i + 1 << " = " << solutions[i] << endl;
    }

    return 0;
}
