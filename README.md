# Matrix-Template
A C++ Template of Matrix  
```
template<ItemType> class Matrix;
```
## Create Matrix
```
Matrix<int> mat1 = {{1,2},{3,4}};  
Matrix<double> mat2({1.1,2.2},{3.3,4.4});  
Matrix<char> mat3(3,5); // 3 rows  5 columns  
``` 
## Print Matrix
```
Matrix<int> mat = {{1,2,3},{4,5,6}};
mat.print();
```
## + - *
*  Can only calculate matrix in same item type.
``` 
Matrix<int> mat1 = {{1,2,3},{3,4,5}};  
Matrix<int> mat2 = {{1,2,3},{3,4,5}};  
Matrix<int> mat3 = {{1,3},{2,5},{3,6}};  
  
Matrix<int> answer = 10 * mat1;  
Matrix<int> answer = mat1 * 10;  
Matrix<int> answer = mat1 + mat2;  
Matrix<int> answer = mat1 * mat3;  
```  
## Item Type Cast
* Matrix in different item type cannot be calculated,so we need cast.
``` 
Matrix<int> mat1 = {{1,2},{3,4}};  
Matrix<double> mat2 = Matrix<double>::itemTypeCast(mat1);  
``` 
## Determinant
```
Matrix<int> mat = {{1,3,7},{0,7,2},{3,1,8}};
std::cout << mat.determinant() << std::endl;
```
## Inverse Matrix
* Always return Matrix\<double\>
```
Matrix<int> mat = {{1,3,4,0,2,33,4},
                  {6,7,8,5,62,7,8},
                  {98,7,6,9,8,7,6},
                  {54,3,2,5,4,3,2},
                  {1,2,0,4,1,2,34},
                  {5,6,7,8,5,6,78},
                  {9,8,7,6,9,8,72},};

mat.inverse().print();
```