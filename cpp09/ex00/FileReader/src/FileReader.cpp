#include "../include/FileReader.hpp"

bool FileReader::ReadFile(const std::string& filename_path)
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

const std::map<int, std::string>& FileReader::GetFileLines() const
{
    return file_content_lines_map_;
}
