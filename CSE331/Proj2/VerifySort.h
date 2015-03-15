#ifndef _VERIFYSORT_H_
#define _VERIFYSORT_H_

#include <vector>

template<class T>

/*!Class to test if a list is sorted*/
class CVerifySort{
public:
  /*! Verfies to see if the list is sorted
  /param p_vec The vector to be sorted
  /returns true when sorted, false otherwise
  */
  bool VerifySort(std::vector<T> *p_vec){
	if(p_vec->size() <= 1)  //If there is 0 or 1 elements, it is already sorted
		return true;
	for(int b =0; b < p_vec->size(); b++)  //Iterates through the vector
	{
		//if an elemetis found out of order, 	
		if ((*p_vec)[b+1]<(*p_vec)[b])
			return false;
	}
	return true;
  }
};

#endif
