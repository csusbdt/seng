#include <cassert>
#include <fstream>
#include <sstream>
#include "FileSystem.h"
#include "AssetContainer.h"

namespace asset 
{
    std::stringstream AssetContainer::error;

    std::string AssetContainer::getLastError()
    {
        return error.str();
    }

    /**
     * \brief Load information about the data in the asset container.
     *
     * The assets in the container are stored in sequence.
     * The last asset in the container has a empty name and zero bytes of data.
     * See header file comment for complete details.
     */
    bool AssetContainer::setContainerFilename(const std::string & filename)
    {
        containerFilename = filename;

        std::ifstream is;
        is.open(filename, std::ios::binary);
        if (is.fail())
        {
            error << "File open failure: " << filename;
            return false;
        }

        /*
        // Read asset names and positions one after another until reaching an empty asset name.
        char assetName[256];
        while (true)
        {
            // Read asset name.
            readString(is, reinterpret_cast<char *>(&assetName), 256);

            // Read asset size.
            unsigned long compressedLength;
            is >> compressedLength;
            if (is.fail())
            {
                std::stringstream ss;
                ss << "Failed to read asset size. Filename: " << filename << " Asset name: " << str;
                Platform::fatalError(ss.str());
                return;
            }

            if (len > Asset::bufSize)
            {
                std::stringstream ss;
                ss << "bufSize of " << Asset::bufSize << " not sufficient; need " << len;
                Platform::fatalError(ss.str());
                return;
            }
        }
        is.read(Asset::buf.data(), len);
        if (is.fail())
        {
            Platform::fatalError("Read failed with content.seng.");
            return;
        }

        is.close();

        // Uncompress all bytes and execute as a Lua script.

        size_t uncompressedLength = 0;
        if (!snappy::GetUncompressedLength(buffer, len, &uncompressedLength))
        {
            delete [] buffer;
            Platform::fatalError("GetUncompressedLength failed with content.seng.");
            return;
        }
        char * uncompressed = new char[uncompressedLength + 1];

        if (!snappy::RawUncompress(buffer, len, uncompressed))
        {
            delete [] buffer;
            delete [] uncompressed;
            Platform::fatalError("GetUncompressedLength failed with content.seng.");
            return;
        }
        uncompressed[uncompressedLength] = 0;  // terminate string with a zero
        Core::doString(uncompressed);

        // TODO: Uncompress all bytes of the background image and store.


        delete [] buffer;
        delete [] uncompressed;
        */
        return true;
    }

    bool AssetContainer::getString(const std::string & filename, char * string, unsigned long maxLength)
    {
        if (assets.count(filename) > 0 && FileSystem::fileExists(filename))
        {
            error << "Asset exists in both file system and in loaded asset container: " << filename;
            return false;
        }
        else if (assets.count(filename) > 0)
        {
            // \todo complete this function.
            return true;
        }
        else if (FileSystem::fileExists(filename))
        {
            unsigned long len;
            if (!FileSystem::readString(filename, string, &len, maxLength))
            {
                return false;
            }
            return true;
        }
        else
        {
            error << "Asset not found.";
            return false;
        }
    }


    /**
     * \brief Read an unsigned long from the input stream.
     */
    bool AssetContainer::readSize(std::istream & is, unsigned long * size)
    {
        is >> *size;
        if (is.fail())
        {
    //        Platform::displayMessage("Failed to read unsigned long in AssetContainer::readSize().\n");
            return false;
        }
        return true;
    }

    /**
     * \brief Read the specified number of bytes from the input stream.
     */
    bool AssetContainer::readBytes(std::istream & is, char bytes[], unsigned long length)
    {
        is.read(bytes, length);
        if (is.fail())
        {
            std::stringstream ss;
            ss << "Failed to read " << length << " bytes in AssetContainer::readBytes().\n";
    //        Platform::displayMessage(ss.str());
            return false;
        }
        return true;
    }

