#include "BigIntCalculator.h"

const QString BigIntCalculator::usedCharsBinary = "01";
const QString BigIntCalculator::usedCharsDecimal = "0123456789";
const QString BigIntCalculator::usedCharsHexadecimal = "0123456789abcdefABCDEF";

BigIntCalculator::BigIntCalculator(QObject* parent): QObject(parent)
{
    m_baseInput = 10;
    m_baseOutput = 10;
}

BigIntCalculator::~BigIntCalculator()
{

}

uint8_t BigIntCalculator::getBaseInput() const
{
    return m_baseInput;
}

uint8_t BigIntCalculator::getBaseOutput() const
{
    return m_baseOutput;
}

QString BigIntCalculator::getBigNumber1() const
{
    return m_bigNumber1;
}

QString BigIntCalculator::getBigNumber2() const
{
    return m_bigNumber2;
}

QString BigIntCalculator::getCalculationsResult() const
{
    return m_calculationsResult;
}

void BigIntCalculator::setBaseInput(const uint8_t &new_baseInput)
{
    if(m_baseInput != new_baseInput)
    {
        m_baseInput = new_baseInput;
        emit baseInputChanged();
    }
}

void BigIntCalculator::setBaseOutput(const uint8_t &new_baseOutput)
{
    if(m_baseOutput != new_baseOutput)
    {
        m_baseOutput = new_baseOutput;
        emit baseOutputChanged();
    }
}

void BigIntCalculator::setBigNumber1(const QString &new_bigNumber1)
{
    if(m_bigNumber1 != new_bigNumber1)
    {
        m_bigNumber1 = new_bigNumber1;
        emit bigNumber1Changed();
    }
}

void BigIntCalculator::setBigNumber2(const QString &new_bigNumber2)
{
    if(m_bigNumber2 != new_bigNumber2)
    {
        m_bigNumber2 = new_bigNumber2;
        emit bigNumber2Changed();
    }
}

void BigIntCalculator::setCalculationsResult(const QString &new_calculationResult)
{
    if(m_calculationsResult != new_calculationResult)
    {
        m_calculationsResult = new_calculationResult;
        emit calculationsResultChanged();
    }
}

bool BigIntCalculator::isCorrect(const QString& bigNumberQString) const
{
    QString usedChars = m_baseInput == 2 ? usedCharsBinary : (m_baseInput == 10 ? usedCharsDecimal : usedCharsHexadecimal);
    for(QString::const_iterator iteratorBigNumberQString = bigNumberQString.constBegin(); iteratorBigNumberQString != bigNumberQString.constEnd(); ++ iteratorBigNumberQString)
    {
        if(!usedChars.contains(*iteratorBigNumberQString))
        {
            return false;
        }
    }
    return true;
}

void BigIntCalculator::calculate(const QString& operation)
{
    if(isCorrect(m_bigNumber1) && isCorrect(m_bigNumber2))
    {
        if(operation == "+")
        {
            setCalculationsResult(QString::fromStdString((BigInt(m_bigNumber1.toStdString(), m_baseInput) + BigInt(m_bigNumber2.toStdString(), m_baseInput)).toStdString(m_baseOutput)));
        }
        else if(operation == "-")
        {
            setCalculationsResult(QString::fromStdString((BigInt(m_bigNumber1.toStdString(), m_baseInput) - BigInt(m_bigNumber2.toStdString(), m_baseInput)).toStdString(m_baseOutput)));
        }
        else if(operation == "*")
        {
            setCalculationsResult(QString::fromStdString((BigInt(m_bigNumber1.toStdString(), m_baseInput) * BigInt(m_bigNumber2.toStdString(), m_baseInput)).toStdString(m_baseOutput)));
        }
        else if(operation == "/")
        {
            if(m_bigNumber2 != "0")
            {
                setCalculationsResult(QString::fromStdString((BigInt(m_bigNumber1.toStdString(), m_baseInput) / BigInt(m_bigNumber2.toStdString(), m_baseInput)).toStdString(m_baseOutput)));
            }
            else
            {
                setCalculationsResult("divide be zero exception");
            }
        }
        else if(operation == "%")
        {
            if(m_bigNumber2 != "0")
            {
                setCalculationsResult(QString::fromStdString((BigInt(m_bigNumber1.toStdString(), m_baseInput) % BigInt(m_bigNumber2.toStdString(), m_baseInput)).toStdString(m_baseOutput)));
            }
            else
            {
                setCalculationsResult("divide be zero exception");
            }
        }
        else if(operation == "pow")
        {
            if(m_bigNumber1 != "0" && m_bigNumber2 != "0")
            {
                setCalculationsResult(QString::fromStdString(pow(BigInt(m_bigNumber1.toStdString(), m_baseInput), BigInt(m_bigNumber2.toStdString(), m_baseInput)).toStdString(m_baseOutput)));
            }
            else
            {
                setCalculationsResult("zero to power zero exception");
            }
        }
        else if(operation == "~")
        {
            setCalculationsResult(QString::fromStdString((~BigInt(m_bigNumber1.toStdString(), m_baseInput)).toStdString(m_baseOutput)));
        }
        else if(operation == "&&")
        {
            setCalculationsResult(QString::fromStdString((BigInt(m_bigNumber1.toStdString(), m_baseInput) & BigInt(m_bigNumber2.toStdString(), m_baseInput)).toStdString(m_baseOutput)));
        }
        else if(operation == "|")
        {
            setCalculationsResult(QString::fromStdString((BigInt(m_bigNumber1.toStdString(), m_baseInput) | BigInt(m_bigNumber2.toStdString(), m_baseInput)).toStdString(m_baseOutput)));
        }
        else if(operation == "^")
        {
            setCalculationsResult(QString::fromStdString((BigInt(m_bigNumber1.toStdString(), m_baseInput) ^ BigInt(m_bigNumber2.toStdString(), m_baseInput)).toStdString(m_baseOutput)));
        }
        else if(operation == "<<")
        {
            setCalculationsResult(QString::fromStdString((BigInt(m_bigNumber1.toStdString(), m_baseInput) << BigInt(m_bigNumber2.toStdString(), m_baseInput).toUint32_t()).toStdString(m_baseOutput)));
        }
        else if(operation == ">>")
        {
            setCalculationsResult(QString::fromStdString((BigInt(m_bigNumber1.toStdString(), m_baseInput) >> BigInt(m_bigNumber2.toStdString(), m_baseInput).toUint32_t()).toStdString(m_baseOutput)));
        }
        else if(operation == "gcd")
        {
            if(m_bigNumber1 != "0" && m_bigNumber2 != "0")
            {
            setCalculationsResult(QString::fromStdString(gcd(BigInt(m_bigNumber1.toStdString(), m_baseInput), BigInt(m_bigNumber2.toStdString(), m_baseInput)).toStdString(m_baseOutput)));
            }
            else
            {
                setCalculationsResult("divide be zero exception");
            }
        }
        else if(operation == "lcm")
        {
            if(m_bigNumber1 != "0" && m_bigNumber2 != "0")
            {
            setCalculationsResult(QString::fromStdString(lcm(BigInt(m_bigNumber1.toStdString(), m_baseInput), BigInt(m_bigNumber2.toStdString(), m_baseInput)).toStdString(m_baseOutput)));
            }
            else
            {
                setCalculationsResult("lcm(0,0) exception");
            }
        }
        else
        {
            setCalculationsResult("");
        }
    }
    else
    {
        setCalculationsResult("incorrect input");
    }
}
