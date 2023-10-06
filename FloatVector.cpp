#include "FloatVector.h"

FloatVector::FloatVector() {
}

FloatVector::~FloatVector() {
}

float FloatVector::at(int index) {
    return data.at(index);
}


float &FloatVector::operator[](int index) {
    return data[index];
}

const float &FloatVector::operator[](int index) const {
    return data[index];
}

void FloatVector::clear() {
    data.clear();
}

void FloatVector::reserve(int size) {
    data.reserve(size);
}

void FloatVector::resize(int size) {
    data.resize(size);
}

int FloatVector::size() const {
    return data.size();
}

void FloatVector::push_front(float value) {
    data.push_front(value);
}

void FloatVector::push_back(float value) {
    data.push_back(value);
}

FloatVector FloatVector::scaled(float k) const {
    FloatVector result;
    int size = data.size();
    for (int i = 0; i < size; i++) {
        result.push_back(data[i] * k);
    }
    return result;
}

FloatVector FloatVector::normalized() const {
    float min = getMin();
    float max = getMax();
    float delta = max - min;

    FloatVector result;
    int size = data.size();
    for (int i = 0; i < size; i++) {
        if (delta) {
            result.push_back((data[i] - min) / delta);
        } else {
            result.push_back(1);
        }

    }
    return result;
}

FloatVector FloatVector::normalizedInvB() const {
    FloatVector invB;
    int size = data.size();
    int maxValue = data[size - 1];
    for (int i = size - 1; i >= 0; i--) {
        int newValue = data[i];
        if (newValue < maxValue) maxValue = newValue;
        invB.push_front(maxValue);
    }

    FloatVector result;
    for (int i = 0; i < size; i++) {
        int newValue = data[i] - invB[i];
        result.push_back(newValue);
    }
    return result;
}

FloatVector FloatVector::intersectPoints(float treshold, int type) const {
    FloatVector points;
    if (data.isEmpty()) {
        return points;
    }
    float oldValue = data[0];
    int size = data.size();
    for (int i = 1; i < size; i++) {
        if ((type == 1 || type == 3) && oldValue < treshold && data[i] > treshold) {
            points.push_back(i);
        }
        if ((type == 2 || type == 3) && oldValue > treshold && data[i] < treshold) {
            points.push_back(i);
        }
        oldValue = data[i];
    }
    return points;
}

float FloatVector::getMin() const {
    assert(data.isEmpty());
    float result = data[0];
    int size = data.size();
    for (int i = 1; i < size; i++) {
        if (data[i] < result) result = data[i];
    }
    return result;
}

float FloatVector::getMax() const {
    assert(data.isEmpty());
    float result = data[0];
    int size = data.size();
    for (int i = 1; i < size; i++) {
        if (data[i] > result) result = data[i];
    }
    return result;
}

float FloatVector::getAvg() const {
    if (data.isEmpty()) {
        return 0;
    }
    double s = 0;
    int size = data.size();
    for (int i = 0; i < size; i++) {
        s += data[i];
    }
    return s / size;
}

float FloatVector::getRMS() const {
    if (data.isEmpty()) {
        return 0;
    }
    double s = 0;
    int size = data.size();
    for (int i = 0; i < size; i++) {
        s += data[i] * data[i];
    }
    return sqrt(s / size);
}

float FloatVector::convoluted(int start, int end) {
    float s = 0;
    //for (int i=start; i < end; i++) s += data[i];
    for (int i = start; i < end; i++) s = fmax(s, data[i]);
    //for (int i=start; i < end; i++) s = max(s, 100*log10(data[i]));
    return s;
}

void FloatVector::printAsJsonToFile(QTextStream &out) {
    out << "[";
    int size = data.size();
    for (int i = 0; i < size; i++) {
        if (i) out << ",";
        out << QString::number(data[i]);
    }
    out << "]";
}

int FloatVector::saveToFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Could not open file for writing";
        return -1;
    }

    QTextStream out(&file);
    int size = data.size();
    for (int i = 0; i < size; i++) {
        if (i) out << "\n";
        out << QString::number(data[i], 'f');
    }

    file.flush();
    file.close();
    return 0;
}

int FloatVector::saveAsJsonToFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Could not open file for writing";
        return -1;
    }

    QTextStream out(&file);
    printAsJsonToFile(out);

    file.flush();
    file.close();
    return 0;
}

