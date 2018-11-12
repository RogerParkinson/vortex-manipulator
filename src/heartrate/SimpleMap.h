/*
 * SimpleMap.h
 *
 *  Created on: Aug 19, 2017
 *      Author: roger
 */

#ifndef SIMPLEMAP_H_
#define SIMPLEMAP_H_
#include "Arduino.h"

class Node {
private:
	long m_key;
	long m_value;
	Node *m_nextNode;

public:
	Node(long key, Node *next) {
		m_key = key;
		m_value = 1;
		m_nextNode = next;
	}
	long getValue() {
		return m_value;
	}
	long incrementValue() {
		return ++m_value;
	}
	long getKey() {
		return m_key;
	}
	Node *next() {
		return m_nextNode;
	}
	void setNext(Node *next) {
		m_nextNode = next;
	}
	virtual ~Node();
};

class SimpleMap {
private:
	int m_count;
	Node *m_firstNode;
public:
	SimpleMap() {
		m_count = 0;
		m_firstNode = NULL;
	};
	void purge();
	long put(long key);
	void dump();
	virtual ~SimpleMap();
};

#endif /* SIMPLEMAP_H_ */
