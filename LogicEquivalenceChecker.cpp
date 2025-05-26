#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

// Function Prototypes
vector<string> seperateString(vector<char>, string);				  // Breaks expression into sub-expressions
vector<char> getPremisis(string);									  // Gets unique variables from expression
int searchResult(vector<string>, string);							  // Search in string vector
int searchResult(vector<char>, char);								  // Search in char vector
int searchResult(vector<int>, int);									  // Search in int vector
vector<vector<bool>> setTruthTable(vector<char>, vector<string>);	  // Generate truth table
void displayString(vector<string>);									  // Print header of truth table
void displayBool(vector<char>, vector<vector<bool>>, vector<string>); // Print full truth table

// Output file for CSV
fstream write("truthTable.csv", ios::out);

int main()
{
	// 											Example expressions for testing
	// "(((p^q)->r)<->(q->r))"
	// "(((p->q)^(q->r))->(p->r))"

	// "(((~q)->(~p))V((~s)->(~r)))"
	// "(((p->q)^(r->s))^(pVr))"

	// "(((p^q)->r)<->(p->(q->r)))"
	// "(((p->q)^(q->r))->(p->r))"

	string rawString;
	cout << "\t\t*** LOGICALLY EQUIVALENCE CHECKER ***\n";
	cout << "\n(1) 'V' for AND\n(2) '^' for OR\n(3) '~' for NOT\n(4) '->' for IMPLICATION\n(5) '<->' for DOUBLE IMPLICATION'\n(6) '+' for XOR \n\n*** BRACKETS ARE ABSOLUTELLY NECCESSARY ***\n";

	cout << "(Brackets are compuslory.Write only one operation in a bracket)\nEnter expression : ";
	cin >> rawString;
	// Extract unique variables from input
	vector<char> variables = getPremisis(rawString);

	// Split expression into premises/sub-expressions
	vector<string> premisis = seperateString(variables, rawString);

	// Display the premises
	cout << "\nPremises:\n";
	for (int i = 0; i < premisis.size(); ++i)
	{
		cout << premisis[i] << endl;
	}
	// Generate truth table
	vector<vector<bool>> truthTable = setTruthTable(variables, premisis);
	// Display the truth table
	cout << "\nTruth Table:\n";
	displayString(premisis);
	displayBool(variables, truthTable, premisis);

	return 0;
}

