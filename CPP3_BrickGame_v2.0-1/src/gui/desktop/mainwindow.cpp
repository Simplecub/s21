/**
 * @file mainwindow.cpp
 * @brief GUI functions
 */

#include "mainwindow.h"

using namespace s21;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setMinimumHeight(520);
  setMinimumWidth(480);
  setWindowTitle("BrickGame v2.0");
  setStyleSheet("background: rgb(105, 120, 150);");

  centralWidget = new QWidget();
  gridLayout = new QGridLayout();

  dataField = new DataField(this);
  dataOverlay = new DataOverlay(dataField->params);
  gridLayout->addWidget(dataField, 0, 0);
  gridLayout->addWidget(dataOverlay, 0, 1);
  connect(dataField, &DataField::updateInfoText, dataOverlay,
          &DataOverlay::updateInfoTextSlot);

  centralWidget->setLayout(gridLayout);
  setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {}

DataField::DataField(QWidget *parent) : QWidget(parent) {
  setFixedSize(200, 400);
  setFocusPolicy(Qt::StrongFocus);

  params = new Params_t();
  stats_game = new GameInfo_t();
  params->stats_game = stats_game;
  isStopped = false;

  statsInit(params);
  getStaticParams(params);

  fefreshViewTimer = new QTimer();
  stepTimer = new QTimer();

  connect(fefreshViewTimer, &QTimer::timeout, this, &DataField::repaintT);
  connect(stepTimer, &QTimer::timeout, this, &DataField::tickNext);

  fefreshViewTimer->start(100);
  stepTimer->start(startSpeed - speedDecrement * params->stats_game->speed);
}

DataOverlay::DataOverlay(Params_t *game) {
  setFixedSize(200, 400);
  params = game;
}

DataField::~DataField() {
  delete fefreshViewTimer;
  delete stepTimer;
  delete params;
  delete stats_game;
}

void DataField::repaintT() { repaint(); }

void DataField::tickNext() {
  if (params->status == GAME && !params->stats_game->pause) {
    updateCurrentState();
    emit updateInfoText(params);
    fefreshViewTimer->setInterval(startSpeed -
                                  speedDecrement * params->stats_game->speed);
  }
  isStopped = false;
  repaint();
}
void DataOverlay::updateInfoTextSlot(Params_t *gameParams) {
  params = gameParams;
  repaint();
}

