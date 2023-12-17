#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_File_triggered();

    void on_actionSave_File_triggered();

    void on_actionSave_As_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionRedo_triggered();

    void on_actionUndo_triggered();

    void on_actionNew_File_triggered();

    void on_actionExit_triggered();

    void on_TextEditBox_textChanged();

    void on_actionAbout_triggered();



private:
    Ui::MainWindow *ui;
    QString File_path, Filter_Extentions;
    void CallErrorMassage();
    void CheckForOpenFiles();
    bool CheckForWhiteSpaces(const std::string &str);
    void LoadApplicationDependences();
};
#endif // MAINWINDOW_H
