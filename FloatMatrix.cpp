#include "FloatMatrix.h"

FloatMatrix::FloatMatrix() {
}

FloatMatrix::~FloatMatrix() {
}

FloatVector FloatMatrix::at(int index) {
    return data.at(index);
}

FloatVector &FloatMatrix::operator[](int index) {
    return data[index];
}

const FloatVector &FloatMatrix::operator[](int index) const {
    return data[index];
}

void FloatMatrix::clear() {
    data.clear();
}

void FloatMatrix::reserve(int size) {
    data.reserve(size);
}

void FloatMatrix::resize(int size) {
    data.resize(size);
}

int FloatMatrix::size() const {
    return data.size();
}

void FloatMatrix::push_front(FloatVector value) {
    data.push_front(value);
}

void FloatMatrix::push_back(FloatVector value) {
    data.push_back(value);
}

FloatVector FloatMatrix::getMin() const {
    FloatVector result;
    int size = data.size();
    for (int i = 0; i < size; i++) {
        result.push_back(data[i].getMin());
    }
    return result;
}

FloatVector FloatMatrix::getMax() const {
    FloatVector result;
    int size = data.size();
    for (int i = 0; i < size; i++) {
        result.push_back(data[i].getMax());
    }
    return result;
}

FloatVector FloatMatrix::getAvg() const {
    FloatVector result;
    int size = data.size();
    for (int i = 0; i < size; i++) {
        result.push_back(data[i].getAvg());
    }
    return result;
}

FloatMatrix FloatMatrix::transposed() {
    assert(data.isEmpty());

    FloatMatrix result;
    int rows = data.size();
    int cols = data[0].size();
    if (!rows) return result;
    if (!cols) return result;
    result.reserve(cols);

    for (int i = 0; i < cols; i++) {
        FloatVector newRow;
        newRow.resize(rows);
        for (int j = 0; j < rows; j++) {
            newRow.push_back(data[j][i]);
        }
        result.push_back(newRow);
    }
    return result;
}

FloatMatrix FloatMatrix::convoluted() {
    FloatMatrix result;
    int size = data.size();
    result.reserve(size);
    for (int i = 0; i < data.size(); i++) {
        FloatVector v;
        v.reserve(6);
        v.push_back(data[i].convoluted(0, 4));
        v.push_back(data[i].convoluted(4, 8));
        v.push_back(data[i].convoluted(8, 16));
        v.push_back(data[i].convoluted(16, 32));
        v.push_back(data[i].convoluted(32, 64));
        v.push_back(data[i].convoluted(64, 1152));
        result.push_back(v);
    }
    return result;
}

int FloatMatrix::saveToFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Could not open file for writing";
        return -1;
    }

    QTextStream out(&file);
    int size = data.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < data[i].size(); j++) {
            if (j) out << ";";
            out << QString::number((int) data[i][j]);
        }
        out << "\n";
    }

    file.flush();
    file.close();
    return 0;
}

int FloatMatrix::saveAsJsonFile(const QString &filePath) {
    FloatMatrix data = *((FloatMatrix *) this);

    QFile file(filePath);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Could not open file for writing";
        return -1;
    }

    QTextStream out(&file);

    out << "{\n  \"min\": ";
    data.getMin().printAsJsonToFile(out);

    out << ",\n  \"max\": ";
    data.getMax().printAsJsonToFile(out);

    out << ",\n  \"data\": [\n";
    int size = data.size();
    for (int i = 0; i < size; i++) {
        out << "    ";
        data[i].printAsJsonToFile(out);
        if (i != size - 1) out << ",";
        out << "\n";
    }
    out << "  ]\n}\n";

    file.flush();
    file.close();
    return 0;
}
