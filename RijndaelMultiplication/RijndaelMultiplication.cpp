// RijndaelMultiplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int multiplyHex(int first, int second);
string convertToBinary(int hex);
vector<int> getDegrees(string binary);
vector<int> multiplyDegrees(vector<int> first, vector<int> second);
void removeSeniorDegrees(vector<int>& degrees);
void removeDuplicates(vector<int>& degrees);
string getBinary(vector<int> degrees);
int convertToHex(string binary);

map<int, vector<int>> seniorDegrees { 
	{8, vector<int>({ 4, 3, 1, 0 })},
	{9, vector<int>({ 5, 4, 2, 1 })},
	{10, vector<int>({ 6, 5, 3, 2 })},
	{11, vector<int>({ 7, 6, 4, 3 })},
	{12, vector<int>({ 8, 7, 5, 4 })},
	{13, vector<int>({ 9, 8, 6, 5 })},
	{14, vector<int>({ 10, 9, 7, 6 })}
};

int main()
{
	int firstHex;
	cout << "Input first: ";
	scanf_s("%x", &firstHex);

	int secondHex;
	cout << "Input second: ";
	scanf_s("%x", &secondHex);

	int multHex = multiplyHex(firstHex, secondHex);
	printf("Result: %x", multHex);

	system("pause");
}

int multiplyHex(int first, int second) {
	string firstBinary = convertToBinary(first);
	string secondBinary = convertToBinary(second);

	vector<int> firstDegrees = getDegrees(firstBinary);
	vector<int> secondDegrees = getDegrees(secondBinary);

	vector<int> multDegrees = multiplyDegrees(firstDegrees, secondDegrees);
	removeSeniorDegrees(multDegrees);

	string resBinary = getBinary(multDegrees);
	return convertToHex(resBinary);
}

string convertToBinary(int hex) {
	char binary[100];
	_itoa_s(hex, binary, 100, 2);
	return string(binary);
}

vector<int> getDegrees(string binary) {
	vector<int> res;

	string revBinary = binary;
	reverse(revBinary.begin(), revBinary.end());

	for (int i = revBinary.size() - 1; i >= 0; i--) {
		if (revBinary[i] == '1') {
			res.push_back(i);
		}
	}

	return res;
}

vector<int> multiplyDegrees(vector<int> first, vector<int> second) {
	vector<int> res;

	for (auto i = first.begin(); i != first.end(); i++) {
		for (auto j = second.begin(); j != second.end(); j++) {
			res.push_back(*i + *j);
		}
	}

	return res;
}

void removeSeniorDegrees(vector<int>& degrees) {
	auto i = degrees.begin();
	while (i != degrees.end()) {
		if (*i > 7) {
			vector<int> seniorDegree = seniorDegrees.at(*i);

			degrees.erase(i);
			degrees.insert(degrees.end(), seniorDegree.begin(), seniorDegree.end());
			removeDuplicates(degrees);

			removeSeniorDegrees(degrees);

			break;
		}

		i++;
	}
}

void removeDuplicates(vector<int>& degrees) {
	vector<int> result;

	for (auto i = degrees.begin(); i != degrees.end(); i++) {
		bool isRemoved = false;
		auto j = result.begin();
		while (j != result.end()) {
			if (*j == *i) {
				result.erase(j);
				isRemoved = true;
				break;
			}

			j++;
		}

		if (!isRemoved) {
			result.push_back(*i);
		}
	}

	degrees = result;
}

string getBinary(vector<int> degrees) {
	string res = "00000000";

	for (auto i = degrees.begin(); i != degrees.end(); i++) {
		res[*i] = '1';
	}
	reverse(res.begin(), res.end());

	return res;
}

int convertToHex(string binary) {
	return stoi(binary, nullptr, 2);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
