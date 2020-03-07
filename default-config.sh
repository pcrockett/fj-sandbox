#!/usr/bin/env bash

set -Eeuo pipefail

# To override any of these defaults, create a new script in this directory
# called "sandbox-config.sh" and re-export the environment variables you want
# to override.

export FJSB_SCREEN_SIZE="800x600"
export FJSB_SANDBOX_ROOT=~/sandboxes
export FJSB_NET="eth0"
