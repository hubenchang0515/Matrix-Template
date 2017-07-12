#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <stdexcept>

/* Declaration */
template<typename ItemType>
class Matrix;

template<typename T>
bool operator == (const Matrix<T>& x, const Matrix<T>& y);

template<typename T>
bool operator != (const Matrix<T>& x, const Matrix<T>& y);

template<typename T>
const Matrix<T> operator + (const Matrix<T>& x, const Matrix<T>& y);

template<typename T>
const Matrix<T> operator - (const Matrix<T>& x, const Matrix<T>& y);

template<typename T>
const Matrix<T> operator * (T n,const Matrix<T>& matrix);

template<typename T>
const Matrix<T> operator * (const Matrix<T>& matrix,T n);

template<typename T>
const Matrix<T> operator * (const Matrix<T>& x,const Matrix<T>& y);

/* Matrix Template Class */
template<typename ItemType>
class Matrix
{
public:
    template<typename originalType,typename castType = ItemType>
    static const Matrix<castType> itemTypeCast(const originalType& matrix);

    Matrix() = delete;
    ~Matrix() = default;
    Matrix(const Matrix<ItemType>& matrix) = default;
    Matrix(Matrix<ItemType>&& matrix) noexcept = default;
    Matrix(const std::initializer_list< std::initializer_list< ItemType > >& matrix);
    Matrix(size_t rows, size_t columns);
    
    const size_t rows() const { return this->rows_; } 
    const size_t columns() const { return this->columns_; }
    void print(void) const;
    
    void rSwap(size_t ri,size_t rj);
    void rMultiply(size_t ri,ItemType n);
    void rTransform(size_t ri,size_t rj,ItemType n);
    void cSwap(size_t ci,size_t cj);
    void cMultiply(size_t ci,ItemType n);
    void cTransform(size_t ci,size_t cj,ItemType n);
    
    ItemType determinant();
    Matrix<double> inverse();
    
    std::vector< ItemType >& operator []  (size_t index);
    const std::vector< ItemType >& operator [] (size_t index) const;
    
    friend bool operator == <ItemType> (const Matrix<ItemType>& x, const Matrix<ItemType>& y);
    friend bool operator != <ItemType> (const Matrix<ItemType>& x, const Matrix<ItemType>& y);
    friend const Matrix<ItemType> operator + <ItemType> (const Matrix<ItemType>& x, const Matrix<ItemType>& y);
    friend const Matrix<ItemType> operator - <ItemType> (const Matrix<ItemType>& x, const Matrix<ItemType>& y);
    friend const Matrix<ItemType> operator * <ItemType> (ItemType n,const Matrix<ItemType>& matrix);
    friend const Matrix<ItemType> operator * <ItemType> (const Matrix<ItemType>& matrix,ItemType n);
    friend const Matrix<ItemType> operator * <ItemType> (const Matrix<ItemType>& x, const Matrix<ItemType>& y);
    

private:
    size_t rows_;
    size_t columns_;
    std::vector< std::vector< ItemType > > data;
};


template<typename ItemType>
template<typename originalType,typename castType>
const Matrix<castType> Matrix<ItemType>::itemTypeCast(const originalType& matrix)
{
    size_t rows = matrix.rows();
    size_t columns = matrix.columns();
    Matrix<castType> outcome(rows,columns);
    for(size_t row = 0; row < rows; row++)
        for(size_t column = 0; column < columns; column++)
        {
            outcome[row][column] = static_cast<castType>(matrix[row][column]);
        }
    
    return outcome;
}


/* construct by an innitializer list */
template<typename ItemType> 
Matrix<ItemType>::Matrix(const std::initializer_list< std::initializer_list< ItemType > >& matrix)
{    
    size_t rows = matrix.size();
    size_t columns = matrix.begin()->size();
    for(const auto& row : matrix)
    {
        if(columns != row.size())
        {
            throw std::runtime_error("constructor : Initializer list is not a matrix.\n");
        }
    }
    
    this->rows_ = rows;
	this->columns_ = columns;
	for(const auto& row : matrix)
		this->data.push_back(row);
}

/* construct by number of rows and columns */
template<typename ItemType> 
Matrix<ItemType>::Matrix(size_t rows,size_t columns)
{
    this->rows_ = rows;
    this->columns_ = columns;
    this->data = std::vector< std::vector< ItemType > >(rows);
    
    for(auto& rowData : this->data)
		rowData.resize(columns,0);
}

