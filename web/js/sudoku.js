(function () {
    const EXAMPLE = {
        boxSize: 3,
        grid: [
            0, 3, 0, 6, 0, 0, 1, 9, 0,
            0, 0, 2, 0, 0, 0, 7, 0, 0,
            0, 9, 7, 0, 0, 2, 0, 6, 0,
            0, 0, 0, 0, 0, 5, 0, 0, 0,
            6, 0, 0, 2, 9, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 4, 0, 7,
            4, 0, 1, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 8, 9, 0, 0, 3,
            0, 8, 9, 5, 0, 0, 0, 1, 0,
        ],
    };

    let boxSize = 3;
    let inputs = [];

    function n() {
        return boxSize * boxSize;
    }

    function setStatus(message, kind) {
        const status = $('#sudoku-status');
        status.textContent = message;
        status.className = 'status-message' + (kind ? ' ' + kind : '');
    }

    function buildGrid() {
        const N = n();
        const grid = $('#sudoku-grid');
        grid.innerHTML = '';
        grid.style.gridTemplateColumns = `repeat(${N}, 38px)`;
        inputs = [];

        for (let row = 0; row < N; row++) {
            for (let col = 0; col < N; col++) {
                const input = el('input', {
                    type: 'number',
                    min: '1',
                    max: String(N),
                    class: 'value-input',
                });
                input.addEventListener('input', () => {
                    input.classList.remove('given', 'solved-value');
                    let value = parseInt(input.value, 10);
                    if (Number.isNaN(value)) {
                        input.value = '';
                        return;
                    }
                    value = Math.max(1, Math.min(N, value));
                    input.value = String(value);
                });

                const cell = el('div', { class: 'cell' }, [input]);
                const isLastCol = col === N - 1;
                const isLastRow = row === N - 1;
                cell.style.borderRight = isLastCol
                    ? 'none'
                    : (col + 1) % boxSize === 0
                      ? '3px solid var(--text)'
                      : '';
                cell.style.borderBottom = isLastRow
                    ? 'none'
                    : (row + 1) % boxSize === 0
                      ? '3px solid var(--text)'
                      : '';
                grid.appendChild(cell);
                inputs.push(input);
            }
        }
        setStatus('', '');
    }

    function collectGrid() {
        return inputs.map((input) => {
            const value = parseInt(input.value, 10);
            return Number.isNaN(value) ? 0 : value;
        });
    }

    function clearGrid() {
        inputs.forEach((input) => {
            input.value = '';
            input.classList.remove('given', 'solved-value');
        });
        setStatus('', '');
    }

    function loadExample() {
        boxSize = EXAMPLE.boxSize;
        $('#sudoku-boxsize').value = String(boxSize);
        buildGrid();
        EXAMPLE.grid.forEach((value, i) => {
            if (value !== 0) {
                inputs[i].value = String(value);
                inputs[i].classList.add('given');
            }
        });
    }

    async function solve() {
        const N = n();
        const grid = collectGrid();
        const wasGiven = grid.map((v) => v !== 0);

        setStatus('Solving…', '');
        const result = await window.PuzzleSolversBridge.solveSudoku(grid, boxSize);

        if (!result.solved) {
            setStatus('No solution found for this grid.', 'error');
            return;
        }

        result.grid.forEach((value, i) => {
            inputs[i].value = String(value);
            inputs[i].classList.toggle('given', wasGiven[i]);
            inputs[i].classList.toggle('solved-value', !wasGiven[i]);
        });
        setStatus('Solved!', 'success');
    }

    document.addEventListener('DOMContentLoaded', () => {
        $('#sudoku-boxsize').addEventListener('change', (e) => {
            const value = Math.max(2, Math.min(4, parseInt(e.target.value, 10) || 3));
            boxSize = value;
            e.target.value = String(value);
            buildGrid();
        });
        $('#sudoku-load-example').addEventListener('click', loadExample);
        $('#sudoku-clear').addEventListener('click', clearGrid);
        $('#sudoku-solve').addEventListener('click', solve);
        buildGrid();
    });
})();
