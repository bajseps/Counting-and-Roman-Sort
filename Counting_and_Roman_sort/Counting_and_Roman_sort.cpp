#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 3) {
		cout << "Use the program: \n" <<
			argv[0] << " <option> <file with integers>\n" <<
			"option c - Counting sort\n" <<
			"option r - Roman sort" << endl;
	}
	else {
		string argument = argv[1];
		ifstream in(argv[2]);
		ofstream out;

		vector<int> A;

		if (in) {
			int value;

			while (in >> value) {
				A.push_back(value);
			}
		}

		int min = *min_element(A.begin(), A.end());

		for (int i = 0; i < A.size(); i++) {
			A[i] = A[i] - min;
		}

		vector<int> B(A.size());

		int max = *max_element(A.begin(), A.end());
		vector<int> C(max + 1, 0);

		for (int i = 0; i < A.size(); i++) {
			C[A[i]]++;
		}

		//counting sort
		if (argument == "c") {

			for (int i = 0; i < C.size(); i++) {
				if (i > 0) {
					C[i] = C[i] + C[i - 1];
				}
			}
			for (int i = A.size() - 1; i >= 0; i--) {
				B[C[A[i]] - 1] = A[i] + min;
				C[A[i]]--;
			}
		}

		//roman sort
		else if (argument == "r") {
			int j = 0;
			for (int i = 0; i < C.size(); i++) {
				while (C[i] > 0) {
					B[j] = i + min;
					j++;
					C[i]--;
				}
			}
		}

		out.open("out.txt");
		for (int i = 0; i < B.size(); i++) {
			out << B[i] << " ";
		}
		out.close();

		cout << ("The sort has been successful, check the out.txt file.");
	}
}