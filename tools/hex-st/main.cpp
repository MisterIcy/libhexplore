#include <QApplication>
#include <QFileDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QMenuBar>
#include <QAction>
#include <QMainWindow>
#include <QMessageBox>
#include <libhexplore/io/StandardIO.hpp>
#include <libhexplore/StringTable.hpp>
#include <stdexcept>

class MyApp : public QMainWindow {
public:
    MyApp() {
        table = new QTableWidget(0, 4, this);  // 0 rows, 4 columns
        table->setHorizontalHeaderLabels({"ID", "String", "Integer1", "Integer2"});

        QWidget *centralWidget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);
        layout->addWidget(table);
        centralWidget->setLayout(layout);
        setCentralWidget(centralWidget);

        // Set up the menu
        createMenu();

        setWindowTitle("Hexplore StringTable Editor");
        resize(1024, 768);
    }

private:
    QTableWidget *table;

    void createMenu() {
        // Create a "File" menu with "Load" and "Save As" actions
        QMenu *fileMenu = menuBar()->addMenu("File");

        QAction *loadAction = new QAction("Load", this);

        // Add the actions to the "File" menu
        fileMenu->addAction(loadAction);

        // Connect the menu actions to their respective slots
        connect(loadAction, &QAction::triggered, this, &MyApp::loadFile);
    }

    void loadFile() {
        try {
            QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Hexplore String Table (*.st1)");
            if (!fileName.isEmpty()) {
                libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
                libhexplore::StringTable *st = new libhexplore::StringTable(io);
                st->onStringLoaded = [this](const libhexplore::StringEntry& entry) {
                    int row = table->rowCount();
                    table->insertRow(row);
                    table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(entry.id))));
                    table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(entry.string)));
                    table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(entry.unknown1))));
                    table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(std::to_string(entry.unknown2))));
                };
                
                bool result = st->load(fileName.toStdString());

                if (result == false) {
                    printf("Error Loading File");
                }
            }
        } catch (const std::runtime_error& err) {
            printf("Error: %s\n", err.what());
        }
    }
};
 
int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    MyApp window;
    window.show();

    return app.exec();
}
