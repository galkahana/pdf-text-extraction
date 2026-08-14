#!/usr/bin/env bash
# Downloads the latest pdf-text-extraction release binary for the current OS
# into ./bin/ next to this script. Safe to re-run (overwrites any previous download).
set -euo pipefail

REPO="galkahana/pdf-text-extraction"
EXE_NAME="textextraction"
ARCHIVE_EXE_NAME="TextExtraction"

SKILL_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BIN_DIR="$SKILL_DIR/bin"
mkdir -p "$BIN_DIR"

case "$(uname -s)" in
  Darwin) OS_KEY="mac" ;;
  Linux) OS_KEY="linux" ;;
  MINGW*|MSYS*|CYGWIN*) OS_KEY="win" ; ARCHIVE_EXE_NAME="TextExtraction.exe" ; EXE_NAME="textextraction.exe" ;;
  *) echo "install.sh: unsupported OS '$(uname -s)'" >&2; exit 1 ;;
esac

echo "install.sh: looking up latest $REPO release..." >&2
RELEASE_JSON="$(curl -sL "https://api.github.com/repos/$REPO/releases/latest")"
ASSET_URL="$(printf '%s\n' "$RELEASE_JSON" | grep -o "\"browser_download_url\": *\"[^\"]*${OS_KEY}[^\"]*\"" | head -1 | sed -E 's/.*"(https[^"]+)".*/\1/')"

if [ -z "$ASSET_URL" ]; then
  echo "install.sh: no '$OS_KEY' asset found in the latest $REPO release" >&2
  exit 1
fi

TMP_DIR="$(mktemp -d)"
trap 'rm -rf "$TMP_DIR"' EXIT

echo "install.sh: downloading $ASSET_URL" >&2
curl -sL -o "$TMP_DIR/archive.tar.gz" "$ASSET_URL"
tar xzf "$TMP_DIR/archive.tar.gz" -C "$TMP_DIR"

SRC_BIN="$TMP_DIR/$ARCHIVE_EXE_NAME"
if [ ! -f "$SRC_BIN" ]; then
  # archive layout changed upstream - fall back to the only file extracted
  SRC_BIN="$(find "$TMP_DIR" -maxdepth 1 -type f ! -name 'archive.tar.gz' | head -1)"
fi
if [ -z "$SRC_BIN" ] || [ ! -f "$SRC_BIN" ]; then
  echo "install.sh: could not find the executable inside the downloaded archive" >&2
  exit 1
fi

cp "$SRC_BIN" "$BIN_DIR/$EXE_NAME"
chmod +x "$BIN_DIR/$EXE_NAME"

echo "install.sh: installed to $BIN_DIR/$EXE_NAME" >&2
echo "$BIN_DIR/$EXE_NAME"
