#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "snappy.h"

// forward declarations
bool readFile(const std::string & fileName);
bool run();

// Global variables
char * buffer = NULL;
unsigned long length = 0;
std::map<std::string, unsigned long> assetNameToBytePosition; // Not yet used.

const unsigned int fileFormatVersionNunmber = 1;

/**
 * \brief Entry point to command line tool to package game assets.
 *
 * The program is not yet complete.  Here is what I want for the next step:
 */
int main(int argc, char * argv[])
{
#ifdef _DEBUG
    if (run())
    {
        std::cout << "OK.  Press enter to finish." << std::endl;
        std::cin.get();
        return 0;
    }
    else
    {
        std::cout << "Failed.  Press enter to finish." << std::endl;
        std::cin.get();
        return 1;
    }
#else
    if (run())
    {
        std::cout << "OK." << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Failed." << std::endl;
        return 1;
    }
#endif
}

bool readFile(const std::string & fileName)
{
    delete [] buffer;
    buffer = NULL;
    length = 0;

    std::ifstream is;
    is.open(fileName, std::ios::binary);
    if (is.fail())
    {
        std::cout << "Failed to open file " << fileName << std::endl;
        return false;
    }
    is.seekg(0, std::ios::end);
    if (is.fail())
    {
        std::cout << "Seek to end failed with " << fileName << std::endl;
        return false;
    }
    length = static_cast<unsigned long>(is.tellg());
    if (is.fail())
    {
        std::cout << "tellg failed with " << fileName << std::endl;
        return false;
    }
    is.seekg(0, std::ios::beg);
    if (is.fail())
    {
        std::cout << "Seek to begin failed with " << fileName << std::endl;
        return false;
    }
    buffer = new char[length];

    is.read(buffer, length);
    if (is.fail())
    {
        std::cout << "Read failed with " << fileName << std::endl;
        delete [] buffer;
        buffer = NULL;
        return false;
    }

    is.close();
    return true;
}

bool run()
{
    std::string contentDir = "../../../content";
    std::string workingDir = "../../../working";

    // Open the output file.
    std::fstream outfile;
    outfile.open(workingDir + "/content.seng", std::ios::out | std::ios::binary);
	if (outfile.fail())
	{
        std::cout << "Failed to create file content.seng." << std::endl;
        return false;
	}

    // Store the init script.
    readFile(contentDir + "/init.lua");
    std::string output;
    if (buffer == NULL)
    {
        return false;
    }

    size_t destlen;
    char * compressed = new char[snappy::MaxCompressedLength(length)];
    snappy::RawCompress(buffer, length, compressed, &destlen);
    outfile << destlen;
    outfile.write(compressed, destlen);

    // Store the background image.
    readFile(contentDir + "/DesertBattleBackground.raw");
    if (buffer == NULL)
    {
        return false;
    }
    delete [] compressed;
    compressed = new char[snappy::MaxCompressedLength(length)];
    snappy::RawCompress(buffer, length, compressed, &destlen);
    outfile << destlen;
    outfile.write(compressed, destlen);

	outfile.close();

    return true;
}

