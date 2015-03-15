#ifndef QSAMPLECLASS_H
#define QSAMPLECLASS_H

#include <QObject>

class QSampleClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int someInt READ someInt WRITE someInt)
    Q_PROPERTY(float someFloat READ someFloat WRITE someFloat)
    Q_PROPERTY(QString someString READ someString WRITE someString)

    int m_someInt;
    float m_someFloat;
    QString m_someString;

public:
    Q_INVOKABLE QSampleClass(QObject *parent = 0);
    ~QSampleClass();

    int someInt() const;
    float someFloat() const;
    QString someString() const;
signals:

public slots:
    void someInt(int arg);
    void someFloat(float arg);
    void someString(QString arg);
};

#endif // QSAMPLECLASS_H
