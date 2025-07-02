#pragma once

#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <tuple>
#include <fstream>

#include <omp.h>

enum class img_type {
    original, 
    greyscale, 
    blurred
};

struct pixel {
private:
    int red_value = 0;
    int green_value = 0;
    int blue_value = 0;

public:
    // default constructor for a pixel
    pixel() {}

    // constructor with rgb values
    pixel(const int r_value_, const int g_value, const int b_value) : 
        red_value{r_value_}, green_value{g_value}, blue_value{b_value} {}

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
    std::string random_info;
    std::string img_width;
    std::string img_height;
    std::string max_col_val;
    std::vector<pixel> original_pixels;
    std::vector<pixel> greyscale_pixels;
    std::vector<pixel> blurred_pixels;
    int tot_bytes = 0;

public:
    // image handler constructor
    // default handler is in byte reading mode
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
                
                // stuff to do if there's some random info
                if ((return_value = fgetc(img_ptr)) != '\n') {
                    if (return_value == '#') {
                        random_info += return_value;

                        // getting the  rest of the random info
                        while ((return_value = fgetc(img_ptr)) != '\n') {
                            random_info += return_value;
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
                    }
                } else {
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

                    // pushing the temporary pixel in the pixels vector
                    original_pixels.push_back(tmp_pixel);
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
            return original_pixels.size();
        } else {
            return -1;
        }
    }

