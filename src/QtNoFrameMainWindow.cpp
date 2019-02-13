#include "QtNoFrameMainWindow.h"

QtNoFrameMainWindow::QtNoFrameMainWindow(QWidget *parent , Qt::WindowFlags flags)
	: QMainWindow(parent,flags), m_postype(NONE)
{
	this->setWindowFlag(Qt::WindowType::FramelessWindowHint);
	this->setMouseTracking(true);
	
}

QtNoFrameMainWindow::~QtNoFrameMainWindow()
{
}

void QtNoFrameMainWindow::mousePressEvent(QMouseEvent *e)
{
	// 获取窗体在屏幕上的位置区域，tl为topleft点，rb为rightbottom点
	if (e->button() == Qt::LeftButton)
	{
		QRect rect = this->rect();
		QPoint tl = mapToGlobal(rect.topLeft());
		QPoint rb = mapToGlobal(rect.bottomRight());
		QPoint ptthis = mapToGlobal(e->pos());
		int x = ptthis.x();
		int y = ptthis.y();

		if (tl.x() + PADDING >= x && tl.x() <= x && tl.y() + PADDING >= y && tl.y() <= y) {
			// 左上角
			m_postype = LEFTTOP;
			//this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
		}
		else if (x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y()) {
			// 右下角
			m_postype = RIGHTBOTTOM;
			//this->setCursor(QCursor(Qt::SizeFDiagCursor));
		}
		else if (x <= tl.x() + PADDING && x >= tl.x() && y >= rb.y() - PADDING && y <= rb.y()) {
			//左下角
			m_postype = LEFTBOTTOM;
			//this->setCursor(QCursor(Qt::SizeBDiagCursor));
		}
		else if (x <= rb.x() && x >= rb.x() - PADDING && y >= tl.y() && y <= tl.y() + PADDING) {
			// 右上角
			m_postype = RIGHTTOP;
			//this->setCursor(QCursor(Qt::SizeBDiagCursor));
		}
		else if (x <= tl.x() + PADDING && x >= tl.x()) {
			// 左边
			m_postype = LEFT;
			//this->setCursor(QCursor(Qt::SizeHorCursor));
		}
		else if (x <= rb.x() && x >= rb.x() - PADDING) {
			// 右边
			m_postype = RIGHT;
			//this->setCursor(QCursor(Qt::SizeHorCursor));
		}
		else if (y >= tl.y() && y <= tl.y() + PADDING) {
			// 上边
			m_postype = TOP;
			//this->setCursor(QCursor(Qt::SizeVerCursor));
		}
		else if (y <= rb.y() && y >= rb.y() - PADDING) {
			// 下边
			m_postype = BOTTOM;
			//this->setCursor(QCursor(Qt::SizeVerCursor));
		}
		else {
			// 默认
			m_postype = NONE;
		    m_dragPosition = ptthis - tl;
			//this->setCursor(QCursor(Qt::ArrowCursor));
		}
	}
	return QMainWindow::mousePressEvent(e);
}

void QtNoFrameMainWindow::mouseMoveEvent(QMouseEvent *e)
{
	QPoint gloPoint = e->globalPos();
	QRect rect = this->rect();
	QPoint tl = mapToGlobal(rect.topLeft());
	QPoint rb = mapToGlobal(rect.bottomRight());
	if (e->buttons() & Qt::LeftButton)
	{
		if (m_postype != NONE)
		{
			QRect rMove(tl, rb);

			switch (m_postype) 
			{
			case LEFT:
				if (rb.x() - gloPoint.x() <= this->minimumWidth())
					rMove.setX(tl.x());
				else
					rMove.setX(gloPoint.x());
				break;
			case RIGHT:
				rMove.setWidth(gloPoint.x() - tl.x());
				break;
			case TOP:
				if (rb.y() - gloPoint.y() <= this->minimumHeight())
					rMove.setY(tl.y());
				else
					rMove.setY(gloPoint.y());
				break;
			case BOTTOM:
				rMove.setHeight(gloPoint.y() - tl.y());
				break;
			case LEFTTOP:
				if (rb.x() - gloPoint.x() <= this->minimumWidth())
					rMove.setX(tl.x());
				else
					rMove.setX(gloPoint.x());
				if (rb.y() - gloPoint.y() <= this->minimumHeight())
					rMove.setY(tl.y());
				else
					rMove.setY(gloPoint.y());
				break;
			case RIGHTTOP:
				rMove.setWidth(gloPoint.x() - tl.x());
				rMove.setY(gloPoint.y());
				break;
			case LEFTBOTTOM:
				rMove.setX(gloPoint.x());
				rMove.setHeight(gloPoint.y() - tl.y());
				break;
			case RIGHTBOTTOM:
				rMove.setWidth(gloPoint.x() - tl.x());
				rMove.setHeight(gloPoint.y() - tl.y());
				break;
			default:
				break;
			}
			this->setGeometry(rMove);
		}
		else 
		{
			move(gloPoint - m_dragPosition);
			e->accept();
		}
	}
	else
	{
		int x = gloPoint.x();
		int y = gloPoint.y();

		if (tl.x() + PADDING >= x && tl.x() <= x && tl.y() + PADDING >= y && tl.y() <= y) {
			// 左上角
			this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
		}
		else if (x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y()) {
			// 右下角
			this->setCursor(QCursor(Qt::SizeFDiagCursor));
		}
		else if (x <= tl.x() + PADDING && x >= tl.x() && y >= rb.y() - PADDING && y <= rb.y()) {
			//左下角
			this->setCursor(QCursor(Qt::SizeBDiagCursor));
		}
		else if (x <= rb.x() && x >= rb.x() - PADDING && y >= tl.y() && y <= tl.y() + PADDING) {
			// 右上角
			this->setCursor(QCursor(Qt::SizeBDiagCursor));
		}
		else if (x <= tl.x() + PADDING && x >= tl.x()) {
			// 左边
			this->setCursor(QCursor(Qt::SizeHorCursor));
		}
		else if (x <= rb.x() && x >= rb.x() - PADDING) {
			// 右边
			this->setCursor(QCursor(Qt::SizeHorCursor));
		}
		else if (y >= tl.y() && y <= tl.y() + PADDING) {
			// 上边
			this->setCursor(QCursor(Qt::SizeVerCursor));
		}
		else if (y <= rb.y() && y >= rb.y() - PADDING) {
			// 下边
			this->setCursor(QCursor(Qt::SizeVerCursor));
		}
		else {
			// 默认
			this->setCursor(QCursor(Qt::ArrowCursor));
		}
	}
	return QMainWindow::mouseMoveEvent(e);
}

void QtNoFrameMainWindow::mouseReleaseEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		m_postype = NONE;
		this->setCursor(QCursor(Qt::ArrowCursor));
	}
	return QMainWindow::mouseReleaseEvent(e);
}
