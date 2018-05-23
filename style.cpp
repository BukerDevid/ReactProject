#include "style.h"

TextStyle::TextStyle(QTextDocument* parent) : QSyntaxHighlighter(parent)
{
    m_lstKeywords << "New Connect" << "authorized";
    m_lstSeewords << "Error" << "Warning";
    m_Server = "Server:";
}

void TextStyle::highlightBlock(const QString& str)
{
    for(int i = 0; i < str.length(); i++){
        /****BEGIN_for****/
        if(str.at(i).isNumber())
        {
            setFormat(i, 1, Qt::yellow);
        }
        else{
            QString strKeyword = getKeyWords(i,str);
        if(!strKeyword.isEmpty())
        {
            setFormat(i, strKeyword.length(), QColor("#FF9010"));
        }
            strKeyword = setServer(i,str);
        if(!strKeyword.isEmpty())
        {
            setFormat(i, strKeyword.length(), QColor("#0080FF"));
        }

            }
        /****END_for****/
    }
}

QString TextStyle::getKeyWords(int i, const QString& str) const
{
    QString strTemp = "";
    foreach (QString strKey, m_lstKeywords) {
        if (str.mid(i, strKey.length()) == strKey) {
            strTemp = strKey;
            break;
        }
    }
    return strTemp;
}

QString TextStyle::setServer(int i, const QString &str) const
{
    QString setTemp = "";
    if(str.mid(i,m_Server.length()) == m_Server)
    {
        setTemp = m_Server;
    }
    return setTemp;
}
