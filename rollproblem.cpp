


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


// n = roller, s = scener, k = skådisar
int n, s, k;
bool debug = false;
vector<vector<int>> acotrsAllowed;
vector<vector<int>> graph;
vector<int> assigned;

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
          if(find(graph[role1-1].begin(), graph[role1-1].end(), role2) == graph[role1-1].end()){
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
