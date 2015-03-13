#include <fstream>
#include <sstream>
#include "snappy.h"
#include "Asset.h"

namespace asset {

const unsigned long Asset::bufSize = 256 * 1024;
std::vector<char> Asset::buf;

/**
 * \brief Load bytes from asset container file that comprise the asset.
 *
 * See http://code.google.com/p/snappy/
 *
 */
void Asset::readBytes(char ** assetData, unsigned long * assetLength)
{
    if (buf.size() == 0)
    {
        buf.reserve(bufSize);
    }

    std::ifstream is;
    is.open(assetContainerFilename, std::ios::binary);
    if (is.fail())
    {
//        Platform::fatalError("File not found: " + assetContainerFilename);
        return;
    }
    is.seekg(startByte);
    if (is.fail())
    {
//        Platform::fatalError("Seek to startByte failed with " + assetContainerFilename);
        return;
    }

    is.read(buf.data(), numberOfBytes);
    if (is.fail())
    {
//        Platform::fatalError("Read failed with " + assetContainerFilename);
        return;
    }

    is.close();

    // Uncompress.

    size_t uncompressedLength = 0;
    if (!snappy::GetUncompressedLength(buf.data(), numberOfBytes, &uncompressedLength))
    {
//        Platform::fatalError("GetUncompressedLength failed with " + assetContainerFilename);
        return;
    }
    if (numberOfBytes + uncompressedLength > bufSize)
    {
        std::stringstream ss;
        ss << "bufSize of " << bufSize << " not sufficient; need " << numberOfBytes + uncompressedLength;
//        Platform::fatalError(ss.str());
        return;
    }

    char * uncompressed = buf.data() + numberOfBytes;

    if (!snappy::RawUncompress(buf.data(), numberOfBytes, uncompressed))
    {
//        Platform::fatalError("RawUncompressed failed with " + assetContainerFilename);
        return;
    }
    *assetData = uncompressed;
    *assetLength = uncompressedLength;
}

}
