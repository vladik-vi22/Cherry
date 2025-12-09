#include <ciphers/EDHcryptorAffine.h>
#include <algorithm>
#include <vector>
#include <cmath>

const QString Affine::alphabetEnglish = "abcdefghijklmnopqrstuvwxyz";
const QString Affine::alphabetSortedByFrequencyEnglish = "eariotnslcudpmhgbfywkvxzjq";
const QString Affine::alphabetUkrainian = "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя";
const QString Affine::alphabetSortedByFrequencyUkrainian = "оаеинтрсвлкмдупяьзбгчйхжцїшщфєґ";
const QString Affine::englishLanguage = "english";
const QString Affine::ukrainianLanguage = "ukrainian";
const int Affine::lenghtAlphabetEnglish = alphabetEnglish.length(); // 26
const int Affine::lenghtAlphabetUkrainian = alphabetUkrainian.length(); // 33
const qreal Affine::coincidenceIndexEnglish = 0.0667;
const qreal Affine::coincidenceIndexUkrainian = 0.0576;
const QList<QString> Affine::mostFrequentBigramsEnglish = (QList<QString>() << "th" << "he" << "in" << "er" << "an" << "re" << "es" << "on" << "st" << "nt" << "en" << "at");
const QList<QString> Affine::mostFrequentBigramsUkrainian = (QList<QString>() << "на" << "но" << "ко" << "ра" << "по" << "ні" << "ти" << "ро" << "ст" << "ен" << "ан" << "то");
const QList<QString> Affine::prohibitedBigramsEnglish = (QList<QString>() << "bq" << "cx" << "gx" << "jq" << "jv" << "kx" << "qv" << "qx" << "qz" << "vq" << "xz" << "zq" << "zx");
const QList<QString> Affine::prohibitedBigramsUkrainian = (QList<QString>() << "аь" << "оь" << "уь" << "еь" << "иь" << "іь" << "їь" << "юь" << "яь" << "єь" << "ьь" << "йь");
QString Affine::alphabet;
QString Affine::alphabetSortedByFrequency;
int Affine::lenghtAlphabet;
qreal Affine::coincidenceIndex;
QList<QString> Affine::mostFrequentBigrams;
QList<QString> Affine::prohibitedBigrams;
int Affine::lenghtMostFrequentBigrams;

Affine::Affine(QObject* parent): QObject(parent)
{
    setLanguage(englishLanguage);
}

Affine::~Affine()
{
}

QString Affine::getText() const
{
    return m_text;
}

qint32 Affine::getKey1() const
{
    return m_key1;
}

qint32 Affine::getKey2() const
{
    return m_key2;
}

QString Affine::getLanguage() const
{
    return m_language;
}

void Affine::setText(const QString &new_text)
{
    if(m_text != new_text)
    {
        m_text = new_text;
        emit textChanged();
    }
}

void Affine::setKey1(const qint32 &new_key)
{
    if(m_key1 != new_key)
    {
        m_key1 = new_key;
        emit key1Changed();
    }
}

void Affine::setKey2(const qint32 &new_key)
{
    if(m_key2 != new_key)
    {
        m_key2 = new_key;
        emit key2Changed();
    }
}

void Affine::setLanguage(const QString &new_language)
{
    if(m_language != new_language)
    {
        m_language = new_language;
        alphabet = isEnglishLanguage() ? alphabetEnglish : alphabetUkrainian;
        alphabetSortedByFrequency = isEnglishLanguage() ? alphabetSortedByFrequencyEnglish : alphabetSortedByFrequencyUkrainian;
        lenghtAlphabet = isEnglishLanguage() ? lenghtAlphabetEnglish : lenghtAlphabetUkrainian;
        coincidenceIndex = isEnglishLanguage() ? coincidenceIndexEnglish : coincidenceIndexUkrainian;
        mostFrequentBigrams = isEnglishLanguage() ? mostFrequentBigramsEnglish : mostFrequentBigramsUkrainian;
        prohibitedBigrams = isEnglishLanguage() ? prohibitedBigramsEnglish : prohibitedBigramsUkrainian;
        lenghtMostFrequentBigrams = mostFrequentBigrams.length();
        emit languageChanged();
    }
}

bool Affine::isEnglishLanguage()
{
    return (m_language == englishLanguage);
}

int Affine::gcd(int number1, int number2)
{
    return number2 == 0 ? number1 : gcd(number2 , number1 % number2);
}

int Affine::inverseModulo(int number, int modulo)
{
    int x1 = 1, x2 = 0;
    int inverseModulo;
    int modulo_temp = modulo;
    while (number > 0)
    {
        int q = modulo_temp / number;
        int r = modulo_temp - (q * number);
        inverseModulo = x2 - (q * x1);
        modulo_temp = number;
        number = r;
        x2 = x1;
        x1 = inverseModulo;
    }
    inverseModulo = x2;
    if(inverseModulo < 0)
        inverseModulo += modulo;
    return inverseModulo;
}

