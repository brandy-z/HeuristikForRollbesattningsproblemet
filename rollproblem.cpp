


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
  // for (int rand : randomNumbers){
  //   cout << rand;
  // }
  // cout << "\n";

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
          if(!contains(graph[el2], el1+1)){ // places to put divas on are NOT next to each other! Good!
            diva2place = el2;
            // cout << "placed divas!! on places (1-indexed) " << diva1place+1 << " and " << diva2place+1 << "\n";
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
  int uniqueActors = 0;
  // int actorNumber = -1;
  // int numberOfRollesPlayedByActor = 0;
  // int roll = -1;

  // get number of unique actors in assigned


  vector<int> assignedCopy;
  for (int i : assigned){
    assignedCopy.push_back(i);
  }

  sort(assignedCopy.begin(), assignedCopy.end());

  auto last = unique(assignedCopy.begin(), assignedCopy.end());
  assignedCopy.erase(last, assignedCopy.end());  
  uniqueActors = assignedCopy.size();

  int numZeroes = 0;
  for (int i : assigned){
    // assigned: 1 2 0 
    if(i == 0){
      numZeroes++;
    }
  }

  if(numZeroes > 1){
    uniqueActors += numZeroes-1; // we must add the zeroes that we did not already count with the unique() method
  }

  cout << uniqueActors << "\n";


  // create datastructure for the answer structure
  vector<vector<int>> answerVector(k+1);
  for(int i=0; i < k+1; i++){ // length is num skådisar including the superskådis-type
    answerVector.push_back(vector<int>());
  }
  
  for (int roll=0; roll<n; roll++){
    answerVector[assigned[roll]].push_back(roll+1);
  }

  for (int i=1; i<k+1; i++){
    if(!answerVector[i].empty()){
      cout << i << " " << answerVector[i].size() << " ";
      for(int role : answerVector[i]){
        cout << role << " ";
      }
      cout << "\n";
    }    
  }

  // number of superduperskådisar
  // cout << answerVector[0].size();

  for(int i = 0; i < answerVector[0].size(); i++){
    cout << k+1+i << " " << 1 << " " << answerVector[0][i] << "\n";
  }


  // for (int i = 0; i < actorsWithRolls; i++) {
  //   cout << actorNumber << " " << numberOfRollesPlayedByActor << " ";
  //   for (int j = 0; j < numberOfRollesPlayedByActor; j++) {
  //     cout << roll; 
  //   }
  //   cout << "\n";
  // }

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

  //printGraph();

  solveAssignmentProblem();

  //printAssigned();

  printSolution();

/*

3
2
3
3 1 2 3
3 1 2 3
3 1 2 3
2 1 3
2 2 3

3
2
2
2 1 2 
2 1 2 
2 1 2 
2 1 2
2 2 3


3 = roller
2 = scener
2 = skådisar
2 1 2 = roll 1 kan spelas av skådis 1 och 2
2 1 2 = roll 2 kan spelas av skådis 1 och 2 
2 1 2 = roll 3 kan spelas av skådis 1 och 2 
2 1 2 = finns kant mellan 1 och 2
2 2 3 = finns kant mellan 2 och 3

3
2
5
5 1 2 3 4 5
5 1 2 3 4 5
5 1 2 3 4 5
2 1 2 
2 2 3

3
4
5
1 2 
2 1 2 
2 1 2 
2 1 2 
2 2 3
2 1 2 
2 2 3

*/

  cout.flush();
  return 0;
}
