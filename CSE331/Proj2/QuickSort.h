#ifndef _QUICKSORT_H_
#define _QUICKSORT_H_

#include <vector>

template<class T>

/*! CQuickSort sorts the element*/ 
class CQuickSort{
public:
  /*! Sorts the input using quick sort method
  /param p_vec The vector to be sorted
  */
  void Sort(std::vector<T> *p_vec){
	if(p_vec->size() >1){
		int center =(p_vec->size()-1);
		T pivot = (*p_vec)[center];
		p_vec->pop_back();
	
		int i;
		int j = p_vec->size()-2;

		std::vector<T> *small_vec = new std::vector<T>();
		std::vector<T> *large_vec = new std::vector<T>();
	
		for(i=0;i<p_vec->size();i++)
		{
			if( (*p_vec)[i]<pivot) {
				small_vec->push_back((*p_vec)[i]);
			}
			else
				large_vec->push_back((*p_vec)[i]);
		}
 
		while(p_vec->size()>0){
			p_vec->pop_back();
		}
		Sort(small_vec);
		Sort(large_vec);



		for(i=0; i< small_vec->size(); i++)
		{
			p_vec->push_back((*small_vec)[i]);
		}

		for(i=0; i< large_vec->size(); i++)
		{
			p_vec->push_back((*large_vec)[i]);
		}

		delete small_vec;
		delete large_vec;
     }
  }
};

#endif
