import java.util.Iterator;
import java.util.NoSuchElementException;

public class myStringBuilder{
    /**
     * The linked list's referance which will be use to store strings
     */
    private myLinkedList<String> linkedList;

    /**
     * Constucture creates a myLinkedList object
     */
    myStringBuilder(){
        linkedList = new myLinkedList();
    }

    /**
     * Appends the string representation of the char argument to this sequence.
     * @param item char
     * @return a reference to this object.
     */
    public myStringBuilder append(char item) {

        linkedList.add(String.valueOf(item));
        return this;

    }

    /**
     * Appends the string representation of the boolean argument to the sequence.
     * @param item boolean
     * @return a reference to this object.
     */
    public myStringBuilder append(boolean item) {

        linkedList.add(String.valueOf(item));
        return this;

    }

    /**
     * Appends the string representation of the int argument to this sequence.
     * @param item a integer
     * @return a reference to this object.
     *
     */
    public myStringBuilder append(int item) {

        linkedList.add(String.valueOf(item));
        return this;

    }
    /**
     * Appends the string representation of the double argument to this sequence.
     * @param item a double
     * @return a reference to this object.
     *
     */
    public myStringBuilder append(double item) {

        linkedList.add(String.valueOf(item));
        return this;

    }
    /**
     * Appends the string representation of the float argument to this sequence.
     * @param item a float
     * @return a reference to this object.
     *
     */
    public myStringBuilder append(float item) {

        linkedList.add(String.valueOf(item));
        return this;

    }
    /**
     * Appends the string representation of the long argument to this sequence.
     * @param item a long
     * @return a reference to this object.
     *
     */
    public myStringBuilder append(long item) {

        linkedList.add(String.valueOf(item));
        return this;

    }
    /**
     * Appends the string representation of the Object argument.
     * @param item an Object
     * @return a reference to this object.
     *
     */
    public myStringBuilder append(Object item) {

        linkedList.add(String.valueOf(item));
        return this;

    }
    /**
     * Appends the specified StringBuffer to this sequence.
     * @param item the StringBuffer to append.
     * @return a reference to this object.
     *
     */
    public myStringBuilder append(StringBuffer  item) {

        linkedList.add(String.valueOf(item));
        return this;

    }
    /**
     * Appends the string representation of the char array argument to this sequence.
     * @param item char array
     * @return a reference to this object.
     *
     */
    public myStringBuilder append(char[] item) {

        linkedList.add(String.valueOf(item));
        return this;

    }

    /**
     * Appends the string representation of a subarray of the char array argument to this sequence.
     * @param item the characters to be appended.
     * @param offset the index of the first char to append
     * @param len the number of chars to append.
     * @return a reference to this object.
     * @throws IndexOutOfBoundsException if 'offset smaller than 0' or 'len smallar than 0' or 'offset+len bigger than str.length'
     */
    public myStringBuilder append(char[] item, int offset , int len)throws IndexOutOfBoundsException {
        if ( offset < 0 || len < 0 || offset+len > item.length)
            throw  new IndexOutOfBoundsException();
        char[] temp = new char[len];
        int j =0;
        for(int i=offset; j<len; ++i)
            temp[j++] = item[i];

        linkedList.add(String.valueOf(temp));
        return this;

    }
    /**
     * Appends the specified character sequence to this Appendable.
     * @param item the characters to be appended.
     * @return a reference to this object.
     *
     */
    public myStringBuilder append(CharSequence item) {

        linkedList.add(String.valueOf(item));
        return this;

    }

    /**
     * Appends the specified character sequence to this Appendable.
     * @param s the sequence to append.
     * @param start  the starting index of the subsequence to be appended.
     * @param end  the end index of the subsequence to be appended.
     * @return a reference to this object.
     * @throws IndexOutOfBoundsException if start is negative, or start is greater than end or end is greater than s.length()
     */

    public myStringBuilder append(CharSequence s, int start, int end)throws IndexOutOfBoundsException{
        if(start<0 || start >end || end>s.length())
            throw  new IndexOutOfBoundsException();

        CharSequence temp = s.subSequence(start,end);

        linkedList.add(String.valueOf(temp));
        return this;
    }
    /**
     * Appends the specified string to this character sequence.
     * @param item a string
     * @return a reference to this object.
     *
     */
    public myStringBuilder append(String item){
        linkedList.add(item);
        return this;

    }
    /**
     * To delete some or one element of myStringBuilder object
     * @param item deleted object
     * @throws NoSuchElementException if item is not found in myStringBuilder
     */
    public void delete(Object item) throws NoSuchElementException{
        linkedList.remove(String.valueOf(item));

    }

    /**
     * Returns a string representing the data in this sequence.
     * The method uses get methods and indexs of myLinkedList class.
     * @return representing the data in this sequence.
     */
    public String toString(){
        String returnString ="";
        for(int i =0; i<linkedList.getSize(); ++i)
            returnString+=linkedList.get(i);

        return returnString;
    }
    /**
     * Returns a string representing the data in this sequence.
     * The method uses Iterator for myLinkedList class.
     * @return representing the data in this sequence.
     */
    public String toString2(){
        String returnString ="";
        Iterator iter = linkedList.iterator();
        while(iter.hasNext())
            returnString += iter.next();


        return returnString;
    }
    /**
     * Returns a string representing the data in this sequence.
     * The method uses linked list's toString method.
     * @return representing the data in this sequence.
     */
    public String toString3(){
        return linkedList.toString();
    }
}
