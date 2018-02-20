#include <stdio.h>
#include <omp.h>
 

class FloydClass{
  
    // Access specifier
    public:

        void convertGraphD3ToFloydMatrix(graph) {
        this.graph = graph;
        var m = [];
        this.graph.nodes.forEach((row, indexRow) => {
            m[indexRow] = [];
            this.graph.nodes.forEach((cell, cellIndex) => {
                var val = this.graph.links.find(f => (f.source.Id == cell.Id && f.target.Id == row.Id) || (f.source.Id == row.Id && f.target.Id == cell.Id)) ? 1 : NaN;
                m[indexRow].push(val);
            });
        });

        this.algoritmoFloydWarshall(m);
        this.getBetweenNess(m);
        this.getCloseNess(m);
        return m;
    }


};





int main() {

int res = 10;
#pragma omp for
for (int I=0;I<10;I++){
    res += I;
}

  printf("%d \n",res);
  printf("\n parallel for ends.\n");
  return 0;
}