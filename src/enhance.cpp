#include "enhance.h"

#include <QImage>
#include <qmath.h>
#include <cmath>
#include <algorithm>

Enhance::Enhance(QObject *parent) :
    QObject(parent)
{

}

//WARNING: code is badly repeated all over here!
//not time, no time!

void Enhance::convertToGray(QImage *img)
{
    int w = img->width();
    int h = img->height();

    int gray;
    QRgb grayRGB;

    for(int x=0; x < w; x++)
        for(int y=0; y < h; y++)
        {
            gray = qGray(img->pixel(x, y));
            grayRGB = qRgb(gray, gray, gray);
            img->setPixel(x, y, grayRGB);
        }
}

void Enhance::applyNegative(QImage *img, int bits)
{
    int max = qPow(2, bits);

    int w = img->width();
    int h = img->height();

    int gray;
    QRgb grayRGB;

    for(int x=0; x < w; x++)
        for(int y=0; y < h; y++)
        {
            gray = qGray(img->pixel(x, y));
            gray = max - gray;
            grayRGB = qRgb(gray, gray, gray);
            img->setPixel(x, y, grayRGB);
        }
}

void Enhance::applyLog(QImage *img, double c)
{
    int w = img->width();
    int h = img->height();

    int gray;
    QRgb grayRGB;

    for(int x=0; x < w; x++)
        for(int y=0; y < h; y++)
        {
            gray = qGray(img->pixel(x, y));
            gray = c*std::log10(gray + 1);
            grayRGB = qRgb(gray, gray, gray);
            img->setPixel(x, y, grayRGB);
        }
}

void Enhance::applyInverseLog(QImage *img, double c)
{
    int w = img->width();
    int h = img->height();

    int gray;
    QRgb grayRGB;

    for(int x=0; x < w; x++)
        for(int y=0; y < h; y++)
        {
            gray = qGray(img->pixel(x, y));
            gray = c*qPow(10, gray);
            grayRGB = qRgb(gray, gray, gray);
            img->setPixel(x, y, grayRGB);
        }
}

void Enhance::applyPower(QImage *img, double c, double gamma)
{
    int w = img->width();
    int h = img->height();

    int gray;
    QRgb grayRGB;

    for(int x=0; x < w; x++)
        for(int y=0; y < h; y++)
        {
            gray = qGray(img->pixel(x, y));
            gray = c*qPow(gray, gamma);
            grayRGB = qRgb(gray, gray, gray);
            img->setPixel(x, y, grayRGB);
        }
}

void Enhance::applyStretching(QImage *img, int smin, int smax)
{
    int w = img->width();
    int h = img->height();

    int rmin, rmax, gray;
    QRgb grayRGB;

    std::vector<int> imgData;

    for(int x=0; x < w; x++)
        for(int y=0; y < h; y++)
        {
            gray = qGray(img->pixel(x, y));
            imgData.push_back(gray);
        }


    rmin = *std::min_element(imgData.begin(), imgData.end());
    rmax = *std::max_element(imgData.begin(), imgData.end());

    for(int x=0; x < w; x++)
        for(int y=0; y < h; y++)
        {
            gray = qGray(img->pixel(x, y));
            gray = ((smax - smin) / (rmax - rmin)) * (gray - rmin) + smin;
            grayRGB = qRgb(gray, gray, gray);
            img->setPixel(x, y, grayRGB);
        }
}
