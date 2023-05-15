#include <iostream>
#include "CopyModelReader.h"
#include "../../utils/utils.h"

CopyModelReader::CopyModelReader(std::string filePath, int windowSize) : Reader(std::move(filePath)) {
    this->windowSize = windowSize;
    this->currentPosition = 0;
    this->pastPosition = 0;
}

bool CopyModelReader::readWindow() {

    if (!Reader::getFileInputStream()->is_open())
        return false;

    this->currentWindow.clear();

    for (int i = 0; i < this->windowSize; i++)
        if (!this->expand())
            return false;
    return true;

}

bool CopyModelReader::expand() {

    if (!Reader::getFileInputStream()->is_open()) {
        std::cerr << "[CopyModelReader::expand] File is not open." << std::endl;
        return false;
    }

    if (Reader::getFileInputStream()->eof()) {
        std::cerr << "[CopyModelReader::expand] File is at the end." << std::endl;
        return false;
    }

    if (Reader::getFileInputStream()->fail()) {
        std::cerr << "[CopyModelReader::expand] File failed to read." << std::endl;
        return false;
    }

    // TODO: When we read a new character, we are reading an integer. This integer is then converted to a char.
    // In practice, it will be truncated and we will only obtain the first 1 Byte. This is the reason why our windows
    // are not working properly, i.e., they usually have the "?" mark at the beginning and at the end.
    // We need to find a way to solve this in the future.

    int characterRead = Reader::getFileInputStream()->get();

    // We want to read only characters that are not white lines, i.e., \n, \t, \r, etc.
    if (!isWhiteLineCharacter(characterRead) && !isForbiddenCharacter(characterRead))
        this->currentWindow.push_back((char) characterRead);

    this->currentPosition++;

    return true;

}

int CopyModelReader::getWindowSize() const {
    return this->windowSize;
}

std::vector<char> CopyModelReader::getCurrentWindow() {
    return this->currentWindow;
}

int CopyModelReader::getCurrentPosition() const {
    return this->currentPosition;
}

int CopyModelReader::getPastPosition() const {
    return this->pastPosition;
}
