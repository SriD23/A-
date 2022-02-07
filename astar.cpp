#include "MinHeap.h"
#include <fstream>
#include <string>
#include <iostream>
#include <list>
#include <map>
#include <set>

using namespace std;

struct Node{

    string curr;
    int num_steps;
    int num_chars;

};

void Lowercase(string &input_string);
int calc_heuristic(string start_string, string end_string);
void a_star_search(map<string, vector<string> >& adj_list, string end_string, set<string>& was_visited1, MinHeap<Node>& heap);

int main(int argc, char* argv[]){

    string start_string, end_string, filename;
    start_string = argv[1];
    end_string = argv[2];
    filename = argv[3];
    int num_nodes;
    vector<string> storage; //vector which stores the lowercase words
    map<string, vector<string> > adj_list; //the adjacency list which stores all adjacent nodes 
    set<string> was_visited1; //set which determines whether a node has been visited or not
    set<string> total_set;  //stores all the lowercase words
    map<string, int> heuristics; //stores f values
    

    //these operations create the tree and its nodes, as well as initialize the values 
    //also adds first node

    MinHeap<Node> heap(2);
    int store_heuristic = calc_heuristic(start_string, end_string);
    Node tree_root;
    tree_root.num_steps = 0;
    tree_root.curr = start_string;
    tree_root.num_chars = 0;
    heap.add(tree_root, store_heuristic);

    //checks to see if file cannot be opened, and if it can't returns an error

    ifstream infile(filename.c_str());
    if(!infile){
        cout << "Can't open, input is invalid" << filename << "!"<<endl;
        return 1;
    }
    infile >> num_nodes;

    //makes lowercase and stores in set and vector and set

    for(int i = 0; i<num_nodes;i++){

        string temp;
        infile >> temp;

        for(unsigned int k = 0; k<temp.size();k++){
            temp[k] = tolower(temp[k]);
        }
        if(temp.size() == start_string.size()){

            total_set.insert(temp);
            storage.push_back(temp);

        }

    }
    //this is to account for the fact that the start and end strings arent made lower case too
    Lowercase(start_string);
    Lowercase(end_string);
    //they just get inserted on their own
    total_set.insert(end_string);
    storage.push_back(end_string);
    
    total_set.insert(start_string);
    storage.push_back(start_string);


    //this for loop finds all the possible combinations and checks whether they exist within the set of words
    //if the words exist, it inserts them into the adjacency list 

    unsigned int temp_var = storage.size();
    
    for(unsigned int i = 0; i<temp_var;i++){

        string temp = storage[i];

        for(unsigned int j = 0; j<temp.size();j++){

            //generates the ascii characters (lowercase letters) to use as combinations

            for(char f = 97; f <= 122;f++){
                temp[j] = f;

                if(total_set.find(temp) != total_set.end()){
                    adj_list[storage[i]].push_back(temp);
                }
            }

            temp = storage[i];
        }


    }
    //this calls the a* search function to perform the search
    a_star_search(adj_list, end_string, was_visited1, heap); 
    return 0;

}
void a_star_search(map<string, vector<string> >&adj_list, string end_string, set<string>& was_visited1, MinHeap<Node>&heap){

    //while loop to begin a* algorithm

    while(!heap.isEmpty()) {

        //creates a const node because peek returns a const value

       const Node upperN = heap.peek();
       heap.remove();

        //checks to see if the node on the top of the tree is the ending word, and if so determines that the shortest
        //path has been found and ends the search

        if(upperN.curr == end_string){
           cout << upperN.num_steps << endl;
           cout << was_visited1.size() << endl;
           return;
       }

       was_visited1.insert(upperN.curr);
       string temp = upperN.curr;
       int nSteps = upperN.num_steps;
       
       //loops through the adjacent nodes to the current node 
       
       for(int i = 0;i < adj_list[temp].size();i++){

           //stores node to check its adjacent nodes 

           string temp2 = adj_list[temp][i];

           //checks to see if it was visited, if it wasnt it adds it on to the tree

           if(was_visited1.find(temp2) == was_visited1.end()){
               
               int f_val = calc_heuristic(temp2, end_string) + nSteps + 1;
               Node new_tree_node;
               new_tree_node.curr = temp2;
               new_tree_node.num_steps = nSteps+1;
               heap.add(new_tree_node, f_val);
               
           }
       }
    }

    //if it reaches this point there was no transformations which could be made 

    cout << "No transformation" << endl;
    cout << was_visited1.size() << endl;

 }
 //this function calculates the heuristic value of each node
 int calc_heuristic(string start_string, string end_string){
     
     int temp = 0;
     for(int i = 0; i<start_string.size();i++){
         if(start_string[i] != end_string[i]){
             temp++;
         }
     }

    return temp;


 }
 //this function makes a word lowercase
 void Lowercase(string &input_string){

     for(int i = 0; i< input_string.length();i++){
         input_string[i] = tolower(input_string[i]);
     }

 }




    
