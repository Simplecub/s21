#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * @file mainwiindow.h
 * @brief  GUI header
 */
#include <QApplication>
#include <QGridLayout>
#include <QKeyEvent>
#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QWidget>

#include "../../controller/controller.h"

namespace s21 {
class DataField;
class DataOverlay;

/** @brief The class of MainWindow
 *
 */
class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  DataField *dataField;
  DataOverlay *dataOverlay;
  QWidget *centralWidget;
  QGridLayout *gridLayout;
};

/** @brief The class of displaying the current state of the playing field
 *
 * @param  parent Pointer to the QWidget *parent
 */
class DataField : public QWidget {
  Q_OBJECT
 public:
  DataField(QWidget *parent);
  Params_t *params;
  GameInfo_t *stats_game;
  UserAction_t *action;
  static const int cellSize = 20;
  bool isStopped;
  ~DataField();

 private:
  QTimer *fefreshViewTimer;
  QTimer *stepTimer;
  static const int startSpeed = 1000;
  static const int speedDecrement = 200;
 private slots:
  void repaintT();
  void tickNext();

 protected:
  void paintEvent(QPaintEvent *e) override;
  void keyPressEvent(QKeyEvent *event) override;
 signals:
  void updateInfoText(Params_t *params);
  void keyPressed(QKeyEvent *event);
};

/** @brief The class displays the interface with the current state
 * during the game
 *
 * @param  game Pointer to the struct of the all information about current state
 */
class DataOverlay : public QWidget {
  Q_OBJECT
 public:
  DataOverlay(Params_t *game);

 private:
  Params_t *params;

 protected:
  void paintEvent(QPaintEvent *event) override;
 public slots:
  void updateInfoTextSlot(Params_t *params);
};
}  // namespace s21
#endif  // MAINWINDOW_H
