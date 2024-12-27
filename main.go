package main

import (
	"fmt"
	"os"
	"strconv"
)

func main() {
	// args
	dir := "."
	if len(os.Args) > 1 {
		dir = os.Args[1]
	}

	// read dir
	files, err := os.ReadDir(dir)
	if err != nil {
		_ = fmt.Errorf("failed to read dir, err: %v", err)
		return
	}

	// determine width for name column
	nameColLen := 0
	sizeColLen := 0
	for _, file := range files {
		fileNameLen := len(file.Name())
		if fileNameLen > nameColLen {
			nameColLen = fileNameLen
		}

		info, err := file.Info()
		if err != nil {
			_ = fmt.Errorf("failed to get file info, err: %v", err)
		} else {
			fileSizeLen := len(strconv.FormatInt(info.Size(), 10))
			if fileSizeLen > sizeColLen {
				sizeColLen = fileSizeLen
			}
		}
	}
	// add 1 char for trailing / for dirs
	nameColLen += 1

	// print files
	const (
		typeCol        = "Type"
		permissionsCol = "Permissions"
		sizeCol        = "Size"
		nameCol        = "Name"
	)
	typeColLen := len(typeCol)
	permissionsColLen := len(permissionsCol)
	fmt.Printf("%s %*s %*s %-*s\n", typeCol, permissionsColLen, permissionsCol, sizeColLen, sizeCol, nameColLen, nameCol)
	for _, file := range files {
		fileType := "-"
		if file.IsDir() {
			fileType = "d"
		}

		info, err := file.Info()
		if err != nil {
			_ = fmt.Errorf("failed to get file info, err: %v", err)
		} else {
			fileSize := strconv.FormatInt(info.Size(), 10)
			fileName := file.Name()
			if file.IsDir() {
				fileName = fmt.Sprintf("%s/", fileName)
			}
			fmt.Printf("%*s %*s %*s %-*s\n", typeColLen, fileType, permissionsColLen, file.Type().Perm(), sizeColLen, fileSize, nameColLen, fileName)
		}
	}
}