/* print */
template<typename ItemType>
void Matrix<ItemType>::print(void) const
{
    for(const auto& row : this->data)
    {
        for(const auto& item : row)
        {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
}

/* swap rows */
template<typename ItemType>
void Matrix<ItemType>::rSwap(size_t ri, size_t rj)
{
	if(ri >= rows_ || rj >= rows_)
	{
		throw std::runtime_error("rSwap : Row number out of range.\n");
	}
	else
	{
		std::swap(this->data[ri], this->data[rj]);
	}
}

/* row multiply */
template<typename ItemType>
void Matrix<ItemType>::rMultiply(size_t ri, ItemType n)
{
	if (ri >= rows_)
	{
		throw std::runtime_error("rMultiply : Row number out of range.\n");
	}
	else
	{
		for(auto& element : this->data[ri])
		{
			element *= n;
		}
	}
}

/* row transform */
template<typename ItemType>
void Matrix<ItemType>::rTransform(size_t ri, size_t rj, ItemType n)
{
	if(ri >= rows_ || rj >= rows_)
	{
		throw std::runtime_error("rTransform : Row number out of range.\n");
	}
	else
	{
		for(size_t element = 0; element < columns_; element++)
		{
			this->data[ri][element] += n * this->data[rj][element];
		}
	}
}

/* column swap */
template<typename ItemType>
void Matrix<ItemType>::cSwap(size_t ci, size_t cj)
{
	if(ci >= columns_ || cj >= columns_)
	{
		throw std::runtime_error("cSwap : Rolumns number out of range.\n");
	}
	else
	{
		for(size_t row = 0; row < rows_; row++)
		{
			std::swap(this->data[row][ci],this->data[row][cj]);
		}
	}
}

/* column multiply */
template<typename ItemType>
void Matrix<ItemType>::cMultiply(size_t ci, ItemType n)
{
	if(ci >= columns_)
	{
		throw std::runtime_error("cMultiply : Rolumns number out of range.\n");
	}
	else
	{
		for(auto& row : this->data)
		{
			row[ci] *= n;
		}
	}
}

/* column transform */
template<typename ItemType>
void Matrix<ItemType>::cTransform(size_t ci, size_t cj, ItemType n)
{
	if(ci >= columns_ || cj >= columns_)
	{
		throw std::runtime_error("cMultiply : Rolumns number out of range.\n");
	}
	else
	{
		for(size_t row = 0; row < rows_; row++)
		{
			this->data[row][ci] += n * this->data[row][cj];
		}
	}
}

/* determinant */
template<typename ItemType>
ItemType Matrix<ItemType>::determinant()
{
    if(this->rows_ != this->columns_)
    {
        throw std::runtime_error("determinant : Not a squra matrix.\n");
    }
    Matrix<double> temp = Matrix<double>::itemTypeCast(*this);
    size_t columns = temp.columns();
    size_t rows = temp.rows();
    ItemType outcome = 1;
    /* Transform temp Matrix to be a lower triangular matrix. */
    for(size_t column = 0; column < columns-1; column++)
    {
        /* Ensure temp[column][column] isn't 0. */
        for(size_t i = column+1; temp[column][column] == 0 && i < columns; i++)
        {
            temp.cSwap(column,i);
            outcome *= -1;
        }
        if(temp[column][column] == 0)
        {
            return 0;
        }

        /* change current column lower elements to be 0 */
        for(size_t row = column+1; row < rows; row++)
        {
            temp.rTransform(row,column,-temp[row][column]/temp[column][column]);
        }
    }
    
    /* calculate determinant */
    for(size_t i = 0; i < rows; i++)
    {
        outcome *= temp[i][i];
    }
    
    return outcome;
}

/* Inverse Matrix */
template<typename ItemType>
Matrix<double> Matrix<ItemType>::inverse()
{
	if(rows_ != columns_)
	{
		throw std::runtime_error("inverse : Not a squra matrix.\n");
	}
	else
	{
		Matrix<double> temp = Matrix<double>::itemTypeCast(*this);
		size_t columns = temp.columns();
        size_t rows = temp.rows();
		Matrix<double> outcome(this->rows_,this->columns_);
		for(size_t i = 0; i < this->rows_; i++)
		{
		    outcome[i][i] = 1;
		}
		/* Transform this Matrix to be an identity matrix. */
		for(size_t column = 0; column < columns; column++)
		{
			/* Ensure temp[column][column] isn't 0. */
			for(size_t row = column + 1; temp[column][column] == 0 && row < rows; row++)
			{
				temp.rSwap(column,row);
				outcome.rSwap(column,row);
			}
			if(temp[column][column] == 0)
			{
				throw std::runtime_error("inverse : Don't have inverse matrix.\n");
				return outcome;
			}

			/* change diagonal element to be 1 */
			double k = 1/temp[column][column];
			temp.rMultiply(column,k);
			outcome.rMultiply(column,k);

			/* change current column upper elements to be 0 */
			for(size_t row = 0; row < column; row++)
			{
				double k = -temp[row][column]/temp[column][column];
				temp.rTransform(row,column,k);
				outcome.rTransform(row,column,k);
			}
			/* change current column lower elements to be 0 */
			for(size_t row = column + 1; row < rows; row++)
			{
				double k = -temp[row][column]/temp[column][column];
				temp.rTransform(row,column,k);
				outcome.rTransform(row,column,k);
			}
			
		}
		return outcome;
	}

	
}

/* [] */
template<typename ItemType>
std::vector< ItemType >& Matrix<ItemType>::operator [] (size_t index)
{
    return this->data[index];
}

/* const [] */
template<typename ItemType>
const std::vector< ItemType >& Matrix<ItemType>::operator [] (size_t index) const
{
    return this->data[index];
}

/* == */
template<typename T>
bool operator == (const Matrix<T>& x, const Matrix<T>& y)
{
    return x.data == y.data;
}

/* != */
template<typename T>
bool operator != (const Matrix<T>& x, const Matrix<T>& y)
{
    return !(x.data == y.data);
}

/* + */
template<typename T>
const Matrix<T> operator + (const Matrix<T>& x, const Matrix<T>& y)
{
    if(x.rows_ != y.rows_ || x.columns_ != y.columns_)
    {
        throw std::runtime_error("operator (+) : Matrixs have different number of rows or columns.\n");
    }
    Matrix<T> outcome(x.rows_,x.columns_);
    for(size_t row = 0; row < x.rows_; row++)
        for(size_t column = 0; column < x.columns_; column++)
        {
            outcome.data[row][column] = x.data[row][column] + y.data[row][column];
        }
    
    return outcome;
}

/* - */
template<typename T>
const Matrix<T> operator - (const Matrix<T>& x, const Matrix<T>& y)
{
    if(x.rows_ != y.rows_ || x.columns_ != y.columns_)
    {
        throw std::runtime_error("operator (-) : Matrixs have different number of rows or columns.\n");
    }
    Matrix<T> outcome(x.rows_,x.columns_);
    for(size_t row = 0; row < x.rows_; row++)
        for(size_t column = 0; column < x.columns_; column++)
        {
            outcome.data[row][column] = x.data[row][column] - y.data[row][column];
        }
    
    return outcome;
}

/* n * Matrix */
template<typename T>
const Matrix<T> operator * (T n,const Matrix<T>& matrix)
{
    Matrix<T> outcome = matrix;
    
    for(const auto& row : outcome)
        for(const auto& item : row)
        {
            item *= n;
        }
        
    return outcome;
}

/* Matrix * n */
template<typename T>
const Matrix<T> operator * (const Matrix<T>& matrix,T n)
{
    Matrix<T> outcome = matrix;
    
    for(const auto& row : outcome)
        for(const auto& item : row)
        {
            item *= n;
        }
        
    return outcome;
}

/* Matrix * Matrix */
template<typename T>
const Matrix<T> operator * (const Matrix<T>& x,const Matrix<T>& y)
{
    if(x.columns_ != y.rows_)
    {
        throw std::runtime_error("operator (*) : Columns of matrix1 is different from rows of matrix2.\n");
    }
    Matrix<T> outcome(x.rows_,y.columns_);
    for(size_t xRow = 0; xRow < x.rows_; xRow++)
    {
        for(size_t yColumn = 0; yColumn < y.columns_; yColumn++)
        {
            T sum = 0;
            for(size_t item = 0; item < x.columns_; item++)
            {
                sum += x.data[xRow][item] * y.data[item][yColumn];
            }
            outcome.data[xRow][yColumn] = sum;
        }
    }
    
    return outcome;
}

#endif //MATRIX_HPP
