#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#define MfMatrixX 100
#define MIN 1

int ROW = 2, Columnumns = 2;

using namespace std;

vector<vector<int>> add(vector<vector<int>> fMatrix, vector<vector<int>> sMatrix) {

	int n = fMatrix.size();
	vector<vector<int>> result;
	result.resize(n, vector<int>(n, 0));
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			result[i][j] = fMatrix[i][j] + sMatrix[i][j];
		}
	}
	return result;
}

vector<vector<int>> multiPly(vector<vector<int>> fMatrix, vector<vector<int>> sMatrix)
{
	int ROW = fMatrix.size();
	int Columnumns = fMatrix[0].size();
	int dimension = sMatrix[0].size();

	vector<vector<int>> result;
	result.resize(ROW, vector<int>(dimension, 0));
	for (int i = 0; i < ROW; i++)
	for (int j = 0; j < dimension; j++) {
		int add = 0;
		for (int k = 0; k < Columnumns; k++)
			add = add + (fMatrix[i][k] * sMatrix[k][j]);
		result[i][j] = add;
	}
	return result;
}

void print(vector<vector<int>> result)
{
	int ROW = result.size();
	int Columnumns = result[0].size();
	cout << "\n";
	for (int i = 0; i < ROW; i++) {
		cout << "[";
		for (int j = 0; j < Columnumns; j++) {
			if (j == Columnumns - 1)
				cout << result[i][j];
			else
				cout << result[i][j] << " ";
		}
		cout << "]\n";
	}
	cout << "\n";
}

int randomNum() {
	srand(time(NULL));
	int randomNum = (rand() % ((MfMatrixX - MIN) + 1)) + MIN;
	return randomNum;
}



vector<vector<int>> sub(vector<vector<int>> fMatrix, vector<vector<int>> sMatrix) {

	int n = fMatrix.size();
	vector<vector<int>> result;
	result.resize(n, vector<int>(n, 0));
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			result[i][j] = fMatrix[i][j] - sMatrix[i][j];
		}
	}
	return result;
}

vector<vector<int>> strassen(vector<vector<int>> fMatrix, vector<vector<int>> sMatrix) {

	int n = fMatrix.size();

	vector<vector<int>> result;
	result.resize(n, vector<int>(n, 0));

	if (n == 1) {
		result[0][0] = fMatrix[0][0] * sMatrix[0][0];
		return result;
	}
	else {
		vector<vector<int>> a11, a12, a21, a22;
		vector<vector<int>> b11, b12, b21, b22;
		vector<vector<int>> c11, c12, c21, c22;
		vector<vector<int>> m1, m2, m3, m4, m5, m6, m7;

		a11.resize(n / 2, vector<int>(n / 2, 0));
		a12.resize(n / 2, vector<int>(n / 2, 0));
		a21.resize(n / 2, vector<int>(n / 2, 0));
		a22.resize(n / 2, vector<int>(n / 2, 0));

		b11.resize(n / 2, vector<int>(n / 2, 0));
		b12.resize(n / 2, vector<int>(n / 2, 0));
		b21.resize(n / 2, vector<int>(n / 2, 0));
		b22.resize(n / 2, vector<int>(n / 2, 0));

		c11.resize(n / 2, vector<int>(n / 2, 0));
		c12.resize(n / 2, vector<int>(n / 2, 0));
		c21.resize(n / 2, vector<int>(n / 2, 0));
		c22.resize(n / 2, vector<int>(n / 2, 0));

		m1.resize(n / 2, vector<int>(n / 2, 0));
		m2.resize(n / 2, vector<int>(n / 2, 0));
		m3.resize(n / 2, vector<int>(n / 2, 0));
		m4.resize(n / 2, vector<int>(n / 2, 0));
		m5.resize(n / 2, vector<int>(n / 2, 0));
		m6.resize(n / 2, vector<int>(n / 2, 0));
		m7.resize(n / 2, vector<int>(n / 2, 0));

		vector<vector<int>> aResult;
		vector<vector<int>> bResult;
		aResult.resize(n / 2, vector<int>(n / 2, 0));
		bResult.resize(n / 2, vector<int>(n / 2, 0));


		int i, j;

		//dividing the matrices in 4 sub-matrices:
		for (i = 0; i < n / 2; i++) {
			for (j = 0; j < n / 2; j++) {
				a11[i][j] = fMatrix[i][j];
				a12[i][j] = fMatrix[i][j + n / 2];
				a21[i][j] = fMatrix[i + n / 2][j];
				a22[i][j] = fMatrix[i + n / 2][j + n / 2];

				b11[i][j] = sMatrix[i][j];
				b12[i][j] = sMatrix[i][j + n / 2];
				b21[i][j] = sMatrix[i + n / 2][j];
				b22[i][j] = sMatrix[i + n / 2][j + n / 2];
			}
		}

		aResult = add(a11, a22); // a11 + a22
		bResult = add(b11, b22); // b11 + b22
		m1 = strassen(aResult, bResult); // m1 = (a11+a22) * (b11+b22)

		aResult = add(a21, a22); // a21 + a22
		m2 = strassen(aResult, b11); // m2 = (a21+a22) * (b11)

		bResult = sub(b12, b22); // b12 - b22
		m3 = strassen(a11, bResult); // m3 = (a11) * (b12 - b22)

		bResult = sub(b21, b11); // b21 - b11
		m4 = strassen(a22, bResult); // m4 = (a22) * (b21 - b11)

		aResult = add(a11, a12); // a11 + a12
		m5 = strassen(aResult, b22); // m5 = (a11+a12) * (b22)	

		aResult = sub(a21, a11); // a21 - a11
		bResult = add(b11, b12); // b11 + b12
		m6 = strassen(aResult, bResult); // m6 = (a21-a11) * (b11+b12)

		aResult = sub(a12, a22); // a12 - a22
		bResult = add(b21, b22); // b21 + b22
		m7 = strassen(aResult, bResult); // m7 = (a12-a22) * (b21+b22)

		// calculating c21, c21, c11 e c22:

		c12 = add(m3, m5); // c12 = m3 + m5
		c21 = add(m2, m4); // c21 = m2 + m4

		aResult = add(m1, m4); // m1 + m4
		bResult = add(aResult, m7); // m1 + m4 + m7
		c11 = sub(bResult, m5); // c11 = m1 + m4 - m5 + m7

		aResult = add(m1, m3); // m1 + m3
		bResult = add(aResult, m6); // m1 + m3 + m6
		c22 = sub(bResult, m2); // c22 = m1 + m3 - m2 + m6

		// Grouping the results obtained in a single matrix
		for (i = 0; i < n / 2; i++) {
			for (j = 0; j < n / 2; j++) {
				result[i][j] = c11[i][j];
				result[i][j + n / 2] = c12[i][j];
				result[i + n / 2][j] = c21[i][j];
				result[i + n / 2][j + n / 2] = c22[i][j];
			}
		}
	}
	return result;
}

int main()
{
	vector<vector<int>> fMatrix;
	vector<vector<int>> sMatrix;

	fMatrix.resize(ROW, vector<int>(Columnumns, 0));
	sMatrix.resize(ROW, vector<int>(Columnumns, 0));

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < Columnumns; j++) {
			fMatrix[i][j] = randomNum();
			sMatrix[i][j] = randomNum();
		}
	}

	print(multiPly(fMatrix, sMatrix));
	print(strassen(fMatrix, sMatrix));

	system("pause");
	return 0;
}


