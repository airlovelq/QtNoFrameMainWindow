#pragma once

#include <QMainWindow>
#include <QMouseEvent>

//边缘宽度定义
#define PADDING 5
class QtNoFrameMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	QtNoFrameMainWindow(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
	~QtNoFrameMainWindow();

public:
	enum POSTYPE
	{
		NONE,
		LEFT,
		TOP,
		RIGHT,
		BOTTOM,
		LEFTTOP,
		LEFTBOTTOM,
		RIGHTTOP,
		RIGHTBOTTOM
	};
protected:
	virtual void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	virtual void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	virtual void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;

	POSTYPE m_postype;
	QPoint m_dragPosition;   // 窗口移动拖动时需要记住的点 
};
