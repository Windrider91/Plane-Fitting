#ifndef PLANE_AXIS_CALCULATOR_H
#define PLANE_AXIS_CALCULATOR_H

#include "Vector3d.hh"
#include "Vector4d.hh"
#include <vector>

class PlaneAxisCalculator{
    private:
    const std::vector<Vector3d> &points;
    bool has_vaid_first_axis,has_vaid_second_axis,has_vaid_third_axis;
    Vector3d first_axis,second_axis,third_axis, origin;
    double first_fitness,second_fitness;
    public:
    //constructor works mainly for assignment and only calculates the origin of the plane
    PlaneAxisCalculator(const std::vector<Vector3d> &inputPoints):
        points(inputPoints),
        has_vaid_first_axis(false),
        has_vaid_second_axis(false),
        has_vaid_third_axis(false),
        origin(0.0,0.0,0.0)
    {
        std::vector<Vector3d>::const_iterator pnt = points.begin();
        for(;pnt!=points.end();pnt++){
            origin+=*pnt;
        }
        origin/=double(points.size());
    }
    //Plane origin always exists
    void get_origin(Vector3d& plane_origin){
        plane_origin = origin;
    }
	
	
	
	//**********************************************************************************************************
	//*****************************TEST FUNCTION, DELETE BEFORE SUBMITTING**************************************
	//**********************************************************************************************************
	void PrintAxisDetails()
	{
		cout << "Origin: " << origin;
	}
	//**********************************************************************************************************
	//*****************************TEST FUNCTION, DELETE BEFORE SUBMITTING**************************************
	//**********************************************************************************************************
	
	
	
    //You can focus on the development of this function for the moment
    bool get_normal(Vector3d& plane_first_axis){
        /* 
        * assume the plane has an equation of the form ax + by + cz + d = 0
        * where a,b,c and d are double (i.e. real) numbers
        * this function has infinite freedom which is a problem
        * we assume a+b+c=1; or c = 1-a-b
        * therefore we want to find the three variables a,b and d in ax + by + (1-a-b)z + d = 0
        * the rest of operations is explained in the notes
        * this function will claculate the followingmember variables orderly
            
            1- first_fitness
            2- has_vaid_first_axis
            3- first_axis
        
        * first_fitness is the average of the sum of the least squared distances
        * has_vaid_first_axis is set to true if the determinant of the resulting matrix is not zero
        * first_axis is Vector3d(a,b,c) after being normalized
        */
		
		
		vector<Vector3d> PointVectors;
		
		//Calculate all of the necessary sums, shifting all points so origin is (0,0,0)
		cout << endl << "Point vectors:" << endl;
		for(int i = 0; i < points.size(); i++)
		{
			Vector3d V = points[i] - origin;
			
			PointVectors.push_back(V);
			
			cout << PointVectors[i] << endl;
		}
		
		
		//Calculate least squares
		cout << endl << "Least squares calculations: " << endl;
		for(int i = 0; i < points.size(); i++)
		{
			PointVectors[i][0] -= PointVectors[i][2];
			PointVectors[i][1] -= PointVectors[i][2];
			cout << PointVectors[i] << endl;
			
		}
		
		//Set up derivative equations
		Vector3d Eq1Consts = {0.0, 0.0, 0.0}; //Constants for dsum(a,b)/da 
		Vector3d Eq2Consts = {0.0, 0.0, 0.0}; //Constants for dsum(a,b)/db
		
		for(int i = 0; i < PointVectors.size(); i++)
		{
			//Calculate equation for dsum(a,b)/da
			Eq1Consts[0] += 2 * PointVectors[i][0] * PointVectors[i][0]; //a
			Eq1Consts[1] += 2 * PointVectors[i][0] * PointVectors[i][1]; //b
			Eq1Consts[2] += 2 * PointVectors[i][0] * PointVectors[i][2]; //c
			
			//Calculate equation for dsum(a,b),db
			Eq2Consts[0] += 2 * PointVectors[i][1] * PointVectors[i][0];
			Eq2Consts[1] += 2 * PointVectors[i][1] * PointVectors[i][1];
			Eq2Consts[2] += 2 * PointVectors[i][1] * PointVectors[i][2];
		}
		
		
		//a and b are found by calculating the values of a 4x2 matrix
		Vector3d Eq1 = {Eq1Consts[0], Eq1Consts[1], -Eq1Consts[2]}; // aX + bY + 0 = -c
		Vector3d Eq2 = {Eq2Consts[0], Eq2Consts[1], -Eq2Consts[2]};
		
		cout << endl << "Eq1: " << Eq1;
		cout << endl << "Eq2: " << Eq2;
		
		//Solve for a
		
		Eq1 *= -Eq2Consts[1];
		Eq2 *= Eq1Consts[1];
		
		Eq2 += Eq1;
		
		if(Eq2[0] == 0)
		{
			has_vaid_first_axis = false;
			return false;
		}
		else
		{
			Eq2 /= Eq2[0];
			
			first_axis[0] = Eq2[2];
		}
		
				cout << endl << Eq2;
		
		//Solve for b
		
		//Reset equations to original constants
		Eq1 = {Eq1Consts[0], Eq1Consts[1], -Eq1Consts[2]};
		Eq2 = {Eq2Consts[0], Eq2Consts[1], -Eq2Consts[2]};
		
		Eq1 *= -Eq2Consts[0];
		Eq2 *= Eq1Consts[0];
		
		Eq2 += Eq1;
		
		if(Eq2[1] == 0)
		{
			has_vaid_first_axis = false;
			return false;
		}
		else
		{
			Eq2 /= Eq2[1];
			
			first_axis[1] = Eq2[2];
		}
		

		cout << endl << Eq2;
		
		//calculate c
		first_axis[2] = 1 - first_axis[0] - first_axis[1];
		
		//first_axis /= sqrt(first_axis * first_axis);
		
		cout << endl << "First axis: " << first_axis << endl;

		
		//Normal: V /= sqrt(V*V);
		
		
		
        plane_first_axis.reset();
        if(has_vaid_first_axis)
            plane_first_axis=first_axis;
            //this boolean variable will tell if the updated plane_first_axis is a valid or not
        return has_vaid_first_axis;
    }
    //other functions that we will take care of them later
    bool get_y_axis(Vector3d& plane_y_axis);
    bool get_x_axis(Vector3d& plane_x_axis);
    //bool get_coorninate_system(CoordinateSystem& local_coordinate_system);
};


#endif // PLANE_AXIS_CALCULATOR_H
