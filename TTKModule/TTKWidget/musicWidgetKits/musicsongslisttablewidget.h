#ifndef MUSICSONGSLISTTABLEWIDGET_H
#define MUSICSONGSLISTTABLEWIDGET_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (c) 2015 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QTimer>
#include "musicsongslistabstracttablewidget.h"

class QPropertyAnimation;
class MusicOpenFileWidget;
class MusicSongsListPlayWidget;
class MusicSongsListItemInfoWidget;

/*! @brief The class of the songs list table widget.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_WIDGET_EXPORT MusicSongsListTableWidget : public MusicSongsListAbstractTableWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit MusicSongsListTableWidget(int index, QWidget *parent = 0);

    virtual ~MusicSongsListTableWidget();

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Update songs file names in table.
     */
    virtual void updateSongsFileName(const MusicSongs &songs) override;
    /*!
     * Clear All Items.
     */
    void clearAllItems();
    /*!
     * Set current searched file indexs.
     */
    void setMusicSongsSearchedFileName(MusicSongs *songs, const MusicObject::MIntList &fileIndexs);

    /*!
     * Select the current play row.
     */
    virtual void selectRow(int index) override;
    /*!
     * Get the current play row.
     */
    inline int getPlayRowIndex() const { return m_playRowIndex; }
    /*!
     * Set music sort.
     */
    inline void setMusicSort(MusicSort *sort) { m_musicSort = sort;}
    /*!
     * Update item time label time.
     */
    void setTimerLabel(const QString &time, const QString &total) const;
    /*!
     * Update current artist when it download finished.
     */
    void updateCurrentArtist();
    /*!
     * Replace current play widget row.
     */
    void replacePlayWidgetRow();
    /*!
     * Create upload file widget.
     */
    bool createUploadFileWidget();

Q_SIGNALS:
    /*!
     * Add new music file or files to list.
     */
    void musicAddNewFiles();
    /*!
     * Add new music dir to list.
     */
    void musicAddNewDir();

    /*!
     * Check current list is searched or not.
     */
    void isSearchFileListEmpty(bool &empty);
    /*!
     * Delete items from indexs and check remove file or not.
     */
    void deleteItemAt(const MusicObject::MIntList &index, bool fileRemove);
    /*!
     * Swap the current play index when user drag and drop.
     */
    void getMusicIndexSwaped(int before, int after, int play, MusicSongs &songs);
    /*!
     * Add or remove music list song to lovest list by row.
     */
    void musicListSongToLovestListAt(bool oper, int row);
    /*!
     * Show the float function widget.
     */
    void showFloatWidget();
    /*!
     * Music list songs sort by type.
     */
    void musicListSongSortBy(int index);

public Q_SLOTS:
    /*!
     * Table widget list cell enter.
     */
    virtual void listCellEntered(int row, int column) override;
    /*!
     * Table widget list cell click.
     */
    virtual void listCellClicked(int row, int column) override;
    /*!
     * Delete item from list at current row.
     */
    virtual void setDeleteItemAt() override;
    /*!
     * Delete item or items from list with file.
     */
    void setDeleteItemWithFile();
    /*!
     * Show play item information widget.
     */
    void showTimeOut();
    /*!
     * Hide play item information widget.
     */
    void stayTimeOut();
    /*!
     * Reset item name by current row.
     */
    void setChangSongName();
    /*!
     * Open music make ring widget.
     */
    void musicMakeRingWidget();
    /*!
     * Open music transform widget.
     */
    void musicTransformWidget();
    /*!
     * To search song mv by song name in play widget.
     */
    void musicSongMovieFoundPy();
    /*!
     * Open music similar found widget in play widget.
     */
    void musicSimilarFoundWidgetPy();
    /*!
     * Open music song shared widget in play widget.
     */
    void musicSongSharedWidgetPy();
    /*!
     * Open music song KMicro widget in play widget.
     */
    void musicSongKMicroWidgetPy();
    /*!
     * Open music song search query.
     */
    void musicSearchQuery(QAction *action);
    /*!
     * Add music to played list and play later.
     */
    void musicAddToPlayLater();
    /*!
     * Add music to played list.
     */
    void musicAddToPlayedList();
    /*!
     * Rename item artist label is finised.
     */
    void setItemRenameFinished(const QString &name);
    /*!
     * Music list songs sort by type.
     */
    void musicListSongSortBy(QAction *action);

protected:
    /*!
     * Override the widget event.
     */
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
    /*!
     * Close rename item.
     */
    void closeRenameItem();
    /*!
     * Start to drag to play list.
     */
    void startToDrag();
    /*!
     * Create context menu.
     */
    void createContextMenu(QMenu &menu);

    int m_dragStartIndex;
    QPoint m_dragStartPoint;
    bool m_mouseMoved;

    QTimer m_timerShow, m_timerStay;
    MusicOpenFileWidget *m_openFileWidget;
    MusicSongsListItemInfoWidget *m_musicSongsInfoWidget;
    MusicSongsListPlayWidget *m_musicSongsPlayWidget;

    bool m_leftButtonPressed, m_listHasSearched;
    bool m_renameActived, m_deleteItemWithFile;
    QTableWidgetItem *m_renameItem;
    MusicSort *m_musicSort;

};

#endif // MUSICSONGSLISTTABLEWIDGET_H
