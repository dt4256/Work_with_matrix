#include <iostream>
#include <vector>
using namespace std;

class Matrix {
private:
    int sign;
    vector<vector<double>> matr;
public:
    Matrix() {
        matr.resize(1, vector<double>(1));
        sign = 1;
    }

    Matrix(vector<vector<double>> matr, int sign) {
        this->matr = matr;
        this->sign = sign;
    }

    Matrix change_sign_out() {
        vector<vector<double>> temp_matr = matr;
        for (int i = 0; i < temp_matr.size(); i++) {
            for (int j = 0; j < temp_matr[i].size(); j++) {
                temp_matr[i][j] *= -1;
            }
        }
        return Matrix(temp_matr, sign * -1);
    }

    Matrix operator* (int x) {
        vector<vector<double>> temp_matr = matr;
        for (int i = 0; i < temp_matr.size(); i++) {
            for (int j = 0; j < temp_matr[i].size(); j++) {
                temp_matr[i][j] *= x;
            }
        }
        return Matrix(temp_matr, sign);
    }

    Matrix& operator*= (int x) {
        for (int i = 0; i < matr.size(); i++) {
            for (int j = 0; j < matr[i].size(); j++) {
                matr[i][j] *= x;
            }
        }
        return *this;
    }

    Matrix transpose() {
        if (matr.empty()) return Matrix();
        int rows = matr.size();
        int cols = matr[0].size();
        vector<vector<double>> temp_matr(cols, vector<double>(rows));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                temp_matr[j][i] = matr[i][j];
            }
        }
        return Matrix(temp_matr, sign);
    }

    void transpose_this() {
        *this = this->transpose();
    }

    Matrix operator+(const Matrix& other) const {
        if (matr.size() != other.matr.size() ||
            (matr.size() > 0 && matr[0].size() != other.matr[0].size())) {
             cout << "diff_size+\n";
             return Matrix();
        }

        vector<vector<double>> result(matr.size(), vector<double>(matr[0].size()));
        int result_sign = 1;

        if (sign == other.sign) {
            for (size_t i = 0; i < matr.size(); ++i) {
                for (size_t j = 0; j < matr[i].size(); ++j) {
                    result[i][j] = matr[i][j] + other.matr[i][j];
                }
            }
            result_sign = sign;
        } else {
            for (size_t i = 0; i < matr.size(); ++i) {
                for (size_t j = 0; j < matr[i].size(); ++j) {
                    result[i][j] = matr[i][j] - other.matr[i][j];
                }
            }
            result_sign = sign;
        }

        return Matrix(result, result_sign);
    }

    Matrix& operator+=(const Matrix& other) {
        if (matr.size() != other.matr.size() ||
            (matr.size() > 0 && matr[0].size() != other.matr[0].size())) {
            cout << "diff_size+=\n";
            return *this;
        }

        if (sign == other.sign) {
            for (size_t i = 0; i < matr.size(); ++i) {
                for (size_t j = 0; j < matr[i].size(); ++j) {
                    matr[i][j] += other.matr[i][j];
                }
            }
        } else {
            for (size_t i = 0; i < matr.size(); ++i) {
                for (size_t j = 0; j < matr[i].size(); ++j) {
                    matr[i][j] -= other.matr[i][j];
                }
            }
        }

        return *this;
    }

    Matrix& operator-=(const Matrix& other) {
        if (matr.size() != other.matr.size() ||
            (matr.size() > 0 && matr[0].size() != other.matr[0].size())) {
             cout << "diff_size-=\n";
             return *this;
        }

        if (sign == other.sign) {
            for (size_t i = 0; i < matr.size(); ++i) {
                for (size_t j = 0; j < matr[i].size(); ++j) {
                    matr[i][j] -= other.matr[i][j];
                }
            }
        } else {
            for (size_t i = 0; i < matr.size(); ++i) {
                for (size_t j = 0; j < matr[i].size(); ++j) {
                    matr[i][j] += other.matr[i][j];
                }
            }
        }

        return *this;
    }

    Matrix operator-() const {
        return Matrix(matr, sign * -1);
    }

    Matrix operator-(const Matrix& other) const {
        Matrix result = *this;
        result -= other;
        return result;
    }

    Matrix operator*(const Matrix& other) {
        if (this->matr.empty() || other.matr.empty() || this->matr[0].size() != other.matr.size()) {
            cout << "wrong_size*\n";
            return Matrix();
        }
        int m = this->matr.size();
        int n = this->matr[0].size();
        int p = other.matr[0].size();
        vector<vector<double>> result(m, vector<double>(p, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < p; j++) {
                for (int k = 0; k < n; k++) {
                    result[i][j] += this->matr[i][k] * other.matr[k][j];
                }
            }
        }

        return Matrix(result, this->sign * other.sign);
    }
};

int main() {
    return 0;
}
