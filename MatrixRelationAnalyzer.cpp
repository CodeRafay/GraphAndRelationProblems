#include <iostream>
#include <windows.h>
using namespace std;

// Check Symmetric/ Anti-Symmetric
bool isSymmetric(int **arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (arr[i][j] != arr[j][i])
				return false;
		}
	}
	return true;
}

// Check Reflexive/ Irreflexive
bool isReflexive(int **arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (arr[i][i] != 1)
				return false;
		}
	}
	return true;
}

// Check Transitive/ Non Transitive
bool isTransitive(int **arr1, int size)
{
	// Make a new matrix into which first matrix will copied
	int **arr2 = new int *[size];
	for (int i = 0; i < size; ++i)
	{
		arr2[i] = new int[size]();
	}
	int **result = new int *[size];
	for (int i = 0; i < size; ++i)
	{
		result[i] = new int[size]();
	}

	// Copying elements of Orignal matrix into another
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			arr2[i][j] = arr1[i][j];
		}
	}

	// Multiply orignal matrix with result matrix
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				result[i][j] += arr1[i][k] * arr2[k][j];
			}
		}
	}

	// To check transitive
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (arr1[i][j] == 0 && result[i][j] != 0)
			{
				return false;
			}
		}
	}
	return true; // For Transitive
}
// Pairs to make Symmetric, Reflexive and  Transitive
void display_Pairs(int **arr, int size)
{
	if (!isSymmetric(arr, size))
	{
		cout << "Pairs to make it Symmetric: ";
		for (int i = 0; i < size; ++i)
		{
			for (int j = i + 1; j < size; ++j)
			{
				if (arr[i][j] != arr[j][i])
				{
					if (arr[i][j] == 1 && arr[j][i] == 0)
					{
						cout << "(" << j << ", " << i << ") ";
					}
					else if (arr[j][i] == 1 && arr[i][j] == 0)
					{
						cout << "(" << i << ", " << j << ") ";
					}
				}
			}
		}
		cout << endl
			 << endl;
	}
	if (!isReflexive(arr, size))
	{
		cout << "Pairs to make it Reflexive: ";
		for (int i = 0; i < size; ++i)
		{
			if (arr[i][i] != 1)
			{
				cout << "(" << i << ", " << i << ")" << "  ";
			}
		}
		cout << endl
			 << endl;
	}
	if (!isTransitive(arr, size))
	{
		cout << "Pairs to make it Transitive: ";
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if (arr[i][j] == 1)
				{
					for (int k = 0; k < size; ++k)
					{
						if (arr[j][k] == 1 && arr[i][k] != 1)
						{
							cout << "(" << i << ", " << k << ")" << "  ";
						}
					}
				}
			}
		}
		cout << endl
			 << endl;
	}
	else
	{
		cout << "";
	}
}

// Display Matrix
void Display(int **arr, int size)
{
	cout << endl;
	cout << "Display Matrix " << endl
		 << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
// Display Graph
void DisplayGraph(int **arr, int size)
{
	cout << "Directed Graph:" << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (arr[i][j] != 0)
			{
				cout << arr[i][j] << " -> " << arr[j][i] << endl;
			}
		}
	}
	cout << endl;
}

// Add Colour
void setColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main()
{
	setColor(FOREGROUND_RED);
	cout << "\n\t\t\t\t\t\t\t\t ---------* RELATIONS *---------\n\n\n";
	setColor(FOREGROUND_GREEN);
	int **arr;
	int size;
	cout << "Enter size of Matrix: ";
	cin >> size;
	arr = new int *[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = new int[size];
	}
	cout << "Enetr Elements of " << size << "x" << size << " Matrix " << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cin >> arr[i][j];
		}
	}
	system("cls");
	setColor(FOREGROUND_BLUE);
	cout << "\n\t\t\t\t\t\t\t\t ---------* RELATIONS *---------\n\n\n";
	// Display Matrix
	setColor(FOREGROUND_RED);
	Display(arr, size);
	//
	setColor(FOREGROUND_BLUE);
	DisplayGraph(arr, size);

	setColor(FOREGROUND_GREEN);
	// check symmetric/ Anti Symmetric
	if (isSymmetric(arr, size) == true ? cout << ".Symmetric = YES " << endl : cout << ".Symmetric = NO" << endl)
		;
	// check Reflexive/ Irreflexive
	if (isReflexive(arr, size) == true ? cout << ".Reflexive = YES " << endl : cout << ".Reflexive = NO" << endl)
		;
	// Check Transitive/ Non Transitive
	if (isTransitive(arr, size) == true ? cout << ".Transitive = YES " << endl : cout << ".Transitive = NO" << endl)
		;
	cout << endl;
	setColor(FOREGROUND_RED);
	display_Pairs(arr, size);

	system("pause");
	return 0;
}