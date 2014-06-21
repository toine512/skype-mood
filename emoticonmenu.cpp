#include "emoticonmenu.h"

EmoticonMenuWidgetAction::EmoticonMenuWidgetAction(QObject *parent) :
    QWidgetAction(parent)
{
    emoticons = EmoticonStack();
    mapper = new QSignalMapper(this);
    connect(mapper, SIGNAL(mapped(const QString &)), this, SLOT(buttonPressed(const QString &)));
}

int EmoticonMenuWidgetAction::computeItemsPerLineCount(int item_count, int preferred_column_count, int maximum_row_count)
{
    if(item_count < 1 || preferred_column_count == 0 || maximum_row_count == 0)
    {
        return 1;
    }

    float items = (float) item_count;
    float cols = (float) abs(preferred_column_count);
    float rows = 0.0;
    float max_rows = (float) abs(maximum_row_count);

    while(true)
    {
        rows = ceil(items / cols);
        if(rows > max_rows)
        {
            cols++;
        }
        else
        {
            break;
        }
    }
    return (int)cols;
}

void EmoticonMenuWidgetAction::buttonPressed(const QString &id)
{
    setData(id);
    trigger();
}

QWidget * EmoticonMenuWidgetAction::createWidget(QWidget *parent)
{
    QWidget *w = new QWidget(parent);
    QGridLayout *l = new QGridLayout;

    //Populating the menu
    int cols = EmoticonMenuWidgetAction::computeItemsPerLineCount(emoticons.count(), 9, 20);
    SKYPE_EMOTICONS_CONTAINER_T::const_iterator i = emoticons.getCIteratorBegin();
    SKYPE_EMOTICONS_CONTAINER_T::const_iterator end = emoticons.getCIteratorEnd();
    int n = 0;
    while(i != end)
    {
        QToolButton *btn = new QToolButton;
        btn->setAutoRaise(true);
        QPixmap px;
        px.loadFromData(i.value()->data, i.value()->dataSize);
        btn->setIcon(px);
        btn->setIconSize(QSize(SKYPE_EMOTICONS_EMOTICON_WIDTH, SKYPE_EMOTICONS_EMOTICON_HEIGHT));
        btn->setToolTip(i.value()->name);

        mapper->setMapping(btn, i.value()->id);
        connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

        l->addWidget(btn, n / cols, n % cols, 1, 1);

        n++;
        ++i;
    }

    w->setLayout(l);
    return w;
}
/*
void EmoticonMenuWidgetAction::deleteWidget(QWidget *widget)
{

}*/

EmoticonMenu::EmoticonMenu(QWidget *parent) :
    QMenu(parent)
{
    addAction(new EmoticonMenuWidgetAction(this));
}

QIcon EmoticonMenu::getIcon()
{
    /*QPixmap p;
    p.loadFromData(QByteArray::fromBase64("iVBORw0KGgoAAAANSUhEUgAAABQAAAAUCAYAAACNiR0NAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAA2ZJREFUeNqMVd9rFFcU/u7MbDabbMlusjGhNO1u6o/65KIIWkESH4rQhyL41oe2UAULkiylYJ/EF1EUkiAoxBd9kv4DRfpgpNBaKC3rU9KiSayJzSabZNTd7I+ZO7ffzJ3uJjEsXjhz59zzne+eO+ecOwI7DPWoL81phDJEyW4z5ykPKRPiaGF+u694g+zXvjFYnaPoOQGkhoFYZiugMgcUp4DVB4BbHhcfF3I7Eno/9yaoTYnkoSwy5wCrL9yh4j+acBHTr24BmLsFtf5HnuZh4/iK3SD0HqQCMvQeyYrBs1yNkqOElkPEialBzU4CK79p0hNF2wqC8NRFkdyfFQOfcOcXeLuxonnpo2p2Vq1PX6SaE/J+dxpWdM44cIahPudRmQ+vDszfB14/177x9/RcWtDzOwNA+iRgtDEA5sUYgPf4Nt9rGUNJbwSJ3UB9BqjR6PwLPPsR6P0cGC5o6Tmt5X/dt/kYH+v7+L7k8LksuGpIdO1i9mbCo9Chvgb1QQ7dyWSwsra+HsybdfFigj48gVzlyipE1x6oRTVkKamygpGjXORD8oNGeASJitfMrf8ObNU7iIG7xCgZAEyIThKSy4IkTNIoHY2Wi7RLiIWreLqsIxPPLgdzQ6cNZg2oLvo1oiXgUBD1e3EVOcwCLv2yqbopjktcGJMIy1WFukE9Ym1ti/gxOL9PgRF60FEadHCbAIO60aJqpLepJq2Qw4OhXJVXr19xMalBlNz1DeSn3Ya+XeYXXJz6ttxco6/P4XOxbNRDWWAxm70NwBen38VXVwQuTVbpLBvrti2DtVPfexj5OtMkpK/P4XOJ6mQ0DcOcix48ynKZDbPGkRzEnZ+Auz/8A3tNt2Ei0Y7PPn0fX560kHBmNS7Cnm8bRO3PR/zmMhN81srNyJjZnRqN7NvP5DzmrmUNbu8iC7vEag8vhCpgs1uqL7VudjIZB+D8NQ25VhyPfePkNOENK8HMTpm7+rOR3eyaylNGW2jdym2MLPYhnCdPIJeX8sz4cOy8azcSvzFmatKeVDay9yPaecwaC7fOglcyzKZJohQQ7Sc0DufvGTZKMSDryEl7xwt245oYg2mNmn39vBL7YcTjW+xeqcSrcIlJ4GbSHe/4TuVa3tj+KF9BmiG0/gUITHRewBu/gP8EGABcP5PAwgynmwAAAABJRU5ErkJggg=="));
    return QIcon(p);*/

    EmoticonStack emoticons;
    QPixmap p;
    const Emoticon *smile = emoticons.getEmoticonByName("smile");
    if(smile != 0)
    {
        p.loadFromData(smile->data, smile->dataSize);
    }
    return QIcon(p);
}
