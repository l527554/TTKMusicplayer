#ifndef MUSICLEFTAREAWIDGET_H
#define MUSICLEFTAREAWIDGET_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (c) 2015 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QWidget>
#include "musicglobaldefine.h"

class MusicSoundKMicroWidget;
class MusicCloudSharedSongWidget;
class MusicQualityChoicePopWidget;

namespace Ui {
    class MusicApplication;
}

/*! @brief The class of the app left area widget.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_GUI_EXPORT MusicLeftAreaWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicLeftAreaWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    ~MusicLeftAreaWidget();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    static MusicLeftAreaWidget *instance();
    /*!
     * Get class object instance.
     */
    void setupUi(Ui::MusicApplication* ui);
    /*!
     * Set up app ui.
     */
    void musictLoveStateClicked(bool state);
    /*!
     * Reset current music love icon state.
     */
    void createSoundKMicroWidget(const QString &name);
    /*!
     * Create sound KMicro widget.
     */

    bool isLrcWidgetShowFullScreen() const;
    /*!
     * Current is show full container.
     */

Q_SIGNALS:
    void currentLoveStateChanged();
    /*!
     * Current music love icon state changed.
     */
    void currentDownloadStateChanged();
    /*!
     * Current music download icon state changed.
     */

public Q_SLOTS:
    void setTransparent(int index);
    /*!
     * Set list background skin transparent.
     */
    void musicDownloadSongToLocal();
    /*!
     * To download music data from net to load.
     */
    void musicDownloadSongFinished();
    /*!
     * To download music data from net finished.
     */
    void cloudSharedSongUploadAllDone();
    /*!
     * All files upload finsihed.
     */
    void lrcWidgetShowFullScreen();
    /*!
     * Show full container or not.
     */
    void switchToSelectedItemStyle(int index);
    /*!
     * Switch to selected item style.
     */

protected:
    void musicStackedSongListWidgetChanged();
    /*!
     * Change to song list widget.
     */
    void musicStackedRadioWidgetChanged();
    /*!
     * Change to radio widget.
     */
    void musicStackedMyDownWidgetChanged();
    /*!
     * Change to my download widget.
     */
    void musicStackedMobileWidgetChanged();
    /*!
     * Change to mobile widget.
     */
    void musicStackedCloudWidgetChanged();
    /*!
     * Change to shared cloud widget.
     */

    Ui::MusicApplication *m_ui;

    int m_currentIndex;
    bool m_lrcWidgetShowFullScreen;
    QWidget *m_stackedWidget;
    MusicSoundKMicroWidget *m_soundKMicroWidget;
    MusicQualityChoicePopWidget *m_qualityChoiceWidget;
    MusicCloudSharedSongWidget *m_cloudSharedSongWidget;

    static MusicLeftAreaWidget *m_instance;
};

#endif // MUSICLEFTAREAWIDGET_H
