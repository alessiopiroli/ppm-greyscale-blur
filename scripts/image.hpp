#pragma once

#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <tuple>
#include <fstream>

struct pixel {
private:
    int red_value;
    int green_value;
    int blue_value;

public:
    // red value getter
    int get_red_value() const {
        return red_value;
    }

    // green value getter
    int get_green_value() const {
        return green_value;
    }

    // blue value getter
    int get_blue_value() const {
        return blue_value;
    }

    // red value setter
    void set_red_value (int red_value_) {
        red_value = red_value_;
    }

    // green value setter
    void set_green_value (int green_value_) {
        green_value = green_value_;
    }

    // blue value setter
    void set_blue_value (int blue_value_) {
        blue_value = blue_value_;
    }
};

class ImageHandler {
private:
    std::FILE* img_ptr = nullptr;
    std::string img_path;
    std::string handle_mode{"reading"};
    std::string magic_number;
    std::string img_width;
    std::string img_height;
    std::string max_col_val;
    std::vector<pixel> pixels;
    int tot_bytes = 0;

public:
    // image handler constructor
    // default handler is in reading mode
    ImageHandler(std::string& img_path_) : img_path{img_path_} {
        if (handle_mode == "reading") {
            img_ptr = std::fopen(img_path_.c_str(), "rb");
            if (img_ptr == nullptr) {
                return;
            } else {
                std::cout << "Image opened correctly" << std::endl;
                // getting the magic_number
                char return_value;
                while ((return_value = fgetc(img_ptr)) != '\n') {
                    magic_number += return_value;  
                }
                
                // getting the width
                while ((return_value = fgetc(img_ptr)) != ' ') {
                    img_width += return_value;   
                }
                
                // getting the height
                while ((return_value = fgetc(img_ptr)) != '\n') {
                    img_height += return_value;
                }

                // getting max colour value
                while ((return_value = fgetc(img_ptr)) != '\n') {
                    max_col_val += return_value;
                }

                // setting the total bytes value
                tot_bytes = std::stoi(img_width) * std::stoi(img_height) * 3;

                // reading the remaining bytes
                for (int i = 0; i < tot_bytes; i+=3) {
                    pixel tmp_pixel;
                    int rv = static_cast<int>(fgetc(img_ptr));
                    int gv = static_cast<int>(fgetc(img_ptr));
                    int bv = static_cast<int>(fgetc(img_ptr));

                    // checking that we have read correctly the pixel rgb values
                    if ((rv == EOF) || (gv == EOF) || (bv == EOF)) {
                        return;
                    } else {
                        // putting values inside temporary pixel
                        tmp_pixel.set_red_value(rv);
                        tmp_pixel.set_green_value(gv);
                        tmp_pixel.set_blue_value(bv);
                    }

                    pixels.push_back(tmp_pixel);
                }
            }
        }
    }

    // printing the content of the ppm file
    void print_raw_content() {
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

    // magic number getter
    std::string get_magic_number() const {
        return magic_number;
    }

    // width getter
    std::string get_width() const {
        return img_width;
    }

    // height getter
    std::string get_height() const {
        return img_height;
    }

    // max color value getter
    std::string get_max_color() const {
        return max_col_val;
    }

    // getter for total number of bytes
    int get_num_bytes() const {
        return tot_bytes;
    }

    // getter for the number of pixels
    int get_num_pixels () const {
        if (img_ptr != nullptr) {
            return pixels.size();
        } else {
            return -1;
        }
    }

    // printing all pixel values
    void print_pixel_values() const {
        if (img_ptr != nullptr) {
            for (int i = 0; i < pixels.size(); i++) {
                std::cout << "pixel: " << i << " r: " << pixels.at(i).get_red_value()
                    << ", g: " << pixels.at(i).get_green_value() << ", b: " << pixels.at(i).get_blue_value() << std::endl;
            }
        } else {
            return;
        }
    }

    // getter for image info
    void print_img_data() const {
        if (img_ptr != nullptr) {
            std::cout << "Image was opened correctly" << std::endl;
            std::cout << "Magic number: " << get_magic_number() << std::endl;
            std::cout << "Width: " << get_width() << std::endl;
            std::cout << "Height: " << get_height() << std::endl;
            std::cout << "Max color value: " << get_max_color() << std::endl;
            std::cout << "Number of bytes: " << get_num_bytes() << std::endl;
            std::cout << "Number of pixels: " << get_num_pixels() << std::endl;
        } else {
            std::cout << "Image was not opened correctly: can't display info" << std::endl;
        }
    }

    void gen_gs_img (std::string filename) {
        std::ofstream newimg{filename}; // creating new image file


    }
    
    // implement a constructor that defines the mode as writing
};