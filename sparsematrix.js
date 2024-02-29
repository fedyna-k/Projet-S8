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
        if (this.#flags & COLUMNS == 0) {
            throw TypeError("Sparse Matrix defined as lines only.");
        }
    }

    #clearLines() {
        for (let index of this.linesIndex) {
            if (Object.keys(this.lines[index]).length == 0) {
                this.linesIndex = this.linesIndex.filter(e => e != index);
            }
        }
    }

    #clearColumns() {
        for (let index of this.columnsIndex) {
            if (Object.keys(this.columns[index]).length == 0) {
                this.columnsIndex = this.columnsIndex.filter(e => e != index);
            }
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

        if (this.#flags & COLUMNS) {
            for (let c_index of this.columnsIndex) {
                delete this.columns[c_index][index];
            }

            this.#clearColumns();
        }

        this.lines[index] = {};
        this.linesIndex = this.linesIndex.filter(e => e != index);
    }

    nullifyColumn(index) {
        this.#assertColumn();

        if (this.#flags & LINES) {
            for (let l_index of this.linesIndex) {
                delete this.lines[l_index][index];
            }

            this.#clearLines();
        }
        
        this.columns[index] = {};
        this.columnsIndex = this.columnsIndex.filter(e => e != index);
    }

    nullifyCoefficient(l_index, c_index) {
        if (this.#flags & LINES) {
            delete this.lines[l_index][c_index];
            this.#clearLines()
        }

        if (this.#flags & COLUMNS) {
            delete this.columns[c_index][l_index];
            this.#clearColumns()
        }
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

const timeit = (message, fn) => {
    console.time(message);
    fn();
    console.timeEnd(message);
} 

let heap = process.memoryUsage().heapUsed;

console.time("Création classe")
let sparse = new SparseMatrix(10000, 10000, COLUMNS | LINES);
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

timeit("Initialisation classe", () => {
    for (let i = 0 ; i < 100 ; i++) {
        for (let j = 0 ; j < 100 ; j++) {
            sparse.setCoefficient(i * 100, j * 100, 1);
        }
    }
})

timeit("Initialisation naïve", () => {
    for (let i = 0 ; i < 100 ; i++) {
        for (let j = 0 ; j < 100 ; j++) {
            non_sparse[i * 100][j * 100] = 1;
        }
    }
})

console.log()

let spa_count = 0;
timeit("Décompte valeurs classe", () => {
    for (let index of sparse.columnsIndex) {
        let columns = sparse.getColumn(index);
        spa_count += Object.keys(columns).length;
    }
})

let non_count = 0;
timeit("Décompte valeurs naïve", () => {
    for (let line of non_sparse) {
        non_count += line.filter(e => e != 0).length;
    }
})

console.log("\nNombre de valeurs non nulles :")
console.log(non_count, "/", 10000**2, "=>", non_count / 1000**2, "%");
console.log(spa_count, "/", 10000**2, "=>", non_count / 1000**2, "%\n");

timeit("Suppression des coef classe", () => {
    for (let i = 0 ; i < 100 ; i++) {
        for (let j = 0 ; j < 100 ; j++) {
            sparse.nullifyCoefficient(i * 100, j * 100);
        }
    }
})

timeit("Suppression des coef naïve", () => {
    for (let i = 0 ; i < 100 ; i++) {
        for (let j = 0 ; j < 100 ; j++) {
            non_sparse[i * 100][j * 100] = 0;
        }
    }
})

for (let i = 0 ; i < 100 ; i++) {
    for (let j = 0 ; j < 100 ; j++) {
        sparse.setCoefficient(i * 100, j * 100, 1);
    }
}

console.log()
timeit("Suppression des colonnes classe", () => {
    for (let i = 0 ; i < 100 ; i++) {
        sparse.nullifyColumn(i * 100);
    }
})

for (let i = 0 ; i < 100 ; i++) {
    for (let j = 0 ; j < 100 ; j++) {
        sparse.setCoefficient(i * 100, j * 100, 1);
    }
}

timeit("Suppression des lignes classe", () => {
    for (let i = 0 ; i < 100 ; i++) {
        sparse.nullifyLine(i * 100);
    }
})

let sparse_col = new SparseMatrix(10000, 10000, COLUMNS);
let sparse_lin = new SparseMatrix(10000, 10000, LINES);

console.log()
for (let i = 0 ; i < 100 ; i++) {
    for (let j = 0 ; j < 100 ; j++) {
        sparse_col.setCoefficient(i * 100, j * 100, 1);
        sparse_lin.setCoefficient(i * 100, j * 100, 1);
    }
}
timeit("Suppression des coef classe (colonnes uniquement)", () => {
    for (let i = 0 ; i < 100 ; i++) {
        for (let j = 0 ; j < 100 ; j++) {
            sparse_col.nullifyCoefficient(i * 100, j * 100);
        }
    }
})
timeit("Suppression des coef classe (lignes uniquement)", () => {
    for (let i = 0 ; i < 100 ; i++) {
        for (let j = 0 ; j < 100 ; j++) {
            sparse_lin.nullifyCoefficient(i * 100, j * 100);
        }
    }
})

for (let i = 0 ; i < 100 ; i++) {
    for (let j = 0 ; j < 100 ; j++) {
        sparse_col.setCoefficient(i * 100, j * 100, 1);
        sparse_lin.setCoefficient(i * 100, j * 100, 1);
    }
}

console.log()
timeit("Suppression des colonnes classe (colonnes uniquement)", () => {
    for (let i = 0 ; i < 100 ; i++) {
        sparse_col.nullifyColumn(i * 100);
    }
})

timeit("Suppression des lignes classe (lignes uniquement)", () => {
    for (let i = 0 ; i < 100 ; i++) {
        sparse_lin.nullifyLine(i * 100);
    }
})