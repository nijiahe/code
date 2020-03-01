#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <memory>
#include <numeric>
#include <iterator>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <utility>
#include <cstring>

class Folder;

class Message {
	friend class Folder;
	friend void swap(Message &lhs, Message &rhs);
public:
	explicit Message(const std::string &str = "") :contents(str) {};
	Message(const Message&);
	Message& operator=(const Message&);
	~Message();
	void save(Folder&);
	void remove(Folder&);
	void addFolder(Folder *);
	void removeFolder(Folder *);
private:
	std::string contents;//消息实际内容
	std::set<Folder *> folders;//记载此contents在哪个目录
	void add_to_Folders(const Message&);
	void remove_from_Folders();
};

class Folder
{
public:
	Folder(const Folder &);
	Folder& operator=(const Folder&);
	~Folder();
	void addMsg(Message *);
	void remMsg(Message *);
private:
	std::set<Message *> msgs;
};

void Message::save(Folder &f)
{
	folders.insert(&f);
	f.addMsg(this);
}

void Message::remove(Folder &f)
{
	folders.erase(&f);
	f.remMsg(this);
}

void Message::add_to_Folders(const Message &m)
{
	for (auto f : m.folders)
		f->addMsg(this);
}

Message::Message(const Message &m) :contents(m.contents), folders(m.folders)
{
	add_to_Folders(m);
}

void Message::remove_from_Folders()
{
	for (auto f : folders)
		f->remMsg(this);
}

Message::~Message()
{
	remove_from_Folders();
}

Message& Message::operator=(const Message& rhs)
{
	remove_from_Folders();
	contents = rhs.contents;
	folders = rhs.folders;
	add_to_Folders(rhs);
	return *this;
}

void swap(Message &lhs, Message &rhs)
{
	using std::swap;
	for (auto f : lhs.folders)
		f->remMsg(&lhs);
	for (auto f : rhs.folders)
		f->remMsg(&rhs);
	swap(lhs.folders, rhs.folders);
	swap(lhs.contents, rhs.contents);
	for (auto f : lhs.folders)
		f->addMsg(&lhs);
	for (auto f : rhs.folders)
		f->addMsg(&rhs);

}

inline
void Message::addFolder(Folder *f)
{
	folders.insert(f);
}

inline
void Message::removeFolder(Folder *f)
{
	folders.erase(f);
}

Folder::Folder(const Folder &f):msgs(f.msgs)
{
	for (auto m : msgs)
	{
		addMsg(m);
		m->addFolder(this);
	}
		
}
Folder& Folder::operator=(const Folder&rhf)
{
	for (auto m : msgs)
	{
		remMsg(m);
		m->removeFolder(this);
	}	
	for (auto m : msgs)
	{
		addMsg(m);
		m->addFolder(this);
	}
	return *this;
}
Folder::~Folder()
{
	for (auto m : msgs) {
		remMsg(m);
		m->removeFolder(this);
	}
		
}
void Folder::addMsg(Message *m)
{
	m->folders.insert(this);
	msgs.insert(m);
}
void Folder::remMsg(Message *m)
{
	m->folders.erase(this);
	msgs.erase(m);
}