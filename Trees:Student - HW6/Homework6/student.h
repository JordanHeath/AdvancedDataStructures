//
//  student.h
//  Homework6
//
//  Created by Jordan Heath on 3/2/16.
//  Copyright © 2016 Jordan Heath. All rights reserved.
//

#ifndef student_h
#define student_h


typedef struct node
{
    char *name_student;
    int number_student;
    
    node(node *a)
    {
        name_student = new char[strlen(a->name_student)+1];
        strcpy(name_student, a->name_student);///creating a deep copy of it
        number_student = a->number_student;// setting the student name equal
    }
    node(char *a, int b)
    {
        name_student = new char[strlen(a)+1];//allocating for the node
        strcpy(name_student, a);
        number_student=b;
    }
    
    
    
    
}Node;

typedef struct treenode//using structs becasue theyre automatically public
{
    //treenode *parent;//points to a parent node
    Node *A,*B,*C;///all three values
    treenode *L,*M1,*M2,*R;// al pointers
    
    treenode()// we got a constructor for creating a completely null tree
    {
        //parent=NULL;
        A=B=C=NULL;
        L=M1=M2=R=NULL;
    }
    
    
    treenode(node *a)//we got this so we can simply add into a nodes child pointer
    {
        B=C=NULL;
        A=new Node(a);//passing in the a value to create the object within
        L=M1=M2=R=NULL;//setting all the pointers to NULL
    }
    
}TreeNode;


template <class T>
class Student {
    
    
public:
    
    
    Student()
    {
        Headptr = NULL;
    }
    Student(const Student &copy)
    {
        this->Headptr = copy.Headptr;
    }
    ~Student()
    {
        
    }
    
    
    bool add(char *name, int number);//watch the type return on this one
    void countlevels(ostream &out);
    void calldisplay(ostream &call);
    void Display_in_order(TreeNode *n, ostream &call);
    bool getName(int Student_ID);
    void getLevel(int Student_ID, ostream &call);
    void CountValuesInNode(int Student_ID, ostream &out);
    void callRemove(int Student_ID)
    {
        TreeNode *n = Headptr;
        if(!getName(Student_ID))// this means the value is found so we will be able to run the function
        {
            TreeNode *p = NULL;
        removeItem(Student_ID, n, p);
        }
    }
    void removeItem(int Student_ID, TreeNode *n, TreeNode *p);
    
    void findname(int Student_ID, ostream &call);
    
private:
    TreeNode *Headptr;///I DONT KNOW ABOUT THIS ONE BEING A POINTER
    
};


