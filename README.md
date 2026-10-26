# MP3 Tag Reader & Editor

A command-line ID3 tag reader and editor written in C with **no external
libraries** — it parses the raw `ID3v2` header and frames itself, then rewrites
the file.

## Usage

```
./mp3 -h
       Display the help menu

./mp3 -v <file_name.mp3>
       View the MP3 tag details

./mp3 -e <modifier> <new_value> <file_name.mp3>
       Edit an MP3 tag
```

### Edit modifiers

| Modifier | Field |
| --- | --- |
| `-t` | Title |
| `-a` | Artist |
| `-A` | Album |
| `-y` | Year |
| `-g` | Genre |
| `-c` | Comment |

### Examples

```sh
./mp3 -v replace_with_your_input.mp3
./mp3 -e -t "Blinding Lights" replace_with_your_input.mp3
./mp3 -e -a "The Weeknd" replace_with_your_input.mp3
```

## Build

```sh
gcc -o mp3 main.c validate.c view.c edit.c help.c
./mp3 -h
```

> **Heads-up:** editing happens **in place**. The program writes the updated
> audio to `temp.mp3`, deletes your original file and renames the temporary file
> over it. Always keep a backup of the file you edit.

## How it works

1. `validate.c` checks the argument count, the `.mp3` extension and that the
   file can be opened.
2. `view.c` reads the `ID3` header, computes the tag size from the four
   sync-safe size bytes and walks each frame (`frame id` + size + flags +
   encoding + payload), printing the known text frames.
3. `edit.c` copies the file frame by frame, replacing the payload of the target
   frame and recomputing the frame and header sizes, then swaps the temporary
   file into place.
4. `help.c` prints the usage screen.

## Project structure

| File | Purpose |
| --- | --- |
| `main.h` | `Mp3_info` / `frame_data` structs and prototypes |
| `main.c` | Driver: dispatches to help, view or edit |
| `validate.c` | Argument and extension validation |
| `view.c` | Read and print ID3 frames |
| `edit.c` | Rewrite a frame and update sizes |
| `help.c` | Help / usage text |
| `replace_with_your_input.mp3` | Sample song for testing — swap in your own |

> The bundled sample is only there so the tool can be run immediately. Replace
> `replace_with_your_input.mp3` with any `.mp3` of your own.
