#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QImage>
#include <iostream>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintDevice>
#include <QPoint>
#include <algorithm>
#include <chrono>
#define maxVer 10000

int maxHt, maxWd;

using namespace std;
using namespace std::chrono;
int gridsize=1;
int vertex_count = 0;

QImage img;
// polygon drawing
std::vector<std::pair<int,int> > vertex_list;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->x_axis->hide();
    ui->y_axis->hide();
    maxHt = ui->frame->height();
    maxWd = ui->frame->width();

    // set the image over the frame
    img=QImage(ui->frame->width(), ui->frame->height(), QImage::Format_RGB888);

    connect(ui->frame, SIGNAL(Mouse_Pos()), this, SLOT(Mouse_Pressed()));
    connect(ui->frame, SIGNAL(sendMousePosition(QPoint&)), this, SLOT(showMousePosition(QPoint&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// function to illuminate a point based on coordinates
void MainWindow::point(int x,int y, int r=150, int g=150, int b=150)
{
    if(gridsize == 1)
        img.setPixel(x,y,qRgb(r, g, b));  // set just one pixel
    else {
        // get the top-left pixel coordinates
        x = (x / gridsize) * gridsize;
        y = (y / gridsize) * gridsize;

        // set all the pixels within that square region, representing one point
        for(int i = x + 1; i <  x + gridsize && i < ui->frame->width(); i++) {
            for(int j = y + 1; j < y + gridsize && j < ui->frame->height(); j++) {
                img.setPixel(i, j, qRgb(r, g, b));
            }
        }
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));
}

// function to convert a pixel to x coordinate
int getXCoordinate (int px) {
    int width = img.width();
    int midx = (width/(2*gridsize))*gridsize;
    if (px >= midx  && px <= midx  + gridsize)
        px = 0;
    else if (px >= width/2)
        px = (px - midx - gridsize)/gridsize + 1 ;
    else
        px = -((midx  - px)/gridsize + 1) ;
    return px;
}

// function to convert a pixel to y coordinate
int getYCoordinate (int py) {
    int height = img.height();
    int midy = (height/(2*gridsize))*gridsize;
    if(py >= midy && py <= midy + gridsize)
        py = 0;
    else if(py >= height/2)
        py = -((py - midy - gridsize)/gridsize + 1);
    else
        py = (midy - py)/gridsize + 1;
    return py;
}

int toXPixel (int x) {
    int width = img.width();
    int midx = (width/(2*gridsize))*gridsize;
    return midx + x*gridsize;
}

int toYPixel (int y) {
    int height = img.height();
    int midy = (height/(2*gridsize))*gridsize;
    return midy - y*gridsize;
}

void delay () {
    int SLEEP_ms = 30;
    QTime dieTime= QTime::currentTime().addMSecs(SLEEP_ms);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::showMousePosition(QPoint &pos)
{
    // compute x, y with respect to origin (x:width/2, y:height/2) and gridsize
    int x = getXCoordinate(pos.x());
    int y = getYCoordinate(pos.y());

    // set the text for mouse position
    const QString posText = "X : " + QString::number(x) + ", Y : " + QString::number(y);
    ui->mouse_movement->setText(posText);
}

void MainWindow::Mouse_Pressed()
{
    // compute x, y with respect to origin (x:width/2, y:height/2) and gridsize
    int x = getXCoordinate(ui->frame->x);
    int y = getYCoordinate(ui->frame->y);

    // set the text for mouse position
    const QString posText = "X : "+QString::number(x)+", Y : "+QString::number(y);
    ui->mouse_pressed->setText(posText);

    // illuminate the point pressed
    point(ui->frame->x,ui->frame->y);
    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_show_axes_clicked()
{
    if(ui->show_axes->isChecked())
    {
        // set x-axis
        for(int i = 0; i < ui->frame->width(); i += gridsize)
            point(i, img.height() / 2);

        // set y-axis
        for(int j = 0; j <  ui->frame->height(); j+= gridsize)
            point(img.width() / 2, j);

    }
    else
    {
        // unset x-axis
        for(int i = 0; i < ui->frame->width(); i += gridsize)
            point(i, img.height() / 2, 0, 0, 0);

        // unset y-axis
        for(int j = 0; j <  ui->frame->height(); j+= gridsize)
            point(img.width() / 2, j, 0, 0, 0);
    }

    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void clearFrame() {
    // set all the pixels to black colour
    for(int i = 0; i < img.width(); i++)
        for(int j = 0; j < img.height(); j++)
            img.setPixel(i, j, qRgb(0, 0, 0));
}

void MainWindow::on_resetButton_clicked()
{
    clearFrame();
    ui->show_axes->setChecked(false);
    ui->mouse_movement->setText("");
    ui->mouse_pressed->setText("");
    ui->frame->setPixmap(QPixmap::fromImage(img));

    vertex_list.clear();
    initEdgeTable();
}

void MainWindow::on_setgridbutton_clicked()
{
    clearFrame();

    // get the gridsize
    gridsize = ui->gridsize->value();

    // set the gridsize, only if it is greater than 1
    if(gridsize>1)
    {
        for(int i = 0; i < img.width(); i += gridsize)
            for(int j = 0; j < img.height(); j++)
            {
                img.setPixel(i,j,qRgb(180,180,180));
                img.setPixel(j,i,qRgb(180,180,180));
            }
    }

    // check if show axes button is checked
    on_show_axes_clicked();
    ui->frame->setPixmap(QPixmap::fromImage(img));

    const QString posText = "X : 0, Y : 0";
    ui->originValue->setText(posText);
    origin.setX(toXPixel(0));
    origin.setY(toYPixel(0));

    vertex_list.clear();
    initEdgeTable();
}

void MainWindow::on_set_point1_clicked()
{
    p1.setX((ui->frame->x/gridsize)*gridsize + gridsize/2);
    p1.setY((ui->frame->y/gridsize)*gridsize + gridsize/2);
}

void MainWindow::on_set_point2_clicked()
{
    p2.setX((ui->frame->x/gridsize)*gridsize + gridsize/2);
    p2.setY((ui->frame->y/gridsize)*gridsize + gridsize/2);
}

void MainWindow::DDALINE (int r, int g, int b) {
    int x1 = getXCoordinate(p1.x()), y1 = getYCoordinate(p1.y());
    int x2 = getXCoordinate(p2.x()), y2 = getYCoordinate(p2.y());

    auto start = high_resolution_clock::now();
    auto pointDuration = start - start;

    float x = x1, y = y1;       // initial coordinates
    int dx = abs(x2 - x1), dy = abs(y2 - y1);       // total span in x and y

    float Dx, Dy;       // increments in x and y
    int steps;

    // if slope is infinite
    if (dy == 0) {
        Dy = 0;
        Dx = 1;
        steps = abs(dx);
    }
    // if slope of line is < 1, get y(x)
    else if (dx > dy)
    {
        Dx = 1;
        Dy = float(dy)/dx;
        steps = abs(dx);
    }
    // if slope is > 1, get x(y)
    else
    {
        Dx = float(dx)/dy;
        Dy = 1;
        steps = abs(dy);
    }

    // if starting point is greater, then decrement is needed
    if(x1 > x2) Dx *= -1;
    if(y1 > y2) Dy *= -1;

    for (int k = 0; k <= steps; k++) {
        // round off to the nearest coordinates
        int ix = floor(x + 0.5);
        int iy = floor(y + 0.5);

        auto start1 = high_resolution_clock::now();
        // transform the coordinates to the original pixels
        point (toXPixel(ix), toYPixel(iy), r, g, b);
        auto stop1 = high_resolution_clock::now();
        pointDuration += stop1 - start1;

        // increment to get the next coordinate
        x += Dx;
        y += Dy;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start - pointDuration);

    ui->timeValue->setText (QString::number(duration.count()) + " µs");

    ui->frame->setPixmap(QPixmap::fromImage(img));
}

// DDA (Digital Differential Analyzer) line drawing algorithm
void MainWindow::on_DDALine_clicked()
{
    DDALINE(240,4,4);
}

void MainWindow::BresenhamLINE (int r, int g, int b) {
    int x0 = getXCoordinate(p1.x()), y0 = getYCoordinate(p1.y());
    int xn = getXCoordinate(p2.x()), yn = getYCoordinate(p2.y());

    auto start = high_resolution_clock::now();
    auto pointDuration = start - start;

    int Dx = abs(xn - x0), Dy = abs(yn - y0);
    int ix = (x0 > xn ? -1: 1), iy = (y0 > yn ? -1: 1);
    bool flag = true;

    int x = x0, y = y0;
    if (Dy > Dx) {
        swap (x, y);
        swap (Dx, Dy);
        swap (ix, iy);
        flag = false;
    }

    int p = 2*Dy - Dx, ip1 = 2*Dy, ip2 = 2*Dy - 2*Dx;

    for (int i = 0; i <= Dx; i++) {
        auto start1 = high_resolution_clock::now();
        if (flag)
            point (toXPixel(x), toYPixel(y),r,g,b);
        else
            point (toXPixel(y), toYPixel(x), r,g,b);
        auto stop1 = high_resolution_clock::now();
        pointDuration += stop1 - start1;
        if (p < 0) {
            p += ip1;
        }
        else {
            p += ip2;
            y += iy;
        }
        x += ix;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start - pointDuration);

    ui->timeValue->setText (QString::number(duration.count()) + " µs");

    ui->frame->setPixmap(QPixmap::fromImage(img));
}

// Bresenham line drawing algorithm
void MainWindow::on_BresenhamLine_clicked()
{
    BresenhamLINE (240, 4, 4);
}

void MainWindow::on_circleCenter_clicked()
{
    cp1.setX(ui->frame->x);
    cp1.setY(ui->frame->y);
}

void MainWindow::on_PolarCircle_clicked()
{
    int cx = getXCoordinate(cp1.x()), cy = getYCoordinate(cp1.y());
    int radius = ui->circleRadius->value();

    auto start = high_resolution_clock::now();
    auto stop = start;
    auto duration = stop - start;

    for (double theta = 0; theta * 180 / M_PI < 360; theta += 1.0 / radius) {
        auto start = high_resolution_clock::now();

        // compute the points
        float x = cx + radius * cos(theta);
        float y = cy + radius * sin(theta);

        // round off to the nearest integer
        int ix = floor (x + 0.5);
        int iy = floor (y + 0.5);

        auto stop = high_resolution_clock::now();
        duration += stop - start;
        delay();
        point (toXPixel(ix), toYPixel(iy), 240, 4, 4);
    }

    ui->timeValue->setText (QString::number(duration_cast<microseconds>(duration).count()) + " µs");

    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_BresenhamCircle_clicked()
{
    int cx = getXCoordinate(cp1.x()), cy = getYCoordinate(cp1.y());
    int radius = ui->circleRadius->value();

    auto start = high_resolution_clock::now();
    auto pointDuration = start - start;

    int x = 0, y = radius;

    int p = 1 - radius;

    while (x <= y) {
        auto start1 = high_resolution_clock::now();
        delay();

        point(toXPixel(cx + x), toYPixel(cy + y), 127, 255, 0);
        point(toXPixel(cx + x), toYPixel(cy - y), 204, 102, 0);
        point(toXPixel(cx - x), toYPixel(cy + y), 255, 255, 0);
        point(toXPixel(cx - x), toYPixel(cy - y), 0, 255, 0);
        point(toXPixel(cx + y), toYPixel(cy + x), 0, 128, 255);
        point(toXPixel(cx + y), toYPixel(cy - x), 255, 0, 255);
        point(toXPixel(cx - y), toYPixel(cy + x), 255, 200, 127);
        point(toXPixel(cx - y), toYPixel(cy - x), 153, 255, 204);

        auto stop1 = high_resolution_clock::now();

        pointDuration += stop1 - start1;
        x = x + 1;
        if (p < 0) {
            p = p + 2*x + 1;
        }
        else {
            y = y - 1;
            p = p + 2*x + 1 - 2*y;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = stop - start - pointDuration;

    ui->timeValue->setText (QString::number(duration_cast<microseconds>(duration).count()) + " µs");
    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_ellipseCenter_clicked()
{
    cp2.setX(ui->frame->x);
    cp2.setY(ui->frame->y);
}

void MainWindow::on_PolarEllipse_clicked()
{
    int cx = getXCoordinate(cp2.x()), cy = getYCoordinate(cp2.y());
    int radiusX = ui->ellipseRadiusX->value(), radiusY = ui->ellipseRadiusY->value();


    auto start = high_resolution_clock::now();
    auto stop = start;
    auto duration = stop - start;

    for (int i = 0; i < 360; i++) {
        auto start = high_resolution_clock::now();

        // convert theta to radian
        double theta = M_PI * i / 180.0;

        // compute the points
        float x = cx + radiusX * cos(theta);
        float y = cy + radiusY * sin(theta);

        // round off to the nearest integer
        int ix = floor (x + 0.5);
        int iy = floor (y + 0.5);

        auto stop = high_resolution_clock::now();
        duration += stop - start;
        delay();
        point (toXPixel(ix), toYPixel(iy), 240, 4, 4);
    }

    ui->timeValue->setText (QString::number(duration_cast<microseconds>(duration).count()) + " µs");

    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_MidPointEllipse_clicked()
{
    int cx = getXCoordinate(cp2.x()), cy = getYCoordinate(cp2.y());
    int a = ui->ellipseRadiusX->value(), b = ui->ellipseRadiusY->value();

    auto start = high_resolution_clock::now();
    auto pointDuration = start - start;

    int x = 0, y = b;
    double d1 = b*b - a*a*b + 0.25*a*a;

    int count = 1;

    while (a*a*(y - 0.5) > b*b*(x+1)) {
        delay();
        auto start1 = high_resolution_clock::now();
        cout << "Count: " << count << " LHS: " << a*a*(y - 0.5) << " RHS: " << b*b*(x+1) << " D1: " << d1 << " x: " << x << " y: " << y << "\n";
        count++;
        point (toXPixel(cx + x), toYPixel(cy + y), 127, 255, 0);
        point (toXPixel(cx + x), toYPixel(cy - y), 255, 0, 255);
        point (toXPixel(cx - x), toYPixel(cy + y), 204, 102, 0);
        point (toXPixel(cx - x), toYPixel(cy - y), 0, 128, 255);
        auto stop1 = high_resolution_clock::now();
        pointDuration += stop1 - start1;

        if (d1 < 0)
            d1 += b*b*(2*x + 3);          // select E
        else {
            d1 += b*b*(2*x + 3) + a*a*(-2*y + 2);     // select SE
            y--;
        }
        x++;
    }
    cout << "LHS: " << a*a*(y - 0.5) << " RHS: " << b*b*(x+1) << "\n";

    double d2 = b*b*(x + 0.5)*(x + 0.5) + a*a*(y-1)*(y-1) - a*a*b*b;
    while (y >= 0) {
        auto start1 = high_resolution_clock::now();
        cout << "Count: " << count << " D2: " << d2 << " x: " << x << " y: " << y << "\n";
        count++;
        point (toXPixel(cx + x), toYPixel(cy + y), 127, 255, 0);
        point (toXPixel(cx + x), toYPixel(cy - y), 255, 0, 255);
        point (toXPixel(cx - x), toYPixel(cy + y), 204, 102, 0);
        point (toXPixel(cx - x), toYPixel(cy - y), 0, 128, 255);
        auto stop1 = high_resolution_clock::now();
        pointDuration += stop1 - start1;

        if (d2 < 0) {
            d2 += b*b*(2*x + 2) + a*a*(-2*y + 3);       // select SE
            x++;
        }
        else
            d2 += a*a*(-2*y + 3);       // select S
        y--;
    }

    auto stop = high_resolution_clock::now();
    auto duration = stop - start - pointDuration;

    ui->timeValue->setText (QString::number(duration_cast<microseconds>(duration).count()) + " µs");
    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_setVertexCountButton_clicked()
{
    vertex_count = ui->vertexCount->value();
}

void MainWindow::on_setVertexButton_clicked()
{
    vertex_list.push_back(make_pair((ui->frame->x/gridsize)*gridsize+gridsize/2,(ui->frame->y/gridsize)*gridsize+gridsize/2));
    int s = vertex_list.size();
    if (s > 1) {
        storeEdgeInTable(vertex_list[s-1].first, vertex_list[s-1].second, vertex_list[s-2].first, vertex_list[s-2].second);
        p1.setX(vertex_list[s-1].first);p1.setY(vertex_list[s-1].second);
        p2.setX(vertex_list[s-2].first);p2.setY(vertex_list[s-2].second);
        DDALINE(240,4,4);
        if (s == vertex_count) {
            storeEdgeInTable(vertex_list[s-1].first, vertex_list[s-1].second, vertex_list[0].first, vertex_list[0].second);
            p1.setX(vertex_list[s-1].first);p1.setY(vertex_list[s-1].second);
            p2.setX(vertex_list[0].first);p2.setY(vertex_list[0].second);
            DDALINE(240,4,4);
        }
    }
}

void MainWindow::on_clearVerticesButton_clicked()
{
    vertex_list.clear();
    initEdgeTable();
}

// Scanline Filling
struct EdgeBucket
{
    int ymax;               // max y-coordinate of edge
    float xofymin;          // x-coordinate of endpoint with lesser y-value
    float slopeinverse;     // 1 / m

    EdgeBucket (int ym = 0, float xm = 0, float si = 0) {
        ymax = ym;
        xofymin = xm;
        slopeinverse = si;
    }
};

struct EdgeTableTuple
{
    int countEdgeBucket;    // no. of edgebuckets
    EdgeBucket buckets[maxVer];
};

EdgeTableTuple EdgeTable[1000], ActiveEdgeTuple;
void MainWindow::initEdgeTable()
{
    for (int i=0; i<maxHt; i++)
        EdgeTable[i].countEdgeBucket = 0;
    ActiveEdgeTuple.countEdgeBucket = 0;
}

void insertionSort(EdgeTableTuple *ett)
{
    EdgeBucket temp;

    for (int i = 1; i < ett->countEdgeBucket; i++) {
        temp = ett->buckets[i];
        int j = i - 1;
        while ((temp.xofymin < ett->buckets[j].xofymin) && (j >= 0)) {
            ett->buckets[j + 1] = ett->buckets[j];
            j = j - 1;
        }
        ett->buckets[j + 1] = temp;
    }
}

void storeEdgeInTuple (EdgeTableTuple *receiver, EdgeBucket eb)
{
    receiver->buckets[receiver->countEdgeBucket] = eb;
    insertionSort(receiver);
    receiver->countEdgeBucket += 1;
}

void MainWindow::storeEdgeInTable (int x1,int y1, int x2, int y2)
{
    float m,minv;
    int ymaxTS,xwithyminTS, scanline;

    if (x2==x1) {
        minv = 0.0;
    }
    else {
        m = ((float)(y2-y1))/((float)(x2-x1));

        if (y2==y1)         // Do not store horizontal edges
            return;

        minv = 1.0 / m;
    }

    if (y1 > y2) {
        scanline = y2;
        ymaxTS = y1;
        xwithyminTS = x2;
    }
    else {
        scanline = y1;
        ymaxTS = y2;
        xwithyminTS = x1;
    }
    storeEdgeInTuple(&EdgeTable[scanline],EdgeBucket(ymaxTS,xwithyminTS,minv));
}

void removeEdgeByYmax(EdgeTableTuple *Tup,int yy)
{
    for (int i=0; i< Tup->countEdgeBucket; i++)
    {
        if (Tup->buckets[i].ymax == yy)
        {
            for (int j = i; j < Tup->countEdgeBucket - 1; j++ )
                Tup->buckets[j] = Tup->buckets[j+1];
            Tup->countEdgeBucket--;
            i--;
        }
    }
}

void updatexbyslopeinv(EdgeTableTuple *Tup)
{
    for (int i=0; i<Tup->countEdgeBucket; i++)
        (Tup->buckets[i]).xofymin = (Tup->buckets[i]).xofymin + (Tup->buckets[i]).slopeinverse;
}

void MainWindow::on_ScanlineFill_clicked()
{
    int i, j, x1, ymax1, x2, ymax2, FillFlag = 0, coordCount;

    for (i=0; i<maxHt; i++)
    {
        for (j=0; j<EdgeTable[i].countEdgeBucket; j++)
        {
            storeEdgeInTuple(&ActiveEdgeTuple, EdgeBucket (EdgeTable[i].buckets[j].ymax, EdgeTable[i].buckets[j].xofymin, EdgeTable[i].buckets[j].slopeinverse));
        }

        removeEdgeByYmax(&ActiveEdgeTuple, i);
        insertionSort(&ActiveEdgeTuple);

        j = 0;
        coordCount = 0;
        x1 = x2 = 0;
        ymax1 = ymax2 = 0;

        while (j<ActiveEdgeTuple.countEdgeBucket) {

            if (coordCount%2 == 0) {
                x1 = (int)(ActiveEdgeTuple.buckets[j].xofymin);
                ymax1 = ActiveEdgeTuple.buckets[j].ymax;

                if (x1 == x2) {
                    if (((x1 == ymax1) && (x2 != ymax2)) || ((x1 != ymax1) && (x2 == ymax2))) {
                        ymax2 = ymax1;
                    }
                    else
                        coordCount++;
                }
                else
                    coordCount++;
            }

            else {
                x2 = (int)ActiveEdgeTuple.buckets[j].xofymin;
                ymax2 = ActiveEdgeTuple.buckets[j].ymax;

                FillFlag = 0;

                if (x1 == x2) {
                    if (((x1 == ymax1) && (x2 != ymax2)) || ((x1 != ymax1) && (x2 == ymax2))) {
                        ymax1 = ymax2;
                    }
                    else {
                        coordCount++;
                        FillFlag = 1;
                    }
                }
                else {
                    coordCount++;
                    FillFlag = 1;
                }

                if(FillFlag) {
                    p1.setX(x1); p1.setY(i);
                    p2.setX(x2); p2.setY(i);
                    on_BresenhamLine_clicked();
                }
            }

            j++;
        }
        updatexbyslopeinv(&ActiveEdgeTuple);
    }

    vertex_list.clear();
    initEdgeTable();
}

void MainWindow::boundaryFillUtil (int x, int y, QRgb edgeCol, int r, int g, int b) {
    if (x < 0 || y < 0 || x >= img.width() || y >= img.height()) return;
    if (img.pixel(x,y) != edgeCol && img.pixel(x,y) != qRgb(r,g,b)) {
        delay();
        point (x,y,r,g,b);
        boundaryFillUtil(x - gridsize, y, edgeCol, r, g, b);
        boundaryFillUtil(x + gridsize, y, edgeCol, r, g, b);
        boundaryFillUtil(x, y - gridsize, edgeCol, r, g, b);
        boundaryFillUtil(x, y + gridsize, edgeCol, r, g, b);
        if (ui->eightWay->isChecked()) {
            boundaryFillUtil(x + gridsize, y + gridsize, edgeCol, r, g, b);
            boundaryFillUtil(x - gridsize, y + gridsize, edgeCol, r, g, b);
            boundaryFillUtil(x - gridsize, y - gridsize, edgeCol, r, g, b);
            boundaryFillUtil(x + gridsize, y - gridsize, edgeCol, r, g, b);
        }
    }
}

void MainWindow::on_BoundaryFill_clicked()
{
    point (ui->frame->x, ui->frame->y, 0, 0, 0);
    boundaryFillUtil(ui->frame->x, ui->frame->y, qRgb(240,4,4), 255, 255, 0);
    ui->frame->setPixmap(QPixmap::fromImage(img));

    vertex_list.clear();
    initEdgeTable();
}

void MainWindow::floodFillUtil (int x, int y, QRgb oldCol, int r, int g, int b) {
    if (x < 0 || y < 0 || x >= img.width() || y >= img.height()) return;
    if (img.pixel(x,y) == oldCol) {
        delay();
        point (x,y,r,g,b);
        floodFillUtil(x - gridsize, y, oldCol, r, g, b);
        floodFillUtil(x + gridsize, y, oldCol, r, g, b);
        floodFillUtil(x, y - gridsize, oldCol, r, g, b);
        floodFillUtil(x, y + gridsize, oldCol, r, g, b);
        if (ui->eightWay->isChecked()) {
            floodFillUtil(x + gridsize, y + gridsize, oldCol, r, g, b);
            floodFillUtil(x - gridsize, y + gridsize, oldCol, r, g, b);
            floodFillUtil(x - gridsize, y - gridsize, oldCol, r, g, b);
            floodFillUtil(x + gridsize, y - gridsize, oldCol, r, g, b);
        }
    }
}

void MainWindow::on_FloodFill_clicked()
{
    point (ui->frame->x, ui->frame->y, 0, 0, 0);
    floodFillUtil(ui->frame->x, ui->frame->y, qRgb(0, 0, 0), 255, 255, 0);
    ui->frame->setPixmap(QPixmap::fromImage(img));

    vertex_list.clear();
    initEdgeTable();
}


// ------------------------------------- POLYGON DRAWING -----------------------------------------
void MainWindow::polyDraw (int r, int g, int b) {
    int s = vertex_list.size();
    initEdgeTable();
    if (s >= 2) {
        for (int i = 1; i < s; i++) {
            storeEdgeInTable(vertex_list[i-1].first, vertex_list[i-1].second, vertex_list[i].first, vertex_list[i].second);//storage of edges in edge table.
            p1.setX(vertex_list[i-1].first);p1.setY(vertex_list[i-1].second);
            p2.setX(vertex_list[i].first);p2.setY(vertex_list[i].second);
            DDALINE(r,g,b);
        }
        if (s > 2) {
            storeEdgeInTable(vertex_list[s-1].first, vertex_list[s-1].second, vertex_list[0].first, vertex_list[0].second);//storage of edges in edge table.
            p1.setX(vertex_list[s-1].first);p1.setY(vertex_list[s-1].second);
            p2.setX(vertex_list[0].first);p2.setY(vertex_list[0].second);
            DDALINE(r,g,b);
        }
    }
}

void MainWindow::on_setOriginButton_clicked()
{
    origin.setX(ui->frame->x);
    origin.setY(ui->frame->y);
    const QString posText = ui->mouse_pressed->text();
    ui->originValue->setText(posText);
}


// --------------------------------------------- TRANSFORMATION ------------------------------------------
void matmul (double trmatrix[3][3], int pt[3]) {
    double result[3];
    for (int i = 0; i < 3; i++) {
        result[i] = 0;
        for (int j = 0; j < 3; j++) {
            result[i] += trmatrix[i][j] * pt[j];
        }
    }
    for (int i = 0; i < 3; i++)
        pt[i] = result[i];
}

void translation (int pt[3], double tx, double ty) {
    double trmatrix[3][3] = {{1, 0, tx}, {0, 1, ty}, {0, 0, 1}};
    matmul (trmatrix, pt);
}

void MainWindow::on_translate_clicked()
{
    polyDraw (240,240,4);
    int tx = ui->tx->value(), ty = ui->ty->value();
    int s = vertex_list.size();
    for (int i = 0; i < s; i++) {
        int px = getXCoordinate(vertex_list[i].first), py = getYCoordinate(vertex_list[i].second);
        int pt[3] = {px, py, 1};
        translation (pt, tx, ty);
        px = pt[0];
        py = pt[1];
        vertex_list[i] = make_pair (toXPixel(px), toYPixel(py));
    }
    polyDraw (240,4,4);
}

void matmul2(double a[3][3], int b[3], double res[3]){
    int i,j;
    for(i=0;i<3;i++){
        res[i]=0;
        for(j=0;j<3;j++)
            res[i]+=(a[i][j]*b[j]);
    }
}

void MainWindow::on_rotate_clicked()
{
    polyDraw (240,240,4);
    int angle = ui->degree->value();
    vector<pair<int,int> > old_vertex (vertex_list);

    double dang=(double)angle*M_PI/180.0;
    double sinang=sin(dang);
    double cosang=cos(dang);

    //Point about which to be rotated
    int piv_x=(origin.x()/gridsize)*gridsize+gridsize/2;
    int piv_y=(origin.y()/gridsize)*gridsize+gridsize/2;

    int i,len=vertex_list.size();

    // matrix for rotation
    double mat[3][3]={{cosang,-sinang,0},{sinang,cosang,0},{0,0,1}};
    int coord[3];
    double res[3];
    for(i=0;i<len;i++)
    {
        coord[0]=vertex_list[i].first-piv_x;
        coord[1]=piv_y-vertex_list[i].second;
        coord[2]=1;
        matmul2(mat,coord,res);
        vertex_list[i].first=res[0]/res[2]+piv_x;
        vertex_list[i].second=piv_y-res[1]/res[2];
    }

    polyDraw (240,4,4);
}

void MainWindow::on_scale_clicked()
{
    polyDraw (240,240,4);
    int ox = getXCoordinate(origin.x()), oy = getYCoordinate(origin.y());
    double sx = (ui->sx->text()).toDouble(), sy = (ui->sy->text()).toDouble();
    int s = vertex_list.size();
    for (int i = 0; i < s; i++) {
        int px = getXCoordinate(vertex_list[i].first), py = getYCoordinate(vertex_list[i].second);
        int pt[3] = {px, py, 1};
        translation (pt, -ox, -oy);
        double scalematrix[3][3] = {{sx, 0, 0}, {0, sy, 0}, {0, 0, 1}};
        matmul (scalematrix, pt);
        translation (pt, ox, oy);
        px = pt[0];
        py = pt[1];
        vertex_list[i] = make_pair (toXPixel(px), toYPixel(py));
    }
    polyDraw (240,4,4);
}

void MainWindow::on_shear_clicked()
{
    polyDraw (240,240,4);
    int ox = getXCoordinate(origin.x()), oy = getYCoordinate(origin.y());
    double shx = (ui->shx->text()).toDouble(), shy = (ui->shy->text()).toDouble();
    int s = vertex_list.size();
    for (int i = 0; i < s; i++) {
        int px = getXCoordinate(vertex_list[i].first), py = getYCoordinate(vertex_list[i].second);
        int pt[3] = {px, py, 1};
        translation (pt, -ox, -oy);
        double shearmatrix[3][3] = {{1, shx, 0}, {shy, 1, 0}, {0, 0, 1}};
        matmul (shearmatrix, pt);
        translation (pt, ox, oy);
        px = pt[0];
        py = pt[1];
        vertex_list[i] = make_pair (toXPixel(px), toYPixel(py));
    }
    polyDraw (240,4,4);
}

void reflectXaxis (int pt[3]) {
    double refxmatrix[3][3] = {{1, 0, 0}, {0, -1, 0}, {0, 0, 1}};
    matmul(refxmatrix, pt);
}

void reflectYaxis (int pt[3]) {
    double refymatrix[3][3] = {{-1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    matmul(refymatrix, pt);
}

void MainWindow::on_reflect_clicked()
{
    polyDraw (240,240,4);
    int l1x = p1.x(), l1y = p1.y(), l2x = p2.x(), l2y = p2.y();
    int s = vertex_list.size();
    if (ui->reflectionLine->currentIndex() == 0) {
        for (int i = 0; i < s; i++) {
            int px = getXCoordinate(vertex_list[i].first), py = getYCoordinate(vertex_list[i].second);
            int pt[3] = {px, py, 1};
            reflectXaxis (pt);
            px = pt[0];
            py = pt[1];
            vertex_list[i] = make_pair (toXPixel(px), toYPixel(py));
        }
    }
    else if (ui->reflectionLine->currentIndex() == 1) {
        for (int i = 0; i < s; i++) {
            int px = getXCoordinate(vertex_list[i].first), py = getYCoordinate(vertex_list[i].second);
            int pt[3] = {px, py, 1};
            reflectYaxis (pt);
            px = pt[0];
            py = pt[1];
            vertex_list[i] = make_pair (toXPixel(px), toYPixel(py));
        }
    }
    else {
        int i,len=vertex_list.size();

        double dx=p1.x()-p2.x();
        double dy=p1.y()-p2.y();

        double a=-dy;
        double b=dx;
        double c=p1.x()*dy-p1.y()*dx;

        for(i=0;i<len;i++) {
            int x1=vertex_list[i].first;
            int y1=vertex_list[i].second;

            vertex_list[i].first=(int)((double)x1-(double)(2*a*(a*x1+b*y1+c))/(double)((a*a+b*b)));
            vertex_list[i].second=(int)((double)y1-(double)(2*b*(a*x1+b*y1+c))/(double)((a*a+b*b)));
        }
    }
    polyDraw (240,4,4);
    p1.setX(l1x);
    p1.setY(l1y);
    p2.setX(l2x);
    p2.setY(l2y);
}


// ----------------------------------------------CLIPPING-----------------------------------------------
int clipper_points[4][2];

void MainWindow::draw_Window()
{
    p1.setX(clipper_points[0][0]);
    p1.setY(clipper_points[0][1]);
    p2.setX(clipper_points[1][0]);
    p2.setY(clipper_points[1][1]);
    DDALINE(248,255,4);

    p1.setX(clipper_points[1][0]);
    p1.setY(clipper_points[1][1]);
    p2.setX(clipper_points[2][0]);
    p2.setY(clipper_points[2][1]);
    DDALINE(248,255,4);

    p1.setX(clipper_points[2][0]);
    p1.setY(clipper_points[2][1]);
    p2.setX(clipper_points[3][0]);
    p2.setY(clipper_points[3][1]);
    DDALINE(248,255,4);

    p1.setX(clipper_points[3][0]);
    p1.setY(clipper_points[3][1]);
    p2.setX(clipper_points[0][0]);
    p2.setY(clipper_points[0][1]);
    DDALINE(248,255,4);
}

void MainWindow::on_setCorner1_clicked()
{
    cp1.setX((ui->frame->x/gridsize)*gridsize+gridsize/2);
    cp1.setY((ui->frame->y/gridsize)*gridsize+gridsize/2);
}

void MainWindow::on_setCorner2_clicked()
{
    cp2.setX((ui->frame->x/gridsize)*gridsize+gridsize/2);
    cp2.setY((ui->frame->y/gridsize)*gridsize+gridsize/2);

    int x_min = min (cp1.x(), cp2.x());
    int x_max = max (cp1.x(), cp2.x());
    int y_min = min (cp1.y(), cp2.y());
    int y_max = max (cp1.y(), cp2.y());

    cp1.setX(x_min);
    cp1.setY(y_min);
    cp2.setX(x_max);
    cp2.setY(y_max);

    clipper_points[0][0]=cp1.x();
    clipper_points[0][1]=cp1.y();
    clipper_points[1][0]=cp1.x();
    clipper_points[1][1]=cp2.y();
    clipper_points[2][0]=cp2.x();
    clipper_points[2][1]=cp2.y();
    clipper_points[3][0]=cp2.x();
    clipper_points[3][1]=cp1.y();

    draw_Window();
}


// ************************** LINE CLIPPING ********************************
// Defining region codes
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000


// Function to compute region code for a point(x, y)
int MainWindow::computeCode(int xa, int ya)
{
//    int x_min=getXCoordinate(cp1.x()),x_max=getXCoordinate(cp2.x()),y_min=getYCoordinate(cp2.y()),y_max=getYCoordinate(cp1.y());

    int x_min=cp1.x(),x_max=cp2.x(),y_min=cp1.y(),y_max=cp2.y();

    // initialized as being inside
    int code = INSIDE;
    if (xa < x_min)       // to the left of rectangle
        code |= LEFT;
    else if (xa > x_max)  // to the right of rectangle
        code |= RIGHT;
    if (ya < y_min)       // below the rectangle
        code |= BOTTOM;
    else if (ya > y_max)  // above the rectangle
        code |= TOP;

    return code;
}

// Implementing Cohen-Sutherland algorithm
// Clipping a line from P1 = (x2, y2) to P2 = (x2, y2)
void MainWindow::cohenSutherlandClip(int x1, int y1,int x2, int y2)
{
    int x_min=clipper_points[0][0],x_max=clipper_points[2][0],y_min=clipper_points[0][1],y_max=clipper_points[2][1];
    // Compute region codes for P1, P2
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);

    // Initialize line as outside the rectangular window
    bool accept = false;

    while (true)
    {

        if ((code1 == 0) && (code2 == 0))
        {
            // If both endpoints lie within rectangle
            accept = true;
            break;
        }
        else if (code1 & code2)
        {
            // If both endpoints are outside rectangle,
            // in same region
            p1.setX(x1);
            p1.setY(y1);

            p2.setX(x2);
            p2.setY(y2);

            DDALINE(0,0,0);
            break;
        }
        else
        {
            // Some segment of line lies within the
            // rectangle
            int code_out;
            int x, y;

            // At least one endpoint is outside the
            // rectangle, pick it.
            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            // Find intersection point;
            // using formulas y = y1 + slope * (x - x1),
            // x = x1 + (1 / slope) * (y - y1)
            if (code_out & TOP)
            {
                // point is above the clip rectangle
                x = x1 + (int)((double)(x2 - x1) * (double)(y_max - y1) / (double)(y2 - y1));
                y = y_max;
            }
            else if (code_out & BOTTOM)
            {
                // point is below the rectangle
                x = x1 + (int)((double)(x2 - x1) * (double)(y_min - y1) / (double)(y2 - y1));
                y = y_min;
            }
            else if (code_out & RIGHT)
            {
                // point is to the right of rectangle
                y = y1 + (int)((double)(y2 - y1) * (double)(x_max - x1) / (double)(x2 - x1));
                x = x_max;
            }
            else if (code_out & LEFT)
            {
                // point is to the left of rectangle
                y = y1 + (int)((double)(y2 - y1) * (double)(x_min - x1) / (double)(x2 - x1));
                x = x_min;
            }

            // Now intersection point x,y is found
            // We replace point outside rectangle
            // by intersection point
            if (code_out == code1)
            {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }
    if (accept)
    {
        //If accepted
        //Just reset and draw the boundary and the line
        //Reset the screen and draw the grid

        p1.setX((x1 / gridsize )*gridsize+gridsize/2);
        p1.setY((y1 / gridsize )*gridsize+gridsize/2);

        p2.setX((x2 / gridsize )*gridsize+gridsize/2);
        p2.setY((y2 / gridsize )*gridsize+gridsize/2);

        BresenhamLINE(240,4,4);
        draw_Window();
    }
    else
    {
        //If not accepted
        //Just reset and draw the boundary
        //Reset the screen and draw the grid
        draw_Window();
    }
}


void MainWindow::on_lineClipping_clicked()
{
    DDALINE(0,0,0);
    cohenSutherlandClip(p1.x(),p1.y(),p2.x(),p2.y());
}


// *********************** POLYGON CLIPPING *************************************
//const int MAX_POINTS = 20;

// Returns x-value of point of intersectipn of two
// lines
int MainWindow::x_intersect(int x1, int y1, int x2, int y2,int x3, int y3, int x4, int y4)
{
    y1=ui->frame->height()-y1+1;
    y2=ui->frame->height()-y2+1;
    y3=ui->frame->height()-y3+1;
    y4=ui->frame->height()-y4+1;
    int num = (x1*y2 - y1*x2) * (x3-x4) -
              (x1-x2) * (x3*y4 - y3*x4);
    int den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    int retx=num/den;
    return retx;
}

// Returns y-value of point of intersectipn of
// two lines
int MainWindow:: y_intersect(int x1, int y1, int x2, int y2,int x3, int y3, int x4, int y4)
{
    y1=ui->frame->height()-y1+1;
    y2=ui->frame->height()-y2+1;
    y3=ui->frame->height()-y3+1;
    y4=ui->frame->height()-y4+1;
    int num = (x1*y2 - y1*x2) * (y3-y4) -
              (y1-y2) * (x3*y4 - y3*x4);
    int den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    int rety= (ui->frame->height()-num/den+1);
    return rety;
}

// This functions clips all the edges w.r.t one clip
// edge of clipping area
void MainWindow::clip(int x1, int y1, int x2, int y2)
{
    int poly_size=vertex_list.size();
    int new_poly_size = 0;

    vector<pair<int,int> > new_points;

    // (ix,iy),(kx,ky) are the co-ordinate values of
    // the points
    for (int i = 0; i < poly_size; i++)
    {
        // i and k form a line in polygon
        int k = (i+1) % poly_size;
        int ix = vertex_list[i].first, iy = vertex_list[i].second;
        int kx = vertex_list[k].first, ky = vertex_list[k].second;

        // Calculating position of first and second point

        int i_pos,k_pos;
        if(x2==x1 && ix>x1) i_pos=1;
        else if(x2==x1 && ix<x1) i_pos=-1;
        else if(y2==y1 && iy<y1) i_pos=1;
        else i_pos=-1;

        if(x2==x1 && kx>x1) k_pos=1;
        else if(x2==x1 && kx<x1) k_pos=-1;
        else if(y2==y1 && ky<y1) k_pos=1;
        else k_pos=-1;

        if(y1>y2||x1>x2)
        {
            i_pos=(-1)*i_pos;
            k_pos=(-1)*k_pos;
        }

        // Case 1 : When both points are inside
        if (i_pos >= 0  && k_pos >= 0)
        {
            //Only second point is added
            new_points.push_back(make_pair(kx,ky));
            new_poly_size++;
        }

        // Case 2: When only first point is outside
        else if (i_pos < 0  && k_pos >= 0)
        {
            // Point of intersection with edge
            // and the second point is added

            new_points.push_back(make_pair(x_intersect(x1,y1, x2, y2, ix, iy, kx, ky),y_intersect(x1,y1, x2, y2, ix, iy, kx, ky)));
            new_poly_size++;

            new_points.push_back(make_pair(kx,ky));
            new_poly_size++;
        }

        // Case 3: When only second point is outside
        else if (i_pos >= 0  && k_pos < 0)
        {
            //Only point of intersection with edge is added

            new_points.push_back(make_pair(x_intersect(x1,y1, x2, y2, ix, iy, kx, ky),y_intersect(x1,y1, x2, y2, ix, iy, kx, ky)));
            new_poly_size++;
        }

        // Case 4: When both points are outside
        else
        {
            //No points are added
        }
    }

    // Copying new points into original array
    // and changing the no. of vertices
    poly_size = new_poly_size;
    vertex_list.clear();
    for (int i = 0; i < int(new_points.size()); i++)
    {
        vertex_list.push_back(new_points[i]);
    }
    vertex_list.push_back(new_points[0]);
}

// Implements Sutherland–Hodgman algorithm
void MainWindow::suthHodgClip()
{
    polyDraw(0,0,0);
    int clipper_size=4;
    //i and k are two consecutive indexes
    for (int i=0; i<clipper_size; i++)
    {
        int k = (i+1) % clipper_size;

        // We pass the current array of vertices, it's size
        // and the end points of the selected clipper line
        clip(clipper_points[i][0], clipper_points[i][1], clipper_points[k][0], clipper_points[k][1]);
    }
    draw_Window();
    polyDraw(84,231,238);
}
void MainWindow::on_polygonClipping_clicked()
{
    suthHodgClip();
}

