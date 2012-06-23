/*
 * juickplugin.h - plugin
 * Copyright (C) 2009-2012 Kravtsov Nikolai, Khryukin Evgeny
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef JUICKPLUGIN_H
#define JUICKPLUGIN_H

#include "psiplugin.h"
#include "stanzafilter.h"
#include "optionaccessor.h"
#include "activetabaccessor.h"
#include "plugininfoprovider.h"
#include "toolbariconaccessor.h"
#include "applicationinfoaccessor.h"
#include "ui_settings.h"

class OptionAccessingHost;
class ActiveTabAccessingHost;
class ApplicationInfoAccessingHost;
class JuickDownloader;
class QDomDocument;

class JuickPlugin : public QObject, public PsiPlugin, public OptionAccessor, public ActiveTabAccessor,
			public StanzaFilter, public ApplicationInfoAccessor, public PluginInfoProvider, public ToolbarIconAccessor
{
	Q_OBJECT
	Q_INTERFACES(PsiPlugin OptionAccessor ActiveTabAccessor StanzaFilter
			ApplicationInfoAccessor PluginInfoProvider ToolbarIconAccessor)

public:
	JuickPlugin();
	virtual QString name() const;
	virtual QString shortName() const;
	virtual QString version() const;
	virtual QWidget* options();
	virtual bool enable();
	virtual bool disable();
	virtual void applyOptions();
	virtual void restoreOptions();
	virtual void setOptionAccessingHost(OptionAccessingHost* host);
	virtual void optionChanged(const QString& ) {}
	virtual void setActiveTabAccessingHost(ActiveTabAccessingHost* host);
	virtual void setApplicationInfoAccessingHost(ApplicationInfoAccessingHost* host);
	virtual QString pluginInfo();
	virtual QList < QVariantHash > getButtonParam() { return QList < QVariantHash >(); }
	virtual QAction* getAction(QObject* parent, int account, const QString& contact);

	virtual bool incomingStanza(int account, const QDomElement& stanza);
	virtual bool outgoingStanza(int , QDomElement& ) { return false; }

private slots:
	void chooseColor(QWidget *);
	void clearCache();
	void updateJidList(const QStringList& jids);
	void requestJidList();
	void removeWidget();
	void updateWidgets(const QList<QByteArray> &urls);

private:
	void createAvatarsDir();
	void setStyles();

	void elementFromString(QDomElement* body, QDomDocument* e, const QString &msg, const QString &jid, const QString &resource = "");
	void addPlus(QDomElement* body, QDomDocument* e, const QString &msg, const QString &jid, const QString &resource = "");
	void addSubscribe(QDomElement* body, QDomDocument* e, const QString &msg, const QString &jid, const QString &resource = "");
	void addHttpLink(QDomElement* body, QDomDocument* e, const QString &msg);
	void addTagLink(QDomElement* body, QDomDocument* e, const QString &tag, const QString &jid);
	void addUserLink(QDomElement* body, QDomDocument* e, const QString& nick, const QString& altText, const QString& pattern, const QString& jid);
	void addMessageId(QDomElement* body, QDomDocument* e, const QString& mId, const QString& altText, const QString& pattern, const QString& jid, const QString& resource = "");
	void addUnsubscribe(QDomElement* body, QDomDocument* e, const QString &msg, const QString &jid, const QString &resource = "");
	void addDelete(QDomElement* body ,QDomDocument* e, const QString& msg, const QString& jid, const QString& resource = "");
	void addFavorite(QDomElement* body, QDomDocument* e, const QString &msg, const QString &jid, const QString &resource = "");
	void addAvatar(QDomElement *body, QDomDocument *doc, const QString &msg, const QString &jidToSend, const QString &ujid);

private:
	bool enabled;
	OptionAccessingHost* psiOptions;
	ActiveTabAccessingHost* activeTab;
	ApplicationInfoAccessingHost* applicationInfo;
	QColor userColor, tagColor, msgColor, quoteColor, lineColor;
	bool userBold,tagBold,msgBold,quoteBold,lineBold;
	bool userItalic,tagItalic,msgItalic,quoteItalic,lineItalic;
	bool userUnderline,tagUnderline,msgUnderline,quoteUnderline,lineUnderline;
	QString idStyle,userStyle,tagStyle,quoteStyle,linkStyle;
	QRegExp tagRx, regx, idRx, nickRx;
	QString userLinkPattern,messageLinkPattern,altTextUser,altTextMsg,commonLinkColor;
	bool idAsResource,showPhoto,showAvatars,workInGroupChat;
	QStringList jidList_;
	QPointer<QWidget> optionsWid;
	QList<QWidget*> logs_;
	Ui::settings ui_;
	JuickDownloader* downloader_;
};

#endif // JUICKPLUGIN_H