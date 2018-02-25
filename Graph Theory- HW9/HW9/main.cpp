//
//  main.cpp
//  HW9
//
//  Created by Jordan Heath on 4/17/16.
//  Copyright © 2016 Jordan Heath. All rights reserved.
//



#include "h.h"
#include "h9.h"

int main(int argc, const char * argv[]) {
    // insert code here...
  
    
    cout << "Jordan Heath, 11376098"<<endl;
    MyString substr;// this is for when we set the object
    vector<MyString> nodevec;
    Graph ourgraph;
    
    
    
    
    //freopen("in1.txt", "r", stdin);

    while(1)
    {
        string command;
        getline(cin, command);
        
        if(command.find("set(") ==0)/// DONE?
        {
            
            //// we want to clear the node first
            //we never relly delete right here but since nothing
            //but i am anyways
            ourgraph.clear();
            
            int next = strlen(getstring(command.c_str(), 4, '|'));
            substr.set(getstring(command.c_str(), 4, '|'));
            substr.Split(',', nodevec);
            
            for(int i=0;i<nodevec.size();i++)
            {
                ourgraph.addnode(nodevec.at(i));
            }
            nodevec.clear();// clear it to make a new one
            substr.set(getstring(command.c_str(), next+5, ')'));
            substr.Split(';', nodevec);
            
            
            for(int i =0; i < nodevec.size(); i++)
            {
                vector<MyString> Edgevec;
                nodevec.at(i).Split(',', Edgevec);
                
                ourgraph.addedge(Edgevec.at(0).getstring(), Edgevec.at(1).getstring(), Edgevec.at(2).todouble());
                
                
                
            }
            
        }
        else if(command.find("degree(")==0)
        {//check if problems
            cout << ourgraph.degreeofnode(getstring(command.c_str(), 7, ')')) <<endl;
        }
        else if(command.find("shortest_path_length(")==0)
        {///21
            //get start
            char *start = getstring(command.c_str(), 21, ',');
            //get end
            char *end= getstring(command.c_str(),22+strlen(start),')');
            // do algorithm
            int a = ourgraph.shortest_length(start, end);
            
            if(a == -1)
            {
                cout << "no path" <<endl;
            }
            else
            {
                cout << a << endl;
            }
            
            //print the length
            
            
        }
        else if(command.find("shortest_path(")==0)
        {///14th char
            char *start = getstring(command.c_str(), 14, ',');
            //get end
            char *end= getstring(command.c_str(),15+strlen(start),')');
            
            ourgraph.shortestpath(start, end, cout);
            
        }
        else if(command.find("quit()")==0)
        {
            cout << "Done" << endl;
            break;//breaks out of the while statement to end the program
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
