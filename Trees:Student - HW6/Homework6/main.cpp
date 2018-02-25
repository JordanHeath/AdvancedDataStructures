//
//  main.cpp
//  Homework6
//
//  Created by Jordan Heath on 3/2/16.
//  Copyright © 2016 Jordan Heath. All rights reserved.
//

#include "h.h"
#include "student.h"



int main(int argc, const char * argv[]) {
    // insert code here...
    
    Student<class T>object;
    
    cout << "Jordan Heath, 11376098" << endl;
   
    
    
    
   /// freopen("file.txt", "r", stdin); //simulates the computer grader
    
    while(true)
    {
        
        string command;//used the same process as last time
        getline(cin, command);
        
        if(command.find("add(")==0)
        {///index 4
            char *si = getstring(command.c_str(), 4, ','); ///// gets the name of the student
            int l = atoi(getstring(command.c_str(), strlen(si) + 5, ')')); //gets the number
            
            
            if(l==8)
            {
                
            }
            object.add(si, l);
            
            
        }
        else if(command.find("countValuesInNode(")==0)
        {
        ///17
            
            int l = atoi(getstring(command.c_str(), 18, ')'));
            object.CountValuesInNode(l, cout);
        
        
        }
        else if(command.find("countLevels()")==0)
        {
            
            object.countlevels(cout);
        }
        else if(command.find("displayInOrder()")==0)
        {
            object.calldisplay(cout);
        }
        else if(command.find("getName(")==0)
        {
            int l = atoi(getstring(command.c_str(), 8, ')'));
            ///object.getName(l, cout);
            object.findname(l, cout);
        }
        else if(command.find("getLevel(")==0)
        {
            int l=atoi(getstring(command.c_str(), 9, ')'));
            object.getLevel(l,cout);
            
        }
        else if(command.find("remove(")==0)
        {
            int l = atoi(getstring(command.c_str(), 7, ')'));
            object.callRemove(l);
            
        }
        else if(command.find("quit")==0)
        {
            cout << "Done" <<endl;
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