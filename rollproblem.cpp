


#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;


// n = roller, s = scener, k = skådisar
int n, s, k;
bool debug = false;
vector<vector<int>> acotrsAllowed;
vector<vector<int>> graph;
vector<int> assigned;
auto rng = default_random_engine {};


bool contains(vector<int> vec, int num){
  return find(vec.begin(), vec.end(), num) != vec.end();
}

void readRollbesattningsProblem() {
  cin >> n >> s >> k;

  //vector<vector<int>> acotrsAllowed(n+1); // handle 1 indexing
  
  for (int i = 0; i < n; i++) {
    acotrsAllowed.push_back(vector<int>());
      
    int numPossibleActors;
    cin >> numPossibleActors;
    for (int j = 0; j < numPossibleActors; j++) {
      int p;
      cin >> p;

      acotrsAllowed[i].push_back(p);
    }
  }

  vector<int> rolesInSameScene;

  for (int i = 0; i < n; i++) {
    graph.push_back(vector<int>());
  }
  for (int i = 0; i < s; i++) {
    int numRolesInScene;
    cin >> numRolesInScene;
    for (int j = 0; j < numRolesInScene; j++) {
      int r;
      cin >> r;
      rolesInSameScene.push_back(r);
    }
    for(int role1 : rolesInSameScene){
      for(int role2 : rolesInSameScene){
        if (role1 != role2){
          // if we can not find role2 inside graph[role1]
          // then we add role2 to graph[role1]
          //cout << " checking if graph at index " << role1-1 << " has a list that contains element with name " << role2;
          //if(find(graph[role1-1].begin(), graph[role1-1].end(), role2) == graph[role1-1].end()){
          if(!contains(graph[role1-1], role2)){
            // can not find
            graph[role1-1].push_back(role2);
            //cout << " ADDING: node " << role1 << " has neighbor " << role2 << "\n";
          }
        }
      }
    }
    rolesInSameScene.clear();
      
  }
}


void solveAssignmentProblem(){
  // add zeroes (superskådisar) at all places
  for (int i = 0; i < n; i++) {
    assigned.push_back(0);
  }
  // add divas

  vector<int> randomNumbers(n);
  for (int i = 0; i < n; i++) {
    randomNumbers.push_back(i);
  }

  shuffle(begin(randomNumbers), end(randomNumbers), rng);
  for (int rand : randomNumbers){
    cout << rand;
  }
  cout << "\n";

  int diva1place;
  int diva2place;

  for (int el1 : randomNumbers){
    if(contains(acotrsAllowed[el1], 1)){ // if allowed actor is diva's name is '1'
      diva1place = el1;
      // when the first diva is assigned, we try to place the second diva!
      for (int el2 : randomNumbers){
        if(el1 == el2){
          continue;
        }
        if(contains(acotrsAllowed[el2], 2)){ // if allowed actor is diva's name '2'
          if(!contains(graph[el2], el1)){ // places to put divas on are NOT next to each other! Good!
            diva2place = el2;
            cout << "ASSIGNING DIVAS COMPLETE!\n";
            cout << "diva1place = " << diva1place <<"\n" ;
            cout << "diva2place = "<< diva2place <<"\n";
            goto afterDivaLoop;
          } 
        }
      }
    }
  }
  afterDivaLoop:
    assigned[diva1place]=1;
    assigned[diva2place]=2;

}

void printAcotrsAllowed(){

  for(int i=0;i<n;i++){
    cout << "role " << i << " can be played by actors: ";
    for(int h = 0; h < acotrsAllowed[i].size(); h++){
      cout << acotrsAllowed[i][h] << " ";
    }
    cout << "\n";
  }
}



void printGraph(){

  for(int i=0;i<n;i++){
    cout << "node " << i+1 << " has neighbors: ";
    for(int h = 0; h < graph[i].size(); h++){
      cout << graph[i][h] << " ";
    }
    cout << "\n";
  }
}

void printAssigned(){

  cout << "assigned: ";
  for(int i=0; i<n; i++){
    cout << assigned[i] << " ";
  }
  cout << "\n";
}

void printSolution() {
  cout << "executing printsolution" << "\n";
  int actorsWithRolls = n;
  int actorNumber = -1;
  int numberOfRollesPlayedByActor = 0;
  int roll = -1;

  cout << actorsWithRolls << "\n";

  for (int i = 0; i < actorsWithRolls; i++) {
    cout << actorNumber << " " << numberOfRollesPlayedByActor << " ";
    for (int j = 0; j < numberOfRollesPlayedByActor; j++) {
      cout << roll; 
    }
    cout << "\n";
  }

  cout.flush();
}


int main(void) {
  // Två trick för att göra cin/cout lite snabbare.
  // Se http://kattis.csc.kth.se/doc/iostreamio
  std::ios::sync_with_stdio(false);
  cin.tie(0);


  // if (debug){
  //   vector<int> v1 = {1,2,3,4};

  //   cout << "did not find element 2, should be false " << (find(v1.begin(), v1.end(), 2) == v1.end()) << "\n";
  //   cout << "did not find element 5, should be true " << (find(v1.begin(), v1.end(), 5) == v1.end()) << "\n";
  //   cout << "find element 2, should be true " << (find(v1.begin(), v1.end(), 2) != v1.end()) << "\n";
  //   cout << "find element 5, should be false " << (find(v1.begin(), v1.end(), 5) != v1.end()) << "\n";
  // }

  readRollbesattningsProblem();

  //printSolution();

  printGraph();

  solveAssignmentProblem();

  printAssigned();

  // cout << n << " " << s << " " << k << "\n";

/*
3
2
3
3 1 2 3
3 1 2 3
3 1 2 3
2 1 3
2 2 3
*/

  cout.flush();
  return 0;
}
