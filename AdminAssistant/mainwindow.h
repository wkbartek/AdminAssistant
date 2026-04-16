/**
 * @file mainwindow.h
 * @brief Główny plik nagłówkowy okna aplikacji AdminAssistant.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Klasa zarządzająca głównym oknem aplikacji i logiką asystenta IT.
 * * Klasa odpowiada za komunikację z modelem LLM (Ollama) oraz wykonywanie
 * komend systemowych w tle.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @brief Konstruktor klasy MainWindow.
     * @param parent Wskaźnik na obiekt rodzica.
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destruktor klasy MainWindow.
     */
    ~MainWindow() override;

private slots:
    /**
     * @brief Slot wywoływany po kliknięciu przycisku uruchamiającego proces.
     * * Funkcja realizuje pełną pętlę: generowanie komendy przez AI,
     * wykonanie jej w systemie oraz analizę wyników.
     */
    void on_runButton_clicked();

private:
    Ui::MainWindow *ui;/**< Wskaźnik na interfejs użytkownika. */
    QNetworkAccessManager *networkManager;/**< Menedżer komunikacji sieciowej z API Ollama. */
};
#endif