bool Implication(bool x, bool y)
{
	if (y == true)
	{
		return true;
	}
	else if (x == false && y == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Xor(bool x, bool y)
{
	if (x != y)

		return true;
	else
		return false;
}
bool And(bool x, bool y)
{
	if (x == true && y == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Or(bool x, bool y)
{
	if (x == true || y == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Negation(bool x)
{
	if (x == true)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool BiConditional(bool x, bool y)
{
	if (x == true && y == true)
	{
		return true;
	}
	else if (x == false && y == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}

vector<vector<bool>> setTruthTable(vector<char> premisis, vector<string> expressions)
{
	int rows = pow(2, premisis.size());
	int column = expressions.size();
	vector<vector<bool>> truthTable(rows);

	for (int i = 0; i < rows; i++)
	{
		truthTable[i].resize(column);

		for (int j = 0; j < column; j++) // set truth table initialy to all false
		{
			truthTable[i][j] = false;
		}
	}

	int num = 2;
	int count = 0;
	bool check;

	for (int i = 0; i < premisis.size(); i++) // setting values for variable columns (p q r)
	{
		count = rows / num;
		check = true;

		for (int j = 0; j < rows; j++)
		{
			if (count > 0)
			{
				truthTable[j][i] = check;
				count--;
			}
			else if (count <= 0 && check == true)
			{
				count = (rows / num) - 1;
				check = false;

				truthTable[j][i] = check;
			}
			else if (count <= 0 && check == false)
			{
				count = (rows / num) - 1;
				check = true;

				truthTable[j][i] = check;
			}
		}

		num *= 2;
	}

	int curr = -1;

	for (int i = premisis.size(); i < truthTable[0].size(); i++)
	{
		curr = i;
		string s1 = "", s2 = expressions[curr];

		int index1 = -1, index2 = -1;

		for (int sIndex = curr - 1; sIndex >= 0; sIndex--)
		{
			s1 = expressions[sIndex];

			int found1 = s2.find(s1);
			if (found1 != string::npos) // unary operators
			{
				index1 = sIndex;
				string s = "";

				if (("(~" + s1 + ')') == s2)
				{
					for (int j = 0; j < rows; j++)
					{
						truthTable[j][i] = Negation(truthTable[j][index1]);
					}
				}

				if ("(" + s1 + ")" == s2)
				{
					for (int j = 0; j < rows; j++)
					{
						truthTable[j][i] = truthTable[j][index1];
					}
				}

				for (int ssIndex = curr - 1; ssIndex >= 0; ssIndex--)
				{
					string s3 = expressions[ssIndex];
					int found2 = s2.find(s3);
					if (found2 != string::npos && found1 != found2)
					{
						index2 = ssIndex;

						if (('(' + s1 + "^" + s3 + ')') == s2)
						{
							for (int j = 0; j < rows; j++)
							{
								truthTable[j][i] = And(truthTable[j][index1], truthTable[j][index2]);
							}
						}
						else if (('(' + s1 + "~" + s3 + ')') == s2)
						{
							for (int j = 0; j < rows; j++)
							{
								truthTable[j][i] = And(truthTable[j][index1], truthTable[j][index2]);
							}
						}
						else if (('(' + s1 + "V" + s3 + ')') == s2)
						{
							for (int j = 0; j < rows; j++)
							{
								truthTable[j][i] = Or(truthTable[j][index1], truthTable[j][index2]);
							}
						}
						else if (('(' + s1 + "->" + s3 + ')') == s2)
						{
							for (int j = 0; j < rows; j++)
							{
								truthTable[j][i] = Implication(truthTable[j][index1], truthTable[j][index2]);
							}
						}
						else if (('(' + s1 + "<->" + s3 + ')') == s2)
						{
							for (int j = 0; j < rows; j++)
							{
								truthTable[j][i] = BiConditional(truthTable[j][index1], truthTable[j][index2]);
							}
						}

						else if (('(' + s3 + "^" + s1 + ')') == s2)
						{
							for (int j = 0; j < rows; j++)
							{
								truthTable[j][i] = And(truthTable[j][index2], truthTable[j][index1]);
							}
						}
						else if (('(' + s3 + "~" + s1 + ')') == s2)
						{
							for (int j = 0; j < rows; j++)
							{
								truthTable[j][i] = And(truthTable[j][index2], truthTable[j][index1]);
							}
						}
						else if (('(' + s3 + "V" + s1 + ')') == s2)
						{
							for (int j = 0; j < rows; j++)
							{
								truthTable[j][i] = Or(truthTable[j][index2], truthTable[j][index1]);
							}
						}
						else if (('(' + s3 + "->" + s1 + ')') == s2)
						{
							for (int j = 0; j < rows; j++)
							{
								truthTable[j][i] = Implication(truthTable[j][index2], truthTable[j][index1]);
							}
						}
						else if (('(' + s3 + "<->" + s1 + ')') == s2)
						{
							for (int j = 0; j < rows; j++)
							{
								truthTable[j][i] = BiConditional(truthTable[j][index2], truthTable[j][index1]);
							}
						}
						else if (('(' + s3 + "+" + s1 + ')') == s2)
						{
							for (int j = 0; j < rows; j++)
							{
								truthTable[j][i] = Xor(truthTable[j][index2], truthTable[j][index1]);
							}
						}
						else if (('(' + s1 + "+" + s3 + ')') == s2)
						{
							for (int j = 0; j < rows; j++)
							{
								truthTable[j][i] = Xor(truthTable[j][index1], truthTable[j][index2]);
							}
						}
					}
				}
			}
		}
	}

	return truthTable;
}

vector<string> seperateString(vector<char> pre, string rawString)
{
	vector<string> premisis;
	vector<int> brackOpenPosition;
	vector<int> brackClosePosition;

	for (int i = 0; i < pre.size(); i++)
	{
		string temp = "";
		temp += pre[i];

		premisis.push_back(temp);
	}

	int brackOpenCount = 0, brackCloseCount = 0;
	char openBrack = '(', closeBrack = ')';

	for (int curr = 0; curr < rawString.length(); curr++)
	{
		if (rawString[curr] == openBrack)
		{
			brackOpenCount++;
		}
		else if (rawString[curr] == closeBrack)
		{
			brackCloseCount++;
		}
	}

	if (brackOpenCount != brackCloseCount)
	{
		cout << "Error :: Bracket Missing";
		exit(0);
	}

	int brackCount = brackOpenCount;

	for (int curr = 0; curr < rawString.length(); curr++)
	{
		if (rawString[curr] == closeBrack && (searchResult(brackClosePosition, curr) == -1))
		{
			brackClosePosition.push_back(curr);

			for (int i = curr; i >= 0; i--)
			{
				if (rawString[i] == openBrack && (searchResult(brackOpenPosition, i) == -1))
				{
					brackOpenPosition.push_back(i);
					break;
				}
			}
		}
	}

	string temp = "";

	for (int curr = 0; curr < brackCount; curr++)
	{
		temp = "";

		for (int i = brackOpenPosition[curr]; i <= brackClosePosition[curr]; i++)
		{
			temp += rawString[i];
		}

		premisis.push_back(temp);
	}

	return premisis;
}

vector<char> getPremisis(string main)
{
	vector<char> premisis;

	for (int i = 0; i < main.length(); i++) // finding and storing all the variables involved in the equation
	{
		for (int curr = 97; curr <= 122; curr++)
		{
			char temp1 = curr, temp2 = main[i];

			if (temp1 == temp2 && searchResult(premisis, temp2) == -1)
			{
				premisis.push_back(temp2);
			}
		}
	}

	for (int i = 0; i < premisis.size() - 1; i++) // order of premises . for example if stored "q p r" it will store "p  q r"
	{
		if (premisis[i] > premisis[i + 1])
		{
			char temp = premisis[i];
			premisis[i] = premisis[i + 1];
			premisis[i + 1] = temp;
		}
	}

	return premisis;
}

int searchResult(vector<char> arr, char k)
{
	vector<char>::iterator it;
	it = find(arr.begin(), arr.end(), k);

	if (it != arr.end())
	{
		return (it - arr.begin());
	}
	else
	{
		return -1;
	}
}

int searchResult(vector<string> arr, string k)
{
	vector<string>::iterator it;
	it = find(arr.begin(), arr.end(), k);

	if (it != arr.end())
	{
		return (it - arr.begin());
	}
	else
	{
		return -1;
	}
}

int searchResult(vector<int> arr, int k)
{
	vector<int>::iterator it;
	it = find(arr.begin(), arr.end(), k);

	if (it != arr.end())
	{
		return (it - arr.begin());
	}
	else
	{
		return -1;
	}
}

void displayBool(vector<char> prem, vector<vector<bool>> truthTable, vector<string> premisis)
{
	for (int i = 0; i < truthTable.size(); i++)
	{
		cout << endl;
		write << endl;
		for (int j = 0; j < truthTable[i].size(); j++)
		{
			cout << "|    " << truthTable[i][j] << "   |";
			write << truthTable[i][j] << ",";
		}
		cout << endl;
	}

	write << endl;
}

void displayString(vector<string> premisis)
{
	for (int curr = 0; curr < premisis.size(); curr++)
	{
		//	int size = max - premisis[curr].size();

		cout << "\t" << premisis[curr];
		write << premisis[curr] << ",";
	}
	write << endl;
	cout << endl;
}
