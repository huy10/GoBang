#include "window.h"

Window::Window(QWidget * parent)
	: QMainWindow(parent)
{
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	setWindowTitle(tr("Gobang!"));
	N = 15;  //size of game
	MenuBarSize = 10;
	setFixedSize(320+MenuBarSize, 320+MenuBarSize);
	bRun = true;  // bRun is a universal variable
	//Method = 2;
	vector<int> temp(N, 0);
	for (int i = 0; i < N; i++)
	{
		gamedata.push_back(temp);
	}
	dealMenu();
}

Window::~Window()
{
}

void Window::paintEvent(QPaintEvent * event)
{
	
	QPainter painter(this);
	painter.setBrush(Qt::lightGray);
	painter.drawRect(0, 0, size().width(), size().height());
       
	game.GetData(gamedata);
	
	for (int x = 20+MenuBarSize; x <= N*20+MenuBarSize; x += 20)
	{
		painter.drawLine(x, 20+MenuBarSize, x, N*20+MenuBarSize); 
	}
	for (int y = 20+MenuBarSize; y <= N*20+MenuBarSize; y += 20)
	{
		painter.drawLine(20+MenuBarSize, y, N*20+MenuBarSize, y);
	}
	
	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N; y++)
		{
			if (gamedata[x][y] == 1) 
			{
				QPainter blackPainter(this);
					blackPainter.setBrush(QBrush("#004fc5"));
					blackPainter.drawEllipse((x+1)*20-10+MenuBarSize, 
						(y+1)*20-10+MenuBarSize, 20, 20);
			}
			else if (gamedata[x][y] == 2) 
			{
					QPainter whitePainter(this);
					whitePainter.setBrush(QBrush("#4c4c4c"));
					whitePainter.drawEllipse((x+1)*20-10+MenuBarSize,
						(y+1)*20-10+MenuBarSize, 20, 20);
			}
		}
	}

	QMainWindow::paintEvent(event);
}

void Window::mousePressEvent(QMouseEvent * event)
{
	//fall
	if (event->button() == Qt::LeftButton && bRun == true)
	{
		int x = event->x();
		int y = event->y();
		POINT ps;
		ps.x = x;
		ps.y = y;
		if (ps.x < 10+MenuBarSize || ps.y < 10+MenuBarSize ||
		    ps.x > 300+20+MenuBarSize || ps.y > 300+20+MenuBarSize)
		{
			return;
		}
		if (!game.Fall(ps, 1, 20+MenuBarSize, 300+20+MenuBarSize))
		{
			return;
		}
		game.Run(ps, 2, 2);
		lastPs = ps;
		ps.x = 20 + MenuBarSize + ps.x*20;
		ps.y = 20 + MenuBarSize + ps.y*20;
		game.Fall(ps, 2, 20+MenuBarSize, 300+20+MenuBarSize);
		game.GetData(gamedata);
		update();
		int player = 0; 
		game.Judge(player);
		if (player == 1) //player
		{
			QMessageBox::information(this, tr("Game Over"),
				tr("YOU WIN"));
			bRun = false;
		}
		else if (player == 2) //computer
		{
			QMessageBox::information(this, tr("Game Over"),
				tr("YOU LOSE"));
			bRun = false;
		}
	}
}

void Window::dealMenu(void)
{
	QMenuBar * MenuBar = new QMenuBar(this);
	QMenu * GameMenu = new QMenu(tr("GAME"), MenuBar);
	QMenu * HelpMenu = new QMenu(tr("Help"), MenuBar);

	QAction * StartGame = new QAction(tr("Start"), GameMenu);
	QAction * StopGame = new QAction(tr("End"), GameMenu);
	QAction * QuitGame = new QAction(tr("Quit"), GameMenu);
	GameMenu->addAction(StartGame);
	GameMenu->addAction(StopGame);
	GameMenu->addAction(QuitGame);
	MenuBar->addMenu(GameMenu);
	connect(StartGame, SIGNAL(triggered()), this, SLOT(startGame()));
	connect(StopGame, SIGNAL(triggered()), this, SLOT(stopGame()));
	connect(QuitGame, SIGNAL(triggered()), this, SLOT(close()));


	QAction * About = new QAction(tr("About"), HelpMenu);
	HelpMenu->addAction(About);
	MenuBar->addMenu(HelpMenu);
	connect(About, SIGNAL(triggered()), this, SLOT(showAbout()));


	setMenuBar(MenuBar);
}

void Window::startGame(void)
{
	if (bRun == false)
	{
		bRun = true;
		game.Clear();
		game.Init();
		lastPs.x = -1; lastPs.y = -1;
		update();
	}
}

void Window::stopGame(void)
{
	if (bRun == true)
	{
		bRun = false;
		game.Clear();
		lastPs.x = -1; lastPs.y = -1;
		update();
	}
}

void Window::showAbout(void)
{
	QMessageBox::information(this, tr("Gobang"),
		tr("Developed by HU YANG"));
}

void Window::Design(void)
{

	stopGame();
	startGame();
}


