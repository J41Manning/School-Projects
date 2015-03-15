#ifndef _INSERTIONSORT_H_
#define _INSERTIONSORT_H_

#include <vector>

template<class T>

/*! CInsertSort sorts the element*/ 
class CInsertionSort{
public:
  /*! Sorts the input using insert sort method
  /param p_vec The vector to be sorted
  */
  void Sort(std::vector<T> *p_vec){
	int j;  //Variable used in loops below

	for(int b =1; b < p_vec->size(); b++)  //Iterates through the vector
	{
		T temp = p_vec->operator[](b);  //Creates temporary variable for the bth element

		//Searches for location in vector to insert element in
		for( j =b; j > 0 && temp < p_vec->operator[](j-1); j-- ) 
			p_vec->operator[](j) = p_vec->operator[](j-1); 
		
		//Then inserts it in the proper location
		p_vec->operator[](j) = temp;           
	}
   }
};

#endif
