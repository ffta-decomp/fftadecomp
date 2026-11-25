/** Built-in tools register independently of the shell and share its project session. */
export function createPanelRegistry(definitions) {
  const indexed = new Map();
  for (const panel of definitions) {
    if (!/^[a-z][a-z-]*$/.test(panel.id) || !panel.label || typeof panel.render !== 'function') {
      throw new Error('Invalid workspace panel');
    }
    if (indexed.has(panel.id)) throw new Error(`Duplicate workspace panel: ${panel.id}`);
    indexed.set(panel.id, Object.freeze({ ...panel }));
  }
  return Object.freeze({
    list: Object.freeze([...indexed.values()]),
    get: id => indexed.get(id),
  });
}
