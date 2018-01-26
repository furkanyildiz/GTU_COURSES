package cse222_hw8;

/**
 * @param <E>
 */
public class AVLTree < E extends Comparable < E >> extends BinarySearchTreeWithRotate < E > {

    /** Flag to indicate that height of tree has increased. */
    private boolean increase;

    /** Flag to indicate that height of tree has decreased */
    private boolean decrease;

    private static class AVLNode<E> extends Node<E> {

        public static final int LEFT_HEAVY = -1;
        public static final int BALANCED = 0;
        public static final int RIGHT_HEAVY = 1;
        private int balance;

        /**
         * Constructure
         * @param item
         */
        public AVLNode(E item) {
            super(item);
            balance = BALANCED;
        }

        /**
         * Return a string representation of this object.
         * @return String representation of this object
         */
        @Override
        public String toString() {
            return balance + ": " + super.toString();
        }
    }

    /**
     * Adds given item to the tree
     * @param item which will be add to the tree
     * @return true if item added otherwise false.
     */
    @Override
    public boolean add(E item) {
        increase = false;
        if(item == null)
            return increase;
        root = add((AVLNode<E>) root, item);
        return addReturn;
    }

    /**
     * Adds given item to the tree
     * @param localRoot root
     * @param item which will be add to the tree
     * @return node with added node.
     */
    private AVLNode < E > add(AVLNode < E > localRoot, E item) {
        if (localRoot == null) {
            addReturn = true;
            increase = true;
            return new AVLNode <  > (item);
        }
        if (item.compareTo(localRoot.data) == 0) {
            // Item is already in the tree.
            increase = false;
            addReturn = false;
            return localRoot;
        }

        else if (item.compareTo(localRoot.data) < 0) {
            // item < data
            localRoot.left = add( (AVLNode < E > ) localRoot.left, item);

            if (increase) {
                decrementBalance(localRoot);
                if (localRoot.balance < AVLNode.LEFT_HEAVY) {
                    increase = false;
                    return rebalanceLeft(localRoot);
                }
            }
            return localRoot; // Rebalance not needed.
        }
        else {
            // item > data
            localRoot.right = add( (AVLNode < E > ) localRoot.right, item);
            if (increase) {
                incrementBalance(localRoot);
                if (localRoot.balance > AVLNode.RIGHT_HEAVY)
                    return rebalanceRight(localRoot);
                else
                    return localRoot;
            }
            else
                return localRoot;
        }

    }
    /**
     * Deteles the given item from the tree.
     * @param item which will be delete.
     * @return tree with deleted item.
     */
    @Override
    public E delete(E item) {
        decrease = false;
        if(item == null)
            return null;
        root = delete( (AVLNode < E > ) root, item);
        return deleteReturn;
    }


