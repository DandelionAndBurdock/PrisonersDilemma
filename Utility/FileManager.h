// Class: FileManager
// Description: Singleton class responsible for creating, reading,
// writing and deleting files.
// Author: Philip Jones
// Date: 14/10/2017

#pragma once

// Standard Library Includes
#include <iostream>
#include <memory>	// For unique_ptr
#include <string>

class FileManager {
public:
	// Returns pointer to single instance of FileManager class.
	static FileManager*   Instance();

	// Opens file at path and returns pointer to contents. Returns nullptr on failure.
	std::string ReadFile(const std::string& path) const;

	// Prints contents of file at path using provided output stream. Returns false on failure.
	bool PrintFile(const std::string& path, std::ostream& os = std::cout) const;

	// Writes contents to file at path. Creates file if it does not exist. 
	// Returns false if file exists but could not be opened
	bool WriteFile(const std::string& path, std::string& contents) const;

	// Returns true if able to delete contents of file at path and false otherwise.
	bool ClearFile(const std::string& path) const;

	// Returns true if able to deletes file at path and false otherwise.
	bool DeleteFile(const std::string& path) const;

private:
	FileManager();
	~FileManager();

	FileManager(const FileManager&) = delete;
	FileManager& operator=(const FileManager&) = delete;
};

