#include "texmakerversion.h"

TexmakerVersion::TexmakerVersion()
{
    _versionNumbers.fill(0,3);
    invalidate();
}

TexmakerVersion::TexmakerVersion(const QString &versionString) : TexmakerVersion()
{
    parseString(versionString);
}

TexmakerVersion::TexmakerVersion(int world, int major, int minor) : TexmakerVersion()
{
    _versionNumbers[0] = world;
    _versionNumbers[1] = major;
    _versionNumbers[2] = minor;
    _valid = true;
}

TexmakerVersion TexmakerVersion::getCurrentVersion()
{
    //TODO fix this again
    TexmakerVersion version(4,0,1);
//    version.parseString(QLatin1String(TEXMAKERVERSION));

    if(!version.isValid()) {
        qWarning() << QObject::tr("Unable to parse current version: ") << QLatin1String(TEXMAKERVERSION);
    }

    return version;
}

void TexmakerVersion::parseString(const QString &versionString)
{
    if(!versionString.isEmpty()) {
        QStringList versionNumbers = versionString.split(".");
        if(versionNumbers.size() == 2 || versionNumbers.size() == 3) {
            bool parsingOK = true;

            _versionNumbers[0] = versionNumbers.at(0).toInt(&parsingOK);

            if(parsingOK) {
                _versionNumbers[1] = versionNumbers.at(1).toInt(&parsingOK);
                if(parsingOK) {
                    if(versionNumbers.size() == 3){
                        _versionNumbers[2] = versionNumbers.at(2).toInt(&parsingOK);
                    } else {
                        _versionNumbers[2] = 0;
                    }
                    if(parsingOK) {
                        _valid = true;
                        return;
                    }
                }
            }

        } else {
            qWarning() << QObject::tr("Unexpected version string, unable to parse");
        }
    }
    invalidate();
}

bool TexmakerVersion::isValid() const
{
    return _valid;
}

QString TexmakerVersion::toString(bool allwaysPrintMinor) const
{

    QString versionString = QObject::tr("0.0.0"); //this will be returned if the version is not valid

    if(isValid()){
        versionString = QString("%1.%2").arg(worldVerion()).arg(majorVersion());
        if((minorVersion() != 0) || allwaysPrintMinor) {
            versionString.append(QString(".%1").arg(minorVersion()));
        }
    }
    return versionString;
}

const QVector<int>& TexmakerVersion::getVersionNumber() const
{
    return _versionNumbers;
}

int TexmakerVersion::worldVerion() const
{
    return _versionNumbers.at(0);
}

int TexmakerVersion::majorVersion() const
{
    return _versionNumbers.at(1);
}

int TexmakerVersion::minorVersion() const
{
    return _versionNumbers.at(2);
}

void TexmakerVersion::invalidate()
{
    _versionNumbers.fill(0,3);
    _valid = false;
}

bool operator< (const TexmakerVersion &v1, const TexmakerVersion &v2)
{
    return (v1 != v2) && !(v1 > v2);
}

bool operator> (const TexmakerVersion &v1, const TexmakerVersion &v2)
{
    const QVector<int>& num1 = v1.getVersionNumber();
    const QVector<int>& num2 = v2.getVersionNumber();

    int i = 0;

    for(; i < num1.size()-1; ++i) {
        if(num1.at(i) != num2.at(i)) {
            break;
        }

    }

    return num1.at(i) > num2.at(i);
}

bool operator<= (const TexmakerVersion &v1, const TexmakerVersion &v2)
{
    return (v1 == v2) || (v1 < v2);
}

bool operator>= (const TexmakerVersion &v1, const TexmakerVersion &v2)
{
    return (v1 == v2) || (v1 > v2);
}

bool operator== (const TexmakerVersion &v1, const TexmakerVersion &v2)
{
    return v1.getVersionNumber() == v2.getVersionNumber();
}

bool operator!= (const TexmakerVersion &v1, const TexmakerVersion &v2)
{
    return !(v1 == v2);
}
