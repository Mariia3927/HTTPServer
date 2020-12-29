//
//  FileHandler.hpp
//  HTTP_Server
//

#ifndef FileHandler_hpp
#define FileHandler_hpp

#include <fstream>
#include <string>

class FileHandler
{
private:
    FILE* m_fileDescriptor;
    std::string m_filePath;
    std::string m_fileName;
    std::string m_fileExtension;
    std::string m_contentTypes[7] = {"image/jpeg", "image/gif", "image/bmp", "image/tiff", "image/png", "text/plain", "application/octet-stream"};
    enum MimeContentType: int { JpegImage = 0, GifImage, BmpImage, TiffImage, PngImage, TextDocument, AnyKindOfBinary };
    
private:
    void parseFileName();
    
public:
    FileHandler();
    FileHandler(const std::string& name, const std::string& path);
    FileHandler(const FileHandler& manager) = delete;
    ~FileHandler();
    
    FileHandler& operator=(const FileHandler& manager) = delete;
    
    std::string getFileName();
    std::string getFilePath();
    unsigned long getFileLength();
    std::string getContentType();
    bool openFile(const std::string& mode);
    bool write(void* buffer, size_t length);
    size_t read(void* buffer, size_t length);
    void closeFile();
};

#endif /* FileHandler_hpp */
