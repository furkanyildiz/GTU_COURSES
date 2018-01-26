public interface FamilyInterface {
    /**
     * Add new person to binary family tree
     * @param name name of person who will be add
     * @param parent parent name of person who will add
     * @param nickname nickname of person who will add
     * @throws java.lang.Exception throws exception is there is more than one person have same nickname
     */
    public void add(String name, String parent, String nickname) throws Exception;
    /**
     * This method traverses the tree pre-order with using iterator and
     * prints it to console.
     */
    public void traversePreOrder();
}
