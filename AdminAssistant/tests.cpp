#include <QtTest/QtTest>
#include <QJsonDocument>
#include <QJsonObject>

class AppTests : public QObject
{
    Q_OBJECT

private slots:
    void testOllamaJsonParsing() {
        QByteArray fakeApiResponse = "{\"model\":\"qwen2.5:3b\",\"response\":\"ping wp.pl\",\"done\":true}";

        QJsonDocument doc = QJsonDocument::fromJson(fakeApiResponse);

        QVERIFY(!doc.isNull());

        QJsonObject jsonObject = doc.object();
        QString extractedCommand = jsonObject["response"].toString();

        QCOMPARE(extractedCommand, QString("ping wp.pl"));
    }

    void testEmptyInputsValidation() {
        QString target = "";
        QString task = "Napisz maila";

        bool hasError = target.isEmpty() || task.isEmpty();

        QVERIFY(hasError == true);
    }
};

QTEST_MAIN(AppTests)
#include "tests.moc"
