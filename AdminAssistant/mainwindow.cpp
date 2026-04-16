#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    networkManager = new QNetworkAccessManager(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Realizuje główny proces asystenta IT.
 * * 1. Wysyła zapytanie do modelu LLM o wygenerowanie komendy CMD.
 * 2. Uruchamia wygenerowaną komendę za pomocą QProcess.
 * 3. Przekazuje wynik działania systemu z powrotem do AI w celu stworzenia raportu.
 * 4. Wyświetla końcowy raport w interfejsie graficznym.
 */

void MainWindow::on_runButton_clicked()
{
    QString target = ui->targetInput->text();
    QString task = ui->taskInput->text();

    if (target.isEmpty() || task.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Proszę wypełnić oba pola!");
        return;
    }

    ui->outputText->setText("KROK 1: Pytam sztuczną inteligencję o komendę...");
    ui->runButton->setEnabled(false);

    QJsonObject json;
    json["model"] = "qwen2.5:3b";
    json["system"] = "Jesteś generatorem komend Windows CMD. Twoim jedynym zadaniem jest zwrócenie poprawnej komendy systemowej. Żadnego tekstu pobocznego, żadnych znaków markdown. Jeśli celem jest adres IP lub domena internetowa, MUSISZ użyć komendy 'ping' (np. ping google.com).";
    json["prompt"] = "Wygeneruj komendę dla celu: " + target;
    json["stream"] = false;

    QNetworkRequest request(QUrl("http://localhost:11434/api/generate"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->post(request, QJsonDocument(json).toJson());

    connect(reply, &QNetworkReply::finished, this, [this, reply, task]() {
        if (reply->error() == QNetworkReply::NoError) {

            QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll()).object();
            QString aiCommand = jsonObject["response"].toString().trimmed();
            aiCommand.replace("`", "");

            ui->outputText->setText("KROK 2: AI wygenerowało komendę:\n[" + aiCommand + "]\n\nKROK 3: Wykonuję w systemie...");

            QProcess *process = new QProcess(this);

            connect(process, &QProcess::finished, this, [this, process, task]() {
                QString output = QString::fromLocal8Bit(process->readAllStandardOutput());
                QString error = QString::fromLocal8Bit(process->readAllStandardError());
                QString fullSystemOutput = output + "\n" + error;

                ui->outputText->append("\nKROK 4: System zwrócił surowe dane. Wysyłam do AI z prośbą o napisanie raportu...");

                QJsonObject json2;
                json2["model"] = "qwen2.5:3b";
                json2["system"] = "Jesteś profesjonalnym asystentem IT. ZAWSZE pisz w poprawnym języku polskim. Otrzymasz surowy wynik z konsoli Windows. " + task;
                json2["prompt"] = "Surowy wynik z systemu:\n" + fullSystemOutput;
                json2["stream"] = false;

                QNetworkRequest request2(QUrl("http://localhost:11434/api/generate"));
                request2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

                QNetworkReply *reply2 = networkManager->post(request2, QJsonDocument(json2).toJson());

                connect(reply2, &QNetworkReply::finished, this, [this, reply2, process]() {
                    if (reply2->error() == QNetworkReply::NoError) {
                        QJsonObject jsonObject2 = QJsonDocument::fromJson(reply2->readAll()).object();
                        QString finalReport = jsonObject2["response"].toString().trimmed();

                        ui->outputText->append("\n\n================== GOTOWY RAPORT ==================\n" + finalReport);
                    } else {
                        ui->outputText->append("\nBłąd podczas generowania raportu: " + reply2->errorString());
                    }

                    reply2->deleteLater();
                    process->deleteLater();
                    ui->runButton->setEnabled(true);
                });
            });

            process->start("cmd.exe", QStringList() << "/c" << aiCommand);

        } else {
            ui->outputText->setText("BŁĄD łączności z Ollamą: " + reply->errorString());
            ui->runButton->setEnabled(true);
        }
        reply->deleteLater();
    });
}
