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
		stat, err := os.Stat(os.Args[1])
		if os.IsNotExist(err) {
			fmt.Println("failed to stat path, err:", err)
			return
		}
		if !stat.IsDir() {
			fmt.Printf("path %s not a directory\n", os.Args[1])
			return
		}
		dir = os.Args[1]
	}

	// read dir
	files, err := os.ReadDir(dir)
	if err != nil {
		fmt.Println("failed to read dir, err:", err)
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
			fmt.Println("failed to get file info, err:", err)
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
		modTimeCol     = "Mod Date Time"
		nameCol        = "Name"
	)
	typeColLen := len(typeCol)
	permissionsColLen := len(permissionsCol)
	modTimeFormatString := "Jan 02 2006 15:04"
	modTimeColLen := len(modTimeFormatString)
	fmt.Printf("%s %*s %*s %*s %-*s\n", typeCol,
		permissionsColLen, permissionsCol,
		sizeColLen, sizeCol,
		modTimeColLen, modTimeCol,
		nameColLen, nameCol)
	for _, file := range files {
		fileType := "-"
		if file.IsDir() {
			fileType = "d"
		}

		info, err := file.Info()
		if err != nil {
			fmt.Println("failed to get file info, err:", err)
		} else {
			fileSize := strconv.FormatInt(info.Size(), 10)
			fileName := file.Name()
			if file.IsDir() {
				fileName = fmt.Sprintf("%s/", fileName)
			}
			modTime := info.ModTime().Format(modTimeFormatString)
			fmt.Printf("%*s %*s %*s %*s %-*s\n",
				typeColLen, fileType,
				permissionsColLen, file.Type().Perm(),
				sizeColLen, fileSize,
				modTimeColLen, modTime,
				nameColLen, fileName)
		}
	}
}
