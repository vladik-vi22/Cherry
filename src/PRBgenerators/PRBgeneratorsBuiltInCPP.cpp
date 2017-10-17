#include "PRBgeneratorsBuiltInCPP.h"

BuiltInCPP::BuiltInCPP()
{
}

BuiltInCPP::~BuiltInCPP()
{
}

void BuiltInCPP::generate()
{
    QBitArray new_number_bit_arr;
    QByteArray new_number_byte_arr;
    QString new_number_str;
    QList<qint16> new_number_list_int;
    QDataStream stream(&new_number_byte_arr, QIODevice::ReadWrite);
    for(int index = 0; index < 72500; ++index)
        new_number_list_int.append(qrand());
    setNumberListInt(new_number_list_int);
//    stream << sizeof(qint16) * 8 * 62500 << m_number_list_int;
    stream.device()->reset();
    stream >> new_number_bit_arr;
    setNumberBitArr(new_number_bit_arr);
    for(int index = 0; index < m_number_list_int.size(); ++index)
        new_number_str.append(QString::number(m_number_list_int[index], 2));
    setNumberStr(new_number_str);
    qDebug() << m_number_str.length();
    qDebug() << m_number_bit_arr.size();
    qDebug() << new_number_byte_arr.size();
}
