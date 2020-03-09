#include "Vector3d.hh"

using namespace std;

int main()
{
	Vector3d TestVect(1.0, 2.0, 3.0);
	
	/*
	TestVect->elem[0] = 1.0;
	TestVect->elem[1] = 2.0;
	TestVect->elem[2] = 3.0;
	*/
	cout << TestVect[0] << endl << TestVect[1] << endl << TestVect[2];
	return 0;
}