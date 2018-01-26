/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package numeric_hw3_p3;


import java.util.Map;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author yldzf
 */
  public class MyEntry<K, V> implements Map.Entry<K, V> {
        private final K x;
        private V y;

        public MyEntry(K key, V value) {
            this.x = key;
            this.y = value;
        }

        @Override
        public K getKey() {
            return x;
        }

        @Override
        public V getValue() {
            return y;
        }

        @Override
        public V setValue(V value) {
            V old = this.y;
            this.y = value;
            return old;
        }
    }
