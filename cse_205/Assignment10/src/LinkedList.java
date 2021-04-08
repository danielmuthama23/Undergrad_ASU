// Assignment #: 10
//         Name: Tyler Fichiera
//    StudentID: 1218959911
//  Lab Lecture: T/Th 4:30pm
//      Section: 33116
//  Description: The LinkedList defines a linked list using its node class
//               object and also defines a iterator class to traverse the linked list.


import java.util.NoSuchElementException;

/**
   A linked list is a sequence of nodes with efficient
   element insertion and removal. This class
   contains a subset of the methods of the standard
   java.util.LinkedList class.
*/
public class LinkedList {
    /** Constructs an empty linked list. */
    public LinkedList() {
        first = null;
    }

    /**
        Returns the first element in the linked list.
        @return the first element in the linked list
    */
    public Object getFirst() {
        if (first == null)
            throw new NoSuchElementException();
        return first.data;
    }

    /**
        Removes the first element in the linked list.
        @return the removed element
    */
    public Object removeFirst() {
        if (first == null)
            throw new NoSuchElementException();
        Object element = first.data;
        first = first.next;
        return element;
    }

    /**
        Adds an element to the front of the linked list.
        @param element the element to add
    */
    public void addFirst(Object element) {
        Node newNode = new Node();
        newNode.data = element;
        newNode.next = first;
        first = newNode;
    }

    /*************** Added methods *******************************/

    // 1. The add adds the parameter string into the linked list. The linked list
    //     should contain all strings in alphabetical order
    public void add(String element) {
        // add as first element if the list is empty or the new element is
        // less than the first one already placed
        if (this.first == null || element.compareTo(this.first.data.toString()) < 0) {
            addFirst(element);
        } else {
            // create a new node with the current element
            Node newNode = new Node();
            newNode.data = element;

            // use these as tracking variables when shifting the list forwards
            // instantiate them using the first node
            Node current = this.first.next, previous = this.first;

            // until the correct position is found
            while (current != null) {
                // compare the arg element to the current one
                if (element.compareTo(current.data.toString()) < 0) {
                    // break the loop once the position of where it should
                    // be inserted is found
                    break;
                }

                // shift the elements
                previous = current;
                current = current.next;
            }

            // make one last change to the list so that all element
            // are in the correct position before finalizing
            newNode.next = previous.next;
            previous.next = newNode;
        }
    }

    // 2. count method counts how many times the parameter object
    //    appears in the linked list and return the number. It returns 0
    //    if the parameter object does not exist in the linked list.
    public int count(String element) {
        // instantiate a new iterator
        LinkedListIterator iterator = new LinkedListIterator();
        // counter var
        int c = 0;

        // iterate through all elements in the linked list
        while (iterator.hasNext()) {
            // if the two elements match, increase counter
            if (iterator.next().equals(element))
                c++;
        }

        // return counter
        return c;
    }
    
    //  3. search method returns the index of the parameter object
    //     in the linked list if it exists. It return -1 if it does not
    //     exits. If the index is out of bounds, then it throws an exception.
    public int search(String element) {
        // instantiate a new iterator
        LinkedListIterator iterator = new LinkedListIterator();
        // index counter
        int i = 0;

        // iterate through all elements in the linked list
        while (iterator.hasNext()) {
            // if the two elements match, return the index it is at
            if (iterator.next().equals(element))
                return i;
            // increment the index after every iteration
            i++;
        }

        // return -1 if no elements match
        return -1;
    }
    
    //  4. remove method removes the element at the parameter
    //     index in the linked list.
    public String remove(int index) {
        // instantiate a new iterator
        LinkedListIterator iterator = new LinkedListIterator();
        // var to hold the removed element
        String element = null;

        // iterate through all elements until the correct index is found
        for (int i = 0; i <= index; i++) {
            // set the element var to the current element
            // at the end of the loop, the element that will be
            // removed is stored
            element = (String)iterator.next();

            // break the loop if the given index is greater than the
            // size of the linked list to prevent a `NoSuchElementException` err
            if (!iterator.hasNext()) {
                break;
            }
        }

        // remove the element
        iterator.remove();

        // return removed element
        return element;
    }

    //  5. The method size return the current size of the linked list,
    //     that is, the number of elements in it.
    public int size() {
        // instantiate a new iterator
        LinkedListIterator iterator = new LinkedListIterator();
        // size counter
        int s = 0;

        // iterate through all the elements in list
        while (iterator.hasNext()) {
            iterator.next();
            // increment the size counter for each element
            s++;
        }

        // return the size
        return s;
    }
    

    //  6. The toString method returns a string containing the content
    //     of the linked list. In this assignment, the linked list will
    //     contain only string, so it returns a concatenation of all strings
    //     in the linked list and a line break
    public String toString() {
        // instantiate a new iterator
        LinkedListIterator iterator = new LinkedListIterator();
        // var for the string with the prefix already defined ("{ ")
        String str = "{ ";

        // iterate over all elements in the list
        while (iterator.hasNext()) {
            // concat the element to the string
            str += iterator.next() + " ";
        }

        // return str with the suffix ("{\n")
        return str + "}\n";
    }


    //  7. The removeLastFew method removes the parameter specified number
    //     of elements from the end of the linked list.
    //     If the parameter integer is larger than the current size of
    //     the linked list, then the linked-list will be empty.
    //     If the parameter integer is less than 0,
    //     nothing should be removed from the linked list.
    public void removeLastFew(int howMany) {
        // store the size of list
        int size = this.size();

        // iterate over only the indexes that should be removed
        // the Math.max prevents scenarios where howMany is greater
        // than the num elements in list
        // in a case like that, all elements in the array are removed
        for (int i = Math.max(size - howMany, 0); i < size; i++) {
            remove(i);
        }
    }
        

    /***************************************************************/

    /**
        Returns an iterator for iterating through this list.
        @return an iterator for iterating through this list
    */
    public ListIterator listIterator() {
        return new LinkedListIterator();
    }

    private Node first;

    private class Node {
        public Object data;
        public Node next;
    }

    private class LinkedListIterator implements ListIterator {
        /**
            Constructs an iterator that points to the front
            of the linked list.
        */
        public LinkedListIterator() {
            position = null;
            previous = null;
        }

        /**
            Moves the iterator past the next element.
            @return the traversed element
        */
        public Object next() {
            if (!hasNext())
                throw new NoSuchElementException();
            previous = position; // Remember for remove

            if (position == null)
                position = first;
            else
                position = position.next;

            return position.data;
        }

        /**
            Tests if there is an element after the iterator
            position.
            @return true if there is an element after the iterator
            position
        */
        public boolean hasNext() {
            if (position == null)
                return first != null;
            else
                return position.next != null;
        }

        /**
             Adds an element before the iterator position
            and moves the iterator past the inserted element.
            @param element the element to add
        */
        public void add(Object element) {
            if (position == null) {
                addFirst(element);
                position = first;
            }
            else {
                Node newNode = new Node();
                newNode.data = element;
                newNode.next = position.next;
                position.next = newNode;
                position = newNode;
            }
            previous = position;
        }

        /**
            Removes the last traversed element. This method may
            only be called after a call to the next() method.
        */
        public void remove() {
            if (previous == position)
                throw new IllegalStateException();

            if (position == first) {
                removeFirst();
            }
            else {
                previous.next = position.next;
            }
            position = previous;
        }

        /**
            Sets the last traversed element to a different
            value.
            @param element the element to set
        */
        public void set(Object element) {
            if (position == null)
                throw new NoSuchElementException();
            position.data = element;
        }

        private Node position;
        private Node previous;
    }
}