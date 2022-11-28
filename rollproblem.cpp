


#include <iostream>

using namespace std;


// n = roller, s = scener, k = skådisar
int n, s, k;


void readRollbesattningsProblem() {
  cin >> n >> s >> k;

  for (int i = 0; i < n; i++) {
    int numPossibleActors;
    cin >> numPossibleActors;
    for (int j = 0; j < numPossibleActors; j++) {
      int p;
      cin >> p;
    }
  }

  for (int i = 0; i < s; i++) {
    int numRolesInScene;
    cin >> numRolesInScene;
    for (int j = 0; j < numRolesInScene; j++) {
      int r;
      cin >> r;
    }
  }
}

void printSolution() {
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

  readRollbesattningsProblem();

  printSolution();

  cout << n << " " << s << " " << k << "\n";

  cout.flush();
  return 0;
}
