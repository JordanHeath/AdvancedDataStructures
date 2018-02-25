//
//  h9.h
//  HW9
//
//  Created by Jordan Heath on 4/17/16.
//  Copyright © 2016 Jordan Heath. All rights reserved.
//

#ifndef h9_h
#define h9_h



//// MY structures
typedef struct edge Edge;

typedef struct node
{
    char *name;
    double lowestcost;
    bool visited;
    node *path;//points to the fastest place
    vector<Edge> edges;
    node()
    {
      
    }
    node(char *n)
    {
        name = new char[strlen(n)];
        strcpy(name, n);
        lowestcost = 999999999;///if crash check the size of this number
        visited = false;
        path = NULL;
    }
    Edge addedge(Edge E);
    void resettable()
    {
        lowestcost = 999999999;///if crash check the size of this number
        visited = false;//reseting the visited
        path = NULL;
    }
    
    
}Node;


typedef struct edge
{
    double weight;
    Node *to;
    Node *from;
    
    
    edge(Node *a, Node *b, double wweight)
    {
        to = a;//references?
        from = b;
        weight = wweight;
    }
    
    
    
    
}Edge;



Edge node::addedge(Edge E)
{
    edges.push_back(E);
    return E;
}







///# pragma mark Graph utilities

class Graph
{
    
    
public:
    Graph()
    {
        
    }
    
    Graph(const Graph &copy)
    {/// if problems arise
        this->NodeList = copy.NodeList;
        this->Edges = copy.Edges;
    }
    
    ~Graph()
    {
        
    }
    
    
    void addnode(MyString name)
    {
        Node addme = *new Node(name.getstring());//simply creates a new node
        NodeList.push_back(addme);//then pushes it beck into the vector
    }
    
    void addedge(char * to, char *from, double weight)
    {
        //take these nodes from our list of nodes and add the edges to them
        Node *a = findanode(to);
        Node *b = findanode(from);
        
        Edges.push_back(b->addedge(Edge(a,b,weight)));// the to from
        
        Edges.push_back(a->addedge(Edge(b,a,weight)));// the from to
        
    
    }
    
    Node *findanode(char *search)
    {
        Node *returnnode = NULL;
        
        for(int i =0; i < NodeList.size();i++)
        {
            if(strcmp(search, NodeList.at(i).name)==0)//compares strings to find specified value
            {
                returnnode = &NodeList.at(i);//returns a reference to the node we anted to find
                break;
            }
        }
        
        return returnnode;
    }
    
    
    int degreeofnode(char *search)
    {
        int a = -1;
        
        Node *finddegof = findanode(search);
        if(finddegof)
        {
            a = finddegof->edges.size() * 2; // for every one coming in, there is also another one leaving
        }
        return a;
    }
    
    int shortest_length(char *sn, char *en)
    {
        
        for(int i =0;i < NodeList.size();i++)
        {/// if problems
            NodeList.at(i).resettable();
        }
        
        
        Node *start = findanode(sn);//creating the nodes to make the path
        Node *end = findanode(en);
        
        if(start && end)//if both of these aren't null meaning we can use them
        {
            
            Node *n = start;
            n->lowestcost = 0;// this is because it takes 0 to get to this node because it's the start
            while(n != end)// loop to check the edges with the costs
            {
                
                for(int i = 0; i < n->edges.size();i++)// for each edge from node n
                {
                    double tempcost = n->lowestcost + n->edges.at(i).weight;
                    if(tempcost < n->edges.at(i).to->lowestcost)
                    {
                        n->edges.at(i).to->lowestcost = tempcost;
                        n->edges.at(i).to->path = n;/// this is creating a path which indicates the shortest path to the item
                    }
                    
                }
                
                n->visited = true;//set the variable to true
                //look at the table to find the one witht he min cost that isn't visited
                int indexofsmallestcost=-1;
                double smallestsofar = 999999999;
                
                for(int i =0; i < NodeList.size();i++)
                {
                    
                    if(NodeList.at(i).visited != true && NodeList.at(i).lowestcost<smallestsofar)//wont enter if already visited
                    {
                        indexofsmallestcost = i;//updates the index
                        smallestsofar = NodeList.at(indexofsmallestcost).lowestcost;
                    }
                    
                }
                
                if(indexofsmallestcost == -1)// meaning we've found no path because everything has been true
                {
                    return -1;// no path found
                }
                n = &NodeList.at(indexofsmallestcost);/////
                
                
                
            }
            
            
            
        }
        int a =end->lowestcost;

        return a;// this
    }
   
  
    int shortestpath(char *start, char *end, ostream &out)
    {
        // find the shortest paths net weight
        if(shortest_length(start, end)== -1)
        {
            out << "no path"<<endl;
        }
        else
        {
        printme(findanode(end),out);
        out << ','<< endl;//including the last character
        }
        
      
        return 1;
    }

    void printme(Node *n, ostream &out)
    {
        
        if(n->path)
        {
            printme(n->path, out);//using recurrsion to print off all my values
            out <<",";
        }
        out << n->name;
        
        return;
        
    }
    
    void clear()
    {
        NodeList.clear();
        Edges.clear();
    }
    
    
private:
    
    vector<Node> NodeList;// instead of making a big huge table, i contained everything within this nodeList
    vector<Edge> Edges;
    
    
   /// vector<double> lowestcost;
   /// vector<bool>visited;
    
    
};



#endif /* h9_h */
