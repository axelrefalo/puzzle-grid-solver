(function () {
    // Sums are given in the same redundant-per-cell format as the original
    // src/KillerSudokuSolver.cpp SudokuKillerGridEasy1 table (the cage's sum
    // repeated across every cell of that cage) so there's no separate mapping
    // to keep in sync by hand.
    const EXAMPLE = {
        boxSize: 3,
        cages: [
            1, 2, 2, 3, 3, 4, 5, 5, 5,
            1, 6, 7, 8, 8, 4, 9, 10, 10,
            11, 6, 7, 12, 4, 4, 9, 13, 14,
            11, 15, 15, 12, 16, 17, 18, 13, 14,
            19, 19, 20, 20, 16, 17, 18, 21, 14,
            22, 22, 20, 23, 23, 24, 24, 21, 25,
            26, 27, 27, 28, 29, 29, 30, 30, 25,
            26, 26, 31, 28, 32, 33, 34, 30, 30,
            35, 35, 31, 31, 32, 33, 34, 36, 36,
        ],
        sumsPerCell: [
            13, 7, 7, 12, 12, 17, 20, 20, 20,
            13, 9, 11, 9, 9, 17, 11, 10, 10,
            13, 9, 11, 16, 17, 17, 11, 10, 6,
            13, 6, 6, 16, 12, 9, 11, 10, 6,
            12, 12, 12, 12, 12, 9, 11, 12, 6,
            13, 13, 12, 6, 6, 4, 4, 12, 15,
            11, 10, 10, 7, 17, 17, 19, 19, 15,
            11, 11, 14, 7, 7, 13, 10, 19, 19,
            11, 11, 14, 14, 7, 13, 10, 10, 10,
        ],
    };

    let boxSize = 3;
    let cages = [];
    let givens = [];
    let sumsByCage = {};
    let cells = [];
    let inputs = [];
    let mode = 'paint';
    let activeCage = 1;
    let paletteIds = [1];
    let isPainting = false;

    function n() {
        return boxSize * boxSize;
    }

    function setStatus(message, kind) {
        const status = $('#killer-status');
        status.textContent = message;
        status.className = 'status-message' + (kind ? ' ' + kind : '');
    }

    function resetState() {
        const N = n();
        cages = new Array(N * N).fill(0);
        givens = new Array(N * N).fill(0);
        sumsByCage = {};
        paletteIds = [1];
        activeCage = 1;
    }

    function paintCell(i) {
        cages[i] = activeCage;
        renderOverlays();
    }

    function buildGrid() {
        const N = n();
        const grid = $('#killer-grid');
        grid.innerHTML = '';
        grid.style.gridTemplateColumns = `repeat(${N}, 38px)`;
        cells = [];
        inputs = [];

        for (let row = 0; row < N; row++) {
            for (let col = 0; col < N; col++) {
                const i = row * N + col;
                const input = el('input', { type: 'number', min: '1', max: String(N), class: 'value-input' });
                input.addEventListener('input', () => {
                    input.classList.remove('given', 'solved-value');
                    const v = parseInt(input.value, 10);
                    givens[i] = Number.isNaN(v) ? 0 : v;
                });

                const cell = el('div', { class: 'cell' }, [input]);

                cell.addEventListener('mousedown', (e) => {
                    if (mode !== 'paint') return;
                    e.preventDefault();
                    isPainting = true;
                    paintCell(i);
                });
                cell.addEventListener('mouseenter', () => {
                    if (mode === 'paint' && isPainting) paintCell(i);
                });

                grid.appendChild(cell);
                cells.push(cell);
                inputs.push(input);
            }
        }
        renderOverlays();
        setStatus('', '');
    }

    function renderOverlays() {
        const N = n();
        cells.forEach((cell, i) => {
            const row = Math.floor(i / N);
            const col = i % N;
            cell.style.background = colorForRegion(cages[i]);

            const isLastCol = col === N - 1;
            const isLastRow = row === N - 1;
            const rightCageDiff = !isLastCol && cages[i] !== cages[i + 1];
            const bottomCageDiff = !isLastRow && cages[i] !== cages[i + N];
            const rightBoxEdge = !isLastCol && (col + 1) % boxSize === 0;
            const bottomBoxEdge = !isLastRow && (row + 1) % boxSize === 0;

            cell.style.borderRight = isLastCol ? 'none' : rightCageDiff || rightBoxEdge ? '3px solid var(--text)' : '';
            cell.style.borderBottom = isLastRow ? 'none' : bottomCageDiff || bottomBoxEdge ? '3px solid var(--text)' : '';

            const existingBadge = cell.querySelector('.cage-sum-badge');
            if (existingBadge) existingBadge.remove();
        });

        // one editable sum badge per cage, placed on its top-left-most cell
        const anchors = {};
        for (let row = 0; row < N; row++) {
            for (let col = 0; col < N; col++) {
                const i = row * N + col;
                const cage = cages[i];
                if (cage && !(cage in anchors)) anchors[cage] = i;
            }
        }

        Object.entries(anchors).forEach(([cageId, i]) => {
            const badge = el('input', {
                type: 'number',
                min: '1',
                class: 'cage-sum-badge',
                placeholder: 'Σ',
            });
            badge.value = sumsByCage[cageId] ?? '';
            badge.addEventListener('mousedown', (e) => e.stopPropagation());
            badge.addEventListener('input', () => {
                const v = parseInt(badge.value, 10);
                sumsByCage[cageId] = Number.isNaN(v) ? undefined : v;
            });
            cells[i].appendChild(badge);
        });

        inputs.forEach((input) => {
            input.style.pointerEvents = mode === 'paint' ? 'none' : 'auto';
            input.style.opacity = mode === 'paint' ? '0.35' : '1';
        });
    }

    function renderPalette() {
        const palette = $('#killer-palette');
        palette.innerHTML = '';

        const eraser = el('div', { class: 'swatch eraser' + (activeCage === 0 ? ' active' : ''), title: 'Unassign' });
        eraser.addEventListener('click', () => {
            activeCage = 0;
            renderPalette();
        });
        palette.appendChild(eraser);

        paletteIds.forEach((id) => {
            const swatch = el('div', { class: 'swatch' + (activeCage === id ? ' active' : ''), title: 'Cage ' + id });
            swatch.style.background = colorForRegion(id).replace('0.35)', '0.9)');
            swatch.addEventListener('click', () => {
                activeCage = id;
                renderPalette();
            });
            palette.appendChild(swatch);
        });

        const addBtn = el('button', { type: 'button', title: 'New cage' }, [document.createTextNode('+')]);
        addBtn.addEventListener('click', () => {
            const nextId = Math.max(0, ...paletteIds) + 1;
            paletteIds.push(nextId);
            activeCage = nextId;
            renderPalette();
        });
        palette.appendChild(addBtn);
    }

    function setMode(newMode) {
        mode = newMode;
        $('#killer-mode-paint').classList.toggle('active', mode === 'paint');
        $('#killer-mode-fill').classList.toggle('active', mode === 'fill');
        renderOverlays();
    }

    function loadExample() {
        boxSize = EXAMPLE.boxSize;
        $('#killer-boxsize').value = String(boxSize);
        resetState();
        cages = EXAMPLE.cages.slice();
        paletteIds = Array.from(new Set(cages)).sort((a, b) => a - b);
        activeCage = paletteIds[0] || 1;
        cages.forEach((id, i) => {
            if (!(id in sumsByCage)) sumsByCage[id] = EXAMPLE.sumsPerCell[i];
        });

        buildGrid();
        renderPalette();
        setMode('fill');
    }

    function clearAll() {
        resetState();
        buildGrid();
        renderPalette();
    }

    async function solve() {
        const N = n();

        // any unpainted cell becomes its own singleton cage; needs a sum too.
        const solveCages = cages.slice();
        let nextId = Math.max(0, ...solveCages) + 1;
        const missingSum = [];
        for (let i = 0; i < solveCages.length; i++) {
            if (solveCages[i] === 0) solveCages[i] = nextId++;
        }

        const distinctCages = Array.from(new Set(solveCages));
        distinctCages.forEach((id) => {
            if (!sumsByCage[id]) missingSum.push(id);
        });
        if (missingSum.length > 0) {
            setStatus('Every cage needs a sum before solving (paint mode, top-left badge).', 'error');
            return;
        }

        const sums = solveCages.map((id) => sumsByCage[id]);
        const wasGiven = givens.map((v) => v !== 0);

        setStatus('Solving…', '');
        const result = await window.PuzzleSolversBridge.solveKillerSudoku(sums, solveCages, givens, boxSize);

        if (!result.solved) {
            setStatus('No solution found for this grid.', 'error');
            return;
        }

        result.solution.forEach((value, i) => {
            inputs[i].value = String(value);
            inputs[i].classList.toggle('given', wasGiven[i]);
            inputs[i].classList.toggle('solved-value', !wasGiven[i]);
        });
        setStatus('Solved!', 'success');
    }

    function resize() {
        boxSize = Math.max(2, Math.min(4, parseInt($('#killer-boxsize').value, 10) || 3));
        $('#killer-boxsize').value = String(boxSize);
        resetState();
        buildGrid();
        renderPalette();
    }

    document.addEventListener('DOMContentLoaded', () => {
        resetState();
        $('#killer-boxsize').addEventListener('change', resize);
        $('#killer-mode-paint').addEventListener('click', () => setMode('paint'));
        $('#killer-mode-fill').addEventListener('click', () => setMode('fill'));
        $('#killer-load-example').addEventListener('click', loadExample);
        $('#killer-clear').addEventListener('click', clearAll);
        $('#killer-solve').addEventListener('click', solve);
        document.addEventListener('mouseup', () => (isPainting = false));

        buildGrid();
        renderPalette();
        setMode('paint');
    });
})();
