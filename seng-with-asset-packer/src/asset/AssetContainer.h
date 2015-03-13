#ifndef ASSET_ASSET_CONTAINER_H
#define ASSET_ASSET_CONTAINER_H

#include <string>
#include <sstream>
#include <map>
#include "Asset.h"

namespace asset 
{
    /**
     * \class AssetContainer
     * 
     * \brief Provides read access to the data stored in a content file.
     *
     * This class provides support for the developmen process in the following way.
     * If DEBUG is defined, then the file system is also searched to resolve references
     * to assets.  This alows the developer to delay packing of assets until a
     * release build.
     *
     * Content file format:
     *
     * The first 4 bytes in the file is the file format version number, currently equal to 1. (uint32)
     * The second item is the number of bytes needed to store the largest block of compressed bytes. (uint32)
     * The third item is the number of bytes needed to store the largest uncompressed block of bytes. (uint32)
     *
     * The remainder of the file are the assets stored as a sequence. 
     * Each asset contains the following:
     *    The byte position of the next asset.  (zero if this is the last asset in the file) (uint32)
     *    The name of the asset as a length-prefixed ascii string. (length is a uint32, characters are char)
     *    The type of asset. (numeric code stored as unit32, see codes below)
     *    The number of bytes needed to store the asset in uncompressed format. (uint32)
     *    The number of bytes of compressed bytes that follows. (uint32)
     *    The compressed bytes (using snappy).
     *
     * The asset types are as follows:
     *
     * 0  ascii string
     *     length (uint32)
     *     length number of characters (ascii char)
     *
     * 1  RBG image
     *     width (uint32)
     *     height (uint32)
     *     pixel data
     *
     * 2  RBGA image
     *     width (uint32)
     *     height (uint32)
     *     pixel data
     *
     *
     */
    class AssetContainer
    {
    public:
        AssetContainer() : buffer(NULL) { }
        std::string getLastError();

        /**
         * \brief Set the filename of the asset container.
         *
         * This function builds the internal map that associates asset
         * names with byte offsets into the file for later retrieval.
         */
        bool setContainerFilename(const std::string & containerFilename);

        bool getString(const std::string & filename, char * string, unsigned long maxLength);

        static std::stringstream error;

    private:
        bool readSize(std::istream & is, unsigned long * size);
        bool readString(std::istream & is, char str[], unsigned long maxLength);
        bool readBytes(std::istream & is, char bytes[], unsigned long length);
        bool uncompressBytes(char compressedBytes[], unsigned long compressedLength, char uncompressedBytes[], unsigned long * uncompressedLength, unsigned long maxUncompressedLength);

        std::string containerFilename;
        std::map<std::string, Asset *> assets;

        /**
         * \brief Pointer to memory that is used to store compressed bytes.
         *
         * I need to figure out a more efficient way to do this.
         */
        char * buffer;
    };
}

#endif