template <class T> void Student<T>::removeItem(int Student_ID, TreeNode *n, TreeNode *p)
{
    if(n != Headptr && n->B == NULL)
    {
        //we want to fuse or rotate
        if(n == p->L)
        {
            if(p->M1->B)// if the adjacent node has more than 1 value
            {
                n->B = p->A;
                p->A = p->M1->A;
                
                p->M1->A = p->M1->B;
                p->M1->B = NULL;
                p->M1->B = p->M1->C;
                p->M1->C = NULL;
                
                
                ///now we need to deal with the children
                
                //shifting child pointers
                n->M2 = p->M1->L;
                p->M1->L=p->M1->M1;
                p->M1->M1=p->M1->M2;
                p->M1->M2=p->M1->R;
                p->M1->R= NULL;//clearing that last one
              
                
            }
            else if(p->B)// this is if it's adjacent only has one value we must go up to the parent
            {
                ///making the child a 3 node
                n->B = p->A;
                p->A = NULL;//clearing it
                n->C = p->M1->A;
                
                //re assigning the child pointers for current node
                n->M2 = p->M1->L;
                n->R = p->M1->M1;
                p->M1 = NULL;
                
                //new parent values;
                p->A=p->B;//shift
                p->B=p->C;
                p->C=NULL;
                
                //parents new children
                p->M1=p->M2;
                p->M2=p->R;
                p->R=NULL;
                
            
                
            }
            else// the parent is a 1 Node and its the parent.. meaning its the root is the parent
            {/// LOOK HERE FOR PROBLEMS
                n->B = p->A;
                p->A = NULL;
                n->C = p->M1->A;
                n->M2 = p->M1->L;
                n->R = p->M1->M1;
                
                Headptr = n;
                p=NULL;
                
            }
            
        }
        else if(n==p->M1)
        {
            
            if(p->L->B)//meaning we can borrow from the left
            {
                
                if(p->L->C)
                {
                    n->B = n->A;//push back value;
                    n->A = p->A;
                    p->A = p->L->C;
                    p->L->C = NULL;
                    
                    //deal with children
                    n->M2 = n->M1;
                    n->M1 = n->L;
                    n->L = p->L->R;
                    p->L->R = NULL;
                    
                }
                else//if there is just a b value
                {
                    
                    n->B=n->A;
                    n->A=p->A;
                    p->A=p->L->B;
                    p->L->B = NULL;
                    
                    //children
                    n->M2 = n->M1;
                    n->M1 = n->L;
                    n->L = p->L->M2;
                    p->L->M2 = NULL;
                    
                }
                
            }
            else if(p->M2 && p->M2->B)//if it exists and if we can borrow from right
            {
                n->B = p->B;
                p->B=p->M2->A;
                p->M2->A=p->M2->B;//shift value over
                p->M2->B = NULL;//setting this to  null pointer or else it willl be duplicate
                
                if(p->M2->C)
                {
                    p->M2->B = p->M2->C;
                    p->M2->C=NULL;
                }
                
                n->M2 = p->M2->L;
                p->M2->L=p->M2->M1;
                p->M2->M1=p->M2->M2;
                p->M2->M2=p->M2->R;
                p->M2->R = NULL;
                
                
            }
            else if(p->B)//meaning we can't borrow from either side because siblings are both 1 node
            {
                
                /*
                p->L->B = p->A;
                p->A = NULL;
                p->L->C = n->A;
                
                //children of the child
                
                p->L->M2 = n->L;
                p->L->R = n->M1;//this was the parent values m1 thats why i might have ran into a crash
                
                p->A = p->B;
                p->B = p->C;
                p->C = NULL;
                
                p->M1= p->M2;
                p->M2 = p->R;
                p->R = NULL;
                n=p->L;///reassigning the pointer to n because it has been replaced by the M2 value
                */
                
                //ASSIGNING FOR THE ACTUAL NODES
                n->C=n->A;
                n->B = p->A;
                n->A = p->L->A;
                
                
                //now children
                n->R = n->M1;
                n->M2 = n->L;
                n->M1 = p->L->M1;
                n->L = p->L->L;
                
                //now the parents nodes because we popped A
                p->A = p->B;
                p->B = p->C;
                p->C = NULL;
                
                //parennts children now
                p->L = p->M1;// this is actually n
                p->M1= p->M2;
                p->M2=p->R;
                p->R = NULL;
                
                
                
                
                
                
            }
            else//meaning its the root pointer paremt
            {
                n->R = n->M1;
                n->M2 = n->L;
                n->M1 = p->L->M1;
                n->L = p->L->L;
                
                n->C = n->A;
                n->B = p->A;
                n->A = p->L->A;
                
                Headptr = n;
                n=Headptr;
                p=NULL;
                
            }
            
            
            
        }
        else if(n==p->M2)
        {
            if(p->M1->B)/////if problems arise look here
            {
                if(p->M1->C)
                {
                    n->B = n->A;//push back
                    n->A = p->B;//bring down parnet
                    p->B = p->M1->C;//bring up c value from m2
                    
                    p->M1->C = NULL;//delete c value
                    
                    
                    n->M2 = n->M1;
                    n->M1 = n->L;
                    n->L = p->M1->R;
                    p->M1->R = NULL;
                }
                else// if there's only a B value
                {
                    n->B = n->A;//push back
                    n->A = p->B;//bring down from parent
                    p->B = p->M1->B;//give the b value
                    p->M1->B = NULL;//get rid of that value
                    
                    n->M2 = n->M1;
                    n->M1 = n->L;
                    n->L = p->M1->M2;
                    p->M1->M2 = NULL;
                }
                
            }
            else if(p->R && p->R->B)
            {
                
                n->B = p->C;//bring down the c from parent
                p->C = p->R->A;//brring up from R
                p->R->A = p->R->B;//shift values if they exist
                p->R->B = p->R->C;
                p->R->C = NULL;
                //dealing with children
                n->M2 = p->R->L;
                p->R->L = p->R->M1;
                p->R->M1=p->R->M2;
                p->R->M2=p->R->R;
                p->R->R= NULL;
                
            }
            else//this means we need to perform a fusion
            {
                /*
                p->M1->B = p->B;
                p->B = p->C;
                p->C = NULL;
                p->M1->C = p->M2->A;
                
                p->M2 = p->R;
                p->R = NULL;
                 */
                
                if(p->C)// this means the parent has 3 values within it
                {
                    //pushing everytinging to the right
                    n->C = n->A;
                    n->A = NULL;
                    n->R = n->M1;
                    n->M2 = n->L;
                    
                    //bringing down the B value from the parent.
                    n->B = p->B;
                    p->B = p->C;
                    p->C = NULL;
                    
                    //getting the values from the M1 pointer includning children
                    n->A = p->M1->A;
                    n->M1 = p->M1->M1;
                    n->L = p->M1->L;
                    
                    p->M1 = p->M2;
                    p->M2 = p->R;
                    p->R = NULL;
                    
                }
                else//by logic there has to be a B value if were pointing to M2
                {
                    n->C = n->A;
                    n->A = NULL;// i dont even know if ths is nesessary but its here jus in case
                    n->B = p->B;
                    p->B = NULL;// getting rid of this pointer making the parent a 1 node
                    n->A = p->M1->A;
                    
                    //deal with children now
                    n->R = n->M1;
                    n->M2 = n->L;
                    n->M1 = p->M1->M1;
                    n->L = p->M1->L;
                    
                    p->M1 = p->M2;
                    p->M2 = NULL;
                }
            }
            
            
        }
        else if(n==p->R)
        {
            
            if(p->M2->B)
            {
           
                if(p->M2->C)// if sibling is 3 node
                {
                    n->B = n->A;//push back A
                    n->A = p->C;//bring down parent
                    p->C = p->M2->C;//bring up siblings C value
                    p->M2->C = NULL;//delete the C value
                    
                    //Reassign children
                    n->M2 = n->M1;
                    n->M1 = n->L;
                    n->L = p->M2->R;
                    p->M2->R = NULL;
                    
                    
                }
                else//if there is only 2 nodes
                {
                    n->B=n->A;
                    n->A = p->C;
                    p->C = p->M2->B;
                    p->M2->B=NULL;
                    
                    n->M2 = n->M1;
                    n->M2=n->L;
                    n->L = p->M2->M2;
                    p->M2->M2=NULL;
                    
                }
                
            
            }
            else//if its adjacent is a one node
            {
                /*
                p->M2->B = p->C;
                p->C = NULL;
                p->M2->C = p->R->A;
                
                p->M2->M2 = n->L;
                p->M2->R = n->M1;
                
                p->R = NULL;
                */
                //re assign nodes
                n->C = n->A;
                n->B = p->C;
                p->C = NULL;
                n->A = p->M2->A;
                
                //re assign children
                n->R = n->M1;
                n->M2 = n->L;
                n->M1 = p->M2->M1;
                n->L = p->M2->L;
                
                p->M2 = p->R;
                p->R = NULL;
                
                
            }
            
            
        }
        
        
    }
    
    
    
    //mow check if n contains the value to delete
    if(n->A->number_student == Student_ID)
    {
        if(n->L)
        {//this means that it isn't a leaf
            
            if(n==Headptr)
            {

                if(n->M1->B)
                {
                    Node *temp = n->M1->A;
                    removeItem(temp->number_student, n, p);
                    n->A = temp;
                }
                else if(n->L->B)
                {
                    if(n->L->C)
                    {
                    Node *temp = n->L->C;
                    removeItem(temp->number_student, n, p);
                    n->A = temp;
                    }
                    else if(n->L->B)
                    {
                        Node *temp = n->L->B;
                        removeItem(temp->number_student, n, p);
                        n->A = temp;
                    }
                    else
                    {
                        Node *temp = n->L->A;
                        removeItem(temp->number_student, n, p);
                        n->A = temp;
                    }
                }
                else
                {// this means both children are 1 nodes
                    
                    n->B=n->A;
                    n->A = n->L->A;
                    n->C = n->M1->A;
                    n->R = n->M1->M1;
                    n->M2=n->M1->L;
                    n->M1=n->L->M1;
                    n->L=n->L->L;
                    
                    //combine the Node
                    if(n->M2)
                    {
                        Node *temp = n->M2->A;
                        removeItem(temp->number_student, n, p);
                        n->B = temp;
                    }
                    else
                    {
                        n->B = n->C;
                        n->C = NULL;
                    }
                    
                    
                }
                
            }
            else{
                
            
            Node *temp = n->M1->A;
            removeItem(temp->number_student, n, p);
            n->A = temp;
            }
        }
        else
        {// it's a leaf
            n->A = NULL;// delete it
            
            //pushing back the values
            if(n->B)
            {
                n->A = n->B;
                n->B = NULL;
            }
            
            if(n->C)
            {
                n->B = n->C;
                n->C = NULL;
            }
        }
        
        
        
    }
    else if(n->B && n->B->number_student == Student_ID)//check if it's there then check if we found the value
    {
        
        if(n->L)//if it's not a leaf
        {
            
            
            Node *temp = n->M2->A;
            removeItem(temp->number_student, n, p);
            n->B = temp;
        }
        else{
            
            n->B = NULL;
            if(n->C)
            {
                n->B = n->C;
                n->C = NULL;
            }
        }
        
        
    }
    else if(n->C && n->C->number_student == Student_ID)
    {
        if(n->L)
        {
            
            Node *temp = n->R->A;
            removeItem(temp->number_student, n, p);
            n->C = temp;
        }
        else
        {
            n->C = NULL;
        }
        
        
    }
    else// this is the case where it doesn't contain the value
    {// we dont need to check if it is null because it if were in this funciton, we know that the item is already in the list
        
        p = n;
        if(Student_ID < n->A->number_student)
        {
            n = n->L;//branch left
        }
        else if(n->B == NULL)
        {
            n= n->M1;//branch right
        }
        else if(Student_ID < n->B->number_student)
        {
            n = n->M1;
        }
        else if(n->C == NULL)
        {
            n=n->M2;
        }
        else if(Student_ID < n->C->number_student)
        {
            n=n->M2;
        }
        else
        {
            n=n->R;
        }
        removeItem(Student_ID, n, p);// recursive call to we can get the parent in
        
    }
    
    
    
}





