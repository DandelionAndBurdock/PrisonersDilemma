// Class: Matrix
// Description: Template class for a square matrix
// Note: Does not include mathematical matrix operations
// Author: Philip Jones
// Date: 19/10/2017

template <typename T>
class Matrix
{
public:
	Matrix(int size = defaultSize); //TODO: Set defaults in other classes
	~Matrix();
	Matrix(const Matrix<T>& src) = delete; //TODO: Think about this
	int GetDimension() const { return m_size; }
	T GetElement(int x, int y) const;
	void SetElement(int x, int y, T elem);
	
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
	return (m_cells[x][y]);
}

template <typename T>
void Matrix<T>::SetElement(int x, int y, T elem) {
	m_cells[x][y] = elem;
}

