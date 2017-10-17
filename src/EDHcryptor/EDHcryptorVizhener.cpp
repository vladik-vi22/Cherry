#include "EDHcryptorVizhener.h"

const QString Vizhener::alphabetEnglish = "abcdefghijklmnopqrstuvwxyz";
const QString Vizhener::alphabetSortedByFrequencyEnglish = "eariotnslcudpmhgbfywkvxzjq";
const QString Vizhener::alphabetRussian = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
const QString Vizhener::alphabetSortedByFrequencyRussian = "оеаинтсрвлкмдпуяыьгзбчйхжшюцщэфёъ";
const QString Vizhener::englishLanguage = "english";
const QString Vizhener::russianLanguage = "russian";
const int Vizhener::lenghtAlphabetEnglish = alphabetEnglish.length(); // 26
const int Vizhener::lenghtAlphabetRussian = alphabetRussian.length(); // 33
const qreal Vizhener::coincidenceIndexEnglish = 0.0644;
const qreal Vizhener::coincidenceIndexRussian = 0.0553;
const QList<QString> Vizhener::mostFrequentBigramsEnglish = (QList<QString>() << "th" << "he" << "in" << "er" << "an" << "re" << "es" << "on" << "st" << "nt" << "en" << "at");
const QList<QString> Vizhener::mostFrequentBigramsRussian = (QList<QString>() << "ст" << "ен" << "ов" << "но" << "ни" << "на" << "ра" << "ко" << "то" << "ро" << "ан" << "ос");
const QList<QString> Vizhener::prohibitedBigramsEnglish = (QList<QString>() << "bq" << "cx" << "gx" << "jq" << "jv" << "kx" << "qv" << "qx" << "qz" << "vq" << "xz" << "zq" << "zx");
const QList<QString> Vizhener::prohibitedBigramsRussian = (QList<QString>() << "оъ" << "оы" << "оь" << "еъ" << "еы" << "еь" << "аъ" << "аы" << "аь" << "иъ" << "иы" << "иь" << "уъ" << "уы" << "уь" << "яъ" << "яы" << "яь" << "юъ" << "юы" << "юь" << "эъ" << "эы" << "эь" << "йъ" << "йы" << "йь" << "ёъ" << "ёы" << "ёь" << "ыъ" << "ыы" << "ыь" << "ьъ" << "ьы" << "ьь" << "ъъ" << "ъы" << "ъь");
QString Vizhener::alphabet;
QString Vizhener::alphabetSortedByFrequency;
int Vizhener::lenghtAlphabet;
qreal Vizhener::coincidenceIndex;
QList<QString> Vizhener::mostFrequentBigrams;
QList<QString> Vizhener::prohibitedBigrams;
int Vizhener::lenghtMostFrequentBigrams;

Vizhener::Vizhener(QObject* parent): QObject(parent)
{
    setLanguage(englishLanguage);
}

Vizhener::~Vizhener()
{
}

QString Vizhener::getText() const
{
    return m_text;
}

QString Vizhener::getKey() const
{
    return m_key;
}

QString Vizhener::getLanguage() const
{
    return m_language;
}

void Vizhener::setText(const QString &new_text)
{
    if(m_text != new_text)
    {
        m_text = new_text;
        emit textChanged();
    }
}

void Vizhener::setKey(const QString &new_key)
{
    if(m_key != new_key)
    {
        m_key = new_key;
        emit keyChanged();
    }
}

void Vizhener::setLanguage(const QString &new_language)
{
    if(m_language != new_language)
    {
        m_language = new_language;
        alphabet = isEnglishLanguage() ? alphabetEnglish : alphabetRussian;
        alphabetSortedByFrequency = isEnglishLanguage() ? alphabetSortedByFrequencyEnglish : alphabetSortedByFrequencyRussian;
        lenghtAlphabet = isEnglishLanguage() ? lenghtAlphabetEnglish : lenghtAlphabetRussian;
        coincidenceIndex = isEnglishLanguage() ? coincidenceIndexEnglish : coincidenceIndexRussian;
        mostFrequentBigrams = isEnglishLanguage() ? mostFrequentBigramsEnglish : mostFrequentBigramsRussian;
        prohibitedBigrams = isEnglishLanguage() ? prohibitedBigramsEnglish : prohibitedBigramsRussian;
        lenghtMostFrequentBigrams = mostFrequentBigrams.length();
        emit languageChanged();
    }
}

bool Vizhener::isEnglishLanguage()
{
    return (m_language == englishLanguage);
}

void Vizhener::changeTextKey()
{
    m_text = m_text.toLower();
    m_key = m_key.toLower();
    for(int indexText = 0; indexText < m_text.length(); ++indexText)
        if (!alphabet.contains(m_text[indexText]))
            m_text.remove(indexText--, 1);
}

bool Vizhener::isKeyCorrect()
{
    for(int indexKey = 0; indexKey < m_key.length(); ++indexKey)
        if(!alphabet.contains(m_key[indexKey]))
            return false;
    return true;
}

void Vizhener::encrypt()
{
    if(isKeyCorrect()){
        changeTextKey();
        int lenghtText = m_text.length();
        int lenghtKey = m_key.length();
        for(int indexText = 0; indexText < lenghtText; ++indexText)
            m_text.replace(indexText, 1, alphabet[(alphabet.indexOf(m_text[indexText]) + alphabet.indexOf(m_key[indexText % lenghtKey])) % lenghtAlphabet]);
    }
    else
        setText("Incorrect Key!!!");
}

