#pragma once

#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

class ImageHandler {
private:
    int n_row_pixel = 0;
    int n_col_pixel = 0;
    std::FILE* img_ptr = nullptr;
    std::string img_path;
    std::string handle_mode{"reading"};
    std::string magic_number;

public:
    // image handler constructor
    // default handler is in reading mode
    ImageHandler(std::string& img_path_) : img_path{img_path_} {
        if (handle_mode == "reading") {
            img_ptr = std::fopen(img_path_.c_str(), "r");
            if (img_ptr == nullptr) {
                return;
            } else {
                std::cout << "Image opened correctly" << std::endl;
                // getting the magic_number
                char return_value;
                while ((return_value = fgetc(img_ptr)) != '\n') {
                    magic_number += return_value;  
                }
            }
        }
    }

    // printing the content of the ppm file
    void print_content() {
        if (img_ptr != nullptr) {
            // if we have access to the image we can print
            int return_value;
            std::vector<char> read_values;
            rewind(img_ptr); // going to the beginning of the image
            while ((return_value = fgetc(img_ptr)) != EOF) {
                read_values.push_back(static_cast<char>(return_value));
            }

            // printing what we actually read
            for (auto it = read_values.begin(); it != read_values.end(); ++it) {
                std::cout << *it;
            }
            
        } else {
            return;
        }
    }

    std::string get_magic_number() {
        return magic_number;
    }

    // implement a constructor that defines the mode as writing
};