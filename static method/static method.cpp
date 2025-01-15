#include <iostream>

struct Matrix {
	double** data;
	size_t rows, cols;

	Matrix(int rows = 3, int cols = 3) {
		this->rows = rows;
		this->cols = cols;

		data = new double*[rows];
		for (int i = 0; i < rows; ++i) {
			data[i] = new double[cols] {0};
		}
	}
	~Matrix() {
		for (int i = 0; i < rows; ++i) {
			delete[] data[i];
		}
		delete[] data;
	}

	static Matrix eye(int n) {
		Matrix result(n,n);
		for (int i = 0; i < n; ++i) {
			result.data[i][i] = 1;
		}
		return result;
	}
};

std::ostream& operator<<(std::ostream& stream, Matrix m)
{
	stream << "[";
	for (int i = 0; i < m.rows;++i) {
		for (int j = 0; j < m.rows;++j) {
			stream << m.data[i][j] << " ";
		}
		if (i + 1 == m.rows) {
			stream << "]";
		}
		else {
		stream << (i == m.rows - 1 ? "\n" : "\n");
		stream << " ";
	}
	}
	return stream;
}
int main() {
	Matrix b = Matrix::eye(3);
	std::cout << b;

}