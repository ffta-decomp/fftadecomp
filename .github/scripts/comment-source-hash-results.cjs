const fs = require('node:fs');

// This runs from the default branch after the untrusted build has finished.
// Treat the artifact as text only and derive PR identity from GitHub, not it.
module.exports = async ({github, context, core, reportPath}) => {
  const run = context.payload.workflow_run;
  const {owner, repo} = context.repo;
  const associated = await github.paginate(github.rest.repos.listPullRequestsAssociatedWithCommit, {
    owner, repo, commit_sha: run.head_sha, per_page: 100,
  });
  const candidates = new Set([...(run.pull_requests || []).map(pr => pr.number),
    ...associated.map(pr => pr.number)]);
  const marker = `<!-- source-hash-run:${run.id}:${run.run_attempt} -->`;
  const status = run.conclusion || 'unknown';
  let report = 'No comparison report was produced; inspect the build logs.';
  if (fs.existsSync(reportPath)) report = fs.readFileSync(reportPath, 'utf8');
  report = report.slice(0, 55000).replaceAll('@', '@\u200b');
  const body = `${marker}\nSource hash build: **${status}** ([run](${run.html_url})).\n\n${report}`;
  for (const pull_number of candidates) {
    const {data: pr} = await github.rest.pulls.get({owner, repo, pull_number});
    if (pr.state !== 'open' || (pr.head.sha !== run.head_sha && pr.merge_commit_sha !== run.head_sha)) continue;
    const comments = await github.paginate(github.rest.issues.listComments, {
      owner, repo, issue_number: pull_number, per_page: 100,
    });
    if (comments.some(comment => comment.body?.includes(marker))) continue;
    await github.rest.issues.createComment({owner, repo, issue_number: pull_number, body});
    core.info(`Posted source hash results to PR #${pull_number}`);
  }
};
