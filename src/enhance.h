#ifndef ENHANCE_H
#define ENHANCE_H

#include <QObject>

class Enhance : public QObject
{
    Q_OBJECT
public:
    explicit Enhance(QObject *parent = 0);

signals:

public slots:
    static void convertToGray(QImage *img);

    static void applyNegative(QImage *img, int bits);
    static void applyLog(QImage *img, double c);
    static void applyInverseLog(QImage *img, double c);
    static void applyPower(QImage *img, double c, double gamma);
    static void applyStretching(QImage *img, int smin, int smax);
};

#endif // ENHANCE_H
