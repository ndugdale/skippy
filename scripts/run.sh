#!/bin/sh

SCRIPT_DIR="$(dirname "$0")"
FILE="$SCRIPT_DIR/../dist/index.html"

if [ -f "$FILE" ]; then
    emrun "$FILE"
else
    echo "Error: $FILE not found. Please build project first."
    exit 1
fi
