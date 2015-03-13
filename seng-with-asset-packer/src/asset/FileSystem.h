#ifndef ASSET_FILE_SYSTEM_H
#define ASSET_FILE_SYSTEM_H

#include <cassert>
#include <string>
#include <sstream>
#include <map>

namespace asset 
{
    /**
     * \class FileSystem
     * 
     * \brief Provides read access to assets stored as files.
     */
    class FileSystem
    {
    public:
        bool getString(const std::string & filename, char * string, unsigned long maxLength);
        static bool fileExists(const std::string & filename);
        static bool readString(const std::string & filename, char * string, unsigned long * length, unsigned long maxLength);
        //bool fileSize(const std::string & filename, unsigned int * length);

    private:
        FileSystem() { assert(false); }
        static bool readBytes(const std::string & filename, char * bytes, unsigned long * length, unsigned long maxLength);
    };
}

#endif
