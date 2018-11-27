/*
  알고리즘 프로젝트
  Hidato Puzzle
  Solver Programming
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cmath>

using namespace std;

class Solver {

	const int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	const int dy[8] = { -1,  0,  1,-1, 1, -1, 0, 1 };
	int row, col;
	int max;
	int* arr;
	bool* isCheckArr;

public:
	void solve(vector<int>& puzz, int max_row, int max_col) {

    row = max_row;
		col = max_col;

		arr = new int[row*col];
		isCheckArr = new bool[row*col];


		for (int i = 0; i <= row * col; i++)
			isCheckArr[i] = 0;


		max = 0;
		int count = 0;
		int x, y;

		for (vector<int>::iterator i = puzz.begin(); i != puzz.end(); i++) { // puzzle 배열을 arr 배열에 복사, isCheckArr배열 변경 ,target 값 구하기

			arr[count] = *i;

			if ( max < arr[count] )
				max = arr[count];

			if ( arr[count] > 0 )
				isCheckArr[ arr[count] ] = 1;

			count++;
		}

		findStartPoint(x, y); // 시작점 1의 인덱스 찾기
		bool solvecheck = search(x, y, 2); // 값이 1인 인덱스에서부터 탐색 시작

		count = 0;
		if (solvecheck){

			for (vector<int>::iterator i = puzz.begin(); i != puzz.end(); i++) {
				if ( (*i) == 0 )
					(*i) = arr[ count ];

				count++;
			}
		}
		else
			cout << " 문제 해결 불가! " << endl;

		delete[] arr;
		delete[] isCheckArr;
	}

	void findStartPoint(int& x, int& y) {

		for (int i = 0; i<col; i++) {

			for (int j = 0; j<row; j++) {

				if (arr[j + row * i] == 1) {

					x = j;
					y = i;

					return;
				}

			}

		}
	}

	bool search(int x, int y, int nextPoint) { // 다음 경로 탐색 함수 , dfs로 구현

    if (nextPoint == max + 1)
      return true;

		if ( isCheckArr[nextPoint] ) {

			for (int i = 0; i < 8; i++) {

      	int row_tmp = x + dx[i];
				int col_tmp = y + dy[i];

        if ((row_tmp < 0) || (col_tmp < 0) || (row_tmp >= row) || (col_tmp >= col)) // 행,열 사이즈가 초과되면 continue
					continue;

        if (arr[row_tmp + col_tmp * row] == nextPoint) { // 현재 인덱스 주변 8개의 인덱스에 nextPoint+1 값이 존재한다면
					if ( search( row_tmp, col_tmp, nextPoint + 1) )
						return true;
				}
			}

			return false;
		}

		else{

			for (int i = 0; i < 8; i++) {

				int row_tmp = x + dx[i];
				int col_tmp = y + dy[i];

	      if ((row_tmp < 0) || (col_tmp < 0) || (row_tmp >= row) || (col_tmp >= col)) // 행,열 사이즈가 초과되면 continue
					continue;

	      if ( arr[row_tmp + col_tmp * row] == 0 ) {

	        arr[row_tmp + col_tmp * row] = nextPoint;

	        if ( search(row_tmp, col_tmp, nextPoint + 1) )
						return true;

	        arr[row_tmp + col_tmp * row] = 0;
				}
			}

			return false;

		}
	}

};

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	ifstream in("solverinput.txt");
	ofstream out("solveroutput.txt");

	int testcases;
	//cin >> testcases;
	in >> testcases;
	while (testcases--) {

		int input_row, input_col;
		//cin >> input_row >> input_col;
		in >> input_row >> input_col;

		Solver S;

		vector<int> puzz;

		int puzz_size = input_row * input_col;

		while (puzz_size--) {

			int add_num;

			in >> add_num;
			puzz.push_back(add_num);

		}

		S.solve( puzz, input_row, input_col );

		int k = 0;

		for ( vector<int>::iterator i = puzz.begin(); i != puzz.end(); i++ ) {

			k++;

			if ( (*i) != -1 && (*i) != 0 )
				out << (*i) << " ";

			else
				out << -1 << " ";

			if ( k == input_row ) {
				out << endl;
				k = 0;
			}
		}

		out << endl;
	}

	in.close();
	out.close();
	return 0;
}

