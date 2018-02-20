var FloydClass = function () {

    this.graph = {};

    this.convertGraphD3ToFloydMatrix = function (graph) {
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

    this.dist = [];
    this.pos = [];
    
    this.recursionCheckNodeBetweenDoubleNodes = function (arr, indexFindInArray) {
        if (this.pos[arr[0]][arr[1]] == indexFindInArray) {
            return true;
        } else if (this.pos[arr[0]][arr[1]] == null) {
            return false;
        } else {
            return this.recursionCheckNodeBetweenDoubleNodes(
                [
                    arr[0],
                    this.pos[arr[0]][arr[1]]
                ],
                indexFindInArray
            );
        }
    }

    this.getDouble = function (grafo) {
        let arr = [];
        for (var k = 0; k < grafo.length; k++)//node haie ke beyn joft node ha hastan
        {
            arr[k] = [];
            for (var i = 0; i < this.pos.length; i++) {// baray tamam halat
                for (var j = 0; j < this.pos.length; j++) {// baray tamam halat ba khodeshoon
                    if (i != j) {
                        if (this.recursionCheckNodeBetweenDoubleNodes([i, j], k))
                            if (!arr.find(f => (f[0] == i && f[1] == j) || (f[1] == i && f[0] == j)))
                                arr[k].push([i, j]);

                    }
                }
            }
        }
        return arr;

    }

    this.getBetweenNess = function (grafo) {
        this.algoritmoFloydWarshall(grafo);
        let arr = this.getDouble(grafo);
        var s = _(arr.map(f => f.length)).sum();
        arr = arr.map(f => (f.length / s));
        arr.forEach((f, index) => {
            this.graph.nodes[index].betweenNess = f;
        });
        return arr;
    }

    this.getCloseNess = function (grafo) {
        this.algoritmoFloydWarshall(grafo);
        let arr = this.dist.map(f => this.dist.length / _(f).sum());
        arr.forEach((f, index) => {
            this.graph.nodes[index].closeNess = f;
        });
        return arr;
    }

    this.algoritmoFloydWarshall = function (grafo) {
        var floydWarshall = {};
        this.dist = this.init(grafo);
        this.pos = this.initPos(grafo);
        for (var k = 0; k < grafo.length; k++) {
            for (var i = 0; i < grafo.length; i++) {
                for (var j = 0; j < grafo.length; j++) {
                    if (this.dist[i][j] > this.dist[i][k] + this.dist[k][j]) {
                        this.dist[i][j] = this.dist[i][k] + this.dist[k][j];
                        this.pos[i][j] = k;
                    }
                }
            }
        }

        return { floydWarshall: this.dist, pos: this.pos };
    }

    this.init = function (grafo) {
        var dist = [];
        for (var i = 0; i < grafo.length; i++) {
            dist[i] = [];
            for (var j = 0; j < grafo.length; j++) {
                if (i === j)
                    dist[i][j] = 0;
                else if (isNaN(grafo[i][j]))
                    dist[i][j] = Infinity;
                else
                    dist[i][j] = grafo[i][j];
            }
        }
        return dist;
    }

    this.initPos = function (grafo) {
        var pos = [];
        for (var i = 0; i < grafo.length; i++) {
            pos[i] = [];
            for (var j = 0; j < grafo.length; j++) {
                pos[i][j] = null;
            }
        }
        return pos;
    }
}

