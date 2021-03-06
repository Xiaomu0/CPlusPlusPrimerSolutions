#include "common/message.h"

#include <set>
#include <string>

#include "common/folder.h"

namespace cps {

Message::~Message() { removeFromFolders(); }
Message::Message(const Message &m)
    : contents_(m.contents_), folders_(m.folders_) {
  addToFolders(m);
}
Message &Message::operator=(const Message &rhs) {
  removeFromFolders();
  contents_ = rhs.contents_;
  folders_ = rhs.folders_;
  addToFolders(rhs);
  return *this;
}
Message::Message(Message &&m) : contents_(std::move(m.contents_)) {
  moveFolders(&m);
}
Message &Message::operator=(Message &&rhs) {
  if (this != &rhs) {
    removeFromFolders();
    contents_ = std::move(rhs.contents_);
    moveFolders(&rhs);
  }
  return *this;
}

void Message::SaveTo(Folder &f) {
  addFolder(&f);
  f.addMsg(this);
}
void Message::RemoveFrom(Folder &f) {
  rmFolder(&f);
  f.rmMsg(this);
}

void Message::moveFolders(Message *m) {
  folders_ = std::move(m->folders_);
  for (auto f : folders_) {
    f->rmMsg(m);
    f->addMsg(this);
  }
  m->folders_.clear();
}

void Message::addFolder(Folder *f) { folders_.insert(f); }
void Message::rmFolder(Folder *f) { folders_.erase(f); }

void Message::addToFolders(const Message &m) {
  for (auto f : m.folders_) {
    f->addMsg(this);
  }
}
void Message::removeFromFolders() {
  for (auto f : folders_) {
    f->rmMsg(this);
  }
}

void swap(Message &l, Message &r) {
  using std::swap;
  swap(l.contents_, r.contents_);

  l.removeFromFolders();
  r.removeFromFolders();
  swap(l.folders_, r.folders_);
  l.addToFolders(l);
  r.addToFolders(r);
}

} // namespace cps
