#ifndef QCSVMODEL_H
#define QCSVMODEL_H
#include <QStandardItemModel>
#include <QVector>
#include <QString>
#include <QList>

class QCSVModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit QCSVModel(QObject *parent = 0);
    ~QCSVModel();

    bool firstColNames() const;
    void setFirstColNames(bool value);
    QString filename() const;

    QObject *object() const;
    // if object is not writable, class MUST have Q_INVOKABLE constructor,
    // which have one argument: parent QObject
    void setObject(QObject *object);

    // store numbers of properties to display
    void setProperties(const QVector<int> &properties);
    QChar separator() const;
public slots:
    bool parse();
    void setFilename(const QString &filename);
    void setSeparator(QChar separator);
signals:
    void error(QString);
protected:
    bool processLine(const QString &line);
    void setDefaultPropertiesOrder();
private:
    QString m_filename;
    // if true, then attributes' names are in first column
    bool m_firstColNames;
    // QObject to display
    QObject *m_object;
    // store numbers of properties to display
    QVector<int> m_properties;
    // separator of field in line
    QChar m_separator;
    // number of line being processed
    std::size_t m_lineNumber;
#ifndef WRITEABLE_OBJECT
    // list of created objects
    QList<QObject *> m_objects;
#endif
};

#endif // QCSVMODEL_H