QList<int> Affine::comparisonByModule(int number1, int number2, int modulo) // number1 * solution == number2 (mod modulo)
{
    number1 = (number1 > 0) ? number1 : number1 + modulo;
    number2 = (number2 > 0) ? number2 : number2 + modulo;
    QList<int> solutionsModuleComparison;
    int gcdNumber1Modulo = gcd(number1, modulo);
    if(number2 % gcdNumber1Modulo == 0)
    {
        int new_number1 = number1 / gcdNumber1Modulo;
        int new_number2 = number2 / gcdNumber1Modulo;
        int new_modulo = modulo / gcdNumber1Modulo;
        int solution = (inverseModulo(new_number1, new_modulo) * new_number2) % new_modulo;
        if(solution < 0)
            solution += new_modulo;
        for(int indexSolution = 0; indexSolution < gcdNumber1Modulo; ++indexSolution)
            solutionsModuleComparison.append(solution + (indexSolution * new_modulo));
    }
    return solutionsModuleComparison;

}

void Affine::changeText()
{
    m_text = m_text.toLower();
    for(int indexText = 0; indexText < m_text.length(); ++indexText)
        if (!alphabet.contains(m_text[indexText]))
            m_text.remove(indexText--, 1);
}

bool Affine::isKeyCorrect()
{
    return ((m_key1 > 0) && (m_key2 >= 0) && (m_key1 < (lenghtAlphabet * lenghtAlphabet)) && (m_key2 < (lenghtAlphabet * lenghtAlphabet)) && (gcd(m_key1, lenghtAlphabet) == 1));
}

void Affine::encrypt()
{
    if(isKeyCorrect()){
        changeText();
        int lenghtText = m_text.length();
        int bigramNumber;
        for(int indexText = 1; indexText < lenghtText; ++++indexText)
        {
            bigramNumber = alphabet.indexOf(m_text[indexText - 1]) * lenghtAlphabet + alphabet.indexOf(m_text[indexText]);
            bigramNumber = (m_key1 * bigramNumber + m_key2) % (lenghtAlphabet * lenghtAlphabet);
            m_text[indexText - 1] = alphabet[bigramNumber / lenghtAlphabet];
            m_text[indexText] = alphabet[bigramNumber % lenghtAlphabet];
        }
    }
    else
        setText("Incorrect Key!!!");

}

void Affine::decrypt()
{
    if(isKeyCorrect()){
        int lenghtText = m_text.length();
        int bigramNumber;
        for(int indexText = 1; indexText < lenghtText; ++++indexText)
        {
            bigramNumber = alphabet.indexOf(m_text[indexText - 1]) * lenghtAlphabet + alphabet.indexOf(m_text[indexText]);
            bigramNumber = inverseModulo(m_key1, (lenghtAlphabet * lenghtAlphabet)) * (bigramNumber - m_key2 + (lenghtAlphabet * lenghtAlphabet)) % (lenghtAlphabet * lenghtAlphabet);
            m_text[indexText - 1] = alphabet[bigramNumber / lenghtAlphabet];
            m_text[indexText] = alphabet[bigramNumber % lenghtAlphabet];
        }
    }
    else
        setText("Incorrect Key!!!");
}

