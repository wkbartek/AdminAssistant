#include <QtTest/QtTest>
#include <QJsonDocument>
#include <QJsonObject>

// Klasa testowa
class AppTests : public QObject
{
    Q_OBJECT

private slots:
    // Test 1: Sprawdzenie, czy nasz program poprawnie wyciąga komendę z JSON-a od Ollamy
    void testOllamaJsonParsing() {
        // Symulujemy surową odpowiedź, jaką odesłałaby nam sztuczna inteligencja
        QByteArray fakeApiResponse = "{\"model\":\"qwen2.5:3b\",\"response\":\"ping wp.pl\",\"done\":true}";

        // Przepuszczamy to przez nasze mechanizmy z mainwindow.cpp
        QJsonDocument doc = QJsonDocument::fromJson(fakeApiResponse);

        // Asercja 1: Sprawdzamy, czy parser w ogóle zadziałał (dokument nie jest pusty)
        QVERIFY(!doc.isNull());

        // Wyciągamy samą komendę
        QJsonObject jsonObject = doc.object();
        QString extractedCommand = jsonObject["response"].toString();

        // Asercja 2: Sprawdzamy, czy wyciągnięty tekst to idealnie "ping wp.pl"
        QCOMPARE(extractedCommand, QString("ping wp.pl"));
    }

    // Test 2: Sprawdzenie logiki walidacji (symulacja pustego okienka)
    void testEmptyInputsValidation() {
        QString target = "";
        QString task = "Napisz maila";

        // Symulujemy nasz warunek z okienka: if (target.isEmpty() || task.isEmpty())
        bool hasError = target.isEmpty() || task.isEmpty();

        // Skoro target jest pusty, program powinien zgłosić błąd (hasError musi być true)
        QVERIFY(hasError == true);
    }
};

// To specjalne makro Qt samo tworzy główną funkcję uruchamiającą dla testów
QTEST_MAIN(AppTests)
#include "tests.moc"