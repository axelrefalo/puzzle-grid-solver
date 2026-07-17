function $(selector, root = document) {
    return root.querySelector(selector);
}

function el(tag, props = {}, children = []) {
    const node = document.createElement(tag);
    Object.entries(props).forEach(([key, value]) => {
        if (key === 'class') node.className = value;
        else if (key === 'dataset') Object.assign(node.dataset, value);
        else if (key.startsWith('on') && typeof value === 'function') node.addEventListener(key.slice(2), value);
        else node.setAttribute(key, value);
    });
    children.forEach((child) => node.appendChild(child));
    return node;
}

// Deterministic color for a region/cage id (0 is reserved for "unassigned").
// Unassigned cells get an opaque neutral fill (not "transparent") so the
// grid's own gap color doesn't bleed through and erase the cell borders.
function colorForRegion(id) {
    if (!id) return 'var(--panel-bg)';
    const hue = (id * 47) % 360;
    return `hsl(${hue}deg 70% 55% / 0.35)`;
}

function initTabs() {
    const buttons = document.querySelectorAll('.tab-button');
    const panels = document.querySelectorAll('.panel');
    buttons.forEach((btn) => {
        btn.addEventListener('click', () => {
            buttons.forEach((b) => b.classList.remove('active'));
            panels.forEach((p) => (p.hidden = true));
            btn.classList.add('active');
            document.getElementById(btn.dataset.target).hidden = false;
        });
    });
}

document.addEventListener('DOMContentLoaded', initTabs);
