#include "RandomAccessReader.h"

#include <utility>
#include <iostream>
#include <cstring>

RandomAccessReader::RandomAccessReader(std::string filePath) {
    this->filePath = std::move(filePath);
}

FILE* RandomAccessReader::openFile() {

    // Open the target sequence file
    FILE* target = fopen(filePath.c_str(), "rb");

    if (target == nullptr) {
        std::cerr << "Error reading text file " << filePath.c_str() << ": " << strerror(errno) << std::endl;
        return nullptr;
    }

    this->targetFile = target;
    return this->targetFile;

}

void RandomAccessReader::closeFile() {
    fclose(this->targetFile);
}

char RandomAccessReader::getCharAt(int position) {

    fseek(this->targetFile, position * (int)sizeof(char), SEEK_SET);
    return (char) fgetc(this->targetFile);

}

