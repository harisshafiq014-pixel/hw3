#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below

  std::vector<T> items_;
  int m_;
  PComparator comp_;

  void trickleUp(size_t index);
  void trickleDown(size_t index);
};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
  : m_(m), comp_(c)
{
  if(m < 2) {
    throw std::invalid_argument("Heap arity must be at least 2");
  }
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return items_.empty();
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return items_.size();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  // Add the item at the end of the vector.
  items_.push_back(item);

  // Move the item upward until the heap property is restored.
  trickleUp(items_.size() - 1);
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(size_t index)
{
  while(index > 0) {
    // Parent of index i in an m-ary heap:
    size_t parent = (index - 1) / m_;

    // comp_ returns true when the first argument has priority.
    // Stop if the child does not have priority over the parent.
    if(!comp_(items_[index], items_[parent])) {
      break;
    }

    T temp = items_[index];
    items_[index] = items_[parent];
    items_[parent] = temp;

    index = parent;
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleDown(size_t index)
{
  while(true) {
    // First child of index i in an m-ary heap:
    size_t firstChild = index * m_ + 1;

    // If the first child is outside the vector, there are no children.
    if(firstChild >= items_.size()) {
      break;
    }

    // Start by assuming the first child has the highest priority.
    size_t priorityChild = firstChild;

    // Check the remaining possible children.
    for(int offset = 1; offset < m_; offset++) {
      size_t child = firstChild + offset;

      if(child >= items_.size()) {
        break;
      }

      if(comp_(items_[child], items_[priorityChild])) {
        priorityChild = child;
      }
    }

    // Stop if the best child does not have priority over the parent.
    if(!comp_(items_[priorityChild], items_[index])) {
      break;
    }

    T temp = items_[index];
    items_[index] = items_[priorityChild];
    items_[priorityChild] = temp;

    index = priorityChild;
  }
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================

    throw std::underflow_error("Cannot access the top of an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element

  return items_[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================

    throw std::underflow_error("Cannot pop an empty heap");
  }

  // If there is only one item, simply remove it.
  if(items_.size() == 1) {
    items_.pop_back();
    return;
  }

  // Move the final item to the root and remove its old position.
  items_[0] = items_.back();
  items_.pop_back();

  // Restore the heap property by moving the new root downward.
  trickleDown(0);
}

#endif