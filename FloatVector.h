#ifndef FLOATVECTOR_H
#define FLOATVECTOR_H

#include <QVector>
#include <QFile>
#include <QDebug>

class FloatVector {
public:
    FloatVector();
    ~FloatVector();

    float at(int index);
    float &operator[](int index);
    const float &operator[](int index) const;

    void clear();
    void reserve(int size);
    void resize(int size);
    int size() const;

    void push_front(float value);
    void push_back(float value);

    FloatVector scaled(float k) const;
    FloatVector normalized() const;
    FloatVector normalizedInvB() const;
    FloatVector intersectPoints(float treshold, int type) const;

    float getMin() const;
    float getMax() const;
    float getAvg() const;
    float getRMS() const;

    float convoluted(int start, int end);

    void printAsJsonToFile(QTextStream &out);

    int saveToFile(const QString &filePath);
    int saveAsJsonToFile(const QString &filePath);

    QVector<float> data;
};

#endif // FLOATVECTOR_H
