#ifndef SRC_REFERENCEREADER_H
#define SRC_REFERENCEREADER_H

#include <string>
#include <fstream>
#include <vector>

#include "Reader.h"

class ReferenceReader : public Reader {

    int windowSize;
    int allocatedWindowSize;
    std::string* currentWindow;
    int currentPosition;

public:

    explicit ReferenceReader(std::string filePath, int windowSize);

    bool next();

    std::string getReferenceName();

    // Getters
    [[nodiscard]] int getWindowSize() const;
    [[nodiscard]] int getAllocatedWindowSize() const;
    std::string* getCurrentWindow();
    int getCurrentPosition() const;

};


#endif
