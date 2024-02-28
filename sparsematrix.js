#! /usr/bin/env node

const COLUMNS   = 0b01;
const LINES     = 0b10;

class SparseMatrix {
    lines;
    columns;
    linesIndex;
    columnsIndex;
    #flags;

    constructor(_lines_size, _columns_size, _flags=COLUMNS) {
        if (_flags < 1 || _flags > 3) {
            throw RangeError("Flag must be COLUMNS, LINES or COLUMN | LINES.");
        }

        if (_flags & COLUMNS) {
            this.columns = Array.from({ length: _columns_size }).map(e => ({}));
            this.columnsIndex = [];
        }

        if (_flags & LINES) {
            this.lines = Array.from({ length: _columns_size }).map(e => ({}));
            this.linesIndex = [];
        }

        this.#flags = _flags;
    }

    #assertLine() {
        if (this.#flags & LINES == 0) {
            throw TypeError("Sparse Matrix defined as columns only.");
        }
    }

    #assertColumn() {
        if (this.#flags & LINES == 0) {
            throw TypeError("Sparse Matrix defined as columns only.");
        }
    }

    getLine(index) {
        this.#assertLine();        

        return this.lines[index];
    }

    getColumn(index) {
        this.#assertColumn();

        return this.columns[index];
    }

    isNullLine(index) {
        this.#assertLine();        

        for (let i of this.linesIndex) {
            if (i == index) {
                return false;
            }
        }
        return true;
    }

    isNullColumn(index) {
        this.#assertColumn();
        
        for (let i of this.columnsIndex) {
            if (i == index) {
                return false;
            }
        }
        return true;
    }

    nullifyLine(index) {
        this.#assertLine();

        this.lines[index] = {};
        this.linesIndex = this.linesIndex.filter(e => e != index);
    }

    nullifyColumn(index) {
        this.#assertColumn();
        
        this.columns[index] = {};
        this.columnsIndex = this.columnsIndex.filter(e => e != index);
    }

    getCoefficient(l_index, c_index) {
        if (this.#flags & LINES) {
            if (this.isNullLine(l_index)) {
                return 0;
            }

            return this.lines[l_index][c_index] ?? 0;
        }

        if (this.isNullColumn(c_index)) {
            return 0;
        }

        return this.columns[c_index][l_index] ?? 0;
    }

    setCoefficient(l_index, c_index, value) {
        if (this.#flags & LINES) {
            if (this.isNullLine(l_index)) {
                this.linesIndex.push(l_index);
            }

            this.lines[l_index][c_index] = value;
        }

        if (this.#flags & COLUMNS) {
            if (this.isNullColumn(c_index)) {
                this.columnsIndex.push(c_index);
            }

            this.columns[c_index][l_index] = value;
        }
    }
}

let heap = process.memoryUsage().heapUsed;

console.time("Création classe")
let sparse = new SparseMatrix(10000, 10000, COLUMNS);
console.timeEnd("Création classe")

let sparse_size = process.memoryUsage().heapUsed - heap;

console.time("Création naïve")
let non_sparse = Array.from({ length: 10000 }).map(e => Array(10000).fill(0));
console.timeEnd("Création naïve")

let non_sparse_size = process.memoryUsage().heapUsed - heap - sparse_size;

console.log()

console.log(`Taille en mémoire classe : ${Math.floor(sparse_size/1024)}Kio`)
console.log(`Taille en mémoire naïve : ${Math.floor(non_sparse_size/1024)}Kio`)

console.log()

console.time("Initialisation classe")
for (let i = 0 ; i < 100 ; i++) {
    for (let j = 0 ; j < 100 ; j++) {
        sparse.setCoefficient(i * 100, j * 100, 1);
    }
}
console.timeEnd("Initialisation classe")


console.time("Initialisation naïve")
for (let i = 0 ; i < 100 ; i++) {
    for (let j = 0 ; j < 100 ; j++) {
        non_sparse[i * 100][j * 100] = 1;
    }
}
console.timeEnd("Initialisation naïve")


console.log()

console.time("Décompte valeurs classe")
let spa_count = 0;
for (let index of sparse.columnsIndex) {
    let columns = sparse.getColumn(index);
    spa_count += Object.keys(columns).length;
}
console.timeEnd("Décompte valeurs classe")

console.time("Décompte valeurs naïve")
let non_count = 0;
for (let line of non_sparse) {
    non_count += line.filter(e => e != 0).length;
}
console.timeEnd("Décompte valeurs naïve")

console.log("\nNombre de valeurs non nulles :")
console.log(non_count, "/", 10000**2, "=>", non_count / 1000**2, "%");
console.log(spa_count, "/", 10000**2, "=>", non_count / 1000**2, "%");