#include <iostream>
#include <fstream>
#include <map>

class FileReader
{
    public:
        FileReader() : file_content_lines_map_()
        {}
        
        ~FileReader() 
        {}

        FileReader(const FileReader& other) = delete;
        FileReader& operator=(const FileReader& other) = delete;

        // Read a file content and map each line with its content.
        // Returns false if the file is not successfully open or
        // read, otherwise returns true.
        bool ReadFile(const std::string& filename_path);
  
        // Return a map with each file line from the last stream read.
        // If no file read before calling this method, the map will be empty.
        const std::map<int, std::string>& GetFileLines() const;
  
    private:
        std::map<int, std::string> file_content_lines_map_;
};