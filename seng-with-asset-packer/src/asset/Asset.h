#ifndef PACKER_ASSET_H
#define PACKER_ASSET_H

#include <string>
#include <vector>

namespace asset {

/**
 * \class Asset
 * 
 * \brief Contains information needed to extract asset data from asset container file.
 *
 */
class Asset
{
public:
    void readBytes(char ** assetData, unsigned long * assetLength);

    /**
     * The size of buf (persistent scratch memory).
     */
    static const unsigned long bufSize; 

    /**
     * Persistantly allocated block of memory to reduce fragmentation.
     */
    static std::vector<char> buf;

private:
    Asset(const std::string & assetContainerFilename, const std::string & assetName, unsigned long startByte, unsigned long numberOfBytes)
        : assetContainerFilename(assetContainerFilename), assetName(assetName), startByte(startByte), numberOfBytes(numberOfBytes) { }

    std::string assetContainerFilename;
    std::string assetName;
    unsigned long startByte;
    unsigned long numberOfBytes;    
};

}

#endif