    private AVLNode < E > delete(AVLNode < E > localRoot, E item) {
        //Tree is empty or item is not found
        if (localRoot == null) {
            deleteReturn = null;
            return localRoot;
        }
        //Item is found the case like be binarySearchTree's delete method.
        if (item.compareTo(localRoot.data) == 0) {
            deleteReturn = localRoot.data;
            // item is at local root.
            if (localRoot.left == null) {
                decrease = true;
                return (AVLNode<E>) localRoot.right;
            }
            else if (localRoot.right == null) {
                decrease = true;
                return (AVLNode<E>) localRoot.left;
            }
            else {
                if (localRoot.left.right == null) {
                    localRoot.data = localRoot.left.data;
                    localRoot.left = localRoot.left.left;
                    return localRoot;
                }
                else {
                    localRoot.data = findLargestChild((AVLNode<E>) localRoot.left);
                    return localRoot;
                }
            }
        }
        //Item smallar than localRoot's data
        else if (item.compareTo(localRoot.data) < 0) {
            localRoot.left = delete( (AVLNode < E > ) localRoot.left, item);
            if (decrease) {
                incrementBalance(localRoot);
                if (localRoot.balance > AVLNode.RIGHT_HEAVY)
                    return rebalanceRightForDelete( (AVLNode < E > ) localRoot);
                else
                    return localRoot;
            }
            else
                return localRoot;
        }
        //localRoot's smallar than Item data
        else {
            localRoot.right = delete( (AVLNode < E > ) localRoot.right, item);
            if (decrease) {
                decrementBalance(localRoot);
                if (localRoot.balance < AVLNode.LEFT_HEAVY)
                    return rebalanceLeftForDelete(localRoot);
                else
                    return localRoot;
            }
            else
                return localRoot;
        }
    }
    /**
     * Find largets child node of given node. The method like
     * BinarySearchTree's findLargestChild method.
     * @param parent deleteing nodes left child.
     * @return the data of largest child
     */
    private E findLargestChild(AVLNode < E > parent) {
        if (parent.right.right == null) {
            E returnValue = parent.right.data;
            parent.right = parent.right.left;
            decrementBalance(parent);
            return returnValue;
        }
        else {
            E returnValue = findLargestChild( (AVLNode < E > ) parent.right);
            if ( ( (AVLNode < E > ) parent.right).balance < AVLNode.LEFT_HEAVY )
                parent.right = rebalanceLeft( (AVLNode < E > ) parent.right);
            //Largest child yer değiştireceğinden, yani aslında largest child
            //location'undan silineceğinden onun parentinin balanceside
            //değişiyor. Onuda dengelemeliyiz.
            if (decrease)
                decrementBalance(parent);
            return returnValue;
        }
    }
    /**
     * Increment balance of given node.
     * @param node
     */
    private void incrementBalance(AVLNode < E > node) {
        ++node.balance;
        //right heavy tree
        if (node.balance > AVLNode.BALANCED) {
            increase = true;
            decrease = false;
        }
        else {
            increase = false;
            decrease = true;
        }
    }
    /**
     * Decrement balance of given node.
     * @param node
     */
    private void decrementBalance(AVLNode < E > node) {
        --node.balance;
        //balanced status
        if (node.balance == AVLNode.BALANCED) {
            increase = false;
        }
    }
    /**
     * Puts the left side of the tree back in balance with deleting operation.
     * @param localRoot not in balanced node.
     * @return rebalanced node
     */
    private AVLNode < E > rebalanceLeftForDelete(AVLNode < E > localRoot) {
        increase = false;
        decrease = true;
        AVLNode < E > leftChild = (AVLNode < E > ) localRoot.left;
        if (leftChild.balance > AVLNode.BALANCED ) {
            AVLNode < E > leftRightChild = (AVLNode < E > ) leftChild.right;

            if (leftRightChild.balance < AVLNode.BALANCED) {
                localRoot.balance = AVLNode.BALANCED;
                leftChild.balance = AVLNode.LEFT_HEAVY;
                leftRightChild.balance = AVLNode.BALANCED;
            }
            else if (leftRightChild.balance > AVLNode.BALANCED) {
                localRoot.balance = AVLNode.RIGHT_HEAVY;
                leftChild.balance = AVLNode.BALANCED;
                leftRightChild.balance = AVLNode.BALANCED;
            }
            else {
                localRoot.balance = AVLNode.BALANCED;
                leftChild.balance = AVLNode.BALANCED;
            }
            localRoot.left = rotateLeft(leftChild);
        }
        return (AVLNode < E > ) rotateRight(localRoot);
    }
    /**
     * Puts the right side of the tree back in balance with deleting operation.
     * @param localRoot not in balanced node.
     * @return rebalanced node
     */
    private AVLNode < E > rebalanceRightForDelete(AVLNode < E > localRoot) {
        increase = false;
        decrease = true;
        AVLNode < E > rightChild = (AVLNode < E > ) localRoot.right;
        if (rightChild.balance < AVLNode.BALANCED ) {
            AVLNode < E > rightLeftChild = (AVLNode < E > ) rightChild.left;

            if (rightLeftChild.balance > AVLNode.BALANCED) {
                rightChild.balance = AVLNode.RIGHT_HEAVY;
                rightLeftChild.balance = AVLNode.BALANCED;
                localRoot.balance = AVLNode.BALANCED;
            }
            else if (rightLeftChild.balance < AVLNode.BALANCED) {
                rightChild.balance = AVLNode.BALANCED;
                rightLeftChild.balance = AVLNode.BALANCED;
                localRoot.balance = AVLNode.LEFT_HEAVY;
            }
            else {
                rightChild.balance = AVLNode.BALANCED;
                localRoot.balance = AVLNode.BALANCED;
            }
            localRoot.right = rotateRight(rightChild);
        }
        return (AVLNode < E > ) rotateLeft(localRoot);
    }
    /**
     * Puts the left side of the tree back in balance.
     * @param localRoot not in balanced node.
     * @return rebalanced node
     */
    private AVLNode < E > rebalanceLeft(AVLNode < E > localRoot) {
        AVLNode < E > leftChild = (AVLNode < E > ) localRoot.left;
        if (leftChild.balance > AVLNode.BALANCED) {
            AVLNode < E > leftRightChild = (AVLNode < E > ) leftChild.right;
            if (leftRightChild.balance < AVLNode.BALANCED) {
                leftChild.balance = AVLNode.BALANCED;
                leftRightChild.balance = AVLNode.BALANCED;
                localRoot.balance = AVLNode.RIGHT_HEAVY;
            }
            else {
                leftChild.balance = AVLNode.LEFT_HEAVY;
                leftRightChild.balance = AVLNode.BALANCED;
                localRoot.balance = AVLNode.BALANCED;
            }
            localRoot.left = rotateLeft(leftChild);
        }
        else {
            leftChild.balance = AVLNode.BALANCED;
            localRoot.balance = AVLNode.BALANCED;
        }
        return (AVLNode < E > ) rotateRight(localRoot);
    }
    /**
     * Puts the right side of the tree back in balance.
     * @param localRoot not in balanced node.
     * @return rebalanced node
     */
    private AVLNode < E > rebalanceRight(AVLNode < E > localRoot) {

        increase = false;
        decrease = true;
        AVLNode < E > rightChild = (AVLNode < E > ) localRoot.right;
        if (rightChild.balance < AVLNode.BALANCED) {
            AVLNode < E > rightLeftChild = (AVLNode < E > ) rightChild.left;

            if (rightLeftChild.balance > AVLNode.BALANCED) {
                localRoot.balance = AVLNode.LEFT_HEAVY;
                rightChild.balance = AVLNode.BALANCED;
                rightLeftChild.balance = AVLNode.BALANCED;
            }
            else if (rightLeftChild.balance < AVLNode.BALANCED) {
                localRoot.balance = AVLNode.BALANCED;
                rightChild.balance = AVLNode.RIGHT_HEAVY;
                rightLeftChild.balance = AVLNode.BALANCED;
            }
            else {
                localRoot.balance = AVLNode.BALANCED;
                rightChild.balance = AVLNode.BALANCED;
                rightLeftChild.balance = AVLNode.BALANCED;
            }
            localRoot.right = rotateRight(rightChild);
        }
        else {
            rightChild.balance = AVLNode.BALANCED;
            localRoot.balance = AVLNode.BALANCED;
        }
        return (AVLNode < E > ) rotateLeft(localRoot);

    }
}