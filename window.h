#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>
#include <iostream>
#include <vector>
#include "wuziqi.h"

using namespace std;

class Window : public QMainWindow
{
	Q_OBJECT
public:
	Window(QWidget * parent = 0);
	~Window();

protected:
	void paintEvent(QPaintEvent * event); 
	void mousePressEvent(QMouseEvent * event); 


protected slots:
	void startGame(void); 
	void stopGame(void);  
	void showAbout(void); 	
	void Design(void); 


private:
	void dealMenu(void);  
	int MenuBarSize; 
	wuziqi game;  
	vector<vector<int> > gamedata; 
	int N;  
	POINT lastPs; 
	bool bRun; 
	
};

#endif
