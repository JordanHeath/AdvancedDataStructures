//
//  Header.h
//  HW8
//
//  Created by Jordan Heath on 4/5/16.
//  Copyright © 2016 Jordan Heath. All rights reserved.
//

#ifndef Header_h
#define Header_h


template<class T>//this is typenamed to anything
class Heap
{
    
public:
    
    Heap()
    {
        
    }
    Heap(int k)
    {
        currentpos = 0;
        numchildren = k;
        
    }
    
    ////Heap(const )
    
    
    ~Heap()
    {
        
    }
    
    
    int parent(int value)
    {
        return (value -1)/numchildren;
    }
    int kthchild(int value, int k)
    {
        return numchildren*value +k;
    }
    void insert(T object)
    {
        
        int i = currentpos;
        currentpos++;//iterates onto the next
        
        if(OurHeap.size() == 0)// if the array is empty
        {
            OurHeap.push_back(object);//add it to front
        }
        else// we aren't empty, so we put our item at the end
        {
            OurHeap.push_back(object);
            ///now we have to sift up
            siftup(i);
        }
        
        
    }
    
    void siftup(int i)// i is the passed in value of the positon we just added to 
    {
        while(parent(i)>=0 && OurHeap.at(i) > OurHeap.at(parent(i)))//we check is parent is less than, while it is we sift up
        {
            swap(OurHeap.at(i), OurHeap.at(parent(i)));//
            i=parent(i);//iterates tot he next
        }
    }
    
    
    
    void displayMe(ostream &call)
    {
        for(int i = 0; i < OurHeap.size();i++)
        {
            call << OurHeap.at(i) << ',';
        }
        call << endl;
    }
    
    
    void remove(ostream &call)
    {
        //take value unroot
        T temp = OurHeap.at(0);//The item at the 0th value
        call << temp<<endl;
        
        
        std::swap(OurHeap.at(0),OurHeap.at(currentpos-1));//takes from the last value
        OurHeap.pop_back();//gets rid of the last item
        currentpos--;//position correlates to the item that were going to add to
        siftdown(0);
    }
    
    
    void siftdown(int index)
    {
        /*
        for(int i = 1; i <= kthchild(index, numchildren);i++)
        {
            if( OurHeap.at(kthchild(index,numchildren-i))  >OurHeap.at(index))
            {
                std::swap(OurHeap.at(kthchild(index,numchildren-i))  ,OurHeap.at(index));
            }
            
            
        }
        */
        
        ///this checks if there are any children at all
        if(kthchild(index, 1) >= OurHeap.size())
        {
            return;//if not, we return
        }
        /*
        for(int i=kthchild(index, 1);(i < OurHeap.size())&&(i <= kthchild(index, numchildren));i++)
        {
            if(OurHeap.at(i)>OurHeap.at(index))//thi
            {
                break;//if one of the values is greater than the parent, were going to go to the next one
            }
        }
        
        */
        
        if(OurHeap.at(index) >= OurHeap.at(LargestChild(index)))//if the parent is bigger than all the children, we return
        {
            return;
        }
        else//we swap the largest child with the current item
        {
            int j = LargestChild(index);// this designates the index of the largest child
            std::swap(OurHeap.at(index),OurHeap.at(j));//we swap the largest child with the index
            siftdown(j);// then jump into sifting it further down if needed
        }
        
        
        
        
        
        
        
        
    }
    
    int LargestChild(int parent)
    {
        int largest = kthchild(parent, 1);//this is the first child
        int i = 2;// indicating the second child to be iterated on
        int nextinline = kthchild(parent, i);//this will always be the variable for next in line
        
        if(nextinline > OurHeap.size())//if we only have 1in the array, we return it
        {
            return largest;
        }
        while((i <= numchildren) && nextinline < OurHeap.size())//we step through all the children and check if we've surpasses our size to avoid all .at() eerrors
        {
            if (OurHeap.at(nextinline) > OurHeap.at(largest) )
            {
                largest = nextinline;//if we occur a larger nextinline than the largest we replace
            }
            i++;//iterates to the next up child
            nextinline = kthchild(parent, i);// this is iterating the nextingline
        }
        
        return largest;// after that while statement we will have the largest
    }
    
    
    
private:
    
    
    vector<T> OurHeap;// this is the vector of T items that we can sort, the class is generic
    int numchildren;//this gets changed in the reset function
    int currentpos;
    
    
    
    
};


typedef struct node
{
    
    int data;//this should be private but 
    
    
    friend ostream &operator << (ostream &call, const node &me)//overload calling method
    {
        call << me.data;
        return call;
    }
    bool operator == (const node &rhs)//I used overload assignment operator instead of the getkey
    {
        return (data == rhs.data);//returns true if the data matches
    }
    bool operator >(const node &rhs)// overload >
    {
        return (data > rhs.data);
    }
    bool operator >=(const node &rhs)// overload >=
    {
        return (data >= rhs.data);
    }
    node(int value)//The constructor for the structure
    {
        data = value;
    }
    
    
}Node;





#endif /* Header_h */
