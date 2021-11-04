#include<iostream>

#include<stack>

#define n 15
using namespace std;

int graph[n][n];

int min(int a, int b) {
  return (a < b) ? a : b;
}

void findComponent(int u, int disc[], int lowLink[], stack < int > & stk, bool stkItem[]) {
  static int time = 0;
  disc[u] = lowLink[u] = ++time;
  stk.push(u);
  stkItem[u] = true;

  for (int v = 0; v < n; v++) {
    if (graph[u][v]) {
      if (disc[v] == -1) {
        findComponent(v, disc, lowLink, stk, stkItem);
        lowLink[u] = min(lowLink[u], lowLink[v]);
      } else if (stkItem[v])
        lowLink[u] = min(lowLink[u], disc[v]);
    }
  }

  int poppedItem = 0;
  if (lowLink[u] == disc[u]) {
    while (stk.top() != u) {
      poppedItem = stk.top();
      cout << poppedItem << " ";
      stkItem[poppedItem] = false;
      stk.pop();
    }
    poppedItem = stk.top();
    cout << poppedItem << endl;
    stkItem[poppedItem] = false;
    stk.pop();
  }
}

void strongConComponent() {
  int disc[n], lowLink[n];
  bool stkItem[n];
  stack <int> stk;

  for (int i = 0; i < n; i++) {
    disc[i] = lowLink[i] = -1;
    stkItem[i] = false;
  }

  for (int i = 0; i < n; i++)
    if (disc[i] == -1)
      findComponent(i, disc, lowLink, stk, stkItem);
}

int main() {
  srand (time(NULL));
  for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
          graph[i][j] = (i + j == 25 && i > j) ? 1 : 0;
          printf("%d ", graph[i][j]);
      }
      cout << endl;
  }
  printf("graph printed.\n");
  strongConComponent();
}
