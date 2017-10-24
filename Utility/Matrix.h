// Class: Matrix
// Description: Template class for a square matrix
// Note: Does not include mathematical matrix operations
// Author: Philip Jones
// Date: 19/10/2017
#pragma once

template <typename T>
class Matrix
{
public:
	Matrix(int size = defaultSize); //TODO: Set defaults in other classes
	~Matrix();
	Matrix(const Matrix<T>& src); //TODO: Think about this
	Matrix<T>& operator=(const Matrix<T>& rhs);
	int GetDimension() const { return m_size; }
	T GetElement(int x, int y) const;
	void SetElement(int x, int y, T elem);
	bool InRange(int x, int y) const;
	
protected:
	T** m_cells;
	int m_size;

	static const int defaultSize = 3;
};

template <typename T>
Matrix<T>::Matrix(int size) :
	m_size(size) {
	m_cells = new T*[m_size];
	for (int i = 0; i < m_size; ++i) {
		m_cells[i] = new T[m_size];
	}
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& src) :
	x_size(src.x_size), y_size(src.y_size)
{
	cells = new T*[x_size];
	for (int i = 0; i < x_size; ++i)
	{
		cells[i] = new T[y_size];
		memcpy_s(cells[i], (y_size * sizeof(T)), src.cells[i], (y_size * sizeof(T)));
	}
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs)
{
	if (this == &rhs) return (*this);

	// release old memory
	for (int i = 0; i < x_size; ++i) {
		delete[] cells[i];
	}
	delete[] cells;

	// allocate new memory
	cells = new T*[rhs.x_size];
	for (int i = 0; i < rhs.x_size; ++i) {
		cells[i] = new T[rhs.y_size];
		memset(cells[i], 0, (rhs.y_size * sizeof(T)));
	}

	// copy values
	for (int i = 0; i < rhs.x_size; ++i) {
		for (int j = 0; j < rhs.y_size; ++j) {
			cells[i][j] = rhs.cells[i][j];
		}
	}
	return *this;
}



template <typename T> //TODO: Think about this
Matrix<T>::~Matrix() {
	for (int i = 0; i < m_size; ++i) {
		delete[] m_cells[i];
	}
	delete[] m_cells;
}



//TODO: Check does not cause access error
template <typename T>
T Matrix<T>::GetElement(int x, int y) const {
	if (InRange(x, y))
		return (m_cells[x][y]);
	else
		return m_cells[-1][-1]; //TODO: Don't do this!
}

template <typename T>
void Matrix<T>::SetElement(int x, int y, T elem) {
	if (InRange(x,y))
		m_cells[x][y] = elem;
}


template <typename T>
bool Matrix<T>::InRange(int x, int y) const {
	if (x >= m_size || y >= m_size) {
		std::cout << "Matrix Error: Trying to access element out of bounds" << std::endl;
		return false;
	}
	else {
		return true;
	}
}