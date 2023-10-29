package io.github.biv2101.Standard;

public class SLLNode<E> {

    public E element;
    public SLLNode<E> succ;

    public SLLNode(E element, SLLNode<E> succ) {
        this.element = element;
        this.succ = succ;
    }


}