template <class T> bool Student<T>::add(char *name, int number)
{
    ///first check for duplicates
    
    ///this sets up the whole thinbgn by setting pointers and parents
    TreeNode *n = Headptr;
    TreeNode *P = NULL;
    Node *toAdd = new Node(name,number);
    
    ///run check for doubles
    
    if(n != NULL && !getName(number))
    {
        return false;
    }
    
    if(n == NULL)//this means theres no items in the list
    {
        TreeNode *newnode= new TreeNode(toAdd);
        
        n = newnode;
        if(n)//if allocated
        {
          ///node was allocated
            Headptr=n;
            return true;
            ///RETURN?
        }
    }
    
    
    
    if(n->C != NULL)//this means that the current node has three values in it and we must split it
    {//we split the list
        
        if(P == NULL)
        {//means that it is the node at the top
            //we split the node
            
            P = new TreeNode(n->B);//moving the value up to the parent
            n->B = NULL;///de allocating
            
            P->M1 = new TreeNode(n->C);
            n->C = NULL;
            
            //re assigning the child nodes
            P->M1->L = n->M2;
            P->M1->M1 = n->R;
            n->M2=n->R=NULL;//getting rid of the pointers to the next ones
            
            P->L = n;
            
            ///assign parents
            
            Headptr = P;
            n= P;
        }
        else//if the parent is not null then we want to move the middle value up into the parent
        {        }
        
    }
    
    ///NOW CHECK IF N IS A LEAF
    if(n->L == NULL)//it isnt pointing to anything so it must be a leaf
    {
        if(n->B == NULL)//for if there is one item
        {
            n->B = toAdd;//placing the new pointer in the leaf
            if(n->B->number_student < n->A->number_student)
            {
                std::swap(n->A,n->B);//swap the two pointers
            }
            //return n;
        }
        else if(n->C==NULL)//for if theres two items
        {
            n->C = toAdd;
            if(n->C->number_student < n->B->number_student)
            {
                std::swap(n->B,n->C);//swap the two pointers
            }
            
            if(n->B->number_student < n->A->number_student)
            {
                std::swap(n->A,n->B);//swap the two pointers
            }
            //return n;
            
        }
        
    }
    else//meaning n in internal
    {
        
        
        while(n->L != NULL)//this will stop when we reach a leaf but will split cases that are 3 nodes
        {
            P=n;
            if(toAdd->number_student < n->A->number_student)
            {
                n = n->L;//branch left
            }
            else if(n->B == NULL)
            {
                n= n->M1;//branch right
            }
            else if(toAdd->number_student < n->B->number_student)
            {
                n = n->M1;
            }
            else if(n->C == NULL)
            {
                n=n->M2;
            }
            else if(toAdd->number_student < n->C->number_student)
            {
                n=n->M2;
            }
            else
            {
                n=n->R;
            }
            
            
            if(n->C != NULL)/// THE NODDE IS FULL
            {//this means that we need to split
                
                if(P->L == n)//if the node to split is to the left of the parent
                {
                    swap(P->B,P->C);
                    swap(P->A, P->B);//pushes the pointer to A to the right one
                    P->A = n->B;//brings B up to the top
                    n->B = NULL;//frees the pointer
                    
                    
                    swap(P->R,P->M2);//moves the pointer to the right one
                    swap(P->M1,P->M2);//moves the right pointer to the right
                    
                    P->M1 = new TreeNode(n->C);
                    n->C = NULL;
                    
                    
                    P->M1->L = n->M2;
                    n->M2 = NULL;//
                    
                    P->M1->M1 = n->R;
                    n->R = NULL;
                    
                    
                    //the left pointer still remains
                }
                
                
                if(P->M1 == n)//if its the middle pointer
                {
                    swap(P->C, P->B);//switches the null value with the middle
                    P->B=n->B;
                    n->B = NULL;
                    
                    //right has to be null since the node isnt a 3 node
                    swap(P->R, P->M2);
                    
                    P->M2 = new TreeNode(n->C);
                    n->C = NULL;
                    
                    P->M2->L = n->M2;
                    n->M2 = NULL;
                    
                    P->M2->M1 = n->R;
                    n->R = NULL;
                    
                    
                    
                    
                }
                
                if(P->M2 == n)//if its the left one
                {
                    P->C = n->B;
                    n->B = NULL;
                    
                    P->R = new TreeNode(n->C);
                    n->C = NULL;
                    
                    P->R->L = n->M2;
                    n->M2 = NULL;
                    
                    P->R->M1 = n->R;
                    n->R = NULL;
                    
                    
                }
                n= P;//points back up to the parent node so we can further traverse
        }
        
        }

        if(n->B == NULL)//for if there is one item
        {
            n->B = toAdd;//placing the new pointer in the leaf
            if(n->B->number_student < n->A->number_student)
            {
                std::swap(n->A,n->B);//swap the two pointers
            }
            //return n;
        }
        else if(n->C==NULL)//for if theres two items
        {
            n->C = toAdd;
            if(n->C->number_student < n->B->number_student)
            {
                std::swap(n->B,n->C);//swap the two pointers
            }
            
            if(n->B->number_student < n->A->number_student)
            {
                std::swap(n->A,n->B);//swap the two pointers
            }
            //return n;
            
        }
        
        
    }
    
   /// Headptr = n;////i dont know
    
    return true;
}

