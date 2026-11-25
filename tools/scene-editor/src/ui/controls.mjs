import { t } from '../i18n.mjs';

export const $ = selector => document.querySelector(selector);
export const serialize = value => JSON.stringify(value, null, 2);
export function el(tag, text, className) {
  const node = document.createElement(tag);
  if (text !== undefined) node.textContent = text;
  if (className) node.className = className;
  return node;
}

export function button(text, action, className) {
  const node = el('button', text, className);
  node.type = 'button';
  node.addEventListener('click', action);
  return node;
}

export function notice(text, error = false) {
  const node = $('#notice');
  node.textContent = text;
  node.classList.toggle('error', error);
  node.hidden = false;
  clearTimeout(notice.timer);
  notice.timer = setTimeout(() => { node.hidden = true; }, error ? 9000 : 3200);
}

export function handle(action) {
  return async (...args) => {
    try { await action(...args); }
    catch (error) { notice(error.message, true); }
  };
}

export function download(name, content, type) {
  const url = URL.createObjectURL(new Blob([content], { type }));
  const link = el('a');
  link.href = url;
  link.download = name;
  link.click();
  setTimeout(() => URL.revokeObjectURL(url), 3000);
}

export function downloadJson(name, value) {
  download(name, serialize(value) + '\n', 'application/json');
}

export function section(title, ...actions) {
  const bar = el('div', undefined, 'section-bar');
  const group = el('div', undefined, 'buttons');
  group.append(...actions);
  bar.append(el('h2', title), group);
  return bar;
}

export function table(headers, rows) {
  const wrap = el('div', undefined, 'table-wrap');
  if (headers.at(-1) === '') wrap.classList.add('row-actions');
  const data = el('table');
  const head = el('thead');
  const heading = el('tr');
  headers.forEach(label => heading.append(el('th', label)));
  head.append(heading);
  const body = el('tbody');
  for (const cells of rows) {
    const row = el('tr');
    for (const content of cells) {
      const cell = el('td');
      cell.append(content ?? '');
      row.append(cell);
    }
    body.append(row);
  }
  data.append(head, body);
  wrap.append(data);
  return wrap;
}

export function dialog(title, elements, apply, applyLabel = t('应用')) {
  $('#edit-title').textContent = title;
  $('#edit-fields').replaceChildren(...elements);
  $('#edit-error').hidden = true;
  $('#apply-edit').hidden = !apply;
  $('#apply-edit').textContent = applyLabel;
  $('#edit-form').onsubmit = async event => {
    event.preventDefault();
    if (!apply) return;
    try { await apply(); $('#editor').close(); }
    catch (error) { $('#edit-error').textContent = error.message; $('#edit-error').hidden = false; }
  };
  if (!$('#editor').open) $('#editor').showModal();
}

export function field(label, input) {
  const container = el('label', label);
  container.append(input);
  return container;
}

export function number(label, value, min, max) {
  const input = el('input');
  Object.assign(input, { type: 'number', value, min, max, required: true });
  return { input, label: field(label, input) };
}

export function textarea(label, value, rows = 10) {
  const input = el('textarea');
  Object.assign(input, { value, rows, spellcheck: false });
  return { input, label: field(label, input) };
}
