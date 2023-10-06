#ifndef FLOATMATRIX_H
#define FLOATMATRIX_H

#include "FloatVector.h"

class FloatMatrix {
public:
    FloatMatrix();
    ~FloatMatrix();

    FloatVector at(int index);
    FloatVector &operator[](int index);

    const FloatVector &operator[](int index) const;

    void clear();
    void reserve(int size);
    void resize(int size);
    int size() const;

    void push_front(FloatVector value);
    void push_back(FloatVector value);

    FloatVector getMin() const;
    FloatVector getMax() const;
    FloatVector getAvg() const;

    FloatMatrix transposed();
    FloatMatrix convoluted();

    int saveToFile(const QString &filePath);
    int saveAsJsonFile(const QString &filePath);

    QVector <FloatVector> data;
};

#endif // FLOATMATRIX_H
