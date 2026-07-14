(function () {
    // Raw arrays in the same redundant-per-cell format as the original
    // src/KakuroSolver.cpp KakuroGrid14 (run sum repeated across every cell
    // of the run). Converted into the editable clue/fillable/blocked layout
    // by deriveLayout() below, so there's nothing to transcribe by hand.
    const EXAMPLE_RAW = {
        rows: 9,
        cols: 9,
        horiz: [
            0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 4, 4, 0, 6, 6, 6, 0,
            0, 0, 24, 24, 24, 24, 24, 24, 0,
            0, 0, 0, 4, 4, 0, 17, 17, 0,
            0, 0, 0, 0, 17, 17, 17, 17, 0,
            0, 0, 23, 23, 23, 23, 23, 0, 0,
            0, 0, 12, 12, 0, 4, 4, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0,
        ],
        vert: [
            0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 4, 12, 0, 7, 24, 15, 0,
            0, 0, 4, 12, 14, 7, 24, 15, 0,
            0, 0, 0, 12, 14, 0, 24, 15, 0,
            0, 0, 0, 0, 14, 6, 24, 15, 0,
            0, 0, 12, 17, 14, 6, 24, 0, 0,
            0, 0, 12, 17, 0, 6, 24, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0,
        ],
        prefilled: [
            0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 4, 0, 0,
            0, 0, 0, 3, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 9, 0, 3, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0,
        ],
    };

    const TYPES = ['blocked', 'clue', 'fillable'];

    let rows = 9;
    let cols = 9;
    let cellType = [];
    let rightSum = [];
    let downSum = [];
    let given = [];
    let cells = [];

    function idx(r, c) {
        return r * cols + c;
    }

    function setStatus(message, kind) {
        const status = $('#kakuro-status');
        status.textContent = message;
        status.className = 'status-message' + (kind ? ' ' + kind : '');
    }

    function resetState() {
        const size = rows * cols;
        cellType = new Array(size).fill('blocked');
        rightSum = new Array(size).fill('');
        downSum = new Array(size).fill('');
        given = new Array(size).fill('');
    }

    function deriveLayout(raw) {
        const size = raw.rows * raw.cols;
        const type = new Array(size).fill('blocked');
        const right = new Array(size).fill('');
        const down = new Array(size).fill('');
        const giv = new Array(size).fill('');
        const c = (r, col) => r * raw.cols + col;

        for (let r = 0; r < raw.rows; r++) {
            for (let col = 0; col < raw.cols; col++) {
                const i = c(r, col);
                if (raw.horiz[i] > 0 || raw.vert[i] > 0) {
                    type[i] = 'fillable';
                    if (raw.prefilled[i] > 0) giv[i] = raw.prefilled[i];
                }
            }
        }
        for (let r = 0; r < raw.rows; r++) {
            for (let col = 0; col < raw.cols; col++) {
                const i = c(r, col);
                if (type[i] !== 'fillable') continue;

                if (raw.horiz[i] > 0 && (col === 0 || type[c(r, col - 1)] !== 'fillable')) {
                    if (col > 0) {
                        const clueIdx = c(r, col - 1);
                        if (type[clueIdx] !== 'fillable') {
                            type[clueIdx] = 'clue';
                            right[clueIdx] = raw.horiz[i];
                        }
                    }
                }
                if (raw.vert[i] > 0 && (r === 0 || type[c(r - 1, col)] !== 'fillable')) {
                    if (r > 0) {
                        const clueIdx = c(r - 1, col);
                        if (type[clueIdx] !== 'fillable') {
                            type[clueIdx] = 'clue';
                            down[clueIdx] = raw.vert[i];
                        }
                    }
                }
            }
        }
        return { type, right, down, giv };
    }

    function cycleType(i) {
        if (cellType[i] === 'blocked') {
            cellType[i] = 'clue';
            rightSum[i] = '';
            downSum[i] = '';
        } else if (cellType[i] === 'clue') {
            cellType[i] = 'fillable';
            rightSum[i] = '';
            downSum[i] = '';
            given[i] = '';
        } else {
            cellType[i] = 'blocked';
            given[i] = '';
        }
        buildGrid();
    }

    function buildGrid() {
        const grid = $('#kakuro-grid');
        grid.innerHTML = '';
        grid.style.gridTemplateColumns = `repeat(${cols}, 38px)`;
        cells = [];

        for (let r = 0; r < rows; r++) {
            for (let c = 0; c < cols; c++) {
                const i = idx(r, c);
                const type = cellType[i];
                const cell = el('div', { class: 'cell ' + type + '-cell' });
                cell.addEventListener('click', () => cycleType(i));

                const isLastCol = c === cols - 1;
                const isLastRow = r === rows - 1;
                cell.style.borderRight = isLastCol ? 'none' : '';
                cell.style.borderBottom = isLastRow ? 'none' : '';

                if (type === 'clue') {
                    const down = el('input', { type: 'number', min: '1', class: 'clue-input down-sum', title: 'Column sum' });
                    down.value = downSum[i];
                    down.addEventListener('click', (e) => e.stopPropagation());
                    down.addEventListener('input', () => {
                        const v = parseInt(down.value, 10);
                        downSum[i] = Number.isNaN(v) ? '' : v;
                    });

                    const right = el('input', { type: 'number', min: '1', class: 'clue-input right-sum', title: 'Row sum' });
                    right.value = rightSum[i];
                    right.addEventListener('click', (e) => e.stopPropagation());
                    right.addEventListener('input', () => {
                        const v = parseInt(right.value, 10);
                        rightSum[i] = Number.isNaN(v) ? '' : v;
                    });

                    cell.appendChild(down);
                    cell.appendChild(right);
                } else if (type === 'fillable') {
                    const input = el('input', { type: 'number', min: '1', max: '9', class: 'fillable-input' });
                    input.value = given[i];
                    if (given[i]) input.classList.add('given');
                    input.addEventListener('click', (e) => e.stopPropagation());
                    input.addEventListener('input', () => {
                        input.classList.remove('given', 'solved-value');
                        const v = parseInt(input.value, 10);
                        given[i] = Number.isNaN(v) ? '' : Math.max(1, Math.min(9, v));
                        input.value = given[i];
                        if (given[i]) input.classList.add('given');
                    });
                    cell.appendChild(input);
                }

                grid.appendChild(cell);
                cells.push(cell);
            }
        }
        setStatus('', '');
    }

    function buildSolverArrays() {
        const size = rows * cols;
        const horiz = new Array(size).fill(0);
        const vert = new Array(size).fill(0);
        const prefilled = new Array(size).fill(0);

        for (let r = 0; r < rows; r++) {
            for (let c = 0; c < cols; c++) {
                const i = idx(r, c);
                if (cellType[i] !== 'clue') continue;

                if (rightSum[i]) {
                    let cc = c + 1;
                    while (cc < cols && cellType[idx(r, cc)] === 'fillable') {
                        horiz[idx(r, cc)] = rightSum[i];
                        cc++;
                    }
                }
                if (downSum[i]) {
                    let rr = r + 1;
                    while (rr < rows && cellType[idx(rr, c)] === 'fillable') {
                        vert[idx(rr, c)] = downSum[i];
                        rr++;
                    }
                }
            }
        }
        for (let i = 0; i < size; i++) {
            if (cellType[i] === 'fillable' && given[i]) prefilled[i] = given[i];
        }
        return { horiz, vert, prefilled };
    }

    function loadExample() {
        rows = EXAMPLE_RAW.rows;
        cols = EXAMPLE_RAW.cols;
        $('#kakuro-rows').value = String(rows);
        $('#kakuro-cols').value = String(cols);

        const layout = deriveLayout(EXAMPLE_RAW);
        cellType = layout.type;
        rightSum = layout.right;
        downSum = layout.down;
        given = layout.giv;

        buildGrid();
    }

    function clearAll() {
        resetState();
        buildGrid();
    }

    async function solve() {
        const { horiz, vert, prefilled } = buildSolverArrays();
        const wasGiven = prefilled.map((v) => v !== 0);

        setStatus('Solving…', '');
        const result = await window.PuzzleSolversBridge.solveKakuro(horiz, vert, prefilled, rows, cols);

        if (!result.solved) {
            setStatus('No solution found for this grid.', 'error');
            return;
        }

        for (let i = 0; i < rows * cols; i++) {
            if (cellType[i] !== 'fillable') continue;
            const cellIndexInDom = i;
            const input = cells[cellIndexInDom].querySelector('input');
            if (!input) continue;
            const value = result.solution[i];
            if (value === 0) continue;
            input.value = String(value);
            given[i] = value;
            input.classList.toggle('given', wasGiven[i]);
            input.classList.toggle('solved-value', !wasGiven[i]);
        }
        setStatus('Solved!', 'success');
    }

    function resize() {
        rows = Math.max(2, Math.min(16, parseInt($('#kakuro-rows').value, 10) || 9));
        cols = Math.max(2, Math.min(16, parseInt($('#kakuro-cols').value, 10) || 9));
        $('#kakuro-rows').value = String(rows);
        $('#kakuro-cols').value = String(cols);
        resetState();
        buildGrid();
    }

    document.addEventListener('DOMContentLoaded', () => {
        resetState();
        $('#kakuro-rows').addEventListener('change', resize);
        $('#kakuro-cols').addEventListener('change', resize);
        $('#kakuro-load-example').addEventListener('click', loadExample);
        $('#kakuro-clear').addEventListener('click', clearAll);
        $('#kakuro-solve').addEventListener('click', solve);
        buildGrid();
    });
})();
