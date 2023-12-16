// CS213-2023-20220835-20220334-20220854
// Team:
// Safa Tawfik, 20220835, safatawfik2002@gmail.com
// Mariam Matarawy, 20220334, mariammatar873@gmail.com
// Nafisa Abdalrahman, 20220854, nafnafabdo137@gmail.com


#include <QApplication>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>

class MachineGUI : public QWidget
{
    Q_OBJECT

public:
    MachineGUI(QWidget *parent = 0) : QWidget(parent)
    {
        setupUI();
    }

private slots:
    void loadProgramFile()
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Program File"), "", tr("Text Files (*.txt);;All Files (*)"));
        if (!fileName.isEmpty()) {
            machine.loadProgram(fileName.toStdString());
            executeProgram();
        }
    }

    void executeProgram()
    {
        machine.executeProgram();
        displayStatus();
    }

    void displayStatus()
    {
        // Display the status in the QTextEdit widget
        QString status;
        QTextStream stream(&status);
        stream << "Machine Status:\n";
        stream << "-----------------\n";
        machine.displayStatus();

        textEdit->setText(status);
    }

private:
    void setupUI()
    {
        QVBoxLayout *layout = new QVBoxLayout();

        textEdit = new QTextEdit(this);
        textEdit->setReadOnly(true);
        layout->addWidget(textEdit);

        QPushButton *loadButton = new QPushButton("Load Program", this);
        connect(loadButton, SIGNAL(clicked()), this, SLOT(loadProgramFile()));
        layout->addWidget(loadButton);

        QPushButton *executeButton = new QPushButton("Execute Program", this);
        connect(executeButton, SIGNAL(clicked()), this, SLOT(executeProgram()));
        layout->addWidget(executeButton);

        setLayout(layout);

        setWindowTitle("VoleMachine GUI");
        setFixedSize(400, 300);
    }

    QTextEdit *textEdit;
    Machine machine;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MachineGUI window;
    window.show();

    return app.exec();
}

#include "main.moc"
