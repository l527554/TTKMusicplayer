#include "musicplayedlistpopwidget.h"
#include "musicfunctionuiobject.h"
#include "musicsongslistplayedtablewidget.h"
#include "musicsettingmanager.h"
#include "musictinyuiobject.h"
#include "musicuiobject.h"
#include "musicapplication.h"

#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include <QToolButton>
#include <QScrollArea>

#define MAX_SIZE    3

MusicPlayedListPopWidget *MusicPlayedListPopWidget::m_instance = nullptr;

MusicPlayedListPopWidget::MusicPlayedListPopWidget(QWidget *parent)
    : MusicToolMenuWidget(parent)
{
    m_instance = this;
    setToolTip(tr("playedList"));
    setStyleSheet(MusicUIObject::MKGBtnPlayedList);

    disconnect(this, SIGNAL(clicked()), this, SLOT(popupMenu()));
    connect(this, SIGNAL(clicked()), SLOT(popupMenu()));

    initWidget();
}

MusicPlayedListPopWidget::~MusicPlayedListPopWidget()
{
    delete m_playedListWidget;
    qDeleteAll(m_labels);
}

QString MusicPlayedListPopWidget::getClassName()
{
    return staticMetaObject.className();
}

MusicPlayedListPopWidget *MusicPlayedListPopWidget::instance()
{
    return m_instance;
}

void MusicPlayedListPopWidget::clear()
{
    m_songLists.clear();
    m_playedListWidget->clear();
    setPlayListCount(0);
}

void MusicPlayedListPopWidget::resetToolIndex(const QList< std::pair<int, int> > &indexs)
{
    for(int i=indexs.count()-1; i>=0; --i)
    {
        std::pair<int, int> index = indexs[i];
        for(int s=0; s<m_songLists.count(); ++s)
        {
            MusicSong *song = &m_songLists[s];
            if(song->getMusicToolIndex() == index.first)
            {
                song->setMusicToolIndex(index.second);
            }
        }
    }
}

QStringList MusicPlayedListPopWidget::getPlayedList() const
{
    QStringList lists;
    foreach(const MusicSong &song, m_songLists)
    {
        lists << song.getMusicPath();
    }
    return lists;
}

void MusicPlayedListPopWidget::remove(int toolIndex, const MusicSong &song)
{
    MusicObject::MIntSet deletedRow;
    for(int i=0; i<m_songLists.count(); ++i)
    {
        MusicSong playedSong = m_songLists[i];
        if(playedSong.getMusicToolIndex() == toolIndex && playedSong == song)
        {
            deletedRow << i;
        }
    }
    MusicObject::MIntList deleteList = deletedRow.toList();
    qSort(deleteList);
    for(int i=deleteList.count()-1; i>=0; --i)
    {
        int index = deleteList[i];
        m_songLists.removeAt(index);
        m_playedListWidget->removeRow(index);
    }

    updateSongsFileName();
}

void MusicPlayedListPopWidget::remove(int toolIndex, const MusicSongs &songs)
{
    MusicObject::MIntSet deletedRow;
    for(int i=0; i<m_songLists.count(); ++i)
    {
        MusicSong playedSong = m_songLists[i];
        if(playedSong.getMusicToolIndex() == toolIndex)
        {
            foreach(const MusicSong &song, songs)
            {
                if(playedSong == song)
                {
                    deletedRow << i;
                }
            }
        }
    }
    MusicObject::MIntList deleteList = deletedRow.toList();
    qSort(deleteList);
    for(int i=deleteList.count() - 1; i>=0; --i)
    {
        int index = deleteList[i];
        m_songLists.removeAt(index);
        m_playedListWidget->removeRow(index);
    }

    updateSongsFileName();
}

void MusicPlayedListPopWidget::append(int toolIndex, const MusicSong &song)
{
    MusicSong s(song);
    s.setMusicToolIndex(toolIndex);
    m_songLists << s;
    updateSongsFileName();
}

void MusicPlayedListPopWidget::append(int toolIndex, const MusicSongs &songs)
{
    foreach(const MusicSong &song, songs)
    {
        MusicSong s(song);
        s.setMusicToolIndex(toolIndex);
        m_songLists << s;
    }
    updateSongsFileName();
}

void MusicPlayedListPopWidget::insert(int toolIndex, const MusicSong &song)
{
    insert(toolIndex, m_playedListWidget->getPlayRowIndex() + 1, song);
}

void MusicPlayedListPopWidget::insert(int toolIndex, int index, const MusicSong &song)
{
    if(index < 0 || index >= m_songLists.count())
    {
        return;
    }

    MusicSong s(song);
    s.setMusicToolIndex(toolIndex);

    m_songLists.insert(index, s);
    m_playedListWidget->clear();
    updateSongsFileName();
}

void MusicPlayedListPopWidget::setCurrentIndex(const QString &path)
{
    int index = -1;
    for(int i=0; i<m_songLists.count(); ++i)
    {
        if(m_songLists[i].getMusicPath() == path)
        {
            index = i;
            break;
        }
    }

    m_playedListWidget->selectRow(index);
}

void MusicPlayedListPopWidget::resizeWindow()
{
//    int h = M_SETTING_PTR->value(MusicSettingManager::WidgetSize).toSize().height();
//    m_containWidget->setFixedSize(300, 500 + h - WINDOW_HEIGHT_MIN);
}

void MusicPlayedListPopWidget::popupMenu()
{
    QPoint pos = mapToGlobal(QPoint(0, 0));
    pos.setY(pos.y() - m_containWidget->height() - 10);
    pos.setX(pos.x() - (m_containWidget->width() - width() - 3));

    m_playedListWidget->selectPlayedRow();
    m_menu->exec(pos);
}