QList<QPair<int, int> > Affine::findKeys()
{
    QList<QPair<int, int> > m_keys;
    QList<int> m_keys1;
    QList<QString> m_mostFrequentBigrams;
    QList<QPair<QString, int> > bigramsFrequency;
    QPair<QString, int> bigramFrequency;
    for(int indexAlphabet1 = 0; indexAlphabet1 < lenghtAlphabet; ++indexAlphabet1)
        for(int indexAlphabet2 = 0; indexAlphabet2 < lenghtAlphabet; ++indexAlphabet2)
        {
            bigramFrequency.first = "";
            bigramFrequency.first.append(alphabet[indexAlphabet1]);
            bigramFrequency.first.append(alphabet[indexAlphabet2]);
            bigramFrequency.second = m_text.count(bigramFrequency.first);
            bigramsFrequency.append(bigramFrequency);
        }
    std::sort(bigramsFrequency.begin(), bigramsFrequency.end(), QPairSecondComparer());
    int bigramNumber1, bigramNumber2, m_bigramNumber1, m_bigramNumber2;
    for(int indexBigram = 0; indexBigram < lenghtMostFrequentBigrams; ++indexBigram)
        m_mostFrequentBigrams.append(bigramsFrequency[indexBigram].first);
    QList<int> m_keys1_temp;
    int m_key2_temp;
    for(int indexBigram1 = 0; indexBigram1 < lenghtMostFrequentBigrams; ++indexBigram1)
        for(int indexBigram2 = 0; indexBigram2 < lenghtMostFrequentBigrams; ++indexBigram2)
            for(int m_indexBigram1 = 0; m_indexBigram1 < lenghtMostFrequentBigrams; ++m_indexBigram1)
                for(int m_indexBigram2 = 0; m_indexBigram2 < lenghtMostFrequentBigrams; ++m_indexBigram2)
                    if((indexBigram1 != indexBigram2) && (m_indexBigram1 != m_indexBigram2))
                    {
                        bigramNumber1 = alphabet.indexOf(mostFrequentBigrams[indexBigram1][0]) * lenghtAlphabet + alphabet.indexOf(mostFrequentBigrams[indexBigram1][1]);
                        bigramNumber2 = alphabet.indexOf(mostFrequentBigrams[indexBigram2][0]) * lenghtAlphabet + alphabet.indexOf(mostFrequentBigrams[indexBigram2][1]);
                        m_bigramNumber1 = alphabet.indexOf(m_mostFrequentBigrams[m_indexBigram1][0]) * lenghtAlphabet + alphabet.indexOf(m_mostFrequentBigrams[m_indexBigram1][1]);
                        m_bigramNumber2 = alphabet.indexOf(m_mostFrequentBigrams[m_indexBigram2][0]) * lenghtAlphabet + alphabet.indexOf(m_mostFrequentBigrams[m_indexBigram2][1]);
                        m_keys1_temp = comparisonByModule(bigramNumber1 - bigramNumber2, m_bigramNumber1 - m_bigramNumber2, lenghtAlphabet * lenghtAlphabet);
                        for(int indexMKeys1Temp = 0; indexMKeys1Temp < m_keys1_temp.length(); ++indexMKeys1Temp)
                            if((m_keys1_temp[indexMKeys1Temp] != 0) && (gcd(m_keys1_temp[indexMKeys1Temp], lenghtAlphabet) == 1))
                            {
                                m_keys1.append(m_keys1_temp[indexMKeys1Temp]);
                                m_key2_temp = (m_bigramNumber1 - m_keys1_temp[indexMKeys1Temp] * bigramNumber1) % (lenghtAlphabet * lenghtAlphabet);
                                if(m_key2_temp < 0)
                                    m_key2_temp += lenghtAlphabet * lenghtAlphabet;
                                m_keys.append(qMakePair(m_keys1_temp[indexMKeys1Temp], m_key2_temp));
                            }
                    }
    for(int indexMKeys = 0; indexMKeys < m_keys.length(); ++indexMKeys)
        if(m_keys.count(m_keys[indexMKeys]) > 1)
        {
            QPair<int, int> m_key_temp = m_keys[indexMKeys];
            m_keys.removeAll(m_keys[indexMKeys--]);
            m_keys.append(m_key_temp);
        }

    return m_keys;
}

void Affine::hack()
{
    QList<QPair<int, int> > m_keys = findKeys();
    QString m_text_start = getText();
    int lenghtKeys = m_keys.length();
    int lenghtText = m_text.length();
    int indexMKeysBest = 0;
    bool correctText;
    std::vector<qreal> coincidenceIndexArray(lenghtKeys);
    for(int indexMKeys = 0; indexMKeys < lenghtKeys; ++indexMKeys)
    {
        setText(m_text_start);
        setKey1(m_keys[indexMKeys].first);
        setKey2(m_keys[indexMKeys].second);
        decrypt();
        coincidenceIndexArray[indexMKeys] = 0;
        for(int indexAlphabet = 0; indexAlphabet < lenghtAlphabet; ++indexAlphabet)
            coincidenceIndexArray[indexMKeys] += m_text.count(alphabet[indexAlphabet]) * (m_text.count(alphabet[indexAlphabet]) - 1);
        coincidenceIndexArray[indexMKeys] /= lenghtText * (lenghtText - 1);
        if(std::fabs(coincidenceIndex - coincidenceIndexArray[indexMKeys]) < std::fabs(coincidenceIndex - coincidenceIndexArray[indexMKeysBest]))
        {
            correctText = true;
            for(int indexProhibitedBigrams = 0; indexProhibitedBigrams < prohibitedBigrams.length(); ++indexProhibitedBigrams)
                if(m_text.count(prohibitedBigrams[indexProhibitedBigrams]) > 0)
                    correctText = false;
            if(correctText)
            {
                indexMKeysBest = indexMKeys;
                qDebug() << m_keys[indexMKeys].first << m_keys[indexMKeys].second;
            }
        }
    }
    setText(m_text_start);
    setKey1(m_keys[indexMKeysBest].first);
    setKey2(m_keys[indexMKeysBest].second);
    decrypt();
}
