# Canvas Drawing Application

## Overview

This project is a terminal-based canvas drawing application written in C. It allows users to draw various shapes, lines, and ellipses with multiple shades and provides functionalities such as copying and pasting sections of the canvas. This application can serve as a basic graphical toolkit for educational purposes or simple terminal-based art projects.

## Features

* **Canvas Management:**

  * Initialize and clear the canvas.
  * Display the canvas with numerical representations of shades.

* **Drawing Functions:**

  * Draw straight lines in multiple directions.
  * Draw filled squares in different orientations.
  * Draw ellipses using two focus points.

* **Shading:**

  * Supports various shades (BLACK, DARK, GREY, LIGHT, WHITE).
  * Provides an eraser functionality.

* **Advanced Editing:**

  * Negative length handling for lines and squares.
  * Copy and paste sections of the canvas.

* **Boundary Handling:**

  * Ensures drawings do not exceed canvas boundaries.

## Usage

The program reads commands from standard input, with each command specifying the type of action to perform:

| Command | Description            |
| ------- | ---------------------- |
| `0`     | Draw ellipse           |
| `1`     | Draw line              |
| `2`     | Draw square            |
| `3`     | Change shade           |
| `4`     | Copy and paste section |

### Command Format Examples

* **Draw ellipse:**

  ```
  0 focus_1_row focus_1_col focus_2_row focus_2_col length fill
  ```

* **Draw line:**

  ```
  1 start_row start_col length direction
  ```

* **Draw square:**

  ```
  2 start_row start_col length direction
  ```

* **Change shade:**

  ```
  3 new_shade
  ```

* **Copy and Paste:**

  ```
  4 start_row start_col length direction target_row target_col
  ```

## Example Input

```
1 10 10 5 90
3 2
2 5 5 3 45
0 8 8 10 10 5 1
4 5 5 3 45 12 12
```

## Compilation and Execution

Compile the program using `gcc`:

```bash
gcc -o canvas_app canvas_app.c -lm
```

Run the program:

```bash
./canvas_app
```

Enter commands as described above and terminate the input with an EOF (Ctrl+D).

## Author

William Djong