template <class T> void Student<T>::countlevels(ostream &out)
{//its always even tree so we should count down
    TreeNode *n=Headptr;
    //starts at 0
    int i=0;
    
    if(!n)
    {
        out << i << endl;
        return;
    }//displays 0 and breaks

    //add one because it isnt numm
    
    while(n)
    {
        i++;//iterates every time
        n=n->L;
    }
    out<<i<<endl;
    
    
}

template <class T> bool Student<T>::getName(int Student_ID)////this one is actually giving me
{
    TreeNode *n = Headptr;
    
    //this is going to go through to find out if the name is actually being used in the data set already... branches are given for certain conditions
    while(n)
    {
        if(Student_ID < n->A->number_student)
        {
            n= n->L;
        }
        else if(Student_ID == n->A->number_student)
        {
            return false;
        }
        else if(!(n->B))
        {
            n=n->M1;
        }
        else if(Student_ID > n->A->number_student && Student_ID < n->B->number_student)
        {
            n=n->M1;
        }
        else if(Student_ID == n->B->number_student)
        {
            return false;
        }
        else if(!(n->C))
        {
            n=n->M2;
        }
        else if(Student_ID > n->B->number_student && Student_ID < n->C->number_student)
        {
            n=n->M1;
        }
        else if(Student_ID == n->C->number_student)
        {
            return false;
        }
        else
        {
            n=n->R;
        }
        
    }
    
    
    return true;
    
    
}