    // printing all pixel values
    void print_pixel_values() const {
        if (img_ptr != nullptr) {
            for (int i = 0; i < original_pixels.size(); i++) {
                std::cout << "pixel: " << i << " r: " << original_pixels.at(i).get_red_value()
                    << ", g: " << original_pixels.at(i).get_green_value() << ", b: " << original_pixels.at(i).get_blue_value() << std::endl;
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

        // appending the initial stuff for the ppm file
        newimg << magic_number << "\n" << random_info << "\n" << get_width()
            << " " << get_height() << "\n" << get_max_color() << "\n";

        #pragma omp parallel
        for (int i = 0; i < get_num_pixels(); i++) {
            // generating the greyscale value for each pixel
            int avg_pixel_value = original_pixels.at(i).get_red_value();
            avg_pixel_value += original_pixels.at(i).get_green_value();
            avg_pixel_value += original_pixels.at(i).get_blue_value();
            avg_pixel_value /= 3;
            
            // writing to greyscale image
            newimg << static_cast<char>(avg_pixel_value);
            newimg << static_cast<char>(avg_pixel_value);
            newimg << static_cast<char>(avg_pixel_value);

            // pushing pixel into greyscale vector
            pixel tmp_pixel;
            tmp_pixel.set_red_value(avg_pixel_value);
            tmp_pixel.set_green_value(avg_pixel_value);
            tmp_pixel.set_blue_value(avg_pixel_value);

            greyscale_pixels.push_back(tmp_pixel);
        }
    }
    
    // return a pixel given the row and the column
    pixel get_pixel_values(std::size_t row_, std::size_t column_, img_type img_type_) {
        if (img_ptr != nullptr) {
            switch (img_type_) {
                // getting pixel from original image
                case (img_type::original):
                    // we check if original vector is not empty
                    if (original_pixels.size() > 0) {
                        // then we check if we are inside the bounds
                        // if we are not we just return an empty pixel
                        if (row_ * std::stoi(get_width()) + column_ < get_num_pixels()) {
                            return original_pixels[row_ * std::stoi(this->get_width()) + column_];
                        } else {
                            // we return an empty pixel
                            return pixel();
                        }
                    }
                    break;

                // getting pixel from greyscale image
                case (img_type::greyscale):
                    // we check if original vector is not empty
                    if (greyscale_pixels.size() > 0) {
                        // then we check if we are inside the bounds
                        // if we are not we just return an empty pixel
                        if (row_ * std::stoi(get_width()) + column_ < get_num_pixels()) {
                            return greyscale_pixels[row_ * std::stoi(this->get_width()) + column_];
                        } else {
                            // we return an empty pixel
                            return pixel();
                        }
                    }
                    break;

                // getting pixel from blurred image
                case (img_type::blurred):
                    // we check if original vector is not empty
                    if (blurred_pixels.size() > 0) {
                        // then we check if we are inside the bounds
                        // if we are not we just return an empty pixel
                        if (row_ * std::stoi(get_width()) + column_ < get_num_pixels()) {
                            return blurred_pixels[row_ * std::stoi(this->get_width()) + column_];
                        } else {
                            // we return an empty pixel
                            return pixel();
                        }
                    }
                    break;

                // default case
                default:
                    return pixel();
            }
        } else {
            return pixel();
        }
        return pixel();
    }

    // write a setter for the pixel values and use it when generating the greyscale image
    void set_pixel_values(const std::size_t row_, const std::size_t column_, 
            const int r_value, const int g_value, const int b_value, img_type img_type_) {
        if (img_ptr != nullptr) {
            // if we are inside the bounds it's okay
            if ((row_ * std::stoi(get_width()) + column_) < get_num_pixels()) {
                switch (img_type_) {
                    // we operate directly on the original image
                    case (img_type::original):
                        original_pixels[row_ * std::stoi(get_width()) + column_].set_red_value(r_value);
                        original_pixels[row_ * std::stoi(get_width()) + column_].set_green_value(g_value);
                        original_pixels[row_ * std::stoi(get_width()) + column_].set_blue_value(b_value);
                        break;
                    // we operate on the greyscale image
                    case (img_type::greyscale):
                        greyscale_pixels[row_ * std::stoi(get_width()) + column_].set_red_value(r_value);
                        greyscale_pixels[row_ * std::stoi(get_width()) + column_].set_green_value(g_value);
                        greyscale_pixels[row_ * std::stoi(get_width()) + column_].set_blue_value(b_value);
                        break;
                
                    // we operate on the blurred image
                    case (img_type::blurred):
                        blurred_pixels[row_ * std::stoi(get_width()) + column_].set_red_value(r_value);
                        blurred_pixels[row_ * std::stoi(get_width()) + column_].set_green_value(g_value);
                        blurred_pixels[row_ * std::stoi(get_width()) + column_].set_blue_value(b_value);
                        break;
                }
            } else {
                return;
            }
        }
    }

    // function to generate a blurred version of the image
    void gen_blr_image(std::string filename, int blr_value) {
        std::ofstream newimg{filename, std::ios::binary}; // creating new image file

        // appending the initial stuff from the original ppm file
        newimg << magic_number << "\n" << random_info << "\n" << get_width()
            << " " << get_height() << "\n" << get_max_color() << "\n";

        #pragma omp parallel for
        for (std::size_t i = 0; i < get_num_pixels(); i++) {
            int act_i = i / std::stoi(get_width());
            int act_j = i % std::stoi(get_width());

            int avg_r_val = 0;
            int avg_g_val = 0;
            int avg_b_val = 0;

            int count_ = 0;

            // getting average value from surrounding pixels
            for (std::size_t i_ = act_i - blr_value; i_ <= act_i + blr_value; i_++) {
                for (std::size_t j_ = act_j - blr_value; j_ <= act_j + blr_value; j_++) {
                    avg_r_val += get_pixel_values(i_, j_, img_type::original).get_red_value();
                    avg_g_val += get_pixel_values(i_, j_, img_type::original).get_green_value();
                    avg_b_val += get_pixel_values(i_, j_, img_type::original).get_blue_value();
                    count_++;
                }
            }

            // taking the average of the pixel values
            if (count_ > 0) {
               avg_r_val /= count_;
                avg_g_val /= count_;
                avg_b_val /= count_;
            } else {
                avg_r_val = 0;
                avg_g_val = 0;
                avg_b_val = 0;
            }

            // writing to blurred image
            newimg << static_cast<char>(avg_r_val);
            newimg << static_cast<char>(avg_g_val);
            newimg << static_cast<char>(avg_b_val);

            // pushing pixel into blurred vector
            pixel tmp_pixel;
            tmp_pixel.set_red_value(avg_r_val);
            tmp_pixel.set_green_value(avg_g_val);
            tmp_pixel.set_blue_value(avg_b_val);

            // pushing pixel into blurred vector
            blurred_pixels.push_back(tmp_pixel);
        }
    }
};