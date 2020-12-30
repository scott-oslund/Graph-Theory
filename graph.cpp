#include <iostream>
#include <ctime>

using namespace std;

const int MAXRAND = 7;

class graph{
/* for creating undirected graphs */
public:
  graph(int i = 25, double d = .1):num_nodes(i),density(d),num_edges(0){ // density must be between 1 and 0
    array = static_cast<int **>(malloc(num_nodes * sizeof(int*)));
    for(int k = 0; k < num_nodes; k++){
      array[k] = static_cast<int *>(calloc(sizeof(int), num_nodes));
    }
    srand(time(nullptr));
    for(int row = 0; row < num_nodes; row++){
      for(int col = row+1; col < num_nodes; col++){ // col = row + 1 prevent self loops and keeps graph undirected
        if(rand()%101 <= density*100){
          num_edges += 2;
          array[row][col] = rand() % MAXRAND + 1; // determines the cost of the path - min cost is 1
          array[col][row] = array[row][col];
        }
      }
    }
  }
  ~graph(){free(array), array = nullptr, cout<<"destructing"<<endl;}

  friend ostream& operator<<(ostream& out, const graph& g);

  inline int vertices() {return num_nodes;}

  inline int edges() {return num_edges;}

private:
  int num_nodes;
  int num_edges;
  double density;
  int **array;
};

ostream& operator<<(ostream& out, const graph& g){
    for(int i = 0; i < g.num_nodes; i++){
      for(int j = 0; j < g.num_nodes; j++){
        out << g.array[i][j] << " ";
      }
      out << endl;
    }
    return out;
}

int main(void){
  graph g;
  cout<< g << endl;
  cout<< "number of edges: "<< g.edges() << endl;
}
