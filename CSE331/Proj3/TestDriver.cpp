 
#include <iostream>

#include "RevList.h"

using namespace std;






void Print( CRevList<int>  * L );

// test modules
void TestPush( CRevList<int>  * L );
void TestConstructors(CRevList<int>  * L  );
void TestReverse( CRevList<int>  * L );
void TestSearch( CRevList<int>  * L );
void TestPopDeleteClear( CRevList<int>  * L );


int main()
{
    cerr<<" c 1"<<endl;
    CRevList<int> List;
    
    cerr<<" c 2"<<endl;
    CRevList<int> Test(List);
    
    cerr<<" c 3"<<endl;
    Test = List;
    
    cout<<"empty?   "<< List.IsEmpty() <<endl;
    

    List.PushFront( 4);
    List.PushFront( 3);
    List.PushFront( 2);
    List.PushFront( 1);
    List.PushBack(5);
    
    Test = List; 		//Fix assignment operator!

    cout<<"empty?   "<< List.IsEmpty() <<endl;
    
    Print( &List );

    CRevList<int>::Node * last = List.End();  
    //List.Reverse();
    cout<< "first:"<<List.Next(last)->Data()<<endl;;

    CRevList<int>::Node * first = List.Begin();  
    List.Reverse();
    cout<< "last:"<<List.Next(first)->Data()<<endl;;



    
    cout<<" --> Test Push\n------------------------\n"<<endl;
    //Test = List;
    TestPush( &List);
    
    cout<<" --> Test Constructors\n------------------------\n"<<endl;
    Test = List;
    TestConstructors(&List   );
    
    cout<<" --> Test Reverse\n------------------------\n"<<endl;
    Test = List;
    TestReverse( &List  );
    
    cout<<" --> Test Search\n------------------------\n"<<endl;
    Test = List;
    TestSearch( &List  );
    
    cout<<" --> Test Pop Delete Clear\n------------------------\n"<<endl;
    Test = List;
    TestPopDeleteClear( &List  );
    
    cout<<"original:\t";
    Print( &List );    


    cout<<"\n\n======================\ntest complete"<<endl;
    




}

void Print( CRevList<int>  * L )
{
    CRevList<int>::Node * curr = NULL;  
    //cout<<"print:  ";

    
    for( curr = L->Begin() ;! ( curr == L->End() ) &&! (curr == NULL ); curr = L->Next( curr ) )
    {


        cout<< curr->Data()<<" , ";
	//cout<<"DFLSDKLFSD";
    
    }
    if( ! ( curr== NULL  ))
    {
        cout<< curr->Data()<<" \n";
	//cout<<"BOOOOOOO";
    }

    else
    {	
	//cout<<"lallalalalalla ";
        cout<<"empty\n"<<endl;

    }

    cout<<"print:  ";
}
void TestPush( CRevList<int>  * L )
{
	L->PushBack(7);
}


void TestConstructors(CRevList<int>  * L  )
{

}


void TestReverse( CRevList<int>  * L )
{

}


void TestSearch( CRevList<int>  * L )
{
	CRevList<int>::Node * curr= L->Find(7);
	if(curr!=NULL){cout<< curr->Data()<<endl;;}
	else{
		cout<<"NULL"<<endl;
	}
}


void TestPopDeleteClear( CRevList<int>  * Test)
{
    CRevList<int> L( *Test ), D( *Test);

    cout<<"original:\t";
    Print( Test );


    cout<<"pop front:\t";
    Test->PopFront(); 		
    Print( Test );

   cout<<"pop back:\t";    
    Test->PopBack();
    Print( Test );    
   
    cout<<"reverse:\t";
    Test->Reverse() ;
    Print( Test );    
    
    cout<<"pop front:\t";
    Test->PopFront();
    Print( Test );

    cout<<"pop back:\t";    
    Test->PopBack();
    Print( Test );    
    
    cout<<"original:\t";
    Print( & L );
    
    cout<<"clear:\t";
    L.Clear();
    Print( &L );

    cout<<"original:\t";
    Print( & D );
   
    cout<<"Delete begin:\t";
    D.Delete( D.Begin() );
    Print( & D );
  
    cout<<"Delete end :\t";
    D.Delete( D.End() );
    Print( & D );
    
    cout<<"reverse:\t";
    D.Reverse();
    Print( & D );
    
    cout<<"Delete begin:\t";
    D.Delete( D.Begin() );
    Print( & D );
    
    cout<<"Delete end :\t";
    D.Delete( D.End() );
    Print( & D );
    

}
