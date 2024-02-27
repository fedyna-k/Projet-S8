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


let sparse = new SparseMatrix(10000, 10000, COLUMNS);
let non_sparse = Array.from({ length: 10000 }).map(e => Array(10000).fill(0));

for (let i = 0 ; i < 10 ; i++) {
    for (let j = 0 ; j < 10 ; j++) {
        sparse.setCoefficient(i * 1000, j * 1000, 1);
        non_sparse[i * 1000][j * 1000] = 1;
    }
}

console.time("Implémentation naïve")
let non_count = 0;
for (let line of non_sparse) {
    non_count += line.filter(e => e != 0).length;
}
console.timeEnd("Implémentation naïve")


console.time("Implémentation liste de map")
let spa_count = 0;
for (let index of sparse.columnsIndex) {
    let columns = sparse.getColumn(index);
    spa_count += Object.keys(columns).length;
}
console.timeEnd("Implémentation liste de map")

console.log(non_count);
console.log(spa_count);