void DataField::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e)
  QBrush gameFieldBrush(QColor(139, 144, 163), Qt::SolidPattern);
  QBrush infoBrush(QColor(200, 200, 200), Qt::SolidPattern);
  QBrush color1CyanBrush(QColor(0, 255, 255), Qt::SolidPattern);
  QBrush color2BlueBrush(QColor(255, 100, 255), Qt::SolidPattern);
  QBrush color3OrangeBrush(QColor(255, 165, 0), Qt::SolidPattern);
  QBrush color4YellowBrush(QColor(255, 255, 0), Qt::SolidPattern);
  QBrush color5GreenBrush(QColor(0, 128, 0), Qt::SolidPattern);
  QBrush color6MagentaBrush(QColor(255, 0, 255), Qt::SolidPattern);
  QBrush color7RedBrush(QColor(255, 0, 0), Qt::SolidPattern);
  QPainter paint;
  paint.begin(this);

  paint.setBrush(gameFieldBrush);
  paint.setPen(QColor(50, 50, 50));
  paint.drawRect(0, 0, width(), height());
  paint.setPen(QColor(0, 0, 0));

  for (size_t row = 0; row < FIELD_HIGHT; ++row) {
    for (size_t col = 0; col < FIELD_WIDTH; ++col) {
      if (params->stats_game->field[row][col]) {
        switch (params->stats_game->field[row][col]) {
          case 1:
            paint.setBrush(color1CyanBrush);
            break;
          case 2:
            paint.setBrush(color2BlueBrush);
            break;
          case 3:
            paint.setBrush(color3OrangeBrush);
            break;
          case 4:
            paint.setBrush(color4YellowBrush);
            break;
          case 5:
            paint.setBrush(color5GreenBrush);
            break;
          case 6:
            paint.setBrush(color6MagentaBrush);
            break;
          case 7:
            paint.setBrush(color7RedBrush);
            break;
          default:
            paint.setBrush(gameFieldBrush);
            break;
        }
        paint.drawRect((col - 0) * cellSize, (row - 0) * cellSize, cellSize,
                       cellSize);
      }
    }
  }

  if (params->status == GameState_t::START) {
    paint.setBrush(infoBrush);
    paint.setPen(QColor(50, 50, 50));
    paint.drawRect(5, height() / 2 - 16, width() - 10, 32);
    paint.setFont(QFont("Times new roman", 12, 700));
    paint.drawText(QRect(5, height() / 2 - 16, width() - 10, 32),
                   Qt::AlignCenter, "Press ENTER to start");
  }

  if (params->status == GameState_t::GAME && params->stats_game->pause) {
    paint.setBrush(infoBrush);
    paint.setPen(QColor(50, 50, 50));
    paint.drawRect(5, height() / 2 - 16, width() - 10, 32);
    paint.setFont(QFont("Times new roman", 12, 700));
    paint.drawText(QRect(5, height() / 2 - 16, width() - 10, 32),
                   Qt::AlignCenter, "PAUSE");
  }

  if (params->status == GameState_t::GAMEOVER) {
    paint.setBrush(infoBrush);
    paint.setPen(QColor(50, 50, 50));
    paint.drawRect(5, height() / 2 - 32, width() - 10, 64);
    paint.setFont(QFont("Times new roman", 12, 700));
#ifdef WIN_SCORE
    paint.drawText(QRect(5, height() / 2 - 32, width() - 10, 64),
                   Qt::AlignCenter,
                   params->stats_game->score == WIN_SCORE
                       ? "YOU WIN\nPress ENTER\nto start again"
                       : "GAMEOVER\nPress ENTER\nto start again");
#else
    paint.drawText(QRect(5, height() / 2 - 32, width() - 10, 64),
                   Qt::AlignCenter, "GAMEOVER\nPress ENTER\nto start again");
#endif
  }

  paint.end();
}

