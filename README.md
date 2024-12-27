# FileManager (fm)

FileManager (fm) is a simple command-line tool written in Go for listing files in a directory. This is a hobby project aimed at learning and exploring Go's capabilities. Currently, `fm` can list files within a specified directory. If no directory is specified, it defaults to the current directory. Note that passing files as parameters is not supported and will result in an error.

## Features

- List files in a specified directory
- Default to current directory if no parameter is provided

## Usage

### Running in Terminal

To list the files in a specific directory, use the following command:

```bash
go run . <directory>
```

If no directory is specified, the current directory is used:

```bash
go run .
```

### Running in VSCode

1. Open the `fm` project folder in VSCode.
1. Press F5 to run the program with the debugger.
1. Change `args` in `.vscode/launch.json` to adjust the program arguments.

## golangci-linter

`golangci-linter` is a fast, flexible, and convenient Go linters runner. It helps you find potential issues in your code. Here's how you can install and use it:

### Installation

To install `golangci-linter`, run:

```bash
go install github.com/golangci/golangci-lint/cmd/golangci-lint@latest
```

Make sure to add `$GOPATH/bin` to your `PATH`.

### Usage

To run golangci-linter on your project, navigate to your project directory and run:

```bash
golangci-lint run ./...
```

This will check your code for potential issues and provide feedback.