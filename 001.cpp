#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <assert.h>
using namespace std;

class matrix_t {
	int **data;
	unsigned int rows;
	unsigned int columns;
public:
	~matrix_t() {
		for (unsigned int i = 0; i < rows; i++) {
			delete[] data[i];
		}
		delete[] data;
	}

	matrix_t(unsigned int rows = 0, unsigned int columns = 0) {
		this->rows = rows;
		this->columns = columns;
	}

	matrix_t(const matrix_t & object) {
		rows = object.rows;
		columns = object.columns;
		data = new int *[rows];
		for (unsigned int i = 0; i < rows; ++i) {
			data[i] = new int[columns];
			for (unsigned int j = 0; j < columns; ++j) {
				data[i][j] = object.data[i][j];
			}
		}
	}

	matrix_t add(matrix_t & other) {
		if (!(rows == other.rows && columns == other.columns))
		{
			cout << "An error has occured while reading input data.\n";
			exit(0);
		}

		matrix_t res(rows, columns);
		res.data = new int *[rows];
		for (unsigned int i = 0; i < rows; ++i) {
			res.data[i] = new int[columns];
			for (unsigned int j = 0; j < columns; ++j) {
				res.data[i][j] = data[i][j] + other.data[i][j];
			}
		}
		return res;
	}
	matrix_t sub(matrix_t & other) {
		if (!(rows == other.rows && columns == other.columns))
		{
			cout << "An error has occured while reading input data.\n";
			exit(0);
		}

		matrix_t res(rows, columns);
		res.data = new int *[rows];
		for (unsigned int i = 0; i < rows; ++i) {
			res.data[i] = new int[columns];
			for (unsigned int j = 0; j < columns; ++j) {
				res.data[i][j] = data[i][j] - other.data[i][j];
			}
		}
		return res;
	}
	matrix_t mul(matrix_t & other) {
		if (columns != other.rows)
		{
			cout << "An error has occured while reading input data.\n";
			exit(0);
		}

		matrix_t res(rows, other.columns);
		res.data = new int *[rows];
		for (unsigned int i = 0; i < rows; ++i) {
			res.data[i] = new int[columns];
			for (unsigned int j = 0; j < other.columns; ++j) {
				res.data[i][j] = 0;
				for (unsigned int k = 0; k < columns; k++)
					res.data[i][j] += (data[i][k] * other.data[k][j]);
			}
		}
		return res;
	}
	matrix_t trans() {
		matrix_t res(columns, rows);
		res.data = new int *[columns];
		for (unsigned int i = 0; i < columns; ++i) {
			res.data[i] = new int[rows];
			for (unsigned int j = 0; j < rows; ++j) {
				res.data[i][j] = data[j][i];
			}
		}
		return res;
	}

	ifstream & read(ifstream & stream) {
		string line, str;
		getline(stream, line);
		unsigned int rows, columns;
		char symbol;

		if (!(stream >> rows && stream >> symbol && symbol == ',' && stream >> columns))
		{
			stream.setstate(ios::failbit);
			return stream;
		}
		this->rows = rows;
		this->columns = columns;

		int ** elements = new int *[rows];
		for (unsigned int i = 0; i < rows; ++i) {
			elements[i] = new int[columns];
			getline(stream, str);
			for (unsigned int j = 0; j < columns; ++j) {
				if (!(stream >> elements[i][j])) {
					stream.setstate(ios::failbit);
					return stream;
				}
			}
		}

		data = new int *[rows];
		for (unsigned int i = 0; i < rows; ++i) {
			data[i] = new int[columns];
			for (unsigned int j = 0; j < columns; ++j) {
				data[i][j] = elements[i][j];
			}
		}

		for (unsigned int i = 0; i < rows; ++i) {
			delete[] elements[i];
		}
		delete[] elements;
		return stream;
	}
	ostream & write(ostream & stream) {
		stream << endl;
		for (unsigned int i = 0; i < rows; ++i) {
			for (unsigned int j = 0; j < columns; ++j) {
				stream << data[i][j] << ' ';
			}
			stream << endl;
		}
		return stream;
	}
};

bool read(istream & stream, matrix_t & matrix)
{
	string file_name;
	if (stream >> file_name) {
		ifstream fin;
		fin.open(file_name);
		if ((fin.is_open()) && (matrix.read(fin)))
			return true;
	}
	return false;
}


bool getcommandifile(ifstream & fs1, ifstream & fs2, char & op) {
	op = 'q';
	string fn;
	getline(cin, fn);

	istringstream sfn(fn);
	string name1 = "";
	string name2 = "";
	char hop;
	while (sfn >> hop) {
		if (hop != '+' && hop != '-' && hop != 'T' && hop != '*') {
			name1 += hop;
		}
		if (hop == '+' || hop == '-' || hop == '*') {
			op = hop;
			while (sfn >> hop) {
				if (hop != '+' && hop != '-' && hop != 'T' && hop != '*') {
					name2 += hop;
				}
				else {
					return false;
				}
			}
			break;
		}
		if (hop == 'T') {
			op = hop;
			break;
		}
	}
	if (op != '+' && op != '-' && op != 'T' && op != '*') {
		return false;
	}
	if (name1 != "") {
		fs1.open(name1);
	}
	if (name2 != "") {
		fs2.open(name2);
	}
	if (fs1.is_open() && (op == 'T')) {
		return true;
	}
	else if (fs1.is_open() && fs2.is_open()) {
		return true;
	}
	else {
		return false;
	}
}
void create_files()
{
	ofstream fout;
	fout.open("A.txt");
	fout << "A.txt\n3, 3\n2 2 2\n2 2 2\n2 2 2";
	fout.close();

	fout.open("B.txt");
	fout << "B.txt\n3, 3\n1 1 1\n1 1 1\n1 1 1";
	fout.close();

	fout.open("C.txt");
	fout << "C.txt\n3, 3\n1 2 3\n4 5 6\n7 8 9";
	fout.close();

	fout.open("D.txt");
	fout << "D.txt\n3, 2\n1 2\n4 5\n7 8";
	fout.close();
}


int main() {
	char com;
	create_files();
	ifstream mtr1, mtr2;
	matrix_t matrix1, matrix2;
	if (!getcommandifile(mtr1, mtr2, com)) {
		mtr1.close();
		mtr2.close();
		cout << "An error has occured while reading input data";
		exit(0);
	}

	if (!matrix1.read(mtr1)) {
		cout << "An error has occured while reading input data";
		mtr1.close();
		mtr2.close();
		exit(0);
	}
	if (com == 'T') {
		matrix_t matrix3 = matrix1.trans();
		matrix3.write(cout);
		mtr1.close();
		mtr2.close();

		exit(0);
	}
	else if (com != '+' && com != '-' && com != '*') {
		cout << "An error has occured while reading input data";
		mtr1.close();
		mtr2.close();
		exit(0);
	}
	if (!matrix2.read(mtr2)) {
		cout << "An error has occured while reading input data";
		mtr1.close();
		mtr2.close();
		exit(0);
	}

	if (com == '+') {
		matrix_t matrix3 = matrix1.add(matrix2);
		matrix3.write(cout);
	}
	else if (com == '-') {
		matrix_t matrix3 = matrix1.sub(matrix2);
		matrix3.write(cout);
	}
	else if (com == '*') {
		matrix_t matrix3 = matrix1.mul(matrix2);
		matrix3.write(cout);
	}

	mtr1.close();
	mtr2.close();

	return 0;
}