template <class T> void Student<T>::Display_in_order(TreeNode *n, ostream &call)
{///FOR THIS IM GOING TO USE RECURRSION
    
    if(n->L)
    {
        Display_in_order(n->L, call);//goes all the way to the leftmost value
    }
    
    
    call << n->A->name_student <<',' << n->A->number_student << ';';//prints the A value
    
    
    if(n->M1)
    {
        Display_in_order(n->M1, call);///call going to the M1 pointer
    }
    
    if(n->B)//if there is a B value, print it out then go down to the M2 NODE
    {
    call << n->B->name_student <<',' << n->B->number_student << ';';//prints B value
        
    if(n->M2)
    {
        Display_in_order(n->M2, call);
    }
        
    }
    
    if(n->C)
    {
    call << n->C->name_student <<',' << n->C->number_student << ';';
    
    
    if(n->R)
    {
        Display_in_order(n->R, call);
    }
    }
    
    
}

template <class T> void Student<T>::getLevel(int Student_ID, ostream &call)
{
    
    int level = 0;
    
    TreeNode *n = Headptr;
    
    if(!n)
    {//this means that the node we wanna search is NULL
        call << -1<<endl;
        return;
    }
    
    
    while(n)
    {
        
        if(Student_ID < n->A->number_student)
        {
            level++;//iterate an move to the next node
            n= n->L;
        }
        else if(Student_ID == n->A->number_student)
        {
            break;//its found break out of thos statement
        }
        else if(Student_ID > n->A->number_student && !(n->B))
        {
            level++;
            n=n->M1;
        }
        else if(Student_ID > n->A->number_student && Student_ID < n->B->number_student)
        {
            level++;
            n=n->M1;
        }
        else if(Student_ID == n->B->number_student)
        {
            break;
        }
        else if(Student_ID > n->B->number_student && !(n->C))
        {
            level++;
            n=n->M2;
        }
        else if(Student_ID > n->B->number_student && Student_ID < n->C->number_student)
        {
            level++;
            n=n->M1;
        }
        else if(Student_ID == n->C->number_student)
        {
            break;
        }
        else
        {
            level++;
            n=n->R;
        }
    }

    if(!n)//if we get to the point where n is NULL then we havent found the value
    {
        call<<-1<<endl;
        return;
    }
    else{
        call<<level<<endl;// we have found the level if it's non null when we leave the while statement
    }
    
}


