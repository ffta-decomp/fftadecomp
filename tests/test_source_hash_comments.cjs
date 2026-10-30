const test = require('node:test');
const assert = require('node:assert/strict');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const publish = require('../.github/scripts/comment-source-hash-results.cjs');

test('posts only to matching open PRs and deduplicates the run attempt', async () => {
  const directory = fs.mkdtempSync(path.join(os.tmpdir(), 'source-hash-report-'));
  try {
    const reportPath = path.join(directory, 'report.md');
    fs.writeFileSync(reportPath, 'function: mismatch @user');
    const posted = [];
    let previous = [];
    const listAssociated = () => {};
    const listComments = () => {};
    const github = {
      rest: {
        repos: {listPullRequestsAssociatedWithCommit: listAssociated},
        pulls: {get: async ({pull_number}) => ({data: {state: 'open', head: {sha: pull_number === 1 ? 'abc' : 'other'}}})},
        issues: {listComments, createComment: async args => posted.push(args)},
      },
      paginate: async method => method === listAssociated ? [{number: 1}, {number: 2}] : previous,
    };
    const args = {github, core: {info() {}}, reportPath,
      context: {repo: {owner: 'o', repo: 'r'}, payload: {workflow_run: {
        id: 10, run_attempt: 1, conclusion: 'failure', head_sha: 'abc', html_url: 'https://example.test/run', pull_requests: []}}}};
    await publish(args);
    assert.equal(posted.length, 1);
    assert.equal(posted[0].issue_number, 1);
    assert.match(posted[0].body, /function: mismatch/);
    assert.ok(!posted[0].body.includes('@user'));
    previous = [{body: posted[0].body}];
    await publish(args);
    assert.equal(posted.length, 1);
  } finally { fs.rmSync(directory, {recursive: true, force: true}); }
});
