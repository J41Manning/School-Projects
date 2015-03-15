#ifndef _DUPLICATESREMOVE_H_
#define _DUPLICATESREMOVE_H_

#include <vector>

template<class T>
/*! Class to remove duplicates*/
class CDuplicatesRemove{
public:
  /*!Deletes repeated elements in the vector
  /param p_vec The vector to be searched through
  */
  void DuplicatesRemove(std::vector<T> *p_vec){
	if(p_vec->size() <= 1)

	for(int b =0; b < p_vec->size(); b++)  //Iterates through the vector
	{
		//Compares the current element with the next
		if ((*p_vec)[b+1]==(*p_vec)[b])
		{
			 // If equal, erase the repeated element
  			p_vec->erase (p_vec->begin()+(b+1));
			p_vec->resize(p_vec->size()-1);
		}
			
	}

  }
};

#endif
