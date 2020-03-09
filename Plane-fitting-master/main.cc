#include "plane_axis_calculator.h"
#include <fstream>

using namespace std;

int main()
{
	ifstream inFile;
	vector<Vector3d> TestPoints;
	
	inFile.open("TestPoints.txt");
	
	if(!inFile)
	{
		cerr << "Unable to open file";
		exit(1);
	}
	
	double PointCoord;
	
	Vector3d Point(0.0, 0.0, 0.0);
	
	int i = 0;
	
	while(inFile >> PointCoord)
	{
		Point[i] = PointCoord;
		i++;
		if(i == 3)
		{
			i = 0;
			TestPoints.push_back(Point);
		}
	}
	
	PlaneAxisCalculator TestCalc(TestPoints);
	
	cout << "Points being used: " << endl;
	for(int i = 0; i < TestPoints.size(); i++)
	{
		cout << TestPoints[i] << endl;
	}
	
	TestCalc.PrintAxisDetails();
	
	Vector3d DummyAxis;
	
	TestCalc.get_normal(DummyAxis);

	
	
	return 0;
}