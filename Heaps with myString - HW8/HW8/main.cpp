//
//  main.cpp
//  HW8
//
//  Created by Jordan Heath on 4/5/16.
//  Copyright © 2016 Jordan Heath. All rights reserved.
//


#include "h.h"
#include "Header.h"





int main(int argc, const char * argv[]) {
    // insert code here...

    cout <<"Jordan Heath,11376098"<<endl;
    Heap<Node> object;// creating a heap of nodes...
    
    /// freopen("in1.txt", "r", stdin);
    
    
    while(true)
    {
        
        
        
        string command;//used the same process as last time
        getline(cin, command);
        
        if(command.find("reset(")==0)
        {//7th
            int a= atoi(getstring(command.c_str(), 6, ')'));
            object = *new Heap<Node>(a);//re constructs the ob
           
        }
        else if(command.find("add(")==0)
        {
            ///if we want to change the type go here
            int a = atoi(getstring(command.c_str(), 4, ')'));
            Node toadd(a);//should this be a pointer?
            object.insert(toadd);
            
        }
        else if(command.find("displayArray()")==0)
        {
            object.displayMe(cout);
            
        }
        else if(command.find("remove()")==0)
        {
            object.remove(cout);
        }
        else if(command.find("quit()"))
        {
            cout << "Done"<<endl;
            break;
        }
        
        
        
    }
    
    
    
    return 0;
}



char *getstring(const char *buffer, int index, char lookfor)//start index
{
    int setindex = 0;// index of the return variable
    char *toset = new char [strlen(buffer) + 1]; //need to allocate or i will get problems with assignment
    
    
    while(index <= strlen(buffer) )
    {
        //
        if(buffer[index] != lookfor)// itll
        {
            toset[setindex]  =buffer[index]; //
            setindex++;//iterate
        }
        else
        {
            toset[setindex] = '\0'; //null terminator for output
            index = strlen(buffer) + 1;// makes the index overload ending the assignment
        }
        
        index++;
    }
    
    
    return toset;
}