#include <cassert>
#include <fstream>
#include <sstream>
#include "AssetContainer.h"
#include "FileSystem.h"

namespace asset
{
    bool FileSystem::fileExists(const std::string & filename)
    {
	    std::fstream file;
	    file.open(filename.c_str(), std::ios::in);
	    if (file.fail())
	    {
		    file.clear();
		    return false;
	    }
	    file.close();
	    file.clear();
	    return true;
    }

    //bool AssetContainer::fileSize(const std::string & filename, unsigned int * len)
    //{
    //    std::ifstream is;
    //    is.open(filename, std::ios::binary);
    //    if (is.fail())
    //    {
    //        error << "File not found: " << filename;
    //        return false;
    //    }
    //    is.seekg(0, std::ios::end);
    //    if (is.fail())
    //    {
    //        error << "Seek to end failed with file: " << filename;
    //        return false;
    //    }
    //    *len = is.tellg();
    //    if (is.fail())
    //    {
    //        error << "tellg failed with file: " << filename;
    //        return false;
    //    }
    //    return true;
    //}

    bool FileSystem::readBytes(const std::string & filename, char * bytes, unsigned long * length, unsigned long maxLength)
    {
        std::ifstream is;
        is.open(filename, std::ios::binary);
        if (is.fail())
        {
            AssetContainer::error << "File open error: " << filename;
            return false;
        }
        is.seekg(0, std::ios::end);
        if (is.fail())
        {
            AssetContainer::error << "Seek to end failed with file: " << filename;
            return false;
        }
        *length = is.tellg();
        if (is.fail())
        {
            AssetContainer::error << "tellg failed with file: " << filename;
            return false;
        }
        if (*length > maxLength)
        {
            AssetContainer::error << "maxLength of string inadequate to store file: " << filename << std::endl;
            AssetContainer::error << "maxLeng is " << maxLength << ". File size is " << *length;
            return false;
        }

        is.seekg(0, std::ios::beg);
        if (is.fail())
        {
            AssetContainer::error << "Seek to begin failed with file: " << filename;
            return false;
        }

        is.read(bytes, *length);
        if (is.fail())
        {
            AssetContainer::error << "Read failed with file: " << filename;
            return false;
        }

        is.close();
        if (is.fail())
        {
            AssetContainer::error << "Close failed with file: " << filename;
            return false;
        }

        return true;
    }

    bool FileSystem::readString(const std::string & filename, char * string, unsigned long * length, unsigned long maxLength)
    {
        if (!readBytes(filename, string, length, maxLength - 1))
        {
            return false;
        }
        string[*length] = 0;  // Terminate string.
        return true;
    }
}
