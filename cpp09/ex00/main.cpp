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
        bool ReadFile(const std::string& filename_path)
        {
            std::ifstream file_stream(filename_path);

            if (!file_stream.is_open())
            {
                std::cout << "Error opening stream file: " 
                          << filename_path;
                return false;
            }

            size_t      line_idx = 0;
            size_t      line_max_size = 1024;
            std::string line(line_max_size, 0);
            while (file_stream.getline(line.data(), line_max_size))
            {
                file_content_lines_map_[line_idx] = line;
                ++line_idx;
            }

            return true;
        }

        // Return a map with each file line from the last stream read.
        // If no file read before calling this method, the map will be empty.
        const std::map<int, std::string>& GetFileDataLines() const
        {
            return file_content_lines_map_;
        }
    private:
        std::map<int, std::string> file_content_lines_map_;
};

int main()
{
    FileReader file_reader;

    if (!file_reader.ReadFile("data.csv"))
    {
        std::cout << "Error reading file.";
        return 1;
    }

    const auto& file_lines = file_reader.GetFileDataLines();

    std::cout << "Number of lines read: " 
              << file_lines.size()
              << std::endl;

    return 0;
}