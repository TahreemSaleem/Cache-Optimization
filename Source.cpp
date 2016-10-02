#include <iostream>
#include <vector>
#include <math.h>
#include <random>
#include <ctime>

using namespace std;

class vectorClass
{

public:
	const int column;
	int * vector;
	//constructor
	vectorClass(const int x) :column(x)
	{
		vector = new int[column];
	}
	//allocate values in vector
	void allocate( int position, int value )
	{
		this->vector[position] = value;
	}
	//display vector
	void show()
	{
		for (int i = 0; i < this->column; i++)
			cout << "\t\t|  " << this->vector[i] << "  |" << endl;
	}
};

class matrixClass
{

public:
	//constructor
	matrixClass(int x, int y) :row(x), column(y)
	{
		matrix = new int[row * column];
	}
	//to allocate values in a matrix
	void allocate(int row, int column, int value)
	{
		//row major ordered
		this->matrix[row + (column * this->column)] = value;
	}
	//display matrix
	void show()
	{
		for (int i = 0; i < this->row; i++) 
		{
			cout << "\t\t| ";
			for (int j = 0; j < this->column; j++) 
			{
				cout << this->matrix[i+j*this->row] << "  ";
			}
			cout << "|" << endl;
		}
	}
	//operator overloading multiplication of matrix with a matrix
	matrixClass operator*(const matrixClass& m)
	{
		matrixClass result(this->row, m.column);
		for (int i = 0; i<this->row* m.column; i++)
		{
			result.matrix[i] = 0;
		}
		for (int i = 0; i < this->row; i++)
		{
			for (int j = 0; j < m.column; j++)
			{
				for (int k = 0; k < this->column; k++) 
				{
					//c[i][j] = c[i][j] + (a[i][k] * b[k][j]);
					int rposi = i + (j*this->column);
					int m1posi = i + (k*this->column);
					int m2posi = k + (j*this->column);
				
					result.matrix[rposi] += this->matrix[m2posi] * m.matrix[m1posi];
				}
			}
		}
		result.show();
		return result;
	}

	//operator overloading multiplication of matrix with a vector
	vectorClass operator*(const vectorClass& v)
	{
		vectorClass result(this->row);
		for (int i = 0; i<v.column; i++) 
		{
			result.vector[i] = 0;
		}
		for (int i = 0; i < (this->row); i++) 
		{
			for (int j = 0; j < v.column; j++) 
			{
				result.vector[i] += (this->matrix[i+(j*this->column)] * v.vector[j]);
			}
		}
		result.show();
		return result;
	}

public:
	const int row;
	const int column;
	int *matrix;
};


int main()
{
	std::uniform_real_distribution<double> dist(1, 3000);  //(min, max)

	//The Mersenne Twister
	 mt19937 mt;

	// initialize the generator
	mt.seed(random_device{}());
	vectorClass v1(2);
	matrixClass m1(2, 2);
	
	for (int i = 0; i < v1.column; i++) 
	{
		
		v1.allocate(i, dist(mt));
	}

	cout << "Your vector: " << endl;
	v1.show();
	for (int i = 0; i < m1.row; i++)
	{
		for (int j = 0; j < m1.column; j++)
		{
			m1.allocate(i, j, dist(mt));

		}
	}
	
	cout << "Your matrix: " << endl;
	m1.show();
	cout << "Result of multiplication:" << endl;
	m1*v1;
	

	matrixClass m2(2, 2);
	for (int i = 0; i < m2.row; i++)
	{
		for (int j = 0; j < m2.column; j++)
		{
			m2.allocate(i, j, dist(mt));

		}
	}
	cout << "Your matrix: " << endl;
	m2.show();
	cout << "Result of multiplication:" << endl;
	m2*m1;
	



}