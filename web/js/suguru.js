(function () {
    const EXAMPLE = {
        rows: 9,
        cols: 9,
        values: [
            0, 3, 7, 2, 0, 5, 4, 0, 0,
            1, 0, 0, 6, 0, 2, 3, 2, 0,
            4, 3, 2, 0, 4, 0, 4, 0, 3,
            0, 0, 0, 0, 2, 0, 0, 6, 0,
            7, 1, 7, 6, 0, 3, 5, 0, 7,
            0, 0, 0, 1, 4, 0, 6, 0, 2,
            1, 0, 0, 0, 7, 3, 0, 7, 1,
            2, 6, 7, 0, 1, 0, 0, 6, 0,
            4, 0, 0, 3, 0, 0, 1, 0, 5,
        ],
        regions: [
            1, 2, 2, 2, 2, 3, 3, 3, 3,
            1, 2, 2, 2, 4, 4, 4, 3, 5,
            6, 6, 6, 6, 7, 5, 5, 5, 5,
            6, 8, 8, 8, 7, 7, 5, 5, 9,
            6, 6, 8, 7, 7, 7, 9, 9, 9,
            10, 10, 8, 8, 11, 7, 9, 9, 9,
            10, 12, 12, 8, 11, 13, 13, 13, 13,
            10, 12, 12, 12, 11, 11, 11, 13, 13,
            10, 12, 12, 11, 11, 14, 14, 14, 13,
        ],
    };

    let rows = 9;
    let cols = 9;
    let values = [];
    let regions = [];
    let cells = [];
    let inputs = [];
    let mode = 'paint';
    let activeRegion = 1;
    let paletteIds = [1];
    let isPainting = false;

    function idx(r, c) {
        return r * cols + c;
    }

    function setStatus(message, kind) {
        const status = $('#suguru-status');
        status.textContent = message;
        status.className = 'status-message' + (kind ? ' ' + kind : '');
    }

    function resetState(keepPalette) {
        values = new Array(rows * cols).fill(0);
        regions = new Array(rows * cols).fill(0);
        if (!keepPalette) {
            paletteIds = [1];
            activeRegion = 1;
        }
    }

    function paintCell(i) {
        regions[i] = activeRegion;
        updateGridVisuals();
    }

    function buildGrid() {
        const grid = $('#suguru-grid');
        grid.innerHTML = '';
        grid.style.gridTemplateColumns = `repeat(${cols}, 52px)`;
        cells = [];
        inputs = [];

        for (let r = 0; r < rows; r++) {
            for (let c = 0; c < cols; c++) {
                const i = idx(r, c);
                const input = el('input', { type: 'number', min: '1', max: '9', class: 'value-input' });
                input.addEventListener('input', () => {
                    input.classList.remove('given', 'solved-value');
                    const v = parseInt(input.value, 10);
                    values[i] = Number.isNaN(v) ? 0 : v;
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
        updateGridVisuals();
        setStatus('', '');
    }

    function updateGridVisuals() {
        for (let r = 0; r < rows; r++) {
            for (let c = 0; c < cols; c++) {
                const i = idx(r, c);
                const cell = cells[i];
                const region = regions[i];
                cell.style.background = colorForRegion(region);

                const isLastCol = c === cols - 1;
                const isLastRow = r === rows - 1;
                const right = isLastCol ? null : regions[idx(r, c + 1)];
                const bottom = isLastRow ? null : regions[idx(r + 1, c)];
                cell.style.borderRight = isLastCol ? 'none' : right !== region ? '2px solid var(--text)' : '';
                cell.style.borderBottom = isLastRow ? 'none' : bottom !== region ? '2px solid var(--text)' : '';
            }
        }
        inputs.forEach((input) => {
            input.style.pointerEvents = mode === 'paint' ? 'none' : 'auto';
            input.style.opacity = mode === 'paint' ? '0.35' : '1';
        });
    }

    function renderPalette() {
        const palette = $('#suguru-palette');
        palette.innerHTML = '';

        const eraser = el('div', { class: 'swatch eraser' + (activeRegion === 0 ? ' active' : ''), title: 'Unassign' });
        eraser.addEventListener('click', () => {
            activeRegion = 0;
            renderPalette();
        });
        palette.appendChild(eraser);

        paletteIds.forEach((id) => {
            const swatch = el('div', {
                class: 'swatch' + (activeRegion === id ? ' active' : ''),
                title: 'Region ' + id,
            });
            swatch.style.background = colorForRegion(id).replace('0.35)', '0.9)');
            swatch.addEventListener('click', () => {
                activeRegion = id;
                renderPalette();
            });
            palette.appendChild(swatch);
        });

        const addBtn = el('button', { type: 'button', title: 'New region' }, [document.createTextNode('+')]);
        addBtn.addEventListener('click', () => {
            const nextId = Math.max(0, ...paletteIds) + 1;
            paletteIds.push(nextId);
            activeRegion = nextId;
            renderPalette();
        });
        palette.appendChild(addBtn);
    }

    function setMode(newMode) {
        mode = newMode;
        $('#suguru-mode-paint').classList.toggle('active', mode === 'paint');
        $('#suguru-mode-fill').classList.toggle('active', mode === 'fill');
        updateGridVisuals();
    }

    function loadExample() {
        rows = EXAMPLE.rows;
        cols = EXAMPLE.cols;
        $('#suguru-rows').value = String(rows);
        $('#suguru-cols').value = String(cols);
        values = EXAMPLE.values.slice();
        regions = EXAMPLE.regions.slice();
        paletteIds = Array.from(new Set(regions)).filter((id) => id !== 0).sort((a, b) => a - b);
        activeRegion = paletteIds[0] || 1;

        buildGrid();
        values.forEach((v, i) => {
            if (v !== 0) {
                inputs[i].value = String(v);
                inputs[i].classList.add('given');
            }
        });
        renderPalette();
        setMode('fill');
    }

    function clearAll() {
        resetState(false);
        buildGrid();
        renderPalette();
    }

    async function solve() {
        // any unpainted cell becomes its own singleton region (forces digit 1 there).
        const solveRegions = regions.slice();
        let nextId = Math.max(0, ...solveRegions) + 1;
        for (let i = 0; i < solveRegions.length; i++) {
            if (solveRegions[i] === 0) solveRegions[i] = nextId++;
        }

        const wasGiven = values.map((v) => v !== 0);
        setStatus('Solving…', '');
        const result = await window.PuzzleSolversBridge.solveSuguru(values, solveRegions, rows, cols);

        if (!result.solved) {
            setStatus('No solution found for this grid.', 'error');
            return;
        }

        result.values.forEach((value, i) => {
            inputs[i].value = String(value);
            inputs[i].classList.toggle('given', wasGiven[i]);
            inputs[i].classList.toggle('solved-value', !wasGiven[i]);
        });
        setStatus('Solved!', 'success');
    }

    function resize() {
        rows = Math.max(2, Math.min(16, parseInt($('#suguru-rows').value, 10) || 9));
        cols = Math.max(2, Math.min(16, parseInt($('#suguru-cols').value, 10) || 9));
        $('#suguru-rows').value = String(rows);
        $('#suguru-cols').value = String(cols);
        resetState(false);
        buildGrid();
        renderPalette();
    }

    document.addEventListener('DOMContentLoaded', () => {
        resetState(false);
        $('#suguru-rows').addEventListener('change', resize);
        $('#suguru-cols').addEventListener('change', resize);
        $('#suguru-mode-paint').addEventListener('click', () => setMode('paint'));
        $('#suguru-mode-fill').addEventListener('click', () => setMode('fill'));
        $('#suguru-load-example').addEventListener('click', loadExample);
        $('#suguru-clear').addEventListener('click', clearAll);
        $('#suguru-solve').addEventListener('click', solve);
        document.addEventListener('mouseup', () => (isPainting = false));

        buildGrid();
        renderPalette();
        setMode('paint');
    });
})();
