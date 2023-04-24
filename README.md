# Differencator

Differencator is a C++ program that reads any mathematical function from a file and calculates its derivative. The output is presented in the form of a PDF file, which is designed as a mock lab work on Mathematical Analysis. The program also provides a GraphViz dump in the form of a tree with the original expression, differentiated expression and the simplified differentiated expression.

## How to use

1. Clone the repository to your local machine:

   ```
   git clone https://github.com/vorontsov-amd/Differencator.git
   ```

2. Open the terminal and go to the directory with the cloned repository:

   ```
   cd Differencator
   ```

3. Compile the program:

   ```
   make
   ```

4. Run the program:

   ```
   ./differencator input.txt
   ```

   Replace `input.txt` with the name of your input file.

5. Check the output files:

   - The PDF file will be saved as `output.pdf`
   - The GraphViz dump will be saved as `dump.gv`

## Input file format

The input file should contain a single line with a mathematical expression in infix notation. The following operators are supported:

- Addition: `+`
- Subtraction: `-`
- Multiplication: `*`
- Division: `/`
- Power: `^`

The following functions are also supported:

- `sin(x)`
- `cos(x)`
- `tan(x)`
- `cot(x)`
- `sh(x)`
- `ch(x)`
- `th(x)`
- `cth(x)`
- `exp(x)`
- `log(x)`
- `ln(x)`

Example input file:

```
x^2 + sin(x) + 2*x
```

## Output file format

The output PDF file will contain a header with the name of the input file, the original expression, and its derivative. The GraphViz dump will contain a tree with the original expression, its derivative, and the simplified derivative.
A funnier version with prison jokes in previous commits.

## Dependencies

- C++ compiler
- GraphViz
- LaTeX

## License

This project is licensed under the MIT License. See the [LICENSE](https://github.com/vorontsov-amd/Differencator/blob/main/LICENSE) file for more information.