template <class T> void Student<T>::CountValuesInNode(int Student_ID, ostream &out)
{
    
    ///search for the node with the value in it
    TreeNode *n=Headptr;
    
    while(n)
    {///using the usual branching 
        
        if(Student_ID < n->A->number_student)
        {
            n= n->L;
        }
        else if(Student_ID == n->A->number_student)
        {
            break;
        }
        else if(Student_ID > n->A->number_student && !(n->B))
        {
            n=n->M1;
        }
        else if(Student_ID > n->A->number_student && Student_ID < n->B->number_student)
        {
            n=n->M1;
        }
        else if(Student_ID == n->B->number_student)
        {
            break;
        }
        else if(Student_ID > n->B->number_student && !(n->C))
        {
            n=n->M2;
        }
        else if(Student_ID > n->B->number_student && Student_ID < n->C->number_student)
        {
            n=n->M1;
        }
        else if(Student_ID == n->C->number_student)
        {
            break;
        }
        else
        {
            n=n->R;
        }
    }
    
    if(n->C)//if there is a non-null C value, then we know there is threee vales in the node
    {
        out << 3 << endl;
    }
    else if(n->B)//2 node
    {
        out << 2 << endl;
    }
    else if (n->A)
    {
        out << 1 << endl;
    }
    else//meaning there's nothing
    {
        out << -1 << endl;
    }
}


