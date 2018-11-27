/*
 * Notification.h
 *
 *  Created on: 28/04/2013
 *      Author: roger
 */

#ifndef NOTIFICATION_H_
#define NOTIFICATION_H_
#include "AppRegistry.h"
#include "ui/Button.h"
#define NOTIFICATION_DEBUG
#define MAX_NOTIFICATIONS 11


class NotificationInstance {

public:
	NotificationInstance *m_next;
	const String *m_content;
	long m_timeStamp;
	NotificationInstance(const char *s) {
		m_content = new String(s);
		m_next = NULL;
		m_timeStamp = now();
	};
	NotificationInstance(const char *s, NotificationInstance *n) {
		m_content = new String(s);
		m_next = n;
		m_timeStamp = now();
	};
	~NotificationInstance() {
		delete m_content;
		m_next = NULL;
	};
};
class Notification : public App {
private:
	virtual void setup();
	int count=0;
	NotificationInstance *m_notificationInstance;

public:
	Notification();
	void deleteLastNotification(NotificationInstance *n);
	virtual unsigned long getUpdateInterval() {return 1000000UL;};
	virtual void init();
	virtual void display();
	virtual const char* getName();
	virtual void notify(const char *s);
	virtual void addMessage(const char *s);
	virtual const Icon *getIcon();
	virtual ~Notification();
};

#endif /* NOTIFICATION_H_ */
