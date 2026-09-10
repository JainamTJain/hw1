#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

void ULListStr::push_back(const std::string& val)
{
  if (tail_ == NULL) {
    // list is empty -- allocate first node
    Item* newItem = new Item();
    newItem->val[0] = val;
    newItem->first = 0;
    newItem->last = 1;
    head_ = tail_ = newItem;
  } else if (tail_->last < ARRSIZE) {
    // room at the end of tail_'s array
    tail_->val[tail_->last] = val;
    tail_->last++;
  } else {
    // tail_ is full -- allocate a new node after it
    Item* newItem = new Item();
    newItem->val[0] = val;
    newItem->first = 0;
    newItem->last = 1;
    newItem->prev = tail_;
    tail_->next = newItem;
    tail_ = newItem;
  }
  size_++;
}

void ULListStr::pop_back()
{
  if (tail_ == NULL) {
    throw std::invalid_argument("pop_back on empty list");
  }

  tail_->last--;

  if (tail_->first == tail_->last) {
    // node is now empty -- deallocate it
    Item* toDelete = tail_;
    tail_ = tail_->prev;
    if (tail_ != NULL) {
      tail_->next = NULL;
    } else {
      head_ = NULL; // list is now empty
    }
    delete toDelete;
  }
  size_--;
}

void ULListStr::push_front(const std::string& val)
{
  if (head_ == NULL) {
    // list is empty, we need to allocate first node
    Item* newItem = new Item();
    newItem->val[0] = val;
    newItem->first = 0;
    newItem->last = 1;
    head_ = tail_ = newItem;
  } else if (head_->first > 0) {
    // room before 'first' in head_'s array
    head_->first--;
    head_->val[head_->first] = val;
  } else {
    // head_ has no room before 'first' -- allocate a new head node
    // place value at the last slot, leaving room before it for future push_fronts
    Item* newItem = new Item();
    newItem->first = ARRSIZE - 1;
    newItem->last = ARRSIZE;
    newItem->val[ARRSIZE - 1] = val;
    newItem->next = head_;
    head_->prev = newItem;
    head_ = newItem;
  }
  size_++;
}

void ULListStr::pop_front()
{
  if (head_ == NULL) {
    throw std::invalid_argument("pop_front on empty list");
  }

  head_->first++;

  if (head_->first == head_->last) {
    // node is now empty -- deallocate it
    Item* toDelete = head_;
    head_ = head_->next;
    if (head_ != NULL) {
      head_->prev = NULL;
    } else {
      tail_ = NULL; // list is now empty
    }
    delete toDelete;
  }
  size_--;
}

std::string const & ULListStr::back() const
{
  if (tail_ == NULL) {
    throw std::invalid_argument("back on empty list");
  }
  return tail_->val[tail_->last - 1];
}

std::string const & ULListStr::front() const
{
  if (head_ == NULL) {
    throw std::invalid_argument("front on empty list");
  }
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const
{
  if (loc >= size_) return NULL;

  Item* cur = head_;
  size_t count = 0;

  while (cur != NULL) {
    size_t used = cur->last - cur->first;
    if (loc < count + used) {
      return const_cast<std::string*>(&cur->val[cur->first + (loc - count)]);
    }
    count += used;
    cur = cur->next;
  }
  return NULL; // I would say shouldn't be reached if size_ is maintained correctly
}
