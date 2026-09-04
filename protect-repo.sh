#!/bin/bash
# protect-repo.sh — Apply standard 42 cpp lab branch protection to a GitHub repo
#
# Usage:
#   ./protect-repo.sh <org/repo> [branch]
#
# Examples:
#   ./protect-repo.sh lab-cpp/cpp05
#   ./protect-repo.sh lab-cpp/cpp06 master
#
# Requirements:
#   - gh CLI authenticated: gh auth status
#   - Admin role on the target repo
#   - Repo must be PUBLIC (branch protection on private repos requires GitHub Pro)

set -euo pipefail

REPO="${1:-}"
BRANCH="${2:-master}"

if [[ -z "$REPO" ]]; then
  echo " Usage: $0 <org/repo> [branch]"
  exit 1
fi

echo "🔍 Checking visibility of $REPO..."
VISIBILITY=$(gh api "repos/$REPO" --jq '.visibility' 2>/dev/null || echo "error")

if [[ "$VISIBILITY" == "private" ]]; then
  echo "  Repo is private — branch protection requires GitHub Pro."
  read -rp "   Make it public now? [y/N] " confirm
  if [[ "$confirm" =~ ^[Yy]$ ]]; then
    gh api --method PATCH "repos/$REPO" -f visibility=public --jq '" Now \(.visibility)"'
  else
    echo "Aborted."
    exit 1
  fi
elif [[ "$VISIBILITY" == "error" ]]; then
  echo " Repo not found or no access: $REPO"
  exit 1
else
  echo " Repo is public"
fi

echo ""
echo " Applying branch protection to $REPO → $BRANCH..."

gh api \
  --method PUT \
  -H "Accept: application/vnd.github+json" \
  "/repos/$REPO/branches/$BRANCH/protection" \
  --input - << 'EOF'
{
  "required_status_checks": {
    "strict": true,
    "contexts": ["CI Gate"]
  },
  "enforce_admins": false,
  "required_pull_request_reviews": {
    "dismiss_stale_reviews": true,
    "require_code_owner_reviews": false,
    "required_approving_review_count": 1
  },
  "restrictions": null,
  "allow_force_pushes": false,
  "allow_deletions": false,
  "block_creations": false,
  "required_linear_history": false
}
EOF

echo ""
echo "  Configuring merge settings..."
gh api --method PATCH "repos/$REPO" \
  -F delete_branch_on_merge=true \
  -F allow_squash_merge=true \
  -F allow_merge_commit=false \
  -F allow_rebase_merge=true \
  --jq '"  • delete_branch_on_merge: \(.delete_branch_on_merge)\n  • squash_merge: \(.allow_squash_merge)\n  • merge_commit: \(.allow_merge_commit)"'

echo ""
echo " Done $REPO/$BRANCH is protected."
echo ""
echo " Rules applied:"
echo "   ✓ CI Gate must pass before merge"
echo "   ✓ Strict: branch must be up-to-date with $BRANCH"
echo "   ✓ 1 approving review required"
echo "   ✓ Stale reviews dismissed on new push"
echo "   ✓ Force push blocked"
echo "   ✓ Branch deletion blocked"
echo "   ✓ Feature branches auto-deleted after merge"
