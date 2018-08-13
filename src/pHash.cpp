#include "pHash.hpp"
#include <opencv2/opencv.hpp>
using namespace cv;
extern "C"
{
    PHPCPP_EXPORT void *get_module()
    {
        static Php::Extension pHash("pHash", "1.0");
        pHash.add<generateHash>("phash", {Php::ByVal("filename", Php::Type::String)});
        pHash.add<calculateDistance>("hamming_distance", {Php::ByVal("hashA", Php::Type::Numeric), Php::ByVal("hashB", Php::Type::Numeric)});
        return pHash;
    }
}

Php::Value calculateDistance(Php::Parameters &params)
{
    int distance = 0;
    int64_t hashA = (int64_t)params[0];
    int64_t hashB = (int64_t)params[1];
    while (hashA != hashB)
    {
        distance += (hashA & 1) ^ (hashB & 1);
        hashA >>= 1;
        hashB >>= 1;
    }
    return distance;
}

Php::Value generateHash(Php::Parameters &params)
{
    const char *imagePath = (const char *)params[0];
    Mat image = imread(imagePath);
    image.convertTo(image, CV_32FC1);
    cvtColor(image, image, COLOR_BGR2GRAY);
    resize(image, image, Size(32, 32));
    Mat imageDCT;
    dct(image, imageDCT);
    image.release();
    double dctMean = 0.0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            dctMean += imageDCT.at<float>(i, j);
        }
    }
    dctMean /= 64.0;
    int64_t imgHash = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            imgHash <<= 1;
            if (imageDCT.at<float>(i, j) >= dctMean)
            {
                imgHash |= 1;
            }
        }
    }
    imageDCT.release();
    return imgHash;
}
