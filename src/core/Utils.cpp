/*
 * Copyright (c) 2016, 2017 ARM Limited.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "arm_compute/core/Utils.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <map>
#include <string>

using namespace arm_compute;

std::string arm_compute::build_information()
{
    static const std::string information =
#include "arm_compute_version.embed"
        ;
    return information;
}

std::string arm_compute::read_file(const std::string &filename, bool binary)
{
    std::string   out;
    std::ifstream fs;

    try
    {
        fs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        std::ios_base::openmode mode = std::ios::in;

        if(binary)
        {
            mode |= std::ios::binary;
        }

        fs.open(filename, mode);

        // Go to the end of the file
        fs.seekg(0, std::ios::end);
        // Reserve the memory required to store the file's content
        out.reserve(fs.tellg());
        // Go back to the beginning of the file
        fs.seekg(0, std::ios::beg);
        // Copy the content of the file
        out.assign(std::istreambuf_iterator<char>(fs), std::istreambuf_iterator<char>());
    }
    catch(const std::ifstream::failure &e)
    {
        ARM_COMPUTE_ERROR("Accessing %s: %s", filename.c_str(), e.what());
    }

    return out;
}

const std::string &arm_compute::string_from_format(Format format)
{
    static std::map<Format, const std::string> formats_map =
    {
        { Format::UNKNOWN, "UNKNOWN" },
        { Format::U8, "U8" },
        { Format::S16, "S16" },
        { Format::U16, "U16" },
        { Format::S32, "S32" },
        { Format::U32, "U32" },
        { Format::F16, "F16" },
        { Format::F32, "F32" },
        { Format::UV88, "UV88" },
        { Format::RGB888, "RGB888" },
        { Format::RGBA8888, "RGBA8888" },
        { Format::YUV444, "YUV444" },
        { Format::YUYV422, "YUYV422" },
        { Format::NV12, "NV12" },
        { Format::NV21, "NV21" },
        { Format::IYUV, "IYUV" },
        { Format::UYVY422, "UYVY422" }
    };

    return formats_map[format];
}

const std::string &arm_compute::string_from_channel(Channel channel)
{
    static std::map<Channel, const std::string> channels_map =
    {
        { Channel::UNKNOWN, "UNKNOWN" },
        { Channel::R, "R" },
        { Channel::G, "G" },
        { Channel::B, "B" },
        { Channel::A, "A" },
        { Channel::Y, "Y" },
        { Channel::U, "U" },
        { Channel::V, "V" },
        { Channel::C0, "C0" },
        { Channel::C1, "C1" },
        { Channel::C2, "C2" },
        { Channel::C3, "C3" }
    };

    return channels_map[channel];
}

const std::string &arm_compute::string_from_data_type(DataType dt)
{
    static std::map<DataType, const std::string> dt_map =
    {
        { DataType::UNKNOWN, "UNKNOWN" },
        { DataType::S8, "S8" },
        { DataType::U8, "U8" },
        { DataType::S16, "S16" },
        { DataType::U16, "U16" },
        { DataType::S32, "S32" },
        { DataType::U32, "U32" },
        { DataType::S64, "S64" },
        { DataType::U64, "U64" },
        { DataType::F16, "F16" },
        { DataType::F32, "F32" },
        { DataType::F64, "F64" },
        { DataType::SIZET, "SIZET" },
    };

    return dt_map[dt];
}

const std::string &arm_compute::string_from_activation_func(ActivationLayerInfo::ActivationFunction act)
{
    static std::map<ActivationLayerInfo::ActivationFunction, const std::string> act_map =
    {
        { ActivationLayerInfo::ActivationFunction::ABS, "ABS" },
        { ActivationLayerInfo::ActivationFunction::LINEAR, "LINEAR" },
        { ActivationLayerInfo::ActivationFunction::LOGISTIC, "LOGISTIC" },
        { ActivationLayerInfo::ActivationFunction::RELU, "RELU" },
        { ActivationLayerInfo::ActivationFunction::BOUNDED_RELU, "BRELU" },
        { ActivationLayerInfo::ActivationFunction::SOFT_RELU, "SRELU" },
        { ActivationLayerInfo::ActivationFunction::SQRT, "SQRT" },
        { ActivationLayerInfo::ActivationFunction::SQUARE, "SQUARE" },
        { ActivationLayerInfo::ActivationFunction::TANH, "TANH" },
    };

    return act_map[act];
}

const std::string &arm_compute::string_from_matrix_pattern(MatrixPattern pattern)
{
    static std::map<MatrixPattern, const std::string> pattern_map =
    {
        { MatrixPattern::BOX, "BOX" },
        { MatrixPattern::CROSS, "CROSS" },
        { MatrixPattern::DISK, "DISK" },
        { MatrixPattern::OTHER, "OTHER" },
    };

    return pattern_map[pattern];
}

const std::string &arm_compute::string_from_non_linear_filter_function(NonLinearFilterFunction function)
{
    static std::map<NonLinearFilterFunction, const std::string> func_map =
    {
        { NonLinearFilterFunction::MAX, "MAX" },
        { NonLinearFilterFunction::MEDIAN, "MEDIAN" },
        { NonLinearFilterFunction::MIN, "MIN" },
    };

    return func_map[function];
}

const std::string &arm_compute::string_from_interpolation_policy(InterpolationPolicy policy)
{
    static std::map<InterpolationPolicy, const std::string> interpolation_policy_map =
    {
        { InterpolationPolicy::AREA, "AREA" },
        { InterpolationPolicy::BILINEAR, "BILINEAR" },
        { InterpolationPolicy::NEAREST_NEIGHBOR, "NEAREST_NEIGHBOUR" },
    };

    return interpolation_policy_map[policy];
}

const std::string &arm_compute::string_from_border_mode(BorderMode border_mode)
{
    static std::map<BorderMode, const std::string> border_mode_map =
    {
        { BorderMode::UNDEFINED, "UNDEFINED" },
        { BorderMode::CONSTANT, "CONSTANT" },
        { BorderMode::REPLICATE, "REPLICATE" },
    };

    return border_mode_map[border_mode];
}

std::string arm_compute::lower_string(std::string val)
{
    std::transform(val.begin(), val.end(), val.begin(), ::tolower);
    return val;
}

const std::pair<unsigned int, unsigned int> arm_compute::scaled_dimensions(unsigned int width, unsigned int height, unsigned int kernel_size,
                                                                           unsigned int stride_x, unsigned int stride_y,
                                                                           unsigned int pad_x, unsigned int pad_y,
                                                                           DimensionRoundingType round_type)
{
    unsigned int w = 0;
    unsigned int h = 0;
    switch(round_type)
    {
        case DimensionRoundingType::FLOOR:
            w = static_cast<unsigned int>(std::floor((static_cast<float>(width + 2 * pad_x - kernel_size) / stride_x) + 1));
            h = static_cast<unsigned int>(std::floor((static_cast<float>(height + 2 * pad_y - kernel_size) / stride_y) + 1));
            break;
        case DimensionRoundingType::CEIL:
            w = static_cast<unsigned int>(std::ceil((static_cast<float>(width + 2 * pad_x - kernel_size) / stride_x) + 1));
            h = static_cast<unsigned int>(std::ceil((static_cast<float>(height + 2 * pad_y - kernel_size) / stride_y) + 1));
            break;
        default:
            ARM_COMPUTE_ERROR("Unsupported rounding type");
    }

    // Make sure that border operations will start from inside the input and not the padded area
    if(((w - 1) * stride_x) >= (width + pad_x))
    {
        --w;
    }
    if(((h - 1) * stride_y) >= (height + pad_y))
    {
        --h;
    }
    ARM_COMPUTE_ERROR_ON(((w - 1) * stride_x) >= (width + pad_x));
    ARM_COMPUTE_ERROR_ON(((h - 1) * stride_y) >= (height + pad_y));

    return std::make_pair(w, h);
}

void arm_compute::print_consecutive_elements(std::ostream &s, DataType dt, const uint8_t *ptr, unsigned int n, int stream_width, const std::string &element_delim)
{
    switch(dt)
    {
        case DataType::U8:
            print_consecutive_elements_impl<uint8_t>(s, ptr, n, stream_width, element_delim);
            break;
        case DataType::U16:
            print_consecutive_elements_impl<uint16_t>(s, reinterpret_cast<const uint16_t *>(ptr), n, stream_width, element_delim);
            break;
        case DataType::S16:
            print_consecutive_elements_impl<int16_t>(s, reinterpret_cast<const int16_t *>(ptr), n, stream_width, element_delim);
            break;
        case DataType::U32:
            print_consecutive_elements_impl<uint32_t>(s, reinterpret_cast<const uint32_t *>(ptr), n, stream_width, element_delim);
            break;
        case DataType::S32:
            print_consecutive_elements_impl<int32_t>(s, reinterpret_cast<const int32_t *>(ptr), n, stream_width, element_delim);
            break;
        case DataType::F32:
            print_consecutive_elements_impl<float>(s, reinterpret_cast<const float *>(ptr), n, stream_width, element_delim);
            break;
        case DataType::F16:
            break;
        default:
            ARM_COMPUTE_ERROR("Undefined element size for given data type");
    }
}

int arm_compute::max_consecutive_elements_display_width(std::ostream &s, DataType dt, const uint8_t *ptr, unsigned int n)
{
    switch(dt)
    {
        case DataType::U8:
            return max_consecutive_elements_display_width_impl<uint8_t>(s, ptr, n);
        case DataType::U16:
            return max_consecutive_elements_display_width_impl<uint16_t>(s, reinterpret_cast<const uint16_t *>(ptr), n);
        case DataType::S16:
            return max_consecutive_elements_display_width_impl<int16_t>(s, reinterpret_cast<const int16_t *>(ptr), n);
        case DataType::U32:
            return max_consecutive_elements_display_width_impl<uint32_t>(s, reinterpret_cast<const uint32_t *>(ptr), n);
        case DataType::S32:
            return max_consecutive_elements_display_width_impl<int32_t>(s, reinterpret_cast<const int32_t *>(ptr), n);
        case DataType::F32:
            return max_consecutive_elements_display_width_impl<float>(s, reinterpret_cast<const float *>(ptr), n);
        case DataType::F16:
            return 0;
        default:
            ARM_COMPUTE_ERROR("Undefined element size for given data type");
    }
}