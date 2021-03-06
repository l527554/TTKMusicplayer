#ifndef MUSICREMOTEWIDGETFORRIPPLES_H
#define MUSICREMOTEWIDGETFORRIPPLES_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (c) 2015 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicremotewidget.h"

class MusicMarqueeWidget;

/*! @brief The class of the desktop ripples remote widget.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_REMOTE_EXPORT MusicRemoteWidgetForRipples : public MusicRemoteWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit MusicRemoteWidgetForRipples(QWidget *parent = 0);

    virtual ~MusicRemoteWidgetForRipples();

    /*!
     * Get class object name.
     */
    static QString getClassName();
    /*!
     * Set current song text.
     */
    virtual void setLabelText(const QString &value) override;

protected:
    /*!
     * Enable ripples control.
     */
    void enableRipples(bool enable);

    MusicMarqueeWidget *m_songNameLabel;

};

#endif // MUSICREMOTEWIDGETFORRIPPLES_H