    bool AssetContainer::uncompressBytes(
        char compressedBytes[],
        unsigned long compressedLength,
        char uncompressedBytes[],
        unsigned long * uncompressedLength,
        unsigned long maxUncompressedLength)
    {
        assert(sizeof(size_t) == sizeof(unsigned long));

        /*

        if (!snappy::GetUncompressedLength(compressedBytes, compressedLength, uncompressedLength))
        {
            Platform::displayMessage("GetUncompressedLength failed in AssetContainer::uncompressBytes().");
            return false;
        }

        if (*uncompressedLength > maxUncompressedLength)
        {
            std::stringstream ss;
            ss << "Length of uncompressed string exceeds maxUncompressedLength in AssetContainer::uncompressBytes().\n";
            ss << "uncompressed length is " << uncompressedLength << ". maxUncompressedLength is " << maxUncompressedLength << ".";
            Platform::displayMessage(ss.str());
            return false;
        }

        if (!snappy::RawUncompress(compressedBytes, compressedLength, uncompressedBytes))
        {
            Platform::fatalError("GetUncompressedLength failed in AssetContainer::uncompressBytes.");
            return false;
        }

        */

        return true;
    }

    /**
     * \brief Read a compressed string from the input stream.
     *
     * Store string as a zero-terminated string at the given location.
     */
    bool AssetContainer::readString(std::istream & is, char str[], unsigned long maxLength)
    {
        unsigned long compressedLength;
        if (!readSize(is, &compressedLength))
        {
    //        Platform::displayMessage("Failed to read length of compressed string.");
            return false;
        }

        if (compressedLength > Asset::bufSize)
        {
            std::stringstream ss;
            ss << "Length of the compressed string exceeds bufSize in AssetContainer::readString().\n";
            ss << "compressed length is " << compressedLength << ". bufSize is " << Asset::bufSize << ".";
    //        Platform::displayMessage(ss.str());
            return false;
        }

        char * compressedBytes =  Asset::buf.data();

        if (!readBytes(is, compressedBytes, compressedLength))
        {
    //        Platform::displayMessage("readBytes() failed in AssetContainer::readString().\n");
            return false;
        }

        unsigned long uncompressedLength = 0;
        if (!uncompressBytes(compressedBytes, compressedLength, str, &uncompressedLength, maxLength))
        {
    //        Platform::displayMessage("uncompressBytes() failed in AssetContainer::readString().\n");
            return false;
        }
        str[uncompressedLength] = 0;  // Terminate string with a zero.
        return true;
    }

    /*
        // Open content.seng and read all bytes into a buffer.

        std::ifstream is;
        is.open("content.seng", std::ios::binary);
        if (is.fail())
        {
            Platform::fatalError("File content.seng not found.");
            return;
        }
        is.seekg(0, std::ios::end);
        if (is.fail())
        {
            Platform::fatalError("Seek to end failed with content.seng.");
            return;
        }
        unsigned long length = is.tellg();
        if (is.fail())
        {
            Platform::fatalError("tellg failed with content.seng.");
            return;
        }
        is.seekg(0, std::ios::beg);
        if (is.fail())
        {
            Platform::fatalError("Seek to begin failed with content.seng.");
            return;
        }
        char * buffer = new char[length];

        // Read the size of the lua init script.
        unsigned int len;
        is >> len;

        is.read(buffer, len);
        if (is.fail())
        {
            delete [] buffer;
            Platform::fatalError("Read failed with content.seng.");
            return;
        }

        is.close();

        // Uncompress all bytes and execute as a Lua script.

        size_t uncompressedLength = 0;
        if (!snappy::GetUncompressedLength(buffer, len, &uncompressedLength))
        {
            delete [] buffer;
            Platform::fatalError("GetUncompressedLength failed with content.seng.");
            return;
        }
        char * uncompressed = new char[uncompressedLength + 1];

        if (!snappy::RawUncompress(buffer, len, uncompressed))
        {
            delete [] buffer;
            delete [] uncompressed;
            Platform::fatalError("GetUncompressedLength failed with content.seng.");
            return;
        }
        uncompressed[uncompressedLength] = 0;  // terminate string with a zero
        Core::doString(uncompressed);

        // TODO: Uncompress all bytes of the background image and store.


        delete [] buffer;
        delete [] uncompressed;
    */

}
