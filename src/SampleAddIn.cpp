/*
 *  Modern Native AddIn
 *  Copyright (C) 2018  Infactum
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#define _CRT_SECURE_NO_WARNINGS


#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>


#include "SampleAddIn.h"

std::string SampleAddIn::extensionName() {
    return "Sample";
}

SampleAddIn::SampleAddIn() {
    // Universal property. Could store any supported by native api type.
    sample_property = std::make_shared<variant_t>();
    AddProperty(L"SampleProperty", L"ОбразецСвойства", sample_property);

    // Full featured property registration example
    AddProperty(L"Version", L"ВерсияКомпоненты", [&]() {
        auto s = std::string(Version);
        return std::make_shared<variant_t>(std::move(s));
    });

    // Method registration.
    // Lambdas as method handlers are not supported.

    AddMethod(L"AutoOrient", L"АвтоОриент", this, &SampleAddIn::AutoOrient);
    
    AddMethod(L"Rotate", L"Повернуть", this, &SampleAddIn::pictureRotate);

    AddMethod(L"Flip", L"ОтразитьПоВертикали", this, &SampleAddIn::pictureFlip);

    AddMethod(L"Flop", L"ОтразитьПоГоризонтали", this, &SampleAddIn::pictureFlop);

    AddMethod(L"Enhance", L"Улучшить", this, &SampleAddIn::pictureEnhance);

    AddMethod(L"Sharpen", L"Заострить", this, &SampleAddIn::pictureSharpen);

    AddMethod(L"Oil", L"Масло", this, &SampleAddIn::pictureOil);

    // Method registration with default arguments
    //
    // Notice that if variant_t would be non-copy you can't use initializer list.
    // Proper way to register def args would be then:
    //        std::map<long, variant_t> def_args;
    //        def_args.insert({0, 5});
    //        AddMethod(u"Sleep", u"Ожидать", this, &SampleAddIn::sleep, std::move(def_args));
    //

}

// Auto Orient image like an EXIF specs (and rewrite it)
void SampleAddIn::AutoOrient(const variant_t &picture_path)
{
    auto pic_path = std::get<std::string>(picture_path);
    Magick::Image image;
    image.read(pic_path);
    image.autoOrient();
    image.write(pic_path);
}

std::string SampleAddIn::pictureRotate(const variant_t& baseString, const variant_t& incomingAngle)
{
    auto base_string = std::get<std::string>(baseString);
    auto angle = std::get<int32_t>(incomingAngle);
    Magick::Blob objectBlob;
    objectBlob.base64(base_string);
    Magick::Image image;
    image.read(objectBlob);
    image.rotate(angle);
    image.write(&objectBlob);
    std::string new_base_string;
    new_base_string = objectBlob.base64();
    return new_base_string;
}

std::string SampleAddIn::pictureFlip(const variant_t& baseString)
{
    auto base_string = std::get<std::string>(baseString);
    Magick::Blob objectBlob;
    objectBlob.base64(base_string);
    Magick::Image image;
    image.read(objectBlob);
    image.flip();
    image.write(&objectBlob);
    std::string new_base_string;
    new_base_string = objectBlob.base64();
    return new_base_string;
}

std::string SampleAddIn::pictureFlop(const variant_t& baseString)
{
    auto base_string = std::get<std::string>(baseString);
    Magick::Blob objectBlob;
    objectBlob.base64(base_string);
    Magick::Image image;
    image.read(objectBlob);
    image.flop();
    image.write(&objectBlob);
    std::string new_base_string;
    new_base_string = objectBlob.base64();
    return new_base_string;
}

std::string SampleAddIn::pictureEnhance(const variant_t& baseString)
{
    auto base_string = std::get<std::string>(baseString);
    Magick::Blob objectBlob;
    objectBlob.base64(base_string);
    Magick::Image image;
    image.read(objectBlob);
    image.enhance();
    image.write(&objectBlob);
    std::string new_base_string;
    new_base_string = objectBlob.base64();
    return new_base_string;
}

std::string SampleAddIn::pictureSharpen(const variant_t& baseString)
{
    auto base_string = std::get<std::string>(baseString);
    Magick::Blob objectBlob;
    objectBlob.base64(base_string);
    Magick::Image image;
    image.read(objectBlob);
    image.sharpen();
    image.write(&objectBlob);
    std::string new_base_string;
    new_base_string = objectBlob.base64();
    return new_base_string;
}

std::string SampleAddIn::pictureOil(const variant_t& baseString)
{
    auto base_string = std::get<std::string>(baseString);
    Magick::Blob objectBlob;
    objectBlob.base64(base_string);
    Magick::Image image;
    image.read(objectBlob);
    image.oilPaint();
    image.write(&objectBlob);
    std::string new_base_string;
    new_base_string = objectBlob.base64();
    return new_base_string;
}

