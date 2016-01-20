/* Edward Rodriguez cs780 */

#pragma once
#include <cstdlib>

template <class T> // forward declaration
class SafeMatrix;
template <class T> //forward declaration
std::ostream& operator<<(std::ostream& os, const SafeMatrix<T>& sm);

template<class T>
class SafeMatrix {
	int row_low, row_high, col_low, col_high;
	T** t_matrix;
public:
	// Constructors
	SafeMatrix();
	SafeMatrix(int);
	SafeMatrix(int, int);
	SafeMatrix(int, int, int, int);
	// Copy Constructor
	SafeMatrix(const SafeMatrix&);
	// Destructor
	~SafeMatrix();
	// Operator * overload
	SafeMatrix operator*(const SafeMatrix&);
	// Operator = overload
	SafeMatrix& operator=(const SafeMatrix&);
	// Operator << overload
	friend std::ostream& operator<< <T> (std::ostream& os, const SafeMatrix<T>& sm);
	// Getters
	int getRow_high() { return row_high; }
	int getCol_high() { return col_high; }

	class Proxy {
		T* t_array;
	public:
		Proxy(T* t_array) : t_array(t_array) {}

		int& operator[] (int i) {
			return t_array[i];
		}
	};

	Proxy operator[] (int i) {
		if (i < row_low || i > row_high) {
			std::cout << "Index for row " << i << " out of range" << std::endl;
			exit(1);
		}
		return Proxy(t_matrix[i]);
	}
};

// Constructors
template<class T>
SafeMatrix<T>::SafeMatrix() :
row_low(0),
row_high(-1),
col_low(0),
col_high(-1) {
	t_matrix = nullptr;
}

template<class T>
SafeMatrix<T>::SafeMatrix(int dim) :
row_low(0),
row_high(dim-1),
col_low(0),
col_high(dim-1) {
	t_matrix = new T*[dim];
	for (int i = 0; i < dim; ++i)
		t_matrix[i] = new T[dim];
}

template<class T>
SafeMatrix<T>::SafeMatrix(int row, int col) :
row_low(0),
row_high(row-1),
col_low(0),
col_high(col-1) {
	t_matrix = new T*[row];
	for (int i = 0; i < row; ++i)
		t_matrix[i] = new T[col];
}

template<class T>
SafeMatrix<T>::SafeMatrix(
	int row_low, int row_high, int col_low, int col_high) :
	row_low(row_low),
	row_high(row_high),
	col_low(col_low),
	col_high(col_high) {
	if (((row_high - row_low + 1) <= 0) ||
		((col_high - col_low + 1) <= 0)) {
		std::cout << "Constructor error in bounds definition" << std::endl;
		exit(1);
	}
	int r = row_high - row_low + 1;
	int c = col_high - col_low + 1;
	t_matrix = new T*[r];
	for (int i = 0; i < r; ++i)
		t_matrix[i] = new T[c];
}

// Copy Constructor
template<class T>
SafeMatrix<T>::SafeMatrix(const SafeMatrix& sm) {
	int r, c, i, j;

	r = sm.row_high - sm.row_low + 1;
	c = sm.col_high - sm.col_low + 1;

	// Copies r-value matrix to l-value matrix
	t_matrix = new T*[r];
	for (i = 0; i < r; ++i)
		t_matrix[i] = new T[c];
	for (i = 0; i < r; ++i)
		for (j = 0; j < c; ++j)
			t_matrix[i][j] = sm.t_matrix[i][j];

	row_low = sm.row_low;
	row_high = sm.row_high;
	col_low = sm.col_low;
	col_high = sm.col_high;
}

// Destructor
template<class T>
SafeMatrix<T>::~SafeMatrix() {
	int r = row_high - row_low + 1;

	// Deletes matrix heap elements
	for (int i = 0; i < r; ++i)
		delete[] t_matrix[i];
	delete[] t_matrix;
}

// Operator * overload
template<class T>
SafeMatrix<T> SafeMatrix<T>::operator*(const SafeMatrix<T>& sm) {

	SafeMatrix<T> result(row_high + 1, sm.col_high + 1);

	// Matrix mult.
	for (int i = 0; i < row_high + 1; ++i) {
		for (int j = 0; j < sm.col_high + 1; ++j) {
			result[i][j] = 0;
			for (int k = 0; k < col_high + 1; ++k) {
				result[i][j] += (t_matrix[i][k] * sm.t_matrix[k][j]);
			}
		}
	}

	return result;
}
// Operator = overload
template<class T>
SafeMatrix<T>& SafeMatrix<T>::operator=(const SafeMatrix<T>& sm) {
	if (this == &sm) return *this;

	int r, c, i, j;

	r = row_high - row_low + 1;

	// Deletes l-value matrix heap elements
	for (i = 0; i < r; ++i)
		delete[] t_matrix[i];
	delete[] t_matrix;

	r = sm.row_high - sm.row_low + 1;
	c = sm.col_high - sm.col_low + 1;

	// Copies r-value matrix to l-value matrix
	t_matrix = new T*[r];
	for (i = 0; i < r; ++i)
		t_matrix[i] = new T[c];
	for (i = 0; i < r; ++i)
		for (j = 0; j < c; ++j)
			t_matrix[i][j] = sm.t_matrix[i][j];

	row_low = sm.row_low;
	row_high = sm.row_high;
	col_low = sm.col_low;
	col_high = sm.col_high;

	return *this;
}

// Operator << overload
template<class T>
std::ostream& operator<<(std::ostream& os, const SafeMatrix<T>& sm) {
	int r = sm.row_high - sm.row_low + 1;
	int c = sm.col_high - sm.col_low + 1;

	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j)
			std::cout << sm.t_matrix[i][j] << ' ';
		std::cout << std::endl;
	}
	return os;
}
