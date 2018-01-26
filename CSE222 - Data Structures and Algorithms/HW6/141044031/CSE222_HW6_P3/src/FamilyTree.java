import java.util.Iterator;

/**
 *
 * @author yldzf
 */
public class FamilyTree extends BinaryTree<String> implements FamilyInterface {
    /**
     * To calculate more than one father/mother with the same name and nickname
     */
    private static int count = 0 ;

    /**
     * No param constructure do not anthing
     */
    public FamilyTree() {

    }
    /**
     * To add root of tree
     * @param name grandfather or mother of family
     */
    public FamilyTree(String name) {
        super.root = new Node<> (name);
    }
    /**
     * Add new person to binary family tree
     * @param name name of person who will be add
     * @param parent parent name of person who will add
     * @param nickname nickname of person who will add
     * @throws java.lang.Exception throws when nickname is same for at most 1 person.
     */
    @Override
    public void add(String name, String parent, String nickname) throws Exception{

        int nickIndex = nickname.indexOf("-");
        String nick = nickname.substring(nickIndex+1);
        String type = nickname.substring(0, nickIndex);
        //önce nicke sonra parenta
        count = 0;
        if(name.compareTo(nick) == 0){
            root = addForEquality(root, parent, name);
            if(count > 1)
                throw new Exception("More than one father/mother with the same name and nickname the insertion cannot be completed.");

        }
        else{
            count = 0;
            if(type.compareTo("ibn") == 0){
                try {

                    this.root = findChild(this.root,nick,parent,name,false);
                } catch (Exception ex) {
                    throw ex;
                }

            }
            else if(type.compareTo("ebu") == 0){
                try {
                    this.root = findChild(this.root,parent,nick,name,true);
                } catch (Exception ex) {
                    throw ex;

                }

            }
            if(count > 1)
                throw new Exception("More than one father/mother with the same name and nickname the insertion cannot be completed.");

        }
    }
    /**
     * The method for use when nickname and name is same. It founds parents
     * then adds new node to it.
     * @param localRoot root of tree
     * @param parent parent of new node
     * @param add new nodes data
     * @return node with added new node
     */
    private Node<String> addForEquality(Node<String> localRoot, String parent, String add){

        if(localRoot == null)
            return localRoot;

        if(localRoot.data.equals(parent)){
            ++count;

            if(localRoot.left == null)
                localRoot.left = new Node<>(add);
            else
                localRoot.left = addRight(localRoot.left,add);

        }
        localRoot.left =  addForEquality(localRoot.left,parent,add);
        localRoot.right = addForEquality(localRoot.right,parent,add);
        return localRoot;

    }
    /**
     * Returns the string representation of tree object
     * @return string representation of tree object
     */
    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder();
        super.preOrderTraverse(this.root, 1, sb);
        return sb.toString();
    }
    /**
     * If the given parent has the given child add's a new child to it according
     * to given nickname from main (in this metod op)
     * @param localRoot root of tree
     * @param target target node's data to add to new Node
     * @param child the child of target
     * @param add data of which will be add node
     * @param op if true the nickname is "ebu", if "ibn" false.
     * @return the node of root with added node
     */
    private Node<String> findChild(Node<String> localRoot, String target, String child, String add,boolean op) {

        if(localRoot == null)
            return localRoot;

        if(localRoot.data.equals(target) && hasTheChild(localRoot,child)){
            //nicknameyı sağlayan yer bulundu
            //localRoot op true ise eklicemiz kisi false ise eklicemizin babası
            ++count;
            if(op){

                if(localRoot.left == null)
                    localRoot.left = new Node<>(add);
                else
                    localRoot.left = addRight(localRoot.left,add);

            }
            else{
                if(localRoot.left.data.equals(child))
                    if(localRoot.left.left == null)
                        localRoot.left.left = new Node(add);
                    else
                        localRoot.left.left = addRight(localRoot.left.left,add);
                else
                    localRoot.left.right = findChildAndAdd(localRoot.left.right,child,add);
            }
        }
        localRoot.left =  findChild(localRoot.left,target,child,add,op);
        localRoot.right = findChild(localRoot.right,target,child,add,op);
        return localRoot;
    }
    /**
     * This method traverses the tree pre-order with using iterator and
     * prints it to console.
     */
    @Override
    public void traversePreOrder(){

        Iterator itr = this.iterator();

        while(itr.hasNext())
            System.out.printf(" %s",itr.next());

        System.out.println();

    }
    /**
     * The method finds the child of given root and add the first left empty Node.
     * The method for search the parent's child node and then add a new Node
     * to it.
     * @param lr Node of parent
     * @param child name of searching child
     * @param add name of new child
     * @return the node with added new child.
     */
    private Node<String> findChildAndAdd(Node<String> lr,String child,String add){

        if(lr.data.equals(child)){
            if(lr.left == null)
                lr.left = new Node<>(add);
            else
                lr.left = addRight(lr.left,add);

            return lr;
        }

        lr.right = findChildAndAdd(lr.right,child,add);
        return lr;

    }
    /**
     * Add's the given root's of first right null node the given string
     * @param localRoot the root of tree to insert new Node
     * @param add the new family member
     * @return given node with added a new Node
     */
    private Node<String> addRight(Node<String> localRoot,String add){

        if(localRoot.right == null){
            localRoot.right = new Node<>(add);
            return localRoot;
        }

        localRoot.right = addRight(localRoot.right,add);
        return localRoot;
    }
    /**
     * Checks the given parent has the given child or not
     * @param parent the root of parent to check
     * @param child the child of family
     * @return if the parent has the child returns true otherwise false.
     */
    private boolean hasTheChild(Node<String> parent, String child) {

        if(parent.left == null)
            return false;

        if(parent.left.data.equals(child))
            return true;

        Node<String> cur = parent.left.right;
        while(cur != null){

            if(cur.data.compareTo(child) == 0)
                return true;

            cur = cur.right;
        }
        return false;
    }
    //  *********************  Q3  **********************************
    /**
     * The methos traverses huffmantree level-order.
     * @return a String according to level-order traversing the huffman tree.
     */
    public String LevelOrderTraverse(){

        StringBuilder br = new StringBuilder();
        int h = height(this);
        for (int i=0; i<=h; i++)
            LevelOrderTraverseHelper(br,this,i);
        return br.toString();

    }

    /**
     * Traverses tree and appends the elements of tree
     * @param br StrinBuilder to add the nodes of traversed tree
     * @param tree the tree which will be traverse
     * @param level the level of tree which level will be traverse
     */
    private void LevelOrderTraverseHelper (StringBuilder br, BinaryTree tree ,int level) {
        if (tree == null)
            return;
        if (level == 1)
            br.append(tree.root.data).append(" ");
        else if (level > 1){
            LevelOrderTraverseHelper(br,tree.getLeftSubtree(), level-1);
            LevelOrderTraverseHelper(br,tree.getRightSubtree(), level-1);
        }
    }
    /**
     * To calculate heigh of tree
     * @param tree root of tree
     * @return heigh of tree
     */
    private int height(BinaryTree tree){
        if (tree == null)
            return 0;
        else{
            int lheight = height(tree.getLeftSubtree());
            int rheight = height(tree.getRightSubtree());

            if (lheight > rheight)
                return(lheight+1);
            else
                return(rheight+1);
        }
    }
}