void DataOverlay::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event)
  QBrush gameFieldBrush(QColor(105, 120, 150), Qt::SolidPattern);
  QBrush infoBrush(QColor(200, 200, 200), Qt::SolidPattern);
  QBrush color1CyanBrush(QColor(0, 255, 255), Qt::SolidPattern);
  QBrush color2BlueBrush(QColor(255, 100, 255), Qt::SolidPattern);
  QBrush color3OrangeBrush(QColor(255, 165, 0), Qt::SolidPattern);
  QBrush color4YellowBrush(QColor(255, 255, 0), Qt::SolidPattern);
  QBrush color5GreenBrush(QColor(0, 128, 0), Qt::SolidPattern);
  QBrush color6MagentaBrush(QColor(255, 0, 255), Qt::SolidPattern);
  QBrush color7RedBrush(QColor(255, 0, 0), Qt::SolidPattern);
  QPainter painter;

  painter.begin(this);
  painter.drawRect(0, 0, width() - 1, height() - 1);
  painter.drawRect(0, 250, width() - 1, height() - 1);
  painter.setPen(QColor(250, 250, 250));
  painter.setFont(QFont("Times new roman", 12, QFont::Bold));
  painter.drawText(
      QRect(10, 10, width() - 10, 20), Qt::AlignLeft,
      "HIGH SCORE: " + QString::number(params->stats_game->high_score));
  painter.drawText(QRect(10, 50, width() - 10, 20), Qt::AlignLeft,
                   "SCORE: " + QString::number(params->stats_game->score));
  painter.drawText(QRect(10, 90, width() - 10, 20), Qt::AlignLeft,
                   "LEVEL: " + QString::number(params->stats_game->level));
  painter.drawText(QRect(10, 130, width() - 10, 20), Qt::AlignLeft,
                   "SPEED: " + QString::number(params->stats_game->speed));
  int hintsCoordY = 252;

  if (params->stats_game->next) {
    painter.drawText(QRect(10, 170, width() - 10, 20), Qt::AlignLeft, "NEXT:");
    QColor colorBack{105, 120, 150};
    painter.setPen(QPen(colorBack));
    for (size_t row = 0; row < SIZE_FIG; ++row) {
      for (size_t col = 0; col < SIZE_FIG; ++col) {
        switch (params->stats_game->next[row][col]) {
          case 1:
            painter.setBrush(color1CyanBrush);
            break;
          case 2:
            painter.setBrush(color2BlueBrush);
            break;
          case 3:
            painter.setBrush(color3OrangeBrush);
            break;
          case 4:
            painter.setBrush(color4YellowBrush);
            break;
          case 5:
            painter.setBrush(color5GreenBrush);
            break;
          case 6:
            painter.setBrush(color6MagentaBrush);
            break;
          case 7:
            painter.setBrush(color7RedBrush);
            break;
          default:
            painter.setBrush(gameFieldBrush);
            break;
        }

        painter.drawRect(80 + col * DataField::cellSize,
                         165 + row * DataField::cellSize, DataField::cellSize,
                         DataField::cellSize);
      }
    }
    QColor colorText{250, 250, 250};
    painter.setPen(QPen(colorText));

    painter.drawText(QRect(9, hintsCoordY, width() - 10, 20), Qt::AlignLeft,
                     "SPACE  — Pause game");
    painter.drawText(QRect(37, hintsCoordY += 25, width() - 10, 20),
                     Qt::AlignLeft, "←    —  Left");
    painter.drawText(QRect(37, hintsCoordY += 25, width() - 10, 20),
                     Qt::AlignLeft, "→    —  Right");
    painter.drawText(QRect(37, hintsCoordY += 25, width() - 10, 20),
                     Qt::AlignLeft, "↓      —  Move down");
    painter.drawText(QRect(40, hintsCoordY += 25, width() - 10, 20),
                     Qt::AlignLeft, "R    —  Rotate");
    painter.drawText(QRect(25, hintsCoordY + 25, width() - 10, 20),
                     Qt::AlignLeft, "ESC   —  Exit game");
  } else {
    painter.drawText(QRect(9, hintsCoordY, width() - 10, 20), Qt::AlignLeft,
                     "SPACE  — Pause game");
    painter.drawText(QRect(37, hintsCoordY += 25, width() - 10, 20),
                     Qt::AlignLeft, "←     —  Left");
    painter.drawText(QRect(37, hintsCoordY += 25, width() - 10, 20),
                     Qt::AlignLeft, "→     —  Right");
    painter.drawText(QRect(40, hintsCoordY += 25, width() - 10, 20),
                     Qt::AlignLeft, "R    —  Move Forward");
    painter.drawText(QRect(25, hintsCoordY + 25, width() - 10, 20),
                     Qt::AlignLeft, "ESC   —  Exit game");
  }
  painter.end();
}

void DataField::keyPressEvent(QKeyEvent *event) {
  if (!isStopped) {
    UserAction_t action = UserAction_t::Up;

    if (event->key() == Qt::Key_Return) {
      action = UserAction_t::Start;
    }
    if (event->key() == Qt::Key_Space) {
      action = UserAction_t::Pause;
    }
    if (event->key() == Qt::Key_Escape) {
      action = UserAction_t::Terminate;
    }
    if (event->key() == Qt::Key_Left) {
      action = UserAction_t::Left;
    }
    if (event->key() == Qt::Key_Right) {
      action = UserAction_t::Right;
    }
    if (event->key() == Qt::Key_Up) {
      action = UserAction_t::Up;
    }
    if (event->key() == Qt::Key_Down) {
      action = UserAction_t::Down;
    }
    if (event->key() == Qt::Key_R) {
      action = UserAction_t::Action;
    }

    if (!isStopped) userInput(action, false);
    if (action == UserAction_t::Terminate) {
      emit keyPressed(event);
      close();
      QApplication::quit();
    }
    if (!isStopped) repaint();
  }
}