void Vizhener::decrypt()
{
    if(isKeyCorrect()){
        int lenghtText = m_text.length();
        int lenghtKey = m_key.length();
        for(int indexText = 0; indexText < lenghtText; ++indexText)
            m_text.replace(indexText, 1, alphabet[(alphabet.indexOf(m_text[indexText]) - alphabet.indexOf(m_key[indexText % lenghtKey]) + lenghtAlphabet) % lenghtAlphabet]);
    }
    else
        setText("Incorrect Key!!!");
}

int Vizhener::findShortLenghtKey()
{
    int lenghtText = m_text.length();
    int minLenghtKey = 1;
    int maxLenghtKey = 5;
    int shortLenghtKey = minLenghtKey;
    qreal coincidenceIndexArray[maxLenghtKey + 1];

    for(int lenghtKey = minLenghtKey; lenghtKey <= maxLenghtKey; ++lenghtKey)
    {
        coincidenceIndexArray[lenghtKey] = 0;

        for(int indexSubtext = 0; indexSubtext < lenghtKey; ++indexSubtext)
        {
            QString m_subtext;
            qreal coincidenceIndexTemp;

            for(int indexText = indexSubtext; indexText < lenghtText; indexText += lenghtKey)
                m_subtext.append(m_text[indexText]);

            for(int indexAlphabet = 0; indexAlphabet < lenghtAlphabet; ++indexAlphabet)
                coincidenceIndexTemp += m_subtext.count(alphabet[indexAlphabet]) * (m_subtext.count(alphabet[indexAlphabet]) - 1);

            coincidenceIndexTemp /= m_subtext.length() * (m_subtext.length() - 1);
            coincidenceIndexArray[lenghtKey] += coincidenceIndexTemp;
        }

        coincidenceIndexArray[lenghtKey] /= lenghtKey;

        if(qFabs(coincidenceIndex - coincidenceIndexArray[lenghtKey]) < qFabs(coincidenceIndex - coincidenceIndexArray[shortLenghtKey]))
            shortLenghtKey = lenghtKey;
    }

    return shortLenghtKey;
}

int Vizhener::findLongLenghtKey()
{
    int lenghtText = m_text.length();
    int minLenghtKey = 6;
    int maxLenghtKey = 22;
    int longLenghtKey = minLenghtKey;
    int numberOfIdenticalLettersArray[maxLenghtKey + 1];

    for(int lenghtKey = minLenghtKey; lenghtKey <= maxLenghtKey; ++lenghtKey)
    {
        numberOfIdenticalLettersArray[lenghtKey] = 0;

        for(int indexSubtext = 0; indexSubtext < lenghtKey; ++indexSubtext)
            for(int indexText = indexSubtext; indexText < lenghtText - lenghtKey; indexText += lenghtKey)
                if(m_text[indexText] == m_text[indexText + lenghtKey])
                    numberOfIdenticalLettersArray[lenghtKey]++;

        if(numberOfIdenticalLettersArray[lenghtKey] > numberOfIdenticalLettersArray[longLenghtKey])
            longLenghtKey = lenghtKey;
    }

    return longLenghtKey;
}

QList<QString> Vizhener::findKeys(int keyLenght)
{
    QString key;
    QList<QString> keys;
    int lenghtText = m_text.length();
    QString m_subtext;
    QChar mostFrequentLetter;

    for(int indexSubtext = 0; indexSubtext < keyLenght; ++indexSubtext)
    {
        m_subtext.clear();
        for(int indexText = indexSubtext; indexText < lenghtText; indexText += keyLenght)
            m_subtext.append(m_text[indexText]);
        mostFrequentLetter = alphabet[0];
        for(int indexAlphabet = 0; indexAlphabet < lenghtAlphabet; ++indexAlphabet)
            if(m_subtext.count(alphabet[indexAlphabet]) > m_subtext.count(mostFrequentLetter))
                mostFrequentLetter = alphabet[indexAlphabet];
        key.append(alphabet[(alphabet.indexOf(mostFrequentLetter) - alphabet.indexOf(alphabetSortedByFrequency[0]) + lenghtAlphabet) % lenghtAlphabet]);
    }

    keys.append(key);
    return keys;
}

void Vizhener::hack()
{
    qDebug() << findKeys(findShortLenghtKey())[0];
    qDebug() << findKeys(findLongLenghtKey())[0];
    QList<QString> m_keys = findKeys(findShortLenghtKey()) + findKeys(findLongLenghtKey());
    QString m_text_start = getText();
    int lenghtKeys = m_keys.length();
    int lenghtText = m_text.length();
    int indexMKeysBest = 0;
    bool correctText;
    qreal coincidenceIndexArray[lenghtKeys];
    for(int indexMKeys = 0; indexMKeys < lenghtKeys; ++indexMKeys)
    {
        setText(m_text_start);
        setKey(m_keys[indexMKeys]);
        decrypt();
        coincidenceIndexArray[indexMKeys] = 0;
        for(int indexAlphabet = 0; indexAlphabet < lenghtAlphabet; ++indexAlphabet)
            coincidenceIndexArray[indexMKeys] += m_text.count(alphabet[indexAlphabet]) * (m_text.count(alphabet[indexAlphabet]) - 1);
        coincidenceIndexArray[indexMKeys] /= lenghtText * (lenghtText - 1);
        if(qFabs(coincidenceIndex - coincidenceIndexArray[indexMKeys]) < qFabs(coincidenceIndex - coincidenceIndexArray[indexMKeysBest]))
        {
            correctText = true;
            for(int indexProhibitedBigrams = 0; indexProhibitedBigrams < prohibitedBigrams.length(); ++indexProhibitedBigrams)
                if(m_text.count(prohibitedBigrams[indexProhibitedBigrams] > 0))
                    correctText = false;
            if(correctText)
            {
                indexMKeysBest = indexMKeys;
            }
        }
    }
    setText(m_text_start);
    setKey(m_keys[indexMKeysBest]);
    decrypt();
}