/*
 
 
 
 if(P->L == n)//this means that it is the value to the left
 {
 if(n->parent->B != NULL)//were going to push it to the right one
 {
 swap(n->parent->B, n->parent->C);///a simple push
 swap(n->parent->A, n->parent->B);//B is already null so now were going to place the values in
 n->parent->A = n->B;
 n->B=NULL;//de allocation
 
 //push the pointers to the left
 n->parent->R = n->parent->M2;
 n->parent->M2 = n->parent->M1;
 
 /////if problem arises check here
 n->parent->L->parent = n->parent;
 
 
 n->parent->M1 = new TreeNode(n->C);
 n->parent->M1->parent = n->parent;
 n->C=NULL;
 
 
 n->parent->M1->L = n->M2;
 n->parent->M1->M1 = n->R;
 
 
 n->M2=NULL;
 n->R=NULL;///////
 }
 else//this means there is only one item in the array
 {
 ///what goes here
 swap(n->parent->A, n->parent->B);
 n->parent->A = n->B;//moving the middle value up to the top
 n->B = NULL;
 
 
 n->parent->M2= n->parent->M1;/// this pushed the higher value to the right
 
 n->parent->M1 = new TreeNode(n->C);
 n->C = NULL;
 n->parent->M1->parent = n->parent;
 
 
 
 n->parent->M1->L = n->M2;
 n->parent->M1->M1 = n->R;
 
 
 n->M2=n->R=NULL;
 
 }
 
 
 }
 else if(n->parent->M1 == n)
 {
 //this means that it s the middle value that needs to go up
 if(n->parent->B == NULL)
 {
 n->parent->B = n->B;
 n->B = NULL;//freeing the pointer
 n->parent->M2 = new TreeNode(n->C);
 n->C = NULL;
 n->parent->M2->L = n->M2;
 n->parent->M2->M1 = n->R;
 
 n->M2=n->R=NULL;
 n->parent->M2->parent= n->parent;
 
 }
 else
 {
 swap(n->parent->B, n->parent->C);
 n->parent->B = n->B;
 n->B=NULL;
 n->parent->R = n->parent->M2;
 delete n->parent->M2;//makes it NULL;
 n->parent->M2 = new TreeNode(n->C);
 n->C=NULL;
 n->parent->M2->parent=n->parent;
 
 
 n->parent->M1->L = n->L;
 n->parent->M1->M1 = n->M1;
 n->parent->M2->L = n->M2;
 n->parent->M2->M1 = n->R;
 
 }
 
 }
 else if(n->parent->M2 == n)
 {
 n->parent->C = n->B;//moving the value up
 n->B = NULL;//getting rid of that allocation
 n->parent->R = new TreeNode(n->C);
 n->C = NULL;
 
 n->parent->R->parent=n->parent;///assigning a parent node for these
 
 n->parent->R->L = n->M2;
 n->parent->R->M1 = n->R;
 
 
 n->M2=NULL;
 n->R=NULL;
 
 }
 n=n->parent;
 

 
 
 */

template <class T> void Student<T>:: findname(int Student_ID, ostream &call)
{
   
    TreeNode *n = Headptr;
    while(n)
    {
        
        if(Student_ID < n->A->number_student)
        {
            n= n->L;
        }
        else if(Student_ID == n->A->number_student)
        {
            call << n->A->name_student << endl;
            return;
        }
        else if(Student_ID > n->A->number_student && !(n->B))
        {
            n=n->M1;
        }
        else if(Student_ID > n->A->number_student && Student_ID < n->B->number_student)
        {
            n=n->M1;
        }
        else if(Student_ID == n->B->number_student)
        {
            call << n->B->name_student << endl;
            return;
        }
        else if(Student_ID > n->B->number_student && !(n->C))
        {
            n=n->M2;
        }
        else if(Student_ID > n->B->number_student && Student_ID < n->C->number_student)
        {
            n=n->M2;
        }
        else if(Student_ID == n->C->number_student)
        {
            call << n->A->name_student << endl;
            return;
        }
        else
        {
            n=n->R;
        }
    }
    call << "(student not found)" << endl;
    
}



template <class T> void Student<T>:: calldisplay(ostream &call)
{
    Display_in_order(Headptr, call);
    call << endl;
}



#endif /* student_h */
