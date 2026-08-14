---
name: pdf-text-extraction
description: Extract text (or tables) from a PDF by parsing its content streams directly via the `textextraction` CLI, instead of rendering pages to images and reading them visually. Use whenever the user asks to extract, read, or dump text from a PDF — especially larger or multi-page PDFs where speed/accuracy matters. Only works on text-based PDFs; scanned/image-only PDFs have no extractable text and need normal (vision-based) reading instead.
user-invocable: false
---

# PDF text/table extraction via `textextraction`

Wraps the `textextraction` CLI (https://github.com/galkahana/pdf-text-extraction), which parses PDF content streams directly (no rendering, no OCR) to pull out text or tables. This is faster and more precise than reading a PDF by rendering pages to images, for any PDF that actually contains text objects. It cannot help with scanned/image-only PDFs — there's no text to parse, so fall back to normal file reading (vision) for those.

## 1. Locate the executable

Try in order, stop at the first that resolves:
1. `command -v textextraction`
2. `bin/textextraction` next to this SKILL.md (i.e. `<dir containing this file>/bin/textextraction`)

## 2. If neither is found, install it

Ask the user for permission first — e.g. "textextraction isn't installed, ok to download the prebuilt binary from the pdf-text-extraction GitHub releases?" Don't run the installer without an explicit yes.

Once approved:
```bash
bash "<dir containing this file>/install.sh"
```
This downloads the latest release archive for the current OS from https://github.com/galkahana/pdf-text-extraction/releases, extracts it, and places the executable at `<dir containing this file>/bin/textextraction`. It prints that path on success — use it for step 3.

Release binaries currently cover macOS (arm64), Linux, and Windows. If `install.sh` fails (unsupported OS/arch, no network, etc.), fall back to a source build — again only after the user confirms they're OK with it (needs a C++ toolchain + cmake, slower):
```bash
cmake -S . -B build && cmake --build build --config Release --target install
cmake --install build --prefix ./etc/install --component executables
```
(run from a checkout of the pdf-text-extraction repo — clone it first if none exists locally). The resulting binary is at `./etc/install/bin/textextraction`.

## 3. Usage

```
textextraction filepath [options]
```

| Option | Meaning |
|---|---|
| `-s, --start <d>` | start page index (negative = counted back from the last page) |
| `-e, --end <d>` | end page index (negative = counted back from the last page) |
| `-b, --bidi <RTL\|LTR>` | apply bidi reversal for right-to-left text; give the document's base direction |
| `-p, --spacing <BOTH\|HOR\|VER\|NONE>` | inter-glyph spacing heuristic, default BOTH |
| `-t, --tables` | extract tables as CSV instead of plain text |
| `-o, --output <path>` | write result to a file instead of stdout |
| `-q, --quiet` | suppress non-error/warning output |
| `-d, --debug <path>` | write a debug output file |

Common tasks:
- **Dump all text**: `textextraction file.pdf` — read the stdout directly, don't bother with `-o` unless the user wants a saved copy.
- **A page range**: `textextraction file.pdf -s 0 -e 4` (or negative indices from the end, e.g. `-s -3` for the last 3 pages)
- **Tables as CSV**: `textextraction file.pdf -t -o out.csv`

Notes:
- No password option exists — if the PDF is encrypted, decrypt it first (see the sibling `pdf-recrypt` skill/tool if available) before extracting text.
- A non-zero exit / stderr output usually means a malformed or unreadable PDF — surface that to the user.
- If the extracted text comes back empty or clearly garbled for a PDF that should have text, it may be a scanned/image-only PDF — fall back to normal (vision-based) reading rather than retrying options blindly.
