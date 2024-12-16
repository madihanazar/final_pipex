# pipex

A C program that recreates shell piping. Running

```sh
./pipex infile "cmd1" "cmd2" outfile
```

does the same thing as

```sh
< infile cmd1 | cmd2 > outfile
```

## Build

```sh
make          # builds ./pipex
make bonus    # builds ./pipex_bonus
make clean    # removes object files
make fclean   # removes object files and binaries
make re       # rebuilds from scratch
```

## Usage

```sh
./pipex infile "grep hello" "wc -l" outfile
```

### Bonus

Chain any number of commands:

```sh
./pipex_bonus infile "cat" "grep a" "sort" "uniq" outfile
# same as: < infile cat | grep a | sort | uniq > outfile
```

Use a here-document as input. The output file is appended to, not overwritten:

```sh
./pipex_bonus here_doc LIMITER "cmd1" "cmd2" outfile
# same as: cmd1 << LIMITER | cmd2 >> outfile
```

## How it works

- A child process is forked for each command, and the processes are connected with `pipe()` and `dup2()`.
- Commands are found by searching the `PATH` from the environment and run with `execve()`.
- The program exits with the last command's exit status.
