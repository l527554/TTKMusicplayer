#ifndef MUSICPLAYLIST_H
#define MUSICPLAYLIST_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (c) 2015 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QStringList>
#include "musicobject.h"
#include "musicglobaldefine.h"

/*! @brief The class of the music playlist.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_CORE_EXPORT MusicPlaylist : public QObject
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit MusicPlaylist(QObject *parent = 0);

    ~MusicPlaylist() = default;

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Get current play mode.
     */
    MusicObject::PlayMode playbackMode() const;
    /*!
     * Set current play mode.
     */
    void setPlaybackMode(MusicObject::PlayMode mode);

    /*!
     * Get current play index.
     */
    int currentIndex() const;
    /*!
     * Get current play music media path.
     */
    QString currentMediaString() const;
    /*!
     * Get all music media path.
     */
    QStringList mediaList() const;
    /*!
     * Get current medias count.
     */
    int mediaCount() const;
    /*!
     * Check current medias is empty.
     */
    bool isEmpty() const;
    /*!
     * Clear current medias.
     */
    bool clear();

    /*!
     * Add music media, not append remember.
     */
    void addMedia(const QString &content);
    /*!
     * Add music media list, not append remember.
     */
    void addMedia(const QStringList &items);
    /*!
     * Insert music media into current medias by index.
     */
    bool insertMedia(int index, const QString &content);
    /*!
     * Insert music medias into current medias by index.
     */
    bool insertMedia(int index, const QStringList &items);
    /*!
     * Remove music media from current medias by index.
     */
    bool removeMedia(int pos);
    /*!
     * Remove music media from current medias by index between start and end.
     */
    bool removeMedia(int start, int end);

Q_SIGNALS:
    /*!
     * Current play index changed emit.
     */
    void currentIndexChanged(int index);
    /*!
     * Current play mode changed emit.
     */
    void playbackModeChanged(MusicObject::PlayMode mode);

public Q_SLOTS:
    /*!
     * Set current play index.
     */
    void setCurrentIndex(int index = DEFAULT_INDEX_LEVEL1);
    /*!
     * Append music media.
     */
    void appendMedia(const QString &content);
    /*!
     * Append music medias.
     */
    void appendMedia(const QStringList &items);
    /*!
     * Update music medias into current medias by index.
     */
    void updateMediaLists(const QStringList &list, int index);

protected:
    int m_currentIndex;
    QStringList m_mediaList;
    MusicObject::PlayMode m_playbackMode;

};

#endif // MUSICPLAYLIST_H
