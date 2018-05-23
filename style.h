#ifndef SERVERTCP_H
#define SERVERTCP_H
#include <QStringList>
#include <QSyntaxHighlighter>

class TextStyle : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    TextStyle(QTextDocument* parent = 0);
private:
    QStringList m_lstKeywords, m_lstSeewords;
    QString m_Server;
protected:
    enum {NormalState = -1, InsideCStyleComment, InsideCString};
    virtual void highlightBlock(const QString&);
    QString getKeyWords(int i, const QString& str) const;
    QString setServer(int i, const QString& str) const;
};

#endif // SERVERTCP_H
