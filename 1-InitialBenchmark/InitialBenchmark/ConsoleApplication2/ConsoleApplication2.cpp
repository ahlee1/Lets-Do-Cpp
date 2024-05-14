// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include<numeric>
using namespace std;
int getMatrixPoint(vector<vector<int>>& matrix, int row, int col) {
    if (row < 0 || col < 0 || row >= matrix.size() || col >= matrix[0].size()) {
        return 0;
    }

    return matrix[row][col];
}

int getMatrixSum(vector<vector<int>>& matrix, int row, int col, int a, int b, int direction) {
    vector<int> points;
    for (int x = 0; x < a; x++) {
        for (int y = 0; y < b; y++) {
            points.push_back(getMatrixPoint(matrix, row + y, col + y* direction));
            if (y != 0 && x != a - 1) {
                points.push_back(getMatrixPoint(matrix, row + y, col+( - 1 + y)*direction));
            }
        }
        if (direction == 1) {
            row += 1;
            col -= 1;
        }
        else {
            row += 1;
            col += 1;
        }

    }

    return accumulate(points.begin(), points.end(), 0);
}

int rotatedRectSum(vector<vector<int>>& matrix, int a, int b) {
    int maxVal = 0;
    for (int i = 0; i < matrix.size(); i++) {
        for (int p = 0; p < matrix[0].size(); p++) {
            maxVal = max(maxVal, getMatrixSum(matrix, i, p, a, b, 1));
            maxVal = max(maxVal, getMatrixSum(matrix, i, p, a, b, -1));
            maxVal = max(maxVal, getMatrixSum(matrix, i, p, b, a, 1));
            maxVal = max(maxVal, getMatrixSum(matrix, i, p, b, a, -1));
        }
    }

    return maxVal;
}
int main() {


    vector<vector<int>> matrix{
        {1, 2, 3, 4, 0},
        {5, 6, 7, 8, 1},
        {3, 2, 4, 1, 4},
        {4, 3, 5, 1, 6}
    };
    cout << rotatedRectSum(matrix, 2, 3) << endl;

    vector<vector<int>> matrix2{
        {-2,3 ,5, -1},
        {4, 3, -10, 10},

    };
    cout << rotatedRectSum(matrix2, 1, 1) << endl;

    vector<vector<int>> matrix3{
        {-2,3 },
        {4, 3},

    };
    cout << rotatedRectSum(matrix3, 1, 2) << endl;
    return 0;
}
