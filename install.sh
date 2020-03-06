#!/usr/bin/env bash

# This script is based on the template here:
#
#     https://gist.github.com/pcrockett/8e04641f8473081c3a93de744873f787
#
# Useful links when writing a script:
#
# Shellcheck: https://github.com/koalaman/shellcheck
# vscode-shellcheck: https://github.com/timonwong/vscode-shellcheck
# https://blog.yossarian.net/2020/01/23/Anybody-can-write-good-bash-with-a-little-effort
#

# https://vaneyckt.io/posts/safer_bash_scripts_with_set_euxo_pipefail/
set -Eeuo pipefail

[[ "${BASH_VERSINFO[0]}" -lt 4 ]] && echo "Bash >= 4 required" && exit 1

SCRIPT_DIR=$(dirname "$(readlink -f "$0")")

BIN_DIR=~/.local/bin
if [ ! -d "$BIN_DIR" ]; then
    mkdir "$BIN_DIR"
fi

ln -s "$SCRIPT_DIR/new-sandbox" "$BIN_DIR/new-sandbox" || true
ln -s "$SCRIPT_DIR/remove-sandbox" "$BIN_DIR/remove-sandbox" || true

echo "Run \"new-sandbox <sandbox-name>\" to create new sandboxes."
