#include <iostream>
#include <fstream>
using namespace std;

class ImageProcessing
{
public:
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int newMin;
	int newMax;
	int** ZeroFramedAry;
	int* neighborAry;

	ImageProcessing(int rows, int cols, int min, int max)
	{
		numRows = rows;
		numCols = cols;
		minVal = min;
		maxVal = max;
		newMin = 0;
		newMax = 0;
		neighborAry = new int[5];
		ZeroFramedAry = new int*[numRows + 2];

		for(int i = 0; i < 5; i++)
		{
			neighborAry[i] = 0;
		}

		for(int l = 0; l < numRows + 2; l++)
		{
			ZeroFramedAry[l] = new int[numCols + 2];
		}

		for(int i = 0; i < numRows + 2; i++)
		{
			for(int j = 0; j < numCols + 2; j++)
			{
				ZeroFramedAry[i][j] = 0;
			}
		}

	}
	~ImageProcessing()
	{
		for (int i = 0; i < numRows + 2; i++)
		{
			delete[] ZeroFramedAry[i];
		}
		delete[] ZeroFramedAry;
		delete[] neighborAry;
	}

	void mirrowFramed()
	{
		for(int i = 0; i <= numCols + 1; i++)
		{
			ZeroFramedAry[0][i] = 0;
			ZeroFramedAry[numRows + 1][i] = 0;
		}

		for(int j = 0; j <= numRows + 1; j++)
		{
			ZeroFramedAry[j][0] = 0;
			ZeroFramedAry[j][numCols + 1] = 0;
		}
	}

	int checkMin()
	{
		int min = 1000;

		for(int i = 0; i < 4; i++)
		{
			if(min > neighborAry[i])
			{

				min = neighborAry[i];

			}
		}
		return min;
	}
	void loadNeighborsTop(int i, int j)  //need to debug
	{
		int counter = 0;

		for(int r = i - 1; r <= i; r++)
		{
			for(int c = j - 1; c <= j + 1; c++)
			{
				if(r == i && c == j)
				{
					break;
				}
				else
				{
					neighborAry[counter] = ZeroFramedAry[r][c];
					counter++;
				}
			}
		}
	}

	void loadNeighborsDown(int i, int j)
	{
		neighborAry[4]= ZeroFramedAry[i][j];
		int counter = 0;
		neighborAry[counter] = ZeroFramedAry[i][j + 1];
		counter++;

		for(int c = j - 1; c <= j + 1; c++)
		{
			neighborAry[counter] =ZeroFramedAry[i + 1][c];
			counter++;
		}
	}

	void firstPassDistance()
	{
		for(int i = 1; i <= numRows; i++)
		{
			for(int j = 1; j <= numCols; j++)
			{
				if(ZeroFramedAry[i][j] > 0)
				{
					loadNeighborsTop(i, j);
					int min = checkMin();
					ZeroFramedAry[i][j] = ++min;
				}
			}
		}
	}

	void secondPassDistance()
	{
		for(int i = numRows+1; i > 1; i--)
		{
			for(int j = numCols+1; j > 1; j--)
			{
				if(ZeroFramedAry[i][j] > 0)
				{
					loadNeighborsDown(i, j);

					int min=1000;

					for(int i = 0; i < 5; i++)
					{
						if(neighborAry[i] < min)
						{
							min=neighborAry[i];
						}
					}

					if(min < ZeroFramedAry[i][j])
					{
						ZeroFramedAry[i][j] = min + 1;
					}
					else
					{
						ZeroFramedAry[i][j] = ZeroFramedAry[i][j] + 1;
					}
				}
			}
		}
	}

	void prettyPrint(ofstream &outFile)
	{
		for(int m = 0; m <= numRows; m++)
		{
			for(int n = 0; n <= numCols; n++)
			{

				if(ZeroFramedAry[m][n] == 0)
				{
					outFile << "  ";
				}
				else
				{
					outFile << ZeroFramedAry[m][n] << " ";
				}
			}
			outFile << endl;
		}
	}
};


int main(int argc, char **argv)
{
	ifstream inFile;
	ofstream outFile1;
	ofstream outFile2;

	if (!inFile)
	{
		cout << "ERROR to open file";
		exit(1);
	}

	inFile.open(argv[1]);
	outFile1.open(argv[2]);
	outFile2.open(argv[3]);

	int rows;
	int cols;
	int min;
	int max;

	inFile >> rows >> cols >> min >> max;

	ImageProcessing image(rows, cols, min, max);

	while(!inFile.eof())
	{
		for(int i = 1; i <= image.numRows; i++)
		{
			for(int j = 1; j <= image.numCols; j++)
			{
				int value;
				inFile >> value;
				image.ZeroFramedAry[i][j] = value;
			}
		}
	}

	image.mirrowFramed();
	outFile2 << "Pretty Print pass 1"  << endl;
	//First Pass
	image.firstPassDistance();
	image.prettyPrint(outFile2);

	outFile2 << "----------------------------------------" << endl;
	outFile2 << "Pretty Print pass 2"  << endl;
	//Second Pass
	image.secondPassDistance();
	image.prettyPrint(outFile2);

	for(int i = 1 ; i < image.numRows + 1 ; i++)
	{
		for(int j = 1; j < image.numRows + 1 ; j++)
		{
			if(image.ZeroFramedAry[i][j] > image.newMax)
			{
				image.newMax = image.ZeroFramedAry[i][j];
			}
			else if(image.ZeroFramedAry[i][j] < image.newMin)
			{
				 image.newMin = image.ZeroFramedAry[i][j];
			}
		}
	}
	outFile1 << rows << " " << cols << " " << image.newMin << " " << image.newMax << endl;
	image.prettyPrint(outFile1);


	inFile.close();
	outFile1.close();
	outFile2.close();
	return 0;
}
