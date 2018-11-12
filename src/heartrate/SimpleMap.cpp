/*
 * SimpleMap.cpp
 *
 *  Created on: Aug 19, 2017
 *      Author: roger
 */

#include "SimpleMap.h"

long SimpleMap::put(long key) {
	if (m_firstNode == NULL) {
		// first node
		m_firstNode = new Node(key, NULL);
		m_count++;
//		Serial.print("First key ");
//		Serial.println(key);
		return m_firstNode->getValue();
	}
	Node *next = m_firstNode;
	Node *prev = NULL;
	while (next != NULL && next->getKey() <= key) {
		prev = next;
//		Serial.print("looping: key: ");
//		Serial.println(prev->getKey());
		next = next->next();
	}
	if (prev == NULL) {
		if (next->getKey() == key) {
			return next->getValue();
		}
		// must be the first node
		m_firstNode = new Node(key, next);
		m_count++;
		return m_firstNode->getValue();
	}
//	Serial.print("found: key: ");
//	Serial.println(prev->getKey());
	if (prev->getKey() == key) {
		// Found the exact key
//		Serial.print("Incremented for key ");
//		Serial.println(key);
		return prev->incrementValue();
	}
	Node *n = new Node(key, next);
	prev->setNext(n);
	m_count++;
//	Serial.print("New key ");
//	Serial.println(key);
	return (n->getValue());
}
void SimpleMap::purge() {
	Node *next = m_firstNode;
	while (next != NULL ) {
		Node *d = next;
		next = next->next();
		delete d;
	}
	m_count = 0;
	m_firstNode = NULL;
}

void SimpleMap::dump() {
	Serial.print("number of nodes=");
	Serial.println(m_count);
	Node *next = m_firstNode;
	while (next != NULL) {
		Serial.print("key,value=");
		Serial.print(next->getKey());
		Serial.print(",");
		Serial.println(next->getValue());
		next = next->next();
	}
}

SimpleMap::~SimpleMap() {
	purge();
}
Node::~Node() {
}

