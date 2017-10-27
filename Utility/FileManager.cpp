#include "FileManager.h"

// Standard Includes
#include <cstdio>
#include <fstream>


FileManager* FileManager::Instance()
{
	static FileManager instance;
	return &instance;
}


std::string FileManager::ReadFile(const std::string& path) const{

	//std::ifstream inFile(path);
	std::ifstream inFile;
	inFile.exceptions(std::ifstream::failbit);
	try {
		inFile.open(path);
	}
	catch (const std::exception& e) {
		std::cout << "Fiddlesticks: Exception thrown opening file" << std::endl;
	}


	if (inFile) {
		return std::string((std::istreambuf_iterator<char>(inFile)),
			(std::istreambuf_iterator<char>()));
	}
	else {
		std::cout << "Warning: Failed to read file at " << path << std::endl;
		return std::string("");
	}
}

bool FileManager::PrintFile(const std::string& path, std::ostream& os) const{
	std::string contents = ReadFile(path);
	if (os){
		os << contents;
		return true;
	}
	else{
		std::cout << "Warning: Failed to print file at " << path << std::endl;
	}

	return true;
}

bool FileManager::WriteFile(const std::string& path, std::string& contents) const{
	std::ofstream outFile(path);
	if (outFile){
		outFile << contents;
		return true;
	}
	else{
		std::cout << "Warning: Failed to write to file at " << path << std::endl;
		return false;
	}
}

bool FileManager::ClearFile(const std::string& path) const{
	if ( std::ifstream(path) ){ // Check if file already exists
		std::cout << "Warning: Failed to clear file at " << path 
				  << ". File already exists" << std::endl;
		return false;
	}

	if ( std::ofstream(path, std::ofstream::trunc) ){
		return true;
	}
	else{
		std::cout << "Warning: Failed to clear file at " << path << std::endl;
		return false;
	}
}


bool FileManager::DeleteFile(const std::string& path) const{
	if ( !remove(path.c_str()) ){
		return true;
	}
	else{
		std::cout << "Warning: Failed to delete file at " << path << std::endl;
		return false;
	}
}									

FileManager::FileManager()
{}


FileManager::~FileManager()
{}