void MusicPlayedListPopWidget::setDeleteItemAt()
{
    setPlayListCount(m_songLists.count());
}

void MusicPlayedListPopWidget::setDeleteItemAll()
{
    if(m_songLists.isEmpty())
    {
        return;
    }

    int count = m_playedListWidget->rowCount();
    for(int i=0; i<count; ++i)
    {
        m_playedListWidget->removeRow(0);
    }

    m_playedListWidget->setPlayRowIndex(-1);
    m_songLists.clear();
    setPlayListCount(0);

    MusicApplication::instance()->musicPlayIndex(-1);
}

void MusicPlayedListPopWidget::initWidget()
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(2);

    layout->addStretch(2);
    for(int i=0; i<MAX_SIZE; ++i)
    {
        QLabel *label = new QLabel(this);
        label->setFixedWidth(9);
        label->setPixmap(QPixmap(":/tiny/lb_number0"));
        layout->addWidget(label);
        m_labels << label;
    }
    layout->addStretch(1);

    setLayout(layout);

    m_containWidget->setFixedSize(320, 400);
    QVBoxLayout *containLayout = new QVBoxLayout(m_containWidget);
    containLayout->setContentsMargins(0, 0, 0, 0);
    containLayout->setSpacing(0);
    containLayout->addWidget( createContainerWidget() );

    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setFrameShape(QFrame::NoFrame);
    m_scrollArea->setFrameShadow(QFrame::Plain);
    m_scrollArea->setAlignment(Qt::AlignLeft);

    QString alphaStr = MusicUIObject::MBackgroundStyle17;
    QWidget *view = m_scrollArea->viewport();
    view->setObjectName("viewport");
    view->setStyleSheet(QString("#viewport{%1}").arg(alphaStr));
    m_scrollArea->setStyleSheet(MusicUIObject::MScrollBarStyle01);

    m_playedListWidget = new MusicSongsListPlayedTableWidget(this);
    m_playedListWidget->setSongsFileName(&m_songLists);
    connect(m_playedListWidget, SIGNAL(updateCountLabel()), SLOT(setDeleteItemAt()));

    QWidget *playedListContainer = new QWidget(m_scrollArea);
    QVBoxLayout *playedListLayout = new QVBoxLayout(playedListContainer);
    playedListLayout->setContentsMargins(0, 0, 0, 0);
    playedListLayout->setSpacing(0);
    playedListLayout->addWidget(m_playedListWidget);
    playedListContainer->setLayout(playedListLayout);

    m_scrollArea->setWidget(playedListContainer);
    m_playedListWidget->setMovedScrollBar(m_scrollArea->verticalScrollBar());

    containLayout->addWidget(m_scrollArea);
    m_containWidget->setLayout(containLayout);
}

QWidget *MusicPlayedListPopWidget::createContainerWidget()
{
    QWidget *topWidget = new QWidget(this);
    topWidget->setFixedHeight(35);
    topWidget->setStyleSheet(MusicUIObject::MBackgroundStyle20);

    QHBoxLayout *topWidgetLayout = new QHBoxLayout(topWidget);
    topWidgetLayout->setSpacing(15);
    QLabel *label = new QLabel(tr("playedList"), topWidget);
    label->setStyleSheet(MusicUIObject::MColorStyle11 + MusicUIObject::MFontStyle01 +
                         MusicUIObject::MFontStyle03);

    QPushButton *shareButton = new QPushButton(this);
    shareButton->setFixedSize(16, 16);
    shareButton->setToolTip(tr("shareList"));
    shareButton->setCursor(QCursor(Qt::PointingHandCursor));
    shareButton->setStyleSheet(MusicUIObject::MKGTinyBtnShare);

    QPushButton *deleteButton = new QPushButton(this);
    deleteButton->setFixedSize(16, 16);
    deleteButton->setToolTip(tr("clearList"));
    deleteButton->setCursor(QCursor(Qt::PointingHandCursor));
    deleteButton->setStyleSheet(MusicUIObject::MKGTinyBtnDelete);
    connect(deleteButton, SIGNAL(clicked()), SLOT(setDeleteItemAll()));

#ifdef Q_OS_UNIX
    shareButton->setFocusPolicy(Qt::NoFocus);
    deleteButton->setFocusPolicy(Qt::NoFocus);
#endif

    QToolButton *closeButton = new QToolButton(this);
    closeButton->setFixedSize(16, 16);
    closeButton->setToolTip(tr("closeList"));
    closeButton->setCursor(QCursor(Qt::PointingHandCursor));
    closeButton->setStyleSheet(MusicUIObject::MKGTinyBtnClose);
    connect(closeButton, SIGNAL(clicked()), m_menu, SLOT(close()));

    topWidgetLayout->addWidget(label);
    topWidgetLayout->addStretch(1);
    topWidgetLayout->addWidget(shareButton);
    topWidgetLayout->addWidget(deleteButton);
    topWidgetLayout->addWidget(closeButton);
    topWidget->setLayout(topWidgetLayout);

    return topWidget;
}

void MusicPlayedListPopWidget::updateSongsFileName()
{
    setPlayListCount(m_songLists.count());
    m_playedListWidget->updateSongsFileName(m_songLists);
}

void MusicPlayedListPopWidget::setPlayListCount(int count)
{
    if(count >= 1000)
    {
        for(int i=MAX_SIZE-1; i>=0; --i)
        {
            m_labels[i]->setPixmap(QPixmap(QString(":/tiny/lb_number%1").arg(9)));
        }
    }
    else
    {
        for(int i=MAX_SIZE-1; i>=0; --i)
        {
            m_labels[i]->setPixmap(QPixmap(QString(":/tiny/lb_number%1").arg(count%10)));
            count = count/10;
        }
    }
}
