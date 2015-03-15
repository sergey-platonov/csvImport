#include "qsampleclass.h"

QSampleClass::QSampleClass(QObject *parent) : QObject(parent)
{

}

QSampleClass::~QSampleClass()
{

}

int QSampleClass::someInt() const
{
    return m_someInt;
}

float QSampleClass::someFloat() const
{
    return m_someFloat;
}

QString QSampleClass::someString() const
{
    return m_someString;
}

void QSampleClass::someInt(int arg)
{
    m_someInt = arg;
}

void QSampleClass::someFloat(float arg)
{
    m_someFloat = arg;
}

void QSampleClass::someString(QString arg)
{
    m_someString = arg;
}

