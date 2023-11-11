package io.github.biv2101.Aud;

import java.util.ArrayList;
import java.util.List;


interface Drawable
{
    void draw();
}

class Circle implements Drawable
{
    @Override
    public void draw() {

    }
}

class Rectangle implements Drawable
{

    @Override
    public void draw() {

    }
}
public class BoxBox<T extends Drawable> {

    private List<T> list;

    public BoxBox() {
        list = new ArrayList<>();
    }

    public BoxBox(List<T> list) {
        this.list = list;
    }

    public void addItem(T item) {
        list.add(item);
    }

    public boolean isEmpty() {
        return list.isEmpty();
    }

    public T getItemFromBox() {
        int item = (int) (Math.random() + list.size());
        return list.get(item);
    }

    public void drawBox()
    {
        list.forEach(i -> i.draw());
        list.stream().forEach(i -> i.draw());
        list.forEach(Drawable::draw);
    }
